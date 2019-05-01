// Requires Streaming.h from http://arduiniana.org/libraries/streaming/

#pragma once

#include <Streaming.h>

#define streamProgStr(myPgmString) (reinterpret_cast<const __FlashStringHelper *>(myPgmString))
#define _hexByte(myByte)     ((((uint8_t) (myByte)) & 0xF0) ?  F("") : F("0")) << _HEX(((uint8_t) (myByte)))
#define _hexWord(myWord)     _hexByte(((((uint16_t) (myWord)) & 0xFF00) >> 8)) << _hexByte((((uint16_t) (myWord)) & 0x00FF))
#define _hexLong(myLong)     _hexWord(((((uint32_t) (myLong)) & 0xFFFF0000) >> 16)) << _hexWord((((uint32_t) (myLong)) & 0x0000FFFF))
#define _binaryByte(myByte)  ((((uint8_t) (myByte)) & 0x80) ? F("1") : F("0")) \
                          << ((((uint8_t) (myByte)) & 0x40) ? F("1") : F("0")) \
                          << ((((uint8_t) (myByte)) & 0x20) ? F("1") : F("0")) \
                          << ((((uint8_t) (myByte)) & 0x10) ? F("1") : F("0")) \
                          << ((((uint8_t) (myByte)) & 0x08) ? F("1") : F("0")) \
                          << ((((uint8_t) (myByte)) & 0x04) ? F("1") : F("0")) \
                          << ((((uint8_t) (myByte)) & 0x02) ? F("1") : F("0")) \
                          << ((((uint8_t) (myByte)) & 0x01) ? F("1") : F("0"))
#define _binaryFlag(myByte)  ((((uint8_t) (myByte)) & 0x80) ? F("@") : F(".")) \
                          << ((((uint8_t) (myByte)) & 0x40) ? F("@") : F(".")) \
                          << ((((uint8_t) (myByte)) & 0x20) ? F("@") : F(".")) \
                          << ((((uint8_t) (myByte)) & 0x10) ? F("@") : F(".")) \
                          << ((((uint8_t) (myByte)) & 0x08) ? F("@") : F(".")) \
                          << ((((uint8_t) (myByte)) & 0x04) ? F("@") : F(".")) \
                          << ((((uint8_t) (myByte)) & 0x02) ? F("@") : F(".")) \
                          << ((((uint8_t) (myByte)) & 0x01) ? F("@") : F("."))
