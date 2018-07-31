
#include "datehelper.h"
#include "conversions.h"
#include "stringmanip.h"

#include <cstring>

#ifdef __linux__
#include <time.h>
#include <sys/time.h>
#elif _WIN32
#include <windows.h>
#endif

namespace boxutil {

DateHelper::DateHelper():m_day{0}, m_month{0}, m_year{0}{

#ifdef __linux__

    struct timeval tv;
    struct timezone tz;
    struct tm *tm;

    gettimeofday(&tv, &tz);
    tm = localtime(&tv.tv_sec);

    this->day = tm->tm_mday;
    this->month = tm->tm_mon+1;
    this->year = tm->tm_year + 1900;

#elif _WIN32

    SYSTEMTIME stSysTime;
    GetLocalTime(&stSysTime);

    this->m_day = stSysTime.wDay;
    this->m_month = stSysTime.wMonth;
    this->m_year = stSysTime.wYear;

#else
    #error "Present-date probing not implemented on this platform"
#endif

}

DateHelper::DateHelper(const unsigned short param_day,
                       const unsigned short param_month,
                       const unsigned short param_year):
m_day{0}, m_month{0}, m_year{0}
{
    SetDate(param_day, param_month, param_year);
}

DateHelper::DateHelper(DateHelper &&other):
m_day{ std::move(other.m_day) },
m_month{ std::move(other.m_month) },
m_year{ std::move(other.m_year) }
{
    SetDate(m_day, m_month, m_year);
}

DateHelper::DateHelper(const std::string &textdate):
m_day{0}, m_month{0}, m_year{0}
{
    SetDate(textdate);
}

DateHelper::DateHelper(const DateHelper &other):
m_day{other.m_day}, m_month{other.m_month}, m_year{other.m_year}
{
}

DateHelper& DateHelper::operator=(const DateHelper &other){
    this->m_day = other.m_day;
    this->m_month = other.m_month;
    this->m_year = other.m_year;
    return (*this);
}

bool DateHelper::IsValidDate(const std::string &textdate) {

#ifdef _WIN32
    unsigned short param_day;
    unsigned short param_month;
    unsigned short param_year;
    ConvertFromText(textdate, param_day, param_month, param_year);
    if (param_day >= 1 && param_day <= 30 && param_month >= 1 && param_month <= 12 && param_year >= 1970 && param_year <= 2080) { return true; }
    else { return false; }
#else
    tm aux;
    return strptime(textdate.c_str(), "%d/%m/%Y", &aux);
#endif

}

bool DateHelper::IsValidDate(const unsigned short param_day,
                 const unsigned short param_month,
                 const unsigned short param_year) {

#ifdef _WIN32
    if (param_day >= 1 && param_day <= 30 && param_month >= 1 && param_month <= 12 && param_year >= 1970 && param_year <= 2080) { return true; }
    else { return false; }
#else
    std::string txtdate = ConvertFromNumbers(param_day, param_month, param_year);
    tm aux;
    return strptime(txtdate.c_str(), "%d/%m/%Y", &aux);
#endif

}

void DateHelper::ConvertFromText(const std::string &textdate,
                                 unsigned short &param_day,
                                 unsigned short &param_month,
                                 unsigned short &param_year)
{

    if (textdate.size() < 10){
        param_day = 0;
        param_month = 0;
        param_year = 0;
        return; // no cake.
    }

    std::string strday;
    std::string strmonth;
    std::string stryear;

    strday = textdate.substr(0, 2);
    strmonth = textdate.substr(3, 2);
    stryear = textdate.substr(6, 4);

    param_day = DecStrToUshort(strday);
    param_month = DecStrToUshort(strmonth);
    param_year = DecStrToUshort(stryear);

}

std::string DateHelper::ConvertFromNumbers(const unsigned short param_day,
                                           const unsigned short param_month,
                                           const unsigned short param_year)
{

    char chdate[32];
    std::memset(chdate, 0x00, 32);
	custom_sprintf_s(chdate, 32, "%02d/%02d/%04d", param_day, param_month, param_year);
    std::string ret {chdate};
    return ret;

}

bool DateHelper::SetDate(const std::string &textdate){

    if (!IsValidDate(textdate)){
        ClearDate();
        return false;
    }

    unsigned short _d{0}, _m{0}, _y{0};
    ConvertFromText(textdate, _d, _m, _y);

    this->m_day = _d;
    this->m_month = _m;
    this->m_year = _y;

    return true;

}

bool DateHelper::SetDate(const unsigned short param_day,
             const unsigned short param_month,
             const unsigned short param_year) {

    if (!IsValidDate(param_day, param_month, param_year)){
        ClearDate();
        return false;
    }

    this->m_day = param_day;
    this->m_month = param_month;
    this->m_year = param_year;

    return true;

}

std::string DateHelper::GetDateString() const {
    return ConvertFromNumbers(m_day, m_month, m_year);
}

void DateHelper::GetDateNumbers(unsigned short &param_day,
                    unsigned short &param_month,
                    unsigned short &param_year) const {
    param_day = m_day;
    param_month = m_month;
    param_year = m_year;
}

void DateHelper::ClearDate(){
	m_day = 0;
    m_month = 0;
	m_year = 0;
}

} // ns: boxutil
