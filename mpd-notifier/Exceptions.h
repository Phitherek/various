#ifndef _EXCEPTIONS_H
#define _EXCEPTIONS_H
#include <exception>
#include <string>
/// \file Exceptions.h
/// \brief Defines MPDNotifier exceptions.
/// \author Phitherek_
/// \date 2013
/// \version 0.1

/// \namespace MPDNotifier
/// \brief A global namespace for MPDNotifier.
namespace MPDNotifier {
/// \class ConnectionException
/// \brief An exception to be thrown when connection fails.
class ConnectionException: public std::exception {
private:
	std::string _what;
public:
	ConnectionException(std::string what); ///< \brief A constructor.
	///< \param what Error message.
	~ConnectionException() throw(); ///< A destructor, as needed by std::exception.
	const char* what() const throw(); ///< \brief A function returning error message.
	///< \return Error message.
};
/// \class NotifyException
/// \brief An exception to be thrown on libnotify error.
class NotifyException: public std::exception {
private:
	std::string _what;
public:
	NotifyException(std::string what); ///< \brief A constructor.
	///< \param what Error message.
	~NotifyException() throw(); ///< A destructor, as needed by std::exception.
	const char* what() const throw(); ///< \brief A function returning error message.
	///< \return Error message.
};
/// \class SettingsException
/// \brief An exception to be thrown on settings file error.
class SettingsException: public std::exception {
private:
	std::string _what;
public:
	SettingsException(std::string what); ///< \brief A constructor.
	///< \param what Error message.
	~SettingsException() throw(); ///< A destructor, as needed by std::exception.
	const char* what() const throw(); ///< \brief A function returning error message.
	///< \return Error message.
};
}
#endif
