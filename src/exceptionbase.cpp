
#include "exceptionbase.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

ExceptionBase::ExceptionBase(const ExceptionBase &_other):message(NULL), function(NULL), line(0)
{

	SetMsg(_other.GetMessage());
	SetFunc(_other.GetFunction());
	SetLine(_other.GetLine());

}

ExceptionBase::ExceptionBase(const char8 *_msg, const char8 *_func, uint32 _line):message(NULL), function(NULL), line(0)
{

	SetMsg(_msg);
	SetFunc(_func);
	SetLine(_line);

}

ExceptionBase::~ExceptionBase(){

	if (message != NULL){
		free(message);
	}
	if (function != NULL){
		free(function);
	}

}


const char8 *ExceptionBase::GetMessage() const {
	return this->message;
}

const char8 *ExceptionBase::GetFunction() const {
	return this->function;
}

uint32 ExceptionBase::GetLine() const {
	return this->line;
}


void ExceptionBase::SetMsg(const char8 *_newmsg){
	if (message){
		free(message);
		message = NULL;
	}
	uint32 msglen = strlen(_newmsg);
	message = static_cast<char8*>(calloc(msglen+1, sizeof(char8)));
	strncpy(message, _newmsg, msglen);
}

void ExceptionBase::SetFunc(const char8 *_newfunc){
	if (function){
		free(function);
		function = NULL;
	}
	uint32 funclen = strlen(_newfunc);
	function = static_cast<char8*>(calloc(funclen+1, sizeof(char8)));
	strncpy(function, _newfunc, funclen);
}

void ExceptionBase::SetLine(uint32 _line){
	this->line = _line;
}

