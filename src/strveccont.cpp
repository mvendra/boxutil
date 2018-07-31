
#include "strveccont.h"

namespace boxutil {

StrVecCont::StrVecCont():m_vecstrings{}
{
}

StrVecCont::StrVecCont(const StrVecCont &other):m_vecstrings{}
{
    CopyOther(other);
}

StrVecCont& StrVecCont::operator= (const StrVecCont &other){
    if (this == &other) return *this;
    CopyOther(other);
    return *this;
}

StrVecCont::~StrVecCont(){
}

void StrVecCont::PushBack(const std::string &element){
    m_vecstrings.push_back(element);
}

bool StrVecCont::Get(const uint32 index, std::string &output) const {
    if (index >= m_vecstrings.size()){
        return false;
    }
    output = m_vecstrings[index];
    return true;
}

void StrVecCont::PopBack() {
    m_vecstrings.pop_back();
}

void StrVecCont::Pop(uint32 index){
    std::vector<std::string>::iterator it;
    uint32 count = 0;
    for (it = m_vecstrings.begin(); it != m_vecstrings.end(); it++){
        if (count == index){
            m_vecstrings.erase(it);
            break;
        }
        count++;
    }
}

void StrVecCont::CopyOther(const StrVecCont &other){
    for (uint32 i = 0; i < other.Size(); i++){
        std::string s;
        other.Get(i, s);
        m_vecstrings.push_back(s);
    }
}

uint32 StrVecCont::Size() const {
    return m_vecstrings.size();
}

void StrVecCont::Clear(){
    m_vecstrings.clear();
}

bool StrVecCont::HasElement(const std::string &element) const {
    for (uint32 i=0; i<Size(); i++){
        if (m_vecstrings[i] == element){
            return true;
        }
    }
    return false;
}

bool StrVecCont::operator==(const StrVecCont &other){
    if (Size() != other.Size()){
        return false;
    }
    for (uint32 i=0; i<Size(); i++){
        std::string s1, s2;
        if ( !(Get(i, s1) && other.Get(i, s2)) ) {
            return false;
        }
        if (s1 != s2){
            return false;
        }
    }
    return true;
}

} // ns: boxutil
