
#include "exceptionbase.h"
#include "stringmanip.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

namespace boxutil {

ExceptionBase::ExceptionBase(const ExceptionBase &other):m_message(nullptr), m_function(nullptr), m_line(0){
    SetMsg(other.GetMessage());
    SetFunc(other.GetFunction());
    SetLine(other.GetLine());
}

ExceptionBase::ExceptionBase(const ExceptionBase &&other):m_message(nullptr), m_function(nullptr), m_line(0){
    SetMsg(other.GetMessage());
    SetFunc(other.GetFunction());
    SetLine(other.GetLine());
}

ExceptionBase::ExceptionBase(const char *msg, const char * func, unsigned int line):m_message(nullptr), m_function(nullptr), m_line(0){
    SetMsg(msg);
    SetFunc(func);
    SetLine(line);
}

ExceptionBase::~ExceptionBase(){
    free(m_message);
    free(m_function);
}

const char *ExceptionBase::GetMessage() const {
    return this->m_message;
}

const char *ExceptionBase::GetFunction() const {
    return this->m_function;
}

unsigned int ExceptionBase::GetLine() const {
    return this->m_line;
}

void ExceptionBase::SetMsg(const char *newmsg){
    free(m_message);
    m_message = nullptr;
    unsigned int msglen = strlen(newmsg);
    m_message = static_cast<char *>(calloc(msglen+1, sizeof(char)));
	custom_strncpy_s(m_message, msglen + 1, newmsg, msglen);
}

void ExceptionBase::SetFunc(const char * newfunc){
    free(m_function);
    m_function = nullptr;
    unsigned int funclen = strlen(newfunc);
    m_function = static_cast<char *>(calloc(funclen+1, sizeof(char)));
	custom_strncpy_s(m_function, funclen + 1, newfunc, funclen);
}

void ExceptionBase::SetLine(unsigned int line){
    this->m_line = line;
}

} // ns: boxutil
