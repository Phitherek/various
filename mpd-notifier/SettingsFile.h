#ifndef _SETTINGSFILE_H
#define _SETTINGSFILE_H
#include <string>
/// \file SettingsFile.h
/// \brief A class to access MPDNotifier' s settings file.
/// \author Phitherek_
/// \date 2013
/// \version 0.1

/// \namespace MPDNotifier
/// \brief A global namespace for MPDNotifier.
namespace MPDNotifier {
/// \class SettingsFile
/// \brief A class to access MPDNotifier' s settings file.
class SettingsFile {
private:
	std::string _path;
	std::string _host;
	int _port;
	int _connectionTimeout;
	int _statusChangeTimeout;
	int _errorTimeout;
public:
	SettingsFile(); ///< A default constructor - use to create and overwrite settings file.
	SettingsFile(std::string path); ///< \brief A constructor that opens and parses existing settings file.
	/// \param path Settings file path.
	void setPath(std::string path); ///< \brief A function that sets settings file path - use to create and overwrite settings file.
	///< \param path Settings file path.
	void setHost(std::string host); ///< \brief A function that sets MPD host to connect.
	///< \param host MPD hostname.
	void setPort(int port); ///< \brief A function that sets MPD port to connect.
	///< \param port MPD port.
	void setConnectionTimeout(int timeout); ///< \brief A function that sets MPD connection timeout.
	///< \param timeout MPD connection timeout [ms].
	void setStatusChangeTimeout(int timeout); ///< \brief A function that sets timeout of status change notification.
	///< \param timeout Timeout of status change notification [ms].
	void setErrorTimeout(int timeout); ///< \brief A function that sets timeout of error notification.
	///< \param timeout Timeout of error notification.
	std::string getHost(); ///< \brief A function that returns MPD hostname.
	///< \return MPD hostname.
	int getPort(); ///< \brief A function that returns MPD port.
	///< \return MPD port.
	int getConnectionTimeout(); ///< \brief A function that returns MPD connection timeout.
	///< \return MPD connection timeout [ms].
	int getStatusChangeTimeout(); ///< \brief A function that returns timeout of status change notification.
	///< \return Timeout of status change notification [ms].
	int getErrorTimeout(); ///< \brief A function that returns timeout of error notification.
	///< \return Timeout of error notification [ms].
	void write(); ///< A function that writes settings to the settings file.
	void display(); ///< A function that displays settings.
};
}
#endif
