/*!
 *  @file Adafruit_INA260.h
 *
 * 	I2C Driver for INA260 Current and Power sensor
 *
 * 	This is a library for the Adafruit INA260 breakout:
 * 	http://www.adafruit.com/products
 *
 * 	Adafruit invests time and resources providing this open source code,
 *  please support Adafruit and open-source hardware by purchasing products from
 * 	Adafruit!
 *
 *
 *	BSD license (see license.txt)
 */

#ifndef _ADAFRUIT_INA260_H
#define _ADAFRUIT_INA260_H

#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>

#define INA260_I2CADDR_DEFAULT  0x40 ///< INA260 default i2c address
#define INA260_REG_CONFIG       0x00 ///< Configuration register
#define INA260_REG_CURRENT      0x01 ///< Current measurement register (signed) in mA
#define INA260_REG_BUSVOLTAGE   0x02 ///< Bus voltage measurement register in mV
#define INA260_REG_POWER        0x03 ///< Power calculation register in mW
#define INA260_REG_MASK_ENABLE  0x06 ///< Interrupt/Alert setting and checking register
#define INA260_REG_ALERT_LIMIT  0x07 ///< Alert limit value register
#define INA260_REG_MFG_UID      0xFE ///< Manufacturer ID Register
#define INA260_REG_DIE_UID      0xFF ///< Die ID and Revision Register
/* mode options */
 

#define INA260_MODE_SHUTDOWN    0x00 ///< SHUTDOWN: Minimize quiescient current and turn 
/* off current into the device inputs. Set another mode to exit shutown mode */


#define INA260_MODE_TRIGGERED   0x03 ///< TRIGGERED: Trigger a one-shot measurement of current and bus voltage
/* Set the TRIGGERED mode again to take a new measurement */


#define INA260_MODE_CONTINUOUS  0x07 ///< CONTINUOUS: (Default) Continuously update the current, 
/* bus voltage and power registers with new measurements*/

/* options for size of averaging window */
#define INA260_COUNT_1          0x01 ///< Window size: 1 sample (Default)
#define INA260_COUNT_4          0x02 ///< Window size: 4 samples
#define INA260_COUNT_16         0x03 ///< Window size: 16 samples
#define INA260_COUNT_64         0x04 ///< Window size: 64 samples
#define INA260_COUNT_128        0x05 ///< Window size: 128 samples
#define INA260_COUNT_256        0x06 ///< Window size: 256 samples
#define INA260_COUNT_512        0x07 ///< Window size: 512 samples
#define INA260_COUNT_1024       0x08 ///< Window size: 1024 samples

/* options for shunt resistor Voltage
and bus voltage measurement time */
#define INA260_TIME_140_us      0x00 ///< Measurement time: 140us
#define INA260_TIME_204_us      0x01 ///< Measurement time: 204us
#define INA260_TIME_332_us      0x02 ///< Measurement time: 332us
#define INA260_TIME_558_us      0x03 ///< Measurement time: 558us
#define INA260_TIME_1_1_ms      0x04 ///< Measurement time: 1.1ms (Default)
#define INA260_TIME_2_116_ms    0x05 ///< Measurement time: 2.116ms
#define INA260_TIME_4_156_ms    0x06 ///< Measurement time: 4.156ms
#define INA260_TIME_8_244_ms    0x07 ///< Measurement time: 8.224ms


/*!
 *    @brief  Class that stores state and functions for interacting with
 *            INA260 Current and Power Sensor
 */
class Adafruit_INA260 {
public:
  Adafruit_INA260();
  boolean begin(uint8_t i2c_addr=INA260_I2CADDR_DEFAULT, TwoWire *theWire = &Wire);
  void reset(void);
  float readCurrent(void);
  float readBusVoltage(void);
  float readPower(void);
  void setMode(uint8_t mode);
  uint8_t getMode(void);

  bool conversionReady(void);

  uint8_t getCurrentConversionTime(void);
  void setCurrentConversionTime(uint8_t time);
  uint8_t getVoltageConversionTime(void);
  void setVoltageConversionTime(uint8_t time);
  void setAveragingCount(uint8_t count);

  Adafruit_I2CRegister *Current, ///< BusIO Register for Current
                       *BusVoltage,  ///< BusIO Register for BusVoltage
                       *Power,  ///< BusIO Register for Power
                       *Config,  ///< BusIO Register for Config
                       *MaskEnable, ///< BusIO Register for MaskEnable
                       *AlertLimit; ///< BusIO Register for AlertLimit

  Adafruit_I2CRegisterBits *AveragingCount, ///< BusIO RegisterBits object for averaging count
                           *ConversionReady, ///< BusIO RegisterBits object for conversion readyness check
                           *CurrentConversionTime, ///< BusIO RegisterBits object for current conversion time
                           *VoltageConversionTime, ///< BusIO RegisterBits object for voltage conversion time
                           *Mode, ///< BusIO RegisterBits object for mode
                           *Reset; ///< BusIO RegisterBits object for reset
private:
  Adafruit_I2CDevice *i2c_dev;

};

#endif
