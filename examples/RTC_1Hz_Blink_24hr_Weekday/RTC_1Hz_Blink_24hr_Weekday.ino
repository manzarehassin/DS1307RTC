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
 * File: RTC_1Hz_Blink_24hr_Weekday.ino
 * Description: Configures the RTC to output a 1Hz blink on the SW pin and prints time in 24-hour format with weekdays.
 */

// Enable weekday and serial print; disable 12-hour conversion for 24-hour format
#define RTC_FEATURE_BLINK 1
#define RTC_FEATURE_WEEKDAYS 1
#define RTC_FEATURE_12H_TIME 0
#define RTC_FEATURE_SERIAL_PRINT 1

#include <Wire.h>
#include "DS1307RTC.h"  // DS1307 library header

DS1307RTC rtc;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  // Optionally set the RTC time here if needed:
  // rtc.setTime(21, 3, 2025, 21, 30, 0);
   rtc.sync(); // Time Sync between Software and Hardware RTC
  
  // Enable the 1Hz oscillator output on the RTC SW pin.
  rtc.setOscillator(true, rtc_osc_1hz);
  Serial.println("RTC 1Hz square wave enabled on SW pin");
}

void loop() {
  // Print current time in 24-hour format with weekday
  rtc.printTime();
  delay(1000);
}
