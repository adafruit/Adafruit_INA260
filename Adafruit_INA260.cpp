/*!
 *  @file Adafruit_INA260.cpp
 *
 *  @mainpage Adafruit INA260 I2C Current and Power sensor
 *
 *  @section intro_sec Introduction
 *
 * 	I2C Driver for the INA260 I2C Current and Power sensor
 *
 * 	This is a library for the Adafruit INA260 breakout:
 * 	http://www.adafruit.com/products
 *
 * 	Adafruit invests time and resources providing this open source code,
 *  please support Adafruit and open-source hardware by purchasing products from
 * 	Adafruit!
 *
 *  @section dependencies Dependencies
 *
 *  This library depends on the Adafruit BusIO library
 *
 *  @section author Author
 *
 *  Bryan Siepert for Adafruit Industries
 *
 * 	@section license License
 *
 * 	BSD (see license.txt)
 *
 * 	@section  HISTORY
 *
 *     v1.0 - First release
 */

#include "Arduino.h"
#include <Wire.h>

#include "Adafruit_INA260.h"

/*!
 *    @brief  Instantiates a new INA260 class
 */
Adafruit_INA260::Adafruit_INA260(void) {}

/*!
 *    @brief  Sets up the HW
 *    @param  theWire
 *    @return True if initialization was successful, otherwise false.
 */
boolean Adafruit_INA260::begin(TwoWire *theWire) {
  i2c_dev = new Adafruit_I2CDevice(INA260_I2CADDR_DEFAULT);

  if (!i2c_dev->begin()) {
    return false;
  }

    Current = new Adafruit_I2CRegister(i2c_dev, INA260_REG_CURRENT, 2, MSBFIRST);
    BusVoltage = new Adafruit_I2CRegister(i2c_dev, INA260_REG_BUSVOLTAGE, 2, MSBFIRST);
    Power = new Adafruit_I2CRegister(i2c_dev, INA260_REG_POWER, 2, MSBFIRST);
    Config = new Adafruit_I2CRegister(i2c_dev, INA260_REG_CONFIG, 2, MSBFIRST);
    MaskEnable = new Adafruit_I2CRegister(i2c_dev, INA260_REG_MASK_ENABLE, 2, MSBFIRST);
    AlertLimit = new Adafruit_I2CRegister(i2c_dev, INA260_REG_ALERT_LIMIT, 2, MSBFIRST);
    

    AveragingCount = new Adafruit_I2CRegisterBits(Config, 3, 9); 
    ConversionReady = new Adafruit_I2CRegisterBits(MaskEnable, 1, 3);
    CurrentConversionTime = new Adafruit_I2CRegisterBits(Config, 3, 3);
    VoltageConversionTime = new Adafruit_I2CRegisterBits(Config, 3, 6);
    Mode = new Adafruit_I2CRegisterBits(Config, 3, 0);
    Reset = new Adafruit_I2CRegisterBits(Config, 1, 15);
    reset();
  return true;
}
/**************************************************************************/
/*!
    @brief  Resets the harware. By setting the MSB of the config register,
    all registers are set to default values, the same as a power-on reset.
*/
/**************************************************************************/
void Adafruit_INA260::reset(void){
  Reset->write(1);
}
/**************************************************************************/
/*!
    @brief Reads and scales the current value of the Current register.
    @return The current current measurement in mA
*/
/**************************************************************************/
float Adafruit_INA260::readCurrent(void) {
  return (int16_t)Current->read() * 1.25;
}
/**************************************************************************/
/*!
    @brief Reads and scales the current value of the Bus Voltage register.
    @return The current bus voltage measurement in mV
*/
/**************************************************************************/
float Adafruit_INA260::readBusVoltage(void) {
  return BusVoltage->read() * 1.25;
}
/**************************************************************************/
/*!
    @brief Reads and scales the current value of the Power register.
    @return The current Power calculation in mW
*/
/**************************************************************************/
float Adafruit_INA260::readPower(void) {
  return Power->read() * 10;
}
/**************************************************************************/
/*!
    @brief Returns the current mode
    @return The current Power calculation in mW
*/
/**************************************************************************/
uint8_t Adafruit_INA260::getMode(void) {
  return Mode->read();
}
/**************************************************************************/
/*!
    @brief Returns the current mode
    @param mode
           The new mode to be set
*/
/**************************************************************************/
void Adafruit_INA260::setMode(uint8_t mode) {
  Mode->write(mode);
}
/**************************************************************************/
/*!
    @brief Set the number of averaging samples
    @param count
           The number of samples to be averaged
*/
/**************************************************************************/
void Adafruit_INA260::setAveragingCount(uint8_t count){
  AveragingCount->write(count);
}
/**************************************************************************/
/*!
    @brief Read the current current conversion time register
    @return The current current conversion time
*/
/**************************************************************************/
uint8_t Adafruit_INA260::getCurrentConversionTime(void){
  return CurrentConversionTime->read();
}
/**************************************************************************/
/*!
    @brief Set the current conversion time
    @param time
           The new current conversion time
*/
/**************************************************************************/
void Adafruit_INA260::setCurrentConversionTime(uint8_t time){
  CurrentConversionTime->write(time);
}
/**************************************************************************/
/*!
    @brief Read the current bus voltage conversion time register
    @return The current bus voltage conversion time
*/
/**************************************************************************/
uint8_t Adafruit_INA260::getVoltageConversionTime(void){
  return VoltageConversionTime->read();
}
/**************************************************************************/
/*!
    @brief Set the bus voltage conversion time
    @param time
           The new bus voltage conversion time
*/
/**************************************************************************/
void Adafruit_INA260::setVoltageConversionTime(uint8_t time){
  VoltageConversionTime->write(time);
}

/**************************************************************************/
/*!
    @brief check if the most recent one shot measurement has completed
    @return true if the conversion has completed
*/
/**************************************************************************/
bool Adafruit_INA260::conversionReady(void){
  return ConversionReady->read();
}
