
#ifndef __BOXUTIL_BYTEARRAY_H__
#define __BOXUTIL_BYTEARRAY_H__

#include <string>

namespace boxutil {

class ByteArray final {

public:
    ByteArray();
    ByteArray(const ByteArray &other);
    ByteArray(const ByteArray &&other);
    ByteArray& operator= (const ByteArray &other);
    ByteArray& operator= (const ByteArray &&other);
    ByteArray(const unsigned char *buff, unsigned int buffsize);
    ~ByteArray();

    const unsigned char * GetBuffer() const;
    ByteArray GetCopy() const;
    bool GetSection(const unsigned int offset, const unsigned int length, ByteArray &output);
    bool GetByte(const unsigned int offset, unsigned char &output);
    void Append(const ByteArray &other);
    void Append(const unsigned char * buff, unsigned int buffsize);
    bool EraseSection(const unsigned int offset, const unsigned int length);
    unsigned int GetLength() const;
    std::string GetHexString() const;
    void Clear();

private:

    void FlushInternalMem();
    void InitInternalMem();
    void CopyOther(const ByteArray  &other);
    void CopyOther(const unsigned char * otherbuff, unsigned int otherbufflen);
    unsigned int ExpandBy(unsigned int amount);
    void Alloc(unsigned int amount);

    unsigned char *m_internalcontents;
    unsigned int m_internallength;

};

} // ns: boxutil

#endif // __BOXUTIL_BYTEARRAY_H__
