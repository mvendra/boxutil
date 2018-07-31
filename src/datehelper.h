
#ifndef __BOXUTIL_DATEHELPER_H__
#define __BOXUTIL_DATEHELPER_H__

#include <string>

namespace boxutil {

class DateHelper final {

// textdate, whereever it is present, is in the
// form of "ddmmyyyy", no slash, no space, just 8 ascii numbers

public:

    DateHelper(); // builds itself with the present date

    DateHelper(const std::string &textdate);

    DateHelper(const unsigned short param_day,
               const unsigned short param_month,
               const unsigned short param_year);

    DateHelper(DateHelper&&);

    ~DateHelper(){}

    DateHelper(const DateHelper&);
    DateHelper& operator=(const DateHelper&);
    DateHelper& operator=(DateHelper&&) = delete;

    static bool IsValidDate(const std::string &textdate);
    static bool IsValidDate(const unsigned short param_day,
                     const unsigned short param_month,
                     const unsigned short param_year);

    static void ConvertFromText(const std::string &textdate,
                                unsigned short &param_day,
                                unsigned short &param_month,
                                unsigned short &param_year);
    static std::string ConvertFromNumbers(const unsigned short param_day,
                                          const unsigned short param_month,
                                          const unsigned short param_year);

    bool SetDate(const std::string &textdate);
    bool SetDate(const unsigned short param_day,
                 const unsigned short param_month,
                 const unsigned short param_year);

    std::string GetDateString() const;
    void GetDateNumbers(unsigned short &param_day,
                        unsigned short &param_month,
                        unsigned short &param_year) const;

    void ClearDate();

private:

    unsigned short m_day;
    unsigned short m_month;
    unsigned short m_year;

};

} // ns: boxutil

#endif // __BOXUTIL_DATEHELPER_H__
