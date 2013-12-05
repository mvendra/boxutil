
#ifndef __strveccont_h__
#define __strveccont_h__

#include "types.h"
#include <string>
#include <vector>

class StrVecCont {
	public:
		StrVecCont();
		StrVecCont(const StrVecCont &_other);
		StrVecCont& operator= (const StrVecCont &_other);
		virtual ~StrVecCont();
		void PushBack(const std::string &_element);
		std::string Get(const uint32 _index) const;
		void PopBack();
		void Pop(uint32 _index);
		uint32 Size() const;
		void Clear();
	private:
		std::vector<std::string> vecstrings;
		void CopyOther(const StrVecCont &_other);
};

#endif // __strveccont_h__

