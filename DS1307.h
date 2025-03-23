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



#ifndef ds1307_h
#define ds1307_h
#include "Arduino.h"
#include <avr/pgmspace.h>
#include "softRTC_lite.h"
#include <Wire.h> 

class DS1307 : private softRTC_lite
{

// PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE
// PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE

  private:

    #define RTC_DEVICE_ID 0x68

    inline void bcd2bin (uint8_t & val) { val = val - 6 * (val >> 4); }
    inline void bin2bcd (uint8_t & val) { val = val + 6 * (val / 10); }
    void readRTC(uint8_t &day, uint8_t& month, uint16_t& year, uint8_t& hour, uint8_t& minute, uint8_t& second)
    {
      Wire.beginTransmission(RTC_DEVICE_ID);
      Wire.write(0x00);	// This is the first register address (Seconds)
      Wire.endTransmission();
      Wire.requestFrom(RTC_DEVICE_ID, 7); // Read 7 bytes: sec, min, hour,week, day, month, year.
      second = Wire.read() & 0x7F; //Second  (Range: 0-59)
      bcd2bin(second);
      minute = Wire.read() & 0x7F; //Minute (Range: 0-59)
      bcd2bin(minute);
      hour = Wire.read() & 0x3F; //Hour (Range: 0-23)
      bcd2bin(hour);
      uint8_t buffer1 = Wire.read(); // day of Week, (Range: 1-7) 1= sunday
      day = Wire.read() & 0x3F; // Date (Range: 1-31)
      bcd2bin(day);
      month = Wire.read() & 0x1F; // Month (Range: 1-12)
      bcd2bin(month);
      buffer1 = Wire.read(); //Year (Range: 00-99)
      bcd2bin(buffer1); // short year as 24
      year = 20 * 100 + buffer1; // full year as 2024
    }

    void writeRTC(uint8_t day, uint8_t month, uint16_t year, uint8_t hour, uint8_t minute, uint8_t second)
    {
      Wire.beginTransmission(RTC_DEVICE_ID);
      Wire.write(0x00); // Start address of data
      // Second ============================
      bin2bcd(second);
      Wire.write(second); //Second
      // Minute ============================
      bin2bcd(minute);
      Wire.write(minute); //Minute
      // Hour ==============================
      bin2bcd(hour);
      Wire.write(hour); //Hour (24 HRS)
      // Week day ==========================
      #if (RTC_FEATURE_WEEKDAYS) && (RTC_FEATURE_WEEKDAYS == 1)
        second = getWeekdayIndex(day, month, year); // buffer to store weekday index
      #else
        second=0;
      #endif
      bin2bcd(second);
      Wire.write(second); //Week
      // Day/ Date =========================
      bin2bcd(day);
      Wire.write(day); //Day
      // Month =============================
      bin2bcd(month);
      Wire.write(month); //Month
      // Year =============================
      second = year % 100;
      bin2bcd(second); //short year
      Wire.write(second); //Short Year
      Wire.endTransmission();
    }

//Weekday access ---------------------------------------------------------------------------
  #if (RTC_FEATURE_WEEKDAYS == 1)
    uint8_t getWeekdayIndex(uint8_t day, uint8_t month, uint16_t year)
    {
      int y0 = year - (month < 3); int x = y0 + y0/4 - y0/100 + y0/400;
      int m0 = month + 12 * (month < 3) - 2;
      return (day + x + m0*31/12) % 7 + 1;
    }

    String getWeekNames(uint8_t val)
    {
      switch(val)
      {
        case 1: return F("Sun"); 
        case 2: return F("Mon");
        case 3: return F("Tue");
        case 4: return F("Wed");
        case 5: return F("Thu");
        case 6: return F("Fri");
        case 7: return F("Sat");
      };
    }
  #endif
//---------------------------------------------------------------------------------------------

// Special register access via i2c -------------------------------------------------------------------------------------------------------------------------------------------------------------
  #if  ((RTC_FEATURE_RAM == 1) || (RTC_FEATURE_EEPROM == 1) || (RTC_FEATURE_BLINK==1))
    void rtcReadByte(uint8_t _address, uint8_t & _data)
    {
      Wire.beginTransmission(RTC_DEVICE_ID);
	  Wire.write(_address);
	  Wire.endTransmission();
      Wire.requestFrom(RTC_DEVICE_ID, 1);
	  _data = Wire.read();
    }

    void rtcWriteByte(uint8_t _address, uint8_t _data)
    {
      Wire.beginTransmission(RTC_DEVICE_ID);
	  Wire.write(_address);
	  Wire.write(_data);	
	  Wire.endTransmission();
    }
  #endif
//------------------------------------------------------------------------------------------

// PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC 
// PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC 

  public:

// Generic public functions ====================================================================================
    void setTime(uint8_t day, uint8_t month, uint16_t year, uint8_t hour, uint8_t minute, uint8_t second)
    {
      writeRTC(day, month, year, hour, minute, second);  //HW
      writeSRTC(day, month, year, hour, minute, second); //SW
    }

