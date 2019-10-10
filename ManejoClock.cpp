#include "ManejoClock.h"
//char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};  

void InicioRTC(RTC_DS3231 &rtc){
  if (! rtc.begin()) {
    Serial.println(F("Couldn't find RTC"));
    //while (1);
  }
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  if (rtc.lostPower()) {
    Serial.println(F("RTC lost power, lets set the time!"));
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  }
String TiempoActual(RTC_DS3231 &rtc){
    DateTime now = rtc.now();
    String dataString = "";
    String stryear=String(now.year());
    String strmonth=String(now.month());
    String strday=String(now.day());
    String strhour=String(now.hour());
    String strminute=String(now.minute());
    String strsecond=String(now.second());
    dataString=stryear+"/"+strmonth+"/"+strday+";";
    dataString+=strhour+":"+strminute+":"+strsecond;
    return dataString;
}

String TiempoActualPC(RTC_DS3231 &rtc){
    DateTime now = rtc.now();
    String dataString = "";
    String stryear=String(now.year());
    String strmonth=String(now.month());
    String strday=String(now.day());
    String strhour=String(now.hour());
    String strminute=String(now.minute());
    String strsecond=String(now.second());
    dataString=stryear+";"+strmonth+";"+strday+";";
    dataString+=strhour+";"+strminute+";"+strsecond;
    return dataString;
}

uint32_t TiempoActualUnix(RTC_DS3231 &rtc){
  DateTime now = rtc.now();
  return now.unixtime();
}
uint32_t TiempoActualInt(RTC_DS3231 &rtc) {
	DateTime now = rtc.now();
	unsigned long lyear = now.year();
	unsigned long lmonth = now.month();
	unsigned long lday = now.day();
	unsigned long  lhour = now.hour();
	unsigned long  lminute = now.minute();
	unsigned long lsecond = now.second();
	lyear *= 365 * 24 * 60 * 60;
	lmonth *= 31 * 24 * 60 * 60;
	lday *= 24 * 60 * 60;
	lhour *= 60 * 60;
	lminute *= 60;
	return lyear+lmonth+lday+lhour+lminute+lsecond;
}
