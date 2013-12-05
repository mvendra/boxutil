
#include "strveccont.h"
#include "exceptionbase.h"

StrVecCont::StrVecCont(){
}

StrVecCont::StrVecCont(const StrVecCont &_other){
	CopyOther(_other);
}

StrVecCont& StrVecCont::operator= (const StrVecCont &_other){
	CopyOther(_other);
	return *this;
}

StrVecCont::~StrVecCont(){
}

void StrVecCont::PushBack(const std::string &_element){
	vecstrings.push_back(_element);
}

std::string StrVecCont::Get(const uint32 _index) const {
	if (_index >= vecstrings.size()){
		RAISE_EXCEPT(ExceptionBase, "String vector out of bounds");
	}
	return vecstrings[_index];
}

void StrVecCont::PopBack() {
	vecstrings.pop_back();
}

void StrVecCont::Pop(uint32 _index){
	std::vector<std::string>::iterator it;
	uint32 count = 0;
	for (it = vecstrings.begin(); it != vecstrings.end(); it++){
		if (count == _index){
			vecstrings.erase(it);
			break;
		}
		count++;
	}
}

void StrVecCont::CopyOther(const StrVecCont &_other){
	for (uint32 i = 0; i < _other.Size(); i++){
		vecstrings.push_back(_other.Get(i));
	}
}

uint32 StrVecCont::Size() const {
	return vecstrings.size();
}

void StrVecCont::Clear(){
	vecstrings.clear();
}

