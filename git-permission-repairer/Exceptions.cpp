#include "Exceptions.h"
using namespace GitPermissionRepairer;

ParseException::ParseException(std::string what) {
	_what = what;
}

ParseException::~ParseException() throw() {
	_what = "";	
}

const char* ParseException::what() const throw() {
	return _what.c_str();
}

FileException::FileException(std::string what) {
	_what = what;
}

FileException::~FileException() throw() {
	_what = "";	
}

const char* FileException::what() const throw() {
	return _what.c_str();
}
