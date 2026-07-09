#include <Arduino.h>

#define BTN_PIN 8
#define LED_PIN 4
#define BAUDRATE 115200
#define POOLING 10
#define DEBOUNCE 50

volatile bool ledState     = false;
volatile uint32_t isrCount = 0; 
volatile bool flagISR = false;
uint32_t poolingTimer = 0;
uint32_t stateTimer = 0;
uint32_t releaseTimer = 0;
// void IRAM_ATTR BtnClick(){
//     flagISR = true;
 
// }
enum buttonState{
  IDLE,
  WAIT_PRESS,
  PRESSED,
  WAIT_RELEASE
};

buttonState currentState = IDLE;
void setup() {
Serial.begin(BAUDRATE);
pinMode(BTN_PIN, INPUT_PULLUP);
 pinMode(LED_PIN, OUTPUT); 
// attachInterrupt(digitalPinToInterrupt(BTN_PIN), BtnClick, FALLING);
}

void loop() {
  
  uint32_t now = millis();
    if(now - poolingTimer >= POOLING){
       Serial.println(currentState);
      switch(currentState){
        
        case IDLE:
          
          if(digitalRead(BTN_PIN) == LOW){
            currentState = WAIT_PRESS;
            stateTimer = now;
          }

        break;
        case WAIT_PRESS:
          
          if(now - stateTimer >= DEBOUNCE){
            stateTimer = now;
            if(digitalRead(BTN_PIN) == LOW){
            ledState = !ledState; 
            currentState = PRESSED;
          }
           
          }
        break;
        case PRESSED:
          if(digitalRead(BTN_PIN) == LOW){
              digitalWrite(LED_PIN, ledState);
            }

          else{
            currentState = WAIT_RELEASE;
          }

        break;
        case WAIT_RELEASE:
          if(digitalRead(BTN_PIN) == HIGH){
            currentState = IDLE;
          }
        break;
      }
      
    }
}

