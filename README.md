# DS1307 Real Time Clock Library

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

This Arduino library provides an interface for the DS1307 Real Time Clock (RTC) module. It supports both hardware I2C communication with the DS1307 and a software-based RTC (softRTC_lite) for maintaining time between hardware updates.

## Features

- **Time Setting:** Easily set the RTC time.
- **12‑Hour and 24‑Hour Formats:** Retrieve and print time in both formats.
- **Weekday Support:** Calculate and display weekdays (e.g. Sun, Mon, Tue, etc.).
- **Square Wave Output:** Configure the DS1307 to output a 1Hz (or other selectable frequencies) square wave on the SW pin.
- **NVRAM Access:** Read from and write to the DS1307 onboard RAM (56 bytes).

## Usage

1. **Include the Library**

   Include the DS1307 header in your sketch:

   ```cpp
   #include <DS1307.h>
   ```
2. **Initialize and Set Time**

Instantiate the DS1307 class, initialize the I2C communication, and set the RTC time. For example:

```cpp
#define RTC_FEATURE_WEEKDAYS 1
#define RTC_FEATURE_12H_TIME 1
#define RTC_FEATURE_SERIAL_PRINT 1

#include <Wire.h>
#include <DS1307.h>

DS1307 rtc;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  // Set RTC time: day, month, year, hour, minute, second.
  rtc.setTime(21, 3, 2025, 21, 30, 0);
  delay(1000); // Allow RTC to update
  Serial.println("RTC time set to 21-03-2025 09:30:00 PM");
}

void loop() {
  // Print current time in 12-hour format with weekday
  rtc.printTime();
  delay(1000);
}
```

## Advanced Features

### Square Wave Output (1Hz Blink)

Configure the RTC to output a 1Hz square wave on its SW pin and display time in 24‑hour format with weekday support:

```cpp
#define RTC_FEATURE_WEEKDAYS 1
#define RTC_FEATURE_12H_TIME 0
#define RTC_FEATURE_SERIAL_PRINT 1

#include <Wire.h>
#include <DS1307.h>

DS1307 rtc;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  // Optionally set the RTC time here
  // rtc.setTime(21, 3, 2025, 21, 30, 0);
  
  // Enable 1Hz square wave on the SW pin.
  rtc.setOscillator(true, rtc_osc_1hz);
  Serial.println("RTC 1Hz square wave enabled on SW pin");
}

void loop() {
  rtc.printTime();
  delay(1000);
}
```
