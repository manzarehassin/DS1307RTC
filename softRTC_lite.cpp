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

Available on github : https://github.com/manzarehassin/DS1307
Published at: 21 March, 2025 9:30 PM (UTC+6).
*/



#include "softRTC_lite.h"
#include "Arduino.h"
#include <avr/pgmspace.h>

void softRTC_lite::writeSRTC(uint8_t day, uint8_t month, uint16_t year, uint8_t hour, uint8_t minute, uint8_t second)
{
  softclk.day        = day;
  softclk.month      = month;
  softclk.year       = year;
  softclk.hour       = hour;
  softclk.minute     = minute;
  softclk.second     = second;
  softclk.lastUpdate = millis();
}

void softRTC_lite::addSeconds(unsigned long secDiff)
{
  const uint8_t PROGMEM dpm[] = {31,28,31,30,31,30,31,31,30,31,30,31};
  softclk.second += secDiff; // Increment seconds and handle carry-over.
  if (softclk.second >= 60) { softclk.minute += softclk.second / 60; softclk.second = softclk.second % 60; }
  // Handle minutes to hours.
  if (softclk.minute >= 60) { softclk.hour += softclk.minute / 60; softclk.minute = softclk.minute % 60; }
  // Handle hours to days.
  if (softclk.hour >= 24) 
  {
    unsigned long extraDays = softclk.hour / 24;
    softclk.hour = softclk.hour % 24;
    softclk.day += extraDays; // Update day and adjust month/year as needed.
    while (true) 
    {
      uint8_t daysInMonth = pgm_read_byte(&dpm[softclk.month - 1]);
      if (softclk.month == 2 && isLeapYear(softclk.year)) { daysInMonth = 29; }
      if (softclk.day <= daysInMonth) break;
      softclk.day -= daysInMonth; softclk.month++;
      if (softclk.month > 12) { softclk.month = 1; softclk.year++; }
    }
  }
}

void softRTC_lite::readSRTC(uint8_t &day, uint8_t &month, uint16_t &year, uint8_t &hour, uint8_t &minute, uint8_t &second)
{
  uint32_t currentMillis = millis();
  unsigned long elapsedSec = (currentMillis - softclk.lastUpdate) / 1000UL; // Determine how many whole seconds have passed since the last update.
  if (elapsedSec > 0) 
  {
    addSeconds(elapsedSec); // Increment the time by the elapsed seconds.
    softclk.lastUpdate += elapsedSec * 1000UL; // Update lastUpdate to account for the processed whole seconds.
  }
  // Return the current time.
  day    = softclk.day;
  month  = softclk.month;
  year   = softclk.year;
  hour   = softclk.hour;
  minute = softclk.minute;
  second = softclk.second;
}