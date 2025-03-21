# DS1307 Real Time Clock Library

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

This Arduino library provides an interface for the DS1307 Real Time Clock (RTC) module. It supports both hardware I2C communication with the DS1307 and a software-based RTC (softRTC_lite) for maintaining time between hardware updates.

## Features

- **Time Setting:** Easily set the RTC time.
- **12‑Hour and 24‑Hour Formats:** Retrieve and print time in both formats.
- **Weekday Support:** Calculate and display weekdays (e.g., Sun, Mon, Tue, etc.).
- **Square Wave Output:** Configure the DS1307 to output a 1Hz (or selectable frequencies) square wave on the SW pin.
- **NVRAM Access:** Read from and write to the DS1307 onboard RAM (56 bytes).

## 2. Initialize and Set Time

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
  rtc.sync(); // Sync time between software and hardware rtc.
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
#define RTC_FEATURE_BLINK 1
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
  rtc.sync(); //synchronize time
  // Enable 1Hz square wave on the SW pin.
  rtc.setOscillator(true, rtc_osc_1hz);
  Serial.println("RTC 1Hz square wave enabled on SW pin");
}

void loop() {
  rtc.printTime();
  delay(1000);
}
```

### NVRAM Read/Write

Write to and read from the DS1307's onboard NVRAM:

```cpp
#define RTC_FEATURE_RAM 1
#define RTC_FEATURE_SERIAL_PRINT 1

#include <Wire.h>
#include <DS1307.h>

DS1307 rtc;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  // Write a byte (0x55) to NVRAM address 0.
  rtc.writeRam(0, 0x55);
  Serial.print("Written to NVRAM address 0: 0x");
  Serial.println(0x55, HEX);
  
  // Read the byte back.
  uint8_t data = rtc.readRam(0);
  Serial.print("Read from NVRAM address 0: 0x");
  Serial.println(data, HEX);
}

void loop() {
  // No repeated action needed.
}
```

## Library Configuration

The library supports several preprocessor directives to enable or disable specific features. Define these **before** including the library header:

- `RTC_FEATURE_WEEKDAYS` – Enable weekday functionality.
- `RTC_FEATURE_12H_TIME` – Enable 12‑hour time format.
- `RTC_FEATURE_SERIAL_PRINT` – Enable serial time printing.
- `RTC_FEATURE_RAM` – Enable NVRAM (RAM) read/write functions.
- `RTC_FEATURE_BLINK` – Enable square wave output functionality.

## Installation

You can install this library using the Arduino Library Manager by searching for "DS1307" or by cloning the repository:

```bash
git clone https://github.com/manzarehassin/DS1307.git
```

## Compatibility

- **Architectures:** AVR, ESP8266, SAM, MegaAVR (see `library.properties` for complete details)
- **Dependencies:** Arduino core, Wire library.

## License

This library is distributed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Repository

For the latest updates and more detailed documentation, visit the [DS1307 GitHub Repository](https://github.com/manzarehassin/DS1307).

Published on: 21 March, 2025 9:30 PM (UTC+6)  
Author: Manzar E Hassin <mnz247@hotmail.com>
