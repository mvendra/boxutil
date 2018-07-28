
#include "strveccont.h"
#include "exceptionbase.h"

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

std::string StrVecCont::Get(const uint32 index) const {
  if (index >= m_vecstrings.size()){
    RAISE_EXCEPT(ExceptionBase, "String vector out of bounds");
  }
  return m_vecstrings[index];
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
    m_vecstrings.push_back(other.Get(i));
  }
}

uint32 StrVecCont::Size() const {
  return m_vecstrings.size();
}

void StrVecCont::Clear(){
  m_vecstrings.clear();
}

