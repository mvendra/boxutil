
#ifndef __datehelper_h__
#define __datehelper_h__

#include "types.h"

#include <string>

class DateHelper final {

// textdate, whereever it is present, is in the
// form of "ddmmyyyy", no slash, no space, just 8 ascii numbers

public:

    DateHelper(); // builds itself with the present date

    DateHelper(const std::string &textdate);

    DateHelper(const uint16 _day,
               const uint16 _month,
               const uint16 _year);

    DateHelper(DateHelper&&);

    ~DateHelper(){}

    DateHelper(const DateHelper&);
    DateHelper& operator=(const DateHelper&);
    DateHelper& operator=(DateHelper&&) = delete;

    static bool IsValidDate(const std::string &textdate);
    static bool IsValidDate(const uint16 _day,
                     const uint16 _month,
                     const uint16 _year);

    static void ConvertFromText(const std::string &textdate,
                                uint16 &_day,
                                uint16 &_month,
                                uint16 &_year);
    static std::string ConvertFromNumbers(const uint16 _day,
                                          const uint16 _month,
                                          const uint16 _year);

    bool SetDate(const std::string &textdate);
    bool SetDate(const uint16 _day,
                 const uint16 _month,
                 const uint16 _year);

    std::string GetDateString() const;
    void GetDateNumbers(uint16 &_day,
                        uint16 &_month,
                        uint16 &_year) const;

    void ClearDate();

private:

    uint16 day;
    uint16 month;
    uint16 year;

};

#endif // __datehelper_h__
