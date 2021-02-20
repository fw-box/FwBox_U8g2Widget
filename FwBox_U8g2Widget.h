//
// Copyright (c) 2020 Fw-Box (https://fw-box.com)
// Author: Hartman Hsieh
//
// Description :
//   
//
// Required Library :
//

#ifndef __FWBOX_U8G2WIDGET_H__
#define __FWBOX_U8G2WIDGET_H__

#include <Arduino.h>
//#include "time.h" // ESP8266 time function support
#include <TimeLib.h> // Library for Time function
#include <U8g2lib.h>
#include "FwBox_TwWeather.h"

//
// Wifi library
//
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
#else
  #include <WiFi.h>
#endif

#define TEXT_GAP 5
#define WORD_WIDTH 16
#define WORD_HEIGHT 16
#define LINE_HEIGHT 20

#define WEATHER_SYMBOL_BOTTOM 28 + (8*6)
#define BIG_TIME_BOTTOM 20 + (8*6)
#define DATE_TIME_BOTTOM (WEATHER_SYMBOL_BOTTOM + 16)
#define SMALL_ICON_LEFT 45
#define SMALL_ICON_BOTTOM 126

#define ICON_ID_6X_CLOUD 64
#define ICON_ID_6X_SUN_CLOUD  65
#define ICON_ID_6X_MOON 66
#define ICON_ID_6X_RAIN 67
#define ICON_ID_6X_SUN  69
#define ICON_ID_2X_WIFI 248
#define ICON_ID_2X_OK 120
#define ICON_ID_2X_NOT_OK 121


void drawPage128X128Wether(U8G2* u8g2, FwBox_WeatherResult* WeatherResult, bool showWifiIcon, bool showServerOkIcon);
void drawPage128X128Time(U8G2* u8g2, FwBox_WeatherResult* WeatherResult, bool showWifiIcon, bool showServerOkIcon);
void drawPage128X128Info(U8G2* u8g2, const char* fwVer, bool showWifiIcon, bool showServerOkIcon);

int getWetherIcon(String strWx, int intHour24);
void drawDateTime(U8G2* u8g2, u8g2_uint_t x, u8g2_uint_t y);
void drawDate(U8G2* u8g2, u8g2_uint_t x, u8g2_uint_t y);
void drawWeek(U8G2* u8g2, u8g2_uint_t x, u8g2_uint_t y);
void drawBigTime(U8G2* u8g2, u8g2_uint_t x, u8g2_uint_t y);
void drawSmallIcons(U8G2* u8g2, bool showWifiIcon, bool showServerOkIcon);
void drawSmallWeather(U8G2* u8g2, u8g2_uint_t x, u8g2_uint_t y, int symbol, int degree);
void drawWeather(U8G2* u8g2, int symbol, int degree);


#endif // __FWBOX_U8G2WIDGET_H__
