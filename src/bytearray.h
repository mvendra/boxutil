
#ifndef __BOXUTIL_BYTEARRAY_H__
#define __BOXUTIL_BYTEARRAY_H__

#include <string>

#include "types.h"

namespace boxutil {

class ByteArray final {

public:
    ByteArray();
    ByteArray(const ByteArray &other);
    ByteArray(const ByteArray &&other);
    ByteArray& operator= (const ByteArray &other);
    ByteArray& operator= (const ByteArray &&other);
    ByteArray(pcbyte buff, uint32 buffsize);
    ~ByteArray();

    pcbyte GetBuffer() const;
    ByteArray GetCopy() const;
    bool GetSection(const uint32 offset, const uint32 length, ByteArray &output);
    bool GetByte(const uint32 offset, byte &output);
    void Append(const ByteArray &other);
    void Append(pcbyte buff, uint32 buffsize);
    bool EraseSection(const uint32 offset, const uint32 length);
    uint32 GetLength() const;
    std::string GetHexString() const;
    void Clear();

private:

    void FlushInternalMem();
    void InitInternalMem();
    void CopyOther(const ByteArray  &other);
    void CopyOther(pcbyte otherbuff, uint32 otherbufflen);
    uint32 ExpandBy(uint32 amount);
    void Alloc(uint32 amount);

    pbyte m_internalcontents;
    uint32 m_internallength;

};

} // ns: boxutil

#endif // __BOXUTIL_BYTEARRAY_H__
