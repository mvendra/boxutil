
#ifndef __bytearray_h__
#define __bytearray_h__

#include <string>

class ByteArray  {

	public:
		ByteArray();
		ByteArray(const ByteArray &_other);
		ByteArray& operator= (const ByteArray &_other);
		ByteArray(pcbyte _buff, uint32 _buffsize);
		virtual ~ByteArray();

		pcbyte GetBuffer() const;
		ByteArray GetCopy() const;
		ByteArray GetSection(const uint32 _offset, const uint32 _length);
		void Append(const ByteArray &_other);
		void Append(pcbyte _buff, uint32 _buffsize);
		void EraseSection(const uint32 _offset, const uint32 _length);
		uint32 GetLength() const;
		std::string GetHexString() const;
		void Clear();

	private:
		void FlushInternalMem();
		void InitInternalMem();
		void CopyOther(const ByteArray  &_other);
		void CopyOther(pcbyte _otherbuff, uint32 _otherbufflen);
		uint32 ExpandBy(uint32 _amount);
		void Alloc(uint32 _amount);
		pbyte internalcontents;
		uint32 internallength;


};

#endif // __bytearray_h__

