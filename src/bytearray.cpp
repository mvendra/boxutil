
#include "types.h"
#include "exceptionbase.h"
#include "bytearray.h"
#include "stringmanip.h"

#include <cstdio>
#include <cstring>
#include <cstdlib>

ByteArray::ByteArray(){
  InitInternalMem();
}

ByteArray::ByteArray(const ByteArray &other){
  InitInternalMem();
  CopyOther(other);
}

ByteArray::ByteArray(pcbyte buff, uint32 buffsize){
  InitInternalMem();
  CopyOther(buff, buffsize);
}

ByteArray& ByteArray::operator= (const ByteArray &other){
    if (this == &other) return *this;
  CopyOther(other);
  return *this;
}

ByteArray::~ByteArray(){
  FlushInternalMem();
}

pcbyte ByteArray::GetBuffer() const {
  return m_internalcontents;
}

ByteArray ByteArray::GetCopy() const {
  return ByteArray(m_internalcontents, m_internallength);
}

uint32 ByteArray::GetLength() const {
  return m_internallength;
}

ByteArray ByteArray::GetSection(const uint32 offset, const uint32 length){

  if (offset > m_internallength || length > m_internallength || (offset+length) > m_internallength){
    RAISE_EXCEPT(ExceptionBase, "Range not within bounds");
  }

  ByteArray retcopy(m_internalcontents+offset, length);
  return retcopy;
}

void ByteArray::Append(const ByteArray &other){
  uint32 offset_free = ExpandBy(other.GetLength());
  memcpy(m_internalcontents+offset_free, other.GetBuffer(), other.GetLength());
}

void ByteArray::Append(pcbyte buff, uint32 buffsize){
  uint32 offset_free = ExpandBy(buffsize);
  memcpy(m_internalcontents+offset_free, buff, buffsize);
}

void ByteArray::EraseSection(const uint32 offset, const uint32 length){

  if (offset > m_internallength || length > m_internallength || (offset+length) > m_internallength){
    RAISE_EXCEPT(ExceptionBase, "Range not within bounds");
  }

  uint32 len_low = offset;
  uint32 len_high = m_internallength-offset-length;

  pbyte backup_low = static_cast<pbyte>(calloc(len_low, sizeof(byte)));
  pbyte backup_high = static_cast<pbyte>(calloc(len_high, sizeof(byte)));

  memcpy(backup_low, m_internalcontents, len_low);
  memcpy(backup_high, m_internalcontents+m_internallength-len_high, len_high);

  FlushInternalMem();
  Alloc(len_low+len_high);

  memcpy(m_internalcontents, backup_low, len_low);
  memcpy(m_internalcontents+len_low, backup_high, len_high);

  free(backup_low);
  free(backup_high);

}

void ByteArray::CopyOther(const ByteArray  &other){
  FlushInternalMem();
  uint32 newlen = other.GetLength();
  pcbyte newbuf = other.GetBuffer();
  Alloc(newlen);
  memcpy(m_internalcontents, newbuf, newlen); 
}

void ByteArray::CopyOther(pcbyte otherbuff, uint32 otherbufflen){
  FlushInternalMem();
  Alloc(otherbufflen);
  memcpy(m_internalcontents, otherbuff, otherbufflen); 
}

uint32 ByteArray::ExpandBy(uint32 amount){
  pbyte backupbuff = static_cast<pbyte>(calloc(m_internallength, sizeof(byte)));
  memcpy(backupbuff, m_internalcontents, m_internallength);
  uint32 backuplen = m_internallength;
  FlushInternalMem();
  Alloc(backuplen+amount);
  memcpy(m_internalcontents, backupbuff, backuplen);
  free(backupbuff);
  return backuplen;
}

void ByteArray::FlushInternalMem(){
  if (m_internalcontents){
    free(m_internalcontents);
    m_internalcontents = NULL;
    m_internallength = 0;
  }
}

void ByteArray::InitInternalMem(){
  m_internalcontents = NULL;
  m_internallength = 0;
}

void ByteArray::Clear(){
  FlushInternalMem();
  InitInternalMem();
}

void ByteArray::Alloc(uint32 amount){
  m_internalcontents = static_cast<pbyte>(calloc(amount, sizeof(byte)));
  m_internallength = amount;
}

std::string ByteArray::GetHexString() const {
  std::string strRet = HexStrFromBuffer(m_internalcontents, m_internallength);
  return strRet;
}

