#ifndef _EXCEPTIONS_H
#define _EXCEPTIONS_H
#include <string>
#include <exception>
/// \file Exceptions.h
/// \brief A common header file that defines exceptions for Git Permission Repairer
/// \author Phitherek_
/// \date 2013
/// \version 0.1

/// \namespace GitPermissionRepairer
/// \brief A global namespace for Git Permission Repairer
namespace GitPermissionRepairer {
/// \class ParseException
/// \brief An exception to be thrown on parse error.
class ParseException: public std::exception {
private:
	std::string _what;
public:
	ParseException(std::string what); ///< \brief A constructor with parameter.
	///< \param what Error message.
	~ParseException() throw(); ///< A destructor, as needed by std::exception.
	const char* what() const throw(); ///< \brief A function returning error message.
	///< \return Error message.
};
/// \class FileException
/// \brief An exception to be thrown on file I/O error.
class FileException: public std::exception {
private:
	std::string _what;
public:
	FileException(std::string what); ///< \brief A constructor with parameter.
	///< \param what Error message.
	~FileException() throw(); ///< A destructor, as needed by std::exception.
	const char* what() const throw(); ///< \brief A function returning error message.
	///< \return Error message.
};
}
#endif
