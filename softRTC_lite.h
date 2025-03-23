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


#ifndef soft_rtc_lite_h
#define soft_rtc_lite_h
#include "Arduino.h"
#include <avr/pgmspace.h>

class softRTC_lite
{
  private:

    inline bool isLeapYear(uint16_t year) { return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0); }
    void addSeconds(unsigned long secDiff);
    
  protected:
    void writeSRTC(uint8_t day, uint8_t month, uint16_t year, uint8_t hour, uint8_t minute, uint8_t second);
    void readSRTC(uint8_t &day, uint8_t &month, uint16_t &year, uint8_t &hour, uint8_t &minute, uint8_t &second);
	
    struct __attribute__((packed)) clockTimeStorage
    {
      uint8_t day    : 5;  // 1-31
      uint8_t month  : 4;  // 1-12
      uint16_t year  : 12; // 0-2099
      uint8_t hour   : 5;  // 00-23
      uint8_t minute : 6;  // 00-59
      uint8_t second : 6;  // 00-59
      uint32_t lastUpdate; // Timestamp (millis) of the last update
    } softclk;
};
#endif // soft_rtc_lite_h
