
#include "bytearray.h"
#include "stringmanip.h"

#include <cstdio>
#include <cstring>
#include <cstdlib>

namespace boxutil {

ByteArray::ByteArray():
m_internalcontents{nullptr}, m_internallength{0}{
    InitInternalMem();
}

ByteArray::ByteArray(const ByteArray &other):
m_internalcontents{nullptr}, m_internallength{0}{
    InitInternalMem();
    CopyOther(other);
}

ByteArray::ByteArray(const ByteArray &&other):
m_internalcontents{std::move(other.m_internalcontents)}, m_internallength{other.m_internallength}{
}

ByteArray::ByteArray(const unsigned char *buff, unsigned int buffsize):
m_internalcontents{nullptr}, m_internallength{0}{
    InitInternalMem();
    CopyOther(buff, buffsize);
}

ByteArray& ByteArray::operator= (const ByteArray &other){
    if (this == &other) return *this;
    CopyOther(other);
    return *this;
}

ByteArray& ByteArray::operator= (const ByteArray &&other){
    m_internallength = other.m_internallength;
    m_internalcontents = std::move(other.m_internalcontents);
    return *this;
}

ByteArray::~ByteArray(){
    FlushInternalMem();
}

const unsigned char * ByteArray::GetBuffer() const {
    return m_internalcontents;
}

ByteArray ByteArray::GetCopy() const {
    return ByteArray(m_internalcontents, m_internallength);
}

unsigned int ByteArray::GetLength() const {
    return m_internallength;
}

bool ByteArray::GetSection(const unsigned int offset, const unsigned int length, ByteArray &output){

    if (offset > m_internallength || length > m_internallength || (offset+length) > m_internallength){
        return false;
    }

    ByteArray retcopy(m_internalcontents+offset, length);
    output = retcopy;
    return true;
}

bool ByteArray::GetByte(const unsigned int offset, unsigned char &output){
    if (offset >= m_internallength){
        return false;
    }
    output = m_internalcontents[offset];
    return true;
}

void ByteArray::Append(const ByteArray &other){
    unsigned int offset_free = ExpandBy(other.GetLength());
    memcpy(m_internalcontents+offset_free, other.GetBuffer(), other.GetLength());
}

void ByteArray::Append(const unsigned char * buff, unsigned int buffsize){
    unsigned int offset_free = ExpandBy(buffsize);
    memcpy(m_internalcontents+offset_free, buff, buffsize);
}

bool ByteArray::EraseSection(const unsigned int offset, const unsigned int length){

    if (offset > m_internallength || length > m_internallength || (offset+length) > m_internallength){
        return false;
    }

    unsigned int len_low = offset;
    unsigned int len_high = m_internallength-offset-length;

    unsigned char *backup_low = static_cast<unsigned char*>(calloc(len_low, sizeof(unsigned char)));
    unsigned char *backup_high = static_cast<unsigned char*>(calloc(len_high, sizeof(unsigned char)));

    memcpy(backup_low, m_internalcontents, len_low);
    memcpy(backup_high, m_internalcontents+m_internallength-len_high, len_high);

    FlushInternalMem();
    Alloc(len_low+len_high);

    memcpy(m_internalcontents, backup_low, len_low);
    memcpy(m_internalcontents+len_low, backup_high, len_high);

    free(backup_low);
    free(backup_high);

    return true;

}

void ByteArray::CopyOther(const ByteArray  &other){
    FlushInternalMem();
    unsigned int newlen = other.GetLength();
    const unsigned char * newbuf = other.GetBuffer();
    Alloc(newlen);
    memcpy(m_internalcontents, newbuf, newlen);
}

void ByteArray::CopyOther(const unsigned char * otherbuff, unsigned int otherbufflen){
    FlushInternalMem();
    Alloc(otherbufflen);
    memcpy(m_internalcontents, otherbuff, otherbufflen);
}

unsigned int ByteArray::ExpandBy(unsigned int amount){
    unsigned char *backupbuff = static_cast<unsigned char*>(calloc(m_internallength, sizeof(unsigned char)));
    memcpy(backupbuff, m_internalcontents, m_internallength);
    unsigned int backuplen = m_internallength;
    FlushInternalMem();
    Alloc(backuplen+amount);
    memcpy(m_internalcontents, backupbuff, backuplen);
    free(backupbuff);
    return backuplen;
}

void ByteArray::FlushInternalMem(){
    free(m_internalcontents);
    m_internalcontents = nullptr;
    m_internallength = 0;
}

void ByteArray::InitInternalMem(){
    m_internalcontents = nullptr;
    m_internallength = 0;
}

void ByteArray::Clear(){
    FlushInternalMem();
    InitInternalMem();
}

void ByteArray::Alloc(unsigned int amount){
    m_internalcontents = static_cast<unsigned char*>(calloc(amount, sizeof(unsigned char)));
    m_internallength = amount;
}

std::string ByteArray::GetHexString() const {
    std::string strRet = HexStrFromBuffer(m_internalcontents, m_internallength);
    return strRet;
}

} // ns: boxutil
