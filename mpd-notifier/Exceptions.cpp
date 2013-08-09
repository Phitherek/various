#include "Exceptions.h"
using namespace MPDNotifier;

ConnectionException::ConnectionException(std::string what) {
	_what = what;
}

ConnectionException::~ConnectionException() throw() {
	_what = "";
}

const char* ConnectionException::what() const throw() {
	return _what.c_str();
}

NotifyException::NotifyException(std::string what) {
	_what = what;
}

NotifyException::~NotifyException() throw() {
	_what = "";
}

const char* NotifyException::what() const throw() {
	return _what.c_str();
}

SettingsException::SettingsException(std::string what) {
	_what = what;
}

SettingsException::~SettingsException() throw() {
	_what = "";
}

const char* SettingsException::what() const throw() {
	return _what.c_str();
}
