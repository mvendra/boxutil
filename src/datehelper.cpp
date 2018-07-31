
#include "datehelper.h"
#include "conversions.h"

#include <cstring>

#ifdef __linux__
#include <time.h>
#include <sys/time.h>
#elif _WIN32
#include <windows.h>
#endif

namespace boxutil {

DateHelper::DateHelper():day{0}, month{0}, year{0}{

#ifdef __linux__

    struct timeval tv;
    struct timezone tz;
    struct tm *tm;

    gettimeofday(&tv, &tz);
    tm = localtime(&tv.tv_sec);

    /*sysTime.m_seconds = tm->tm_sec;
    sysTime.m_minutes = tm->tm_min;
    sysTime.m_hours = tm->tm_hour;
    sysTime.m_monthday = tm->tm_mday;
    sysTime.m_month = tm->tm_mon+1;
    sysTime.m_year = tm->tm_year%100;*/

    this->day = tm->tm_mday;
    this->month = tm->tm_mon+1;
    this->year = tm->tm_year + 1900;

#elif _WIN32

    SYSTEMTIME stSysTime;
    GetLocalTime(&stSysTime);

    this->day = stSysTime.wDay;
    this->month = stSysTime.wMonth;
    this->year = stSysTime.wYear;

#else
    #error "Present-date probing not implemented on this platform"
#endif

}

DateHelper::DateHelper(const uint16 _day,
                       const uint16 _month,
                       const uint16 _year):
day{0}, month{0}, year{0}
{
    SetDate(_day, _month, _year);
}

DateHelper::DateHelper(DateHelper &&other):
day{ std::move(other.day) },
month{ std::move(other.month) },
year{ std::move(other.year) }
{
    SetDate(day, month, year);
}

DateHelper::DateHelper(const std::string &textdate):
day{0}, month{0}, year{0}
{
    SetDate(textdate);
}

DateHelper::DateHelper(const DateHelper &other):
day{other.day}, month{other.month}, year{other.year}
{
}

DateHelper& DateHelper::operator=(const DateHelper &other){
    this->day = other.day;
    this->month = other.month;
    this->year = other.year;
    return (*this);
}

bool DateHelper::IsValidDate(const std::string &textdate) {

#ifdef _WIN32
    uint16 _day;
    uint16 _month;
    uint16 _year;
    ConvertFromText(textdate, _day, _month, _year);
    if (_day >= 1 && _day <= 30 && _month >= 1 && _month <= 12 && _year >= 1970 && _year <= 2080) { return true; }
    else { return false; }
#else
    tm aux;
    return strptime(textdate.c_str(), "%d/%m/%Y", &aux);
#endif

}

bool DateHelper::IsValidDate(const uint16 _day,
                 const uint16 _month,
                 const uint16 _year) {

#ifdef _WIN32
    if (_day >= 1 && _day <= 30 && _month >= 1 && _month <= 12 && _year >= 1970 && _year <= 2080) { return true; }
    else { return false; }
#else
    std::string txtdate = ConvertFromNumbers(_day, _month, _year);
    tm aux;
    return strptime(txtdate.c_str(), "%d/%m/%Y", &aux);
#endif

}

void DateHelper::ConvertFromText(const std::string &textdate,
                                 uint16 &_day,
                                 uint16 &_month,
                                 uint16 &_year)
{

    if (textdate.size() < 10){
        _day = 0;
        _month = 0;
        _year = 0;
        return; // no cake.
    }

    std::string strday;
    std::string strmonth;
    std::string stryear;

    strday = textdate.substr(0, 2);
    strmonth = textdate.substr(3, 2);
    stryear = textdate.substr(6, 4);

    _day = DecStrToUshort(strday);
    _month = DecStrToUshort(strmonth);
    _year = DecStrToUshort(stryear);

}

std::string DateHelper::ConvertFromNumbers(const uint16 _day,
                                           const uint16 _month,
                                           const uint16 _year)
{

    char chdate[32];
    std::memset(chdate, 0x00, 32);
    std::sprintf(chdate, "%02d/%02d/%04d", _day, _month, _year);
    std::string ret {chdate};
    return ret;

}

bool DateHelper::SetDate(const std::string &textdate){

    if (!IsValidDate(textdate)){
        ClearDate();
        return false;
    }

    uint16 _d{0}, _m{0}, _y{0};
    ConvertFromText(textdate, _d, _m, _y);

    this->day = _d;
    this->month = _m;
    this->year = _y;

    return true;

}

bool DateHelper::SetDate(const uint16 _day,
             const uint16 _month,
             const uint16 _year) {

    if (!IsValidDate(_day, _month, _year)){
        ClearDate();
        return false;
    }

    this->day = _day;
    this->month = _month;
    this->year = _year;

    return true;

}

std::string DateHelper::GetDateString() const {
    return ConvertFromNumbers(day, month, year);
}

void DateHelper::GetDateNumbers(uint16 &_day,
                    uint16 &_month,
                    uint16 &_year) const {
    _day = day;
    _month = month;
    _year = year;
}

void DateHelper::ClearDate(){
    day = 0;
    month = 0;
    year = 0;
}

} // ns: boxutil
