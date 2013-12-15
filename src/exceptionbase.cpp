
#include "exceptionbase.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

ExceptionBase::ExceptionBase(const ExceptionBase &other):m_message(NULL), m_function(NULL), m_line(0)
{

	SetMsg(other.GetMessage());
	SetFunc(other.GetFunction());
	SetLine(other.GetLine());

}

ExceptionBase::ExceptionBase(const char8 *msg, const char8 *func, uint32 line):m_message(NULL), m_function(NULL), m_line(0)
{

	SetMsg(msg);
	SetFunc(func);
	SetLine(line);

}

ExceptionBase::~ExceptionBase(){

	if (m_message != NULL){
		free(m_message);
	}
	if (m_function != NULL){
		free(m_function);
	}

}


const char8 *ExceptionBase::GetMessage() const {
	return this->m_message;
}

const char8 *ExceptionBase::GetFunction() const {
	return this->m_function;
}

uint32 ExceptionBase::GetLine() const {
	return this->m_line;
}


void ExceptionBase::SetMsg(const char8 *newmsg){
	if (m_message){
		free(m_message);
		m_message = NULL;
	}
	uint32 msglen = strlen(newmsg);
	m_message = static_cast<char8*>(calloc(msglen+1, sizeof(char8)));
	strncpy(m_message, newmsg, msglen);
}

void ExceptionBase::SetFunc(const char8 *newfunc){
	if (m_function){
		free(m_function);
		m_function = NULL;
	}
	uint32 funclen = strlen(newfunc);
	m_function = static_cast<char8*>(calloc(funclen+1, sizeof(char8)));
	strncpy(m_function, newfunc, funclen);
}

void ExceptionBase::SetLine(uint32 line){
	this->m_line = line;
}

