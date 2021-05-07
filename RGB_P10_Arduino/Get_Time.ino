void GetDateTime() {

  DateTime now = rtc.now();
  _day = now.day();
  _month = now.month();
  _year = now.year();
  _hour24 = now.hour();
  _hour12 = now.hour();
  _minute = now.minute();
  _second = now.second();
  _dtw = now.dayOfTheWeek();
  
  hr24 = _hour24;
  if (_hour24 >= 12) {
    st = "PM";
    _hour24 = _hour24 - 12;
    if (_hour24 == 0) {
      _hour24 = 12;
    }
  }
  else {
    if (_hour24 == 0) {
      st = "AM";
      _hour24 = 12; // Night 12 AM
    }
  }
  if (hr24 < 12) {
    st = "AM";
  }
  else {
    st = "PM";
  }
//  _hour24 = EEPROM.read(2);
}
