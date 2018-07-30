
#include "datehelper.h"
#include "conversions.h"

#ifdef __linux__
#include <time.h>
#include <sys/time.h>
#elif _WIN32
#include <windows.h>
#endif

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

DateHelper::DateHelper(const unsigned short _day,
                       const unsigned short _month,
                       const unsigned short _year):
day{0}, month{0}, year{0}
{
    setDate(_day, _month, _year);
}

DateHelper::DateHelper(DateHelper &&other):
day{ std::move(other.day) },
month{ std::move(other.month) },
year{ std::move(other.year) }
{
    setDate(day, month, year);
}

DateHelper::DateHelper(const std::string &textdate):
day{0}, month{0}, year{0}
{
    setDate(textdate);
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

bool DateHelper::isValidDate(const std::string &textdate) {

#ifdef _WIN32
    unsigned short _day;
    unsigned short _month;
    unsigned short _year;
    convertFromText(textdate, _day, _month, _year);
    if (_day >= 1 && _day <= 30 && _month >= 1 && _month <= 12 && _year >= 1970 && _year <= 2080) { return true; }
    else { return false; }
#else
    tm aux;
    return strptime(textdate.c_str(), "%d/%m/%Y", &aux);
#endif

}

bool DateHelper::isValidDate(const unsigned short _day,
                 const unsigned short _month,
                 const unsigned short _year) {

#ifdef _WIN32
    if (_day >= 1 && _day <= 30 && _month >= 1 && _month <= 12 && _year >= 1970 && _year <= 2080) { return true; }
    else { return false; }
#else
    std::string txtdate = convertFromNumbers(_day, _month, _year);
    tm aux;
    return strptime(txtdate.c_str(), "%d/%m/%Y", &aux);
#endif

}

void DateHelper::convertFromText(const std::string &textdate,
                                 unsigned short &_day,
                                 unsigned short &_month,
                                 unsigned short &_year)
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

std::string DateHelper::convertFromNumbers(const unsigned short _day,
                                           const unsigned short _month,
                                           const unsigned short _year)
{

    char chdate[11]{0};
    sprintf(chdate, "%02d/%02d/%04d", _day, _month, _year);
    std::string ret {chdate};
    return ret;

}

bool DateHelper::setDate(const std::string &textdate){

    if (!isValidDate(textdate)){
        clearDate();
        return false;
    }

    unsigned short _d{0}, _m{0}, _y{0};
    convertFromText(textdate, _d, _m, _y);

    this->day = _d;
    this->month = _m;
    this->year = _y;

    return true;

}

bool DateHelper::setDate(const unsigned short _day,
             const unsigned short _month,
             const unsigned short _year) {

    if (!isValidDate(_day, _month, _year)){
        clearDate();
        return false;
    }

    this->day = _day;
    this->month = _month;
    this->year = _year;

    return true;

}

std::string DateHelper::getDateString() const {
    return convertFromNumbers(day, month, year);
}

void DateHelper::getDateNumbers(unsigned short &_day,
                    unsigned short &_month,
                    unsigned short &_year) const {
    _day = day;
    _month = month;
    _year = year;
}

void DateHelper::clearDate(){
    day = 0;
    month = 0;
    year = 0;
}
