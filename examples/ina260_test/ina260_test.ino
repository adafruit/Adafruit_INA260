#include <Adafruit_INA260.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

Adafruit_INA260 ina260 = Adafruit_INA260();

void setup() {
  while (!Serial) { delay(10); }
  Serial.begin(115200);
  Serial.println("Adafruit INA260 Test");
  ina260.begin();
}

void loop() {
  Serial.print("Current: ");
  Serial.println(ina260.readCurrent());
  Serial.print("Bus Voltage: ");
  Serial.println(ina260.readBusVoltage());
  Serial.print("Power: ");
  Serial.println(ina260.readCurrent());
  Serial.println();
  delay(1000);
}
