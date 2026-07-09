#include <Arduino.h>

#define BTN_PIN 8
#define LED_PIN 4
#define BAUDRATE 115200
#define DEBOUNCE 200

volatile bool ledState     = false;
volatile uint32_t isrCount = 0; 
volatile bool flagISR = false;
uint32_t debounceTimer = 0;
void IRAM_ATTR BtnClick(){
    flagISR = true;
 
}
void setup() {
Serial.begin(BAUDRATE);
pinMode(BTN_PIN, INPUT_PULLUP);
pinMode(LED_PIN, OUTPUT); 
attachInterrupt(digitalPinToInterrupt(BTN_PIN), BtnClick, FALLING);
}

void loop() {
  
    if(flagISR){
      flagISR = false;
      uint32_t now = millis();
      if(now - debounceTimer >= DEBOUNCE){

      isrCount++;
      debounceTimer = now;
      ledState = !ledState;
       digitalWrite(LED_PIN, ledState);
      Serial.println(isrCount);
    }
    }
    
  
 
}

