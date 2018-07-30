
#ifndef __datehelper_h__
#define __datehelper_h__

#include <string>

class DateHelper {

// textdate, whereever it is present, is in the
// form of "ddmmyyyy", no slash, no space, just 8 ascii numbers

public:

    DateHelper(); // builds itself with the present date

    DateHelper(const std::string &textdate);

    DateHelper(const unsigned short _day,
               const unsigned short _month,
               const unsigned short _year);

    DateHelper(DateHelper&&);

    ~DateHelper(){}

    DateHelper(const DateHelper&);
    DateHelper& operator=(const DateHelper&);
    DateHelper& operator=(DateHelper&&) = delete;

    static bool isValidDate(const std::string &textdate);
    static bool isValidDate(const unsigned short _day,
                     const unsigned short _month,
                     const unsigned short _year);

    static void convertFromText(const std::string &textdate,
                                unsigned short &_day,
                                unsigned short &_month,
                                unsigned short &_year);
    static std::string convertFromNumbers(const unsigned short _day,
                                          const unsigned short _month,
                                          const unsigned short _year);

    bool setDate(const std::string &textdate);
    bool setDate(const unsigned short _day,
                 const unsigned short _month,
                 const unsigned short _year);

    std::string getDateString() const;
    void getDateNumbers(unsigned short &_day,
                        unsigned short &_month,
                        unsigned short &_year) const;

    void clearDate();

private:

    unsigned short day;
    unsigned short month;
    unsigned short year;

};

#endif // __datehelper_h__
