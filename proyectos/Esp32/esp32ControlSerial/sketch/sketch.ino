#include <Arduino.h>
#include "Button.h"
#include "Led.h"
#include "dataSerialStruct.h"
#include "AdcInterface.h"

#define INPUT_SWITCH 18
#define OUTPUT_LED_BLINK 19
#define OUTPUT_LED_SWTICH 21
#define PIN_ADC_READER 4


hw_timer_t* timer = NULL;
bool timerFlag = false;
Button button = {INPUT_SWITCH,0,false};
Led ledResponse = {OUTPUT_LED_SWTICH,false};
AdcConfigurer adcModule("READ", PIN_ADC_READER,12);

void ARDUINO_ISR_ATTR onTimer(){
  timerFlag = true;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(OUTPUT_LED_BLINK, OUTPUT);
  pinMode(OUTPUT_LED_SWTICH, OUTPUT);
  pinMode(INPUT_SWITCH, INPUT);
  Serial.begin(512000);
  adcModule.adcSetup();

      // Use 1st timer of 4 (counted from zero).
    // Set 80 divider for prescaler (see ESP32 Technical Reference Manual for more
    // info).
    timer = timerBegin(0, 80, true);        

    // Attach onTimer function to our timer.
    timerAttachInterrupt(timer, &onTimer, true);

    // Set alarm to call onTimer function every second (value in microseconds).
    // Repeat the alarm (third parameter)
    timerAlarmWrite(timer, 50000, true);

    // Start an alarm
    timerAlarmEnable(timer);


}

void loop() {
  if(timerFlag){
    DataSerialStruct data(adcModule.adcRead(),millis());
    timerFlag = false;
    Serial.println(data.toJsonString());
  }
}

void toggleLed(Button* button, Led* led){

  bool actualState = digitalRead(INPUT_SWITCH); 
  bool previousState = button->pressed; 
  
  if(previousState != actualState && actualState) {
    led->status = !led->status;
    Serial.print("cambio" + String(led->PIN) + String(led->status));
    digitalWrite(led->PIN, led->status);
  }
  button->pressed = actualState;
}

void blinkLed(){
  digitalWrite(OUTPUT_LED_BLINK, HIGH);
  delay(1000);
  digitalWrite(OUTPUT_LED_BLINK, LOW);
  delay(1000);
}
