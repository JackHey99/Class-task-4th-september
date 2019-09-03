#include <Arduino.h>

int32_t pot_value = 0;
uint8_t pot_pin = 15;
float pot_voltage = 0;
uint8_t input_pin = 10;
float input_voltage = 0;
bool pin_state_changed = 0;

void ISR_voltage_trigger();

//unit test
void setup()
{
  Serial.begin(115200);  
  pinMode(input_pin, INPUT);
  pinMode(pot_pin, INPUT);
  attachInterrupt(input_pin, ISR_voltage_trigger, CHANGE);
}

void loop()
{
  if(digitalRead(input_pin) == LOW){
    input_voltage = 0;
  }
  else
  {
    input_voltage = 3.3;
  }
  
  if (pin_state_changed)
  {
    Serial.print(pot_voltage);
    Serial.print(",");
    pin_state_changed = 0;
  }
  else
  {

    Serial.print(0);
    Serial.print(",");
  }
  
  

  pot_value = analogRead(pot_pin);
  pot_voltage = (pot_value * 3.3 / 1023);
  Serial.print(pot_voltage);
  Serial.print(",");
  Serial.println(input_voltage);
  delay(1);
  Serial.flush();
 }


 void ISR_voltage_trigger(){
   pin_state_changed = true;
 }
