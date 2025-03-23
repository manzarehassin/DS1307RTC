/*
MIT License

Copyright (c) 2025 Manzar-E-Hassin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Available on github : https://github.com/manzarehassin/DS1307RTC
Published at: 21 March, 2025 9:30 PM (UTC+6).
*/


/*
 * File: NVRAM_ReadWrite.ino
 * Description: Writes to and reads from the DS1307's NVRAM.
 */

// Enable NVRAM and serial print features
#define RTC_FEATURE_RAM 1
#define RTC_FEATURE_SERIAL_PRINT 1

#include <Wire.h>
#include "DS1307RTC.h"  // DS1307 library header

DS1307RTC rtc;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  // Write example data (0x55) to NVRAM address 0 (offset from RTC internal RAM start)
  uint8_t dataToWrite = 0x55;  
  rtc.writeRam(0, dataToWrite);
  Serial.print("Written to NVRAM address 0: 0x");
  Serial.println(dataToWrite, HEX);
  
  // Read the data back from NVRAM address 0
  uint8_t dataRead = rtc.readRam(0);
  Serial.print("Read from NVRAM address 0: 0x");
  Serial.println(dataRead, HEX);
}

void loop() {
  // No repeated action needed.
}