    void sync()
    {
      uint8_t day, month, hour, minute, second; uint16_t year;
      readRTC(day, month, year, hour, minute, second);   //HW
      writeSRTC(day, month, year, hour, minute, second); //SW
    }
//-----------------------------------------------------------------------------------------------------------------

// Weekday access ---------------------------------------------------------------
  #if (RTC_FEATURE_WEEKDAYS == 1)
    String Weekday()
    {
      //return getWeekNames(getWeekdayIndex(softclk.day, softclk.month, softclk.year));
    }
  #endif
//-------------------------------------------------------------------------------

// 24h time with weekdays ---------------------------------------------------------------------
  #if defined(RTC_FEATURE_WEEKDAYS) && (RTC_FEATURE_WEEKDAYS == 1)
    void getTime24h(uint8_t &day, uint8_t& month, uint16_t& year, uint8_t& hour, uint8_t& minute, uint8_t& second, uint8_t& week)
    {
      readSRTC(day, month, year, hour, minute, second);
      week = getWeekdayIndex(day, month, year); // buffer to store weekday index
    }
  #else if (RTC_FEATURE_WEEKDAYS) && (RTC_FEATURE_WEEKDAYS == 0)
    void getTime24h(uint8_t &day, uint8_t& month, uint16_t& year, uint8_t& hour, uint8_t& minute, uint8_t& second)
    {
      readSRTC(day, month, year, hour, minute, second);
    }
  #endif
//------------------------------------------------------------------------------

// 12h time with weekdays ---------------------------------------------------------------------
  #if defined(RTC_FEATURE_12H_TIME) && defined(RTC_FEATURE_WEEKDAYS) && (RTC_FEATURE_12H_TIME == 1) && (RTC_FEATURE_WEEKDAYS == 1)
    void getTime12h(uint8_t &day, uint8_t& month, uint16_t& year, uint8_t& hour, uint8_t& minute, uint8_t& second, bool& isPM, uint8_t& week)
    {
      readSRTC(day, month, year, hour, minute, second);
      week = getWeekdayIndex(day, month, year); // buffer to store weekday index
      isPM = (hour >= 12); hour = hour % 12; if (hour == 0) hour = 12; //12h conversion
    }
  #endif
//------------------------------------------------------------------------------

// 12h time with no weekdays ---------------------------------------------------------------------
  #if defined(RTC_FEATURE_12H_TIME) && (RTC_FEATURE_12H_TIME == 1)
    void getTime12h(uint8_t &day, uint8_t& month, uint16_t& year, uint8_t& hour, uint8_t& minute, uint8_t& second, bool& isPM)
    {
      readSRTC(day, month, year, hour, minute, second);
      isPM = (hour >= 12); hour = hour % 12; if (hour == 0) hour = 12; //12h conversion
    }
  #endif
//------------------------------------------------------------------------------

// Serial print ----------------------------------------------------------------------------------------------------------
  #if RTC_FEATURE_SERIAL_PRINT == 1

    inline String leadingZero(uint8_t value)
    {
      if(value>=10) { return String(value); } 
      return String(F("0")) + String(value);
    }

    void printTime()
    {
      uint8_t day, month, hour, minute, second; uint16_t year;
      readSRTC(day, month, year, hour, minute, second);
      Serial.print(day);Serial.print(F("-"));
      Serial.print(month);Serial.print(F("-"));
      Serial.print(year);Serial.print(F(" "));
      #if(RTC_FEATURE_12H_TIME == 1)
        bool isPM = (hour >= 12);hour = hour % 12; if (hour == 0) {hour = 12;} //12h conversion
      #endif
      Serial.print(leadingZero(hour));Serial.print(F(":"));          
      Serial.print(leadingZero(minute));Serial.print(F(":"));
      Serial.print(leadingZero(second));
      #if(RTC_FEATURE_12H_TIME == 1)
        if(isPM){Serial.print(F(" PM"));}
        else{Serial.print(F(" AM"));}
      #endif
      #if (RTC_FEATURE_WEEKDAYS == 1)
        Serial.print(F(" "));
        uint8_t week = getWeekdayIndex(day, month, year);
        Serial.print(getWeekNames(week));
      #endif
        Serial.println();
    }
  #endif
//--------------------------------------------------------------------------------------------------------------------------

// ram access------------------------------------------------------------------------------------------------
  #if defined(RTC_FEATURE_RAM) && (RTC_FEATURE_RAM == 1)

    #define rtc_ram_start 0x08 // max 56 bytes
    uint8_t readRam(uint8_t address) 
    { 
      uint8_t value;
      rtcReadByte(rtc_ram_start + address, value); 
      return value; 
    }
    void writeRam(uint8_t address, uint8_t value) { rtcWriteByte(rtc_ram_start + address, value); }
  #endif
//-----------------------------------------------------------------------------------------------------------

// rtc sq pin config access ------------------------------------------------------------------------------------------------
  #if (RTC_FEATURE_BLINK) && (RTC_FEATURE_BLINK == 1)
    #define rtc_osc_1hz   1
    #define rtc_osc_4khz  4
    #define rtc_osc_8khz  8
    #define rtc_osc_32khz 32

    void setOscillator(bool Enable, uint8_t frequency)
    {
	  #define OSC_RESET      0b00000011
	  #define OSC_1HZ        0b00010000
	  #define OSC_4KHZ       0b00010001
	  #define OSC_8KHZ       0b00010010
	  #define OSC_32KHZ      0b00010011
	  #define CONTROL_REGISTER_LOCATION 0x07

      uint8_t _Buffer;
      if(Enable)
      {
        switch(frequency)
        {
          case rtc_osc_1hz   : _Buffer = OSC_1HZ; break;
          case rtc_osc_4khz  : _Buffer = OSC_4KHZ; break;
          case rtc_osc_8khz  : _Buffer = OSC_8KHZ; break;
          case rtc_osc_32khz : _Buffer = OSC_32KHZ; break;
          default            : _Buffer = OSC_RESET; break;
        };
      }
      else
      {
        _Buffer = OSC_RESET;
      }
      rtcWriteByte(CONTROL_REGISTER_LOCATION, _Buffer);
    }
  #endif
//-------------------------------------------------------------------------------------------------------

}; // end of class
#endif //end of ds1307_h
