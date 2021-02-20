//
// Copyright (c) 2020 Fw-Box (https://fw-box.com)
// Author: Hartman Hsieh
//
// Description :
//   
//
// Required Library :
//

#include "FwBox_U8g2Widget.h"


void drawPage128X128Wether(U8G2* u8g2, FwBox_WeatherResult* WeatherResult, bool showWifiIcon, bool showServerOkIcon)
{
    u8g2->setFont(u8g2_font_unifont_t_chinese1);
    String line = "今日天氣預報";
    u8g2->setCursor(15, 20);
    u8g2->print(line);

    if (WeatherResult->WxResult == true) {
      drawWeather(u8g2, getWetherIcon(WeatherResult->Wx1, hour()), WeatherResult->T1);
    }

    drawDateTime(u8g2, 0, DATE_TIME_BOTTOM);
    drawSmallIcons(u8g2, showWifiIcon, showServerOkIcon);
}

void drawPage128X128Time(U8G2* u8g2, FwBox_WeatherResult* WeatherResult, bool showWifiIcon, bool showServerOkIcon)
{
    drawWeek(u8g2, 0, 16);
    drawSmallWeather(u8g2, 85, 16, getWetherIcon(WeatherResult->Wx1, hour()), WeatherResult->T1);
    drawBigTime(u8g2, 2, BIG_TIME_BOTTOM);
    drawDate(u8g2, 15, BIG_TIME_BOTTOM + 24);
    drawSmallIcons(u8g2, showWifiIcon, showServerOkIcon);
}

void drawPage128X128Info(U8G2* u8g2, const char* fwVer, bool showWifiIcon, bool showServerOkIcon)
{
    u8g2->setFont(u8g2_font_unifont_t_chinese1); // Width:16, Height:16
    String line = "韌體:v";
    line += fwVer;
    u8g2->setCursor(TEXT_GAP, WORD_HEIGHT + TEXT_GAP + (LINE_HEIGHT * 0));
    u8g2->print(line);

    u8g2->setCursor(TEXT_GAP, WORD_HEIGHT + TEXT_GAP + (LINE_HEIGHT * 1));
    u8g2->print(WiFi.localIP());

    //
    // MAC address is too long, use the small font.
    //
    u8g2->setFont(u8g2_font_7x13_tf); // Width:6, Height:13
    u8g2->setCursor(TEXT_GAP, WORD_HEIGHT + TEXT_GAP + (LINE_HEIGHT * 2));
    u8g2->print(WiFi.macAddress());
    
    drawSmallIcons(u8g2, showWifiIcon, showServerOkIcon);
}

int getWetherIcon(String strWx, int intHour24)
{
  if(strWx.indexOf("雨") >= 0) {
    return ICON_ID_6X_RAIN;
  }
  else if(strWx.indexOf("陰") >= 0) {
    return ICON_ID_6X_CLOUD;
  }
  else if((strWx.indexOf("晴") >= 0) && (strWx.indexOf("雲") >= 0)) {
    return ICON_ID_6X_SUN_CLOUD;
  }
  else if(strWx.indexOf("晴") >= 0) {
    if(intHour24 >= 6 && intHour24 <= 18)
      return ICON_ID_6X_SUN;
    else
      return ICON_ID_6X_MOON;
  }
  else if(strWx.indexOf("雲") >= 0) {
    return ICON_ID_6X_CLOUD;
  }
  return -1; // Error
}

void drawDateTime(U8G2* u8g2, u8g2_uint_t x, u8g2_uint_t y)
{
  char buff[20];
  memset(&(buff[0]), 0, 20);
  u8g2->setFont(u8g2_font_unifont_t_chinese1); // Width:16, Height:16
  //String line = String(year()) + "-" + month() + "-" + String(day(), 2) + " " + hour() + ":" + minute();
  sprintf(buff, "%d-%02d-%02d %02d:%02d", year(), month(), day(), hour(), minute());
  u8g2->setCursor(x, y);
  u8g2->print(buff);
}

void drawDate(U8G2* u8g2, u8g2_uint_t x, u8g2_uint_t y)
{
  char buff[20];
  memset(&(buff[0]), 0, 20);
  u8g2->setFont(u8g2_font_logisoso16_tn);
  sprintf(buff, "%d-%02d-%02d", year(), month(), day());
  u8g2->setCursor(x, y);
  u8g2->print(buff);
}
void drawWeek(U8G2* u8g2, u8g2_uint_t x, u8g2_uint_t y)
{
  char* WEEK_DAY_NAME_TW[] = {"日", "一", "二", "三", "四", "五", "六"}; // Days Of The Week 
  char buff[20];
  memset(&(buff[0]), 0, 20);
  u8g2->setFont(u8g2_font_unifont_t_chinese1); // Width:16, Height:16
  sprintf(buff, "星期%s", WEEK_DAY_NAME_TW[weekday() - 1]);
  u8g2->setCursor(x, y);
  u8g2->print(buff);
}
void drawBigTime(U8G2* u8g2, u8g2_uint_t x, u8g2_uint_t y)
{
  char buff[8];
  memset(&(buff[0]), 0, 8);
  u8g2->setFont(u8g2_font_logisoso42_tn); // Width:24, Height:50
  //sprintf(buff, "%d-%02d-%02d %02d:%02d", year(), month(), day(), hour(), minute());
  sprintf(buff, "%02d:%02d", hour(), minute());
  u8g2->setCursor(x, y);
  u8g2->print(buff);
}

void drawSmallIcons(U8G2* u8g2, bool showWifiIcon, bool showServerOkIcon)
{
  //Serial.printf("wifiStatus = %d\n", wifiStatus);
  //Serial.printf("serverStatus = %d\n", serverStatus);
  if(showWifiIcon) {
    u8g2->setFont(u8g2_font_open_iconic_all_2x_t);
    u8g2->drawGlyph(SMALL_ICON_LEFT + (22*3), SMALL_ICON_BOTTOM, ICON_ID_2X_WIFI);
  }
  if(showServerOkIcon) {
    u8g2->setFont(u8g2_font_open_iconic_all_2x_t);
    u8g2->drawGlyph(SMALL_ICON_LEFT + (22*2), SMALL_ICON_BOTTOM, ICON_ID_2X_OK);
  }
}
void drawSmallWeather(U8G2* u8g2, u8g2_uint_t x, u8g2_uint_t y, int symbol, int degree)
{
  if(symbol >= 0) {
    u8g2->setFont(u8g2_font_open_iconic_weather_2x_t);
    u8g2->drawGlyph(x, y, symbol);
  }

  u8g2->setFont(u8g2_font_unifont_t_chinese1); // Width:16, Height:16
  u8g2->setCursor(x + 18, y);
  u8g2->print(degree);
  u8g2->print("°C");    // requires enableUTF8Print()
}
void drawWeather(U8G2* u8g2, int symbol, int degree)
{
  if(symbol >= 0) {
    u8g2->setFont(u8g2_font_open_iconic_weather_6x_t);
    u8g2->drawGlyph(0, WEATHER_SYMBOL_BOTTOM, symbol);
  }

  u8g2->setFont(u8g2_font_logisoso32_tf); // Width:37, Height:47
  u8g2->setCursor((8*6) + 3, WEATHER_SYMBOL_BOTTOM - 3);
  u8g2->print(degree);
  u8g2->print("°C");    // requires enableUTF8Print()
}
