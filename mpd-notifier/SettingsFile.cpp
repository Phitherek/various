#include "SettingsFile.h"
#include "Exceptions.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace MPDNotifier;

SettingsFile::SettingsFile() {
	_path = "";
	_host = "localhost";
	_port = 6600;
	_connectionTimeout = 60000;
	_statusChangeTimeout = 10000;
	_errorTimeout = 30000;
}

SettingsFile::SettingsFile(std::string path) {
	_path = path;
	std::ifstream in(path.c_str());
	if(!in) {
		throw SettingsException("Could not open settings file from given path!");
	}
	std::string action = "parse";
	while(!in.eof()) {
		std::string line = "";
		in >> line;
		if(in) {
			if(action == "parse") {
			if(line[0] == '[') {
				std::string command = "";
				for(int i = 1; i < line.length() && line[i] != ']'; i++) {
					command += line[i];
				}
				if(command == "hostname" || command == "port" || command == "connectiontimeout" || command == "statuschangetimeout" || command == "errortimeout") {
					action = command;
				} else {
					throw SettingsException("Parse error: Unknown command!");
				}
			} else {
				throw SettingsException("Parse error: Expected command!");
			}
			} else if(action == "hostname") {
				_host = line;
				action = "parse";
			} else if(action == "port") {
				_port = atoi(line.c_str());
				action = "parse";
			} else if(action == "connectiontimeout") {
				_connectionTimeout = atoi(line.c_str());
				action = "parse";
			} else if(action == "statuschangetimeout") {
				_statusChangeTimeout = atoi(line.c_str());
				action = "parse";
			} else if(action == "errortimeout") {
				_errorTimeout = atoi(line.c_str());
				action = "parse";
			} else {
				throw SettingsException("Parse error: Unknown action!");
			}
		}
	}
	in.close();
}

void SettingsFile::setPath(std::string path) {
	_path = path;
}

void SettingsFile::setHost(std::string host) {
	_host = host;
}

void SettingsFile::setPort(int port) {
	_port = port;
}

void SettingsFile::setConnectionTimeout(int timeout) {
	_connectionTimeout = timeout;
}

void SettingsFile::setStatusChangeTimeout(int timeout) {
	_statusChangeTimeout = timeout;
}

void SettingsFile::setErrorTimeout(int timeout) {
	_errorTimeout = timeout;
}

std::string SettingsFile::getHost() {
	return _host;
}

int SettingsFile::getPort() {
	return _port;
}

int SettingsFile::getConnectionTimeout() {
	return _connectionTimeout;
}

int SettingsFile::getStatusChangeTimeout() {
	return _statusChangeTimeout;
}

int SettingsFile::getErrorTimeout() {
	return _errorTimeout;
}

void SettingsFile::write() {
	std::ofstream out(_path.c_str());
	if(!out) {
		throw SettingsException("Could not write settings file to given path!");
	}
	out << "[hostname]" << std::endl << _host << std::endl << "[port]" << std::endl << _port << std::endl << "[connectiontimeout]" << std::endl << _connectionTimeout << std::endl << "[statuschangetimeout]" << std::endl << _statusChangeTimeout << std::endl << "[errortimeout]" << std::endl << _errorTimeout;
	out.close();
	}

void SettingsFile::display() {
	std::cout << "MPD hostname: " << _host << std::endl << "MPD port: " << _port << std::endl << "MPD connection timeout [ms]: " << _connectionTimeout << std::endl << "Status change notification timeout [ms]: " << _statusChangeTimeout << std::endl << "Error notification timeout [ms]: " << _errorTimeout << std::endl;
}
