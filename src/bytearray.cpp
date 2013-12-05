
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

ByteArray::ByteArray(const ByteArray &_other){
	InitInternalMem();
	CopyOther(_other);
}

ByteArray::ByteArray(pcbyte _buff, uint32 _buffsize){
	InitInternalMem();
	CopyOther(_buff, _buffsize);
}

ByteArray& ByteArray::operator= (const ByteArray &_other){
	CopyOther(_other);
	return *this;
}

ByteArray::~ByteArray(){
	FlushInternalMem();
}

pcbyte ByteArray::GetBuffer() const {
	return internalcontents;
}

ByteArray ByteArray::GetCopy() const {
	return ByteArray(internalcontents, internallength);
}

uint32 ByteArray::GetLength() const {
	return internallength;
}

ByteArray ByteArray::GetSection(const uint32 _offset, const uint32 _length){

	if (_offset > internallength || _length > internallength || (_offset+_length) > internallength){
		RAISE_EXCEPT(ExceptionBase, "Range not within bounds");
	}

	ByteArray retcopy(internalcontents+_offset, _length);
	return retcopy;
}

void ByteArray::Append(const ByteArray &_other){
	uint32 offset_free = ExpandBy(_other.GetLength());
	memcpy(internalcontents+offset_free, _other.GetBuffer(), _other.GetLength());
}

void ByteArray::Append(pcbyte _buff, uint32 _buffsize){
	uint32 offset_free = ExpandBy(_buffsize);
	memcpy(internalcontents+offset_free, _buff, _buffsize);
}

void ByteArray::EraseSection(const uint32 _offset, const uint32 _length){

	if (_offset > internallength || _length > internallength || (_offset+_length) > internallength){
		RAISE_EXCEPT(ExceptionBase, "Range not within bounds");
	}

	uint32 len_low = _offset;
	uint32 len_high = internallength-_offset-_length;

	pbyte backup_low = static_cast<pbyte>(calloc(len_low, sizeof(byte)));
	pbyte backup_high = static_cast<pbyte>(calloc(len_high, sizeof(byte)));

	memcpy(backup_low, internalcontents, len_low);
	memcpy(backup_high, internalcontents+internallength-len_high, len_high);

	FlushInternalMem();
	Alloc(len_low+len_high);

	memcpy(internalcontents, backup_low, len_low);
	memcpy(internalcontents+len_low, backup_high, len_high);

	free(backup_low);
	free(backup_high);

}

void ByteArray::CopyOther(const ByteArray  &_other){
	FlushInternalMem();
	uint32 newlen = _other.GetLength();
	pcbyte newbuf = _other.GetBuffer();
	Alloc(newlen);
	memcpy(internalcontents, newbuf, newlen); 
}

void ByteArray::CopyOther(pcbyte _otherbuff, uint32 _otherbufflen){
	FlushInternalMem();
	Alloc(_otherbufflen);
	memcpy(internalcontents, _otherbuff, _otherbufflen); 
}

uint32 ByteArray::ExpandBy(uint32 _amount){
	pbyte backupbuff = static_cast<pbyte>(calloc(internallength, sizeof(byte)));
	memcpy(backupbuff, internalcontents, internallength);
	uint32 backuplen = internallength;
	FlushInternalMem();
	Alloc(backuplen+_amount);
	memcpy(internalcontents, backupbuff, backuplen);
	free(backupbuff);
	return backuplen;
}

void ByteArray::FlushInternalMem(){
	if (internalcontents){
		free(internalcontents);
		internalcontents = NULL;
		internallength = 0;
	}
}

void ByteArray::InitInternalMem(){
	internalcontents = NULL;
	internallength = 0;
}

void ByteArray::Clear(){
	FlushInternalMem();
	InitInternalMem();
}

void ByteArray::Alloc(uint32 _amount){
	internalcontents = static_cast<pbyte>(calloc(_amount, sizeof(byte)));
	internallength = _amount;
}

std::string ByteArray::GetHexString() const {
	std::string strRet = HexStrFromBuffer(internalcontents, internallength);
	return strRet;
}

