#include <Arduino.h>
#include <EEPROM.h>
#include <Streaming.h>
#include "StreamingExtras.h"
#include <Wire.h>

#include "eepromData.h"

#define DEVICE_ADDRESS    0x50 //Address of 24LC256 eeprom chip
#define EEPROM_SIZE    65536/8

uint8_t i2c_eeprom_read_byte(uint8_t deviceaddress, size_t eeaddress) {
  uint8_t rdata = 0xFF;
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8)); // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();
  Wire.requestFrom(deviceaddress, 1U);
  if (Wire.available()) rdata = Wire.read();
  delay(2) ;
  return rdata;
}

void i2c_eeprom_write_byte(uint8_t deviceaddress, size_t eeaddress, uint8_t data) {
  int rdata = data;
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8)); // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.write(rdata);
  Wire.endTransmission();
  delay(6) ;
}

void i2c_eeprom_update_byte(uint8_t deviceaddress, size_t eeaddress, uint8_t data) {
    uint8_t current = i2c_eeprom_read_byte(deviceaddress, eeaddress) ;
    if (current != data) i2c_eeprom_write_byte(deviceaddress, eeaddress, data) ;
}

void writeOnboardEEPROM() {
    size_t maxAddress = EEPROM.length() ;
    for (size_t addr = 0 ; addr < maxAddress ; addr++) {
        uint8_t modulus = addr % 128 ;
        if (modulus == 0)   Serial << _hexWord(addr) << F(" : ") ;
        EEPROM.update(addr, pgm_read_byte(&onboard[addr])) ;
        Serial << F(".") ;
        if (modulus == 127) Serial << endl ;
    }
    Serial << F("done") << endl ;
}

void dumpOnboardEEPROM() {
    size_t  theAddress = 0 ;
    size_t  maxAddress = EEPROM.length() ;
    uint8_t theValue ;
    char    asciiDump[17] ;

    Serial << endl ;
    Serial << F("uint8_t const onboard[] PROGMEM = {") << endl ;
    while (true) {
        size_t commentAddress = theAddress ;
        Serial << F("    ") ;

        asciiDump[16]   = 0 ;
        for (uint8_t ii = 0 ; ii < 16 ; ii++) {
            theValue  = EEPROM.read(theAddress) ;
            Serial << F("0x") << _hexByte(theValue) << F(", ") ;

            if ((theValue >= 0x20) && (theValue < 0x7f))
                asciiDump[ii /*% 16*/]  = theValue ;
            else
                asciiDump[ii /*% 16*/]  = '.' ;

            theAddress++ ;
            if (theAddress >= maxAddress) {
                asciiDump[ii + 1] = 0 ;
                for (uint8_t jj = ii ; jj < 15 ; jj++) Serial << F("   ") ;
                break ;
            }
        }
        Serial << F(" // ") << _hexWord(commentAddress) << F(" : ") << asciiDump << endl ;
        if (theAddress >= maxAddress) break ;
    }
    Serial << F("} ;") << endl ;
}

void writeExternalEEPROM() {
    size_t maxAddress = EEPROM_SIZE ;
    for (size_t addr = 0 ; addr < maxAddress ; addr++) {
        uint8_t modulus = addr % 128 ;
        if (modulus == 0)   Serial << _hexWord(addr) << F(" : ") ;
        i2c_eeprom_update_byte(DEVICE_ADDRESS, addr, pgm_read_byte(&external[addr])) ;
        Serial << F(".") ;
        if (modulus == 127) Serial << endl ;
    }
    Serial << F("done") << endl ;
}

void dumpExternalEEPROM() {
    size_t  theAddress = 0 ;
    size_t  maxAddress = EEPROM_SIZE ;
    uint8_t theValue ;
    char    asciiDump[17] ;

    Serial << endl ;
    Serial << F("uint8_t const external[] PROGMEM = {") << endl ;
    while (true) {
        size_t commentAddress = theAddress ;
        Serial << F("    ") ;

        asciiDump[16]   = 0 ;
        for (uint8_t ii = 0 ; ii < 16 ; ii++) {
            theValue  = i2c_eeprom_read_byte(DEVICE_ADDRESS, theAddress) ;
            Serial << F("0x") << _hexByte(theValue) << F(", ") ;

            if ((theValue >= 0x20) && (theValue < 0x7f))
                asciiDump[ii /*% 16*/]  = theValue ;
            else
                asciiDump[ii /*% 16*/]  = '.' ;

            theAddress++ ;
            if (theAddress >= maxAddress) {
                asciiDump[ii + 1] = 0 ;
                for (uint8_t jj = ii ; jj < 15 ; jj++) Serial << F("   ") ;
                break ;
            }
        }
        Serial << F(" // ") << _hexWord(commentAddress) << F(" : ") << asciiDump << endl ;
        if (theAddress >= maxAddress) break ;
    }
    Serial << F("} ;") << endl ;
}

void setup() {
    int charRead = -1 ;

    Wire.begin(); // initialise the connection
    Serial.begin(57600) ;
    delay(250) ;
    Serial << endl ;
    Serial << F("Y to write to onboard EEPROM: ") ;
    while(charRead <  0) charRead = Serial.read() ;
    Serial << endl ;
    if (charRead == 'Y') writeOnboardEEPROM() ;
    delay(500) ;
    while(charRead >= 0) charRead = Serial.read() ; ; // flush in case they included line endings

    Serial << F("Make sure I2C switch is in the Ar and not the Pi position.") << endl ;
    Serial << F("Y to write to I2C EEPROM: ") ;
    while(charRead <  0) charRead = Serial.read() ;
    Serial << endl ;
    if (charRead == 'Y') writeExternalEEPROM() ;
    delay(500) ;
    while(charRead >= 0) charRead = Serial.read() ; ; // flush in case they included line endings

    Serial << endl << F("--------------------------------") << endl << endl ;

    Serial << F("Copy and paste the following into eepromData.h, then recompile") << endl << endl ;
    dumpOnboardEEPROM() ;
    dumpExternalEEPROM() ;
}

void loop() {
    while(1) {}
}
