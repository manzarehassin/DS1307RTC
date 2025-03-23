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

Available on github : https://github.com/manzarehassin/tinyRTCds1307
Published at: 21 March, 2025 9:30 PM (UTC+6).
*/

/*
 * File: TimeSet_12hr_Weekday.ino
 * Description: Sets the RTC time and prints it in 12-hour format with weekdays.
 */

// Enable weekday and 12-hour features along with serial print
#define RTC_FEATURE_WEEKDAYS 1
#define RTC_FEATURE_12H_TIME 1
#define RTC_FEATURE_SERIAL_PRINT 1

#include <Wire.h>
#include "tinyRTCds1307.h"  // tinyRTCds1307 library header

tinyRTCds1307 rtc;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  // Set RTC time: Date: 21-03-2025, Time: 21:30:00 (24h value; 12h will show 9:30 PM)
  rtc.setTime(21, 3, 2025, 21, 30, 0);
  rtc.sync(); // Time sync between Software and Hardware RTC.
  Serial.println("RTC time set to 21-03-2025 09:30:00 PM");
}

void loop() {
  // Print current time in 12-hour format with weekday
  rtc.printTime();
  delay(1000);
}
