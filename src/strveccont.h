
#ifndef __BOXUTIL_STRVECCONT_H__
#define __BOXUTIL_STRVECCONT_H__

#include <string>
#include <vector>

namespace boxutil {

class StrVecCont final {
public:
    StrVecCont();
    StrVecCont(const StrVecCont &other);
    StrVecCont(const StrVecCont &&other) = delete;
    StrVecCont& operator= (const StrVecCont &other);
    StrVecCont& operator= (const StrVecCont &&other) = delete;
    ~StrVecCont();
    void PushBack(const std::string &element);
    bool Get(const unsigned int index, std::string &output) const;
    void PopBack();
    void Pop(unsigned int index);
    unsigned int Size() const;
    void Clear();
    bool HasElement(const std::string &element) const;
    bool operator==(const StrVecCont &other);
private:
    std::vector<std::string> m_vecstrings;
    void CopyOther(const StrVecCont &other);
};

} // ns: boxutil

#endif // __BOXUTIL_STRVECCONT_H__
