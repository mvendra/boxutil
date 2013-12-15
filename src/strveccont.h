
#ifndef __strveccont_h__
#define __strveccont_h__

#include "types.h"
#include <string>
#include <vector>

class StrVecCont {
public:
    StrVecCont();
    StrVecCont(const StrVecCont &other);
    StrVecCont& operator= (const StrVecCont &other);
    virtual ~StrVecCont();
    void PushBack(const std::string &element);
    std::string Get(const uint32 index) const;
    void PopBack();
    void Pop(uint32 index);
    uint32 Size() const;
    void Clear();
private:
    std::vector<std::string> m_vecstrings;
    void CopyOther(const StrVecCont &other);
};

#endif // __strveccont_h__

