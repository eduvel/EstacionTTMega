#include <Wire.h>
#include "RTClib.h"
void InicioRTC(RTC_DS3231 &rtc);
String TiempoActual(RTC_DS3231 &rtc);
uint32_t TiempoActualUnix(RTC_DS3231 &rtc);
uint32_t TiempoActualInt(RTC_DS3231 &rtc);
String TiempoActualPC(RTC_DS3231 &rtc);
