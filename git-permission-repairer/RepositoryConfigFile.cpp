#include "RepositoryConfigFile.h"
#include "Exceptions.h"
#include <fstream>
using namespace GitPermissionRepairer;

RepositoryConfigFile::RepositoryConfigFile(std::string path) {
	_path = path;
	_reponame = "";
	_repodir = "";
	_userown = "";
	_groupown = "";
	std::ifstream in(_path.c_str());
	if(!in) {
		std::string err = "";
		err += "Could not open file: ";
		err += _path;
		err += "!";
		throw FileException(err);
	}
	while(!in.eof()) {
		std::string line = "";
		std::string action = "parse";
		char c;
		do {
			in.get(c);
			line += c;
		} while (c != '\n' && in);
		if(!in) {
			break;
		}
		if(action == "parse") {
			if(line[0] == '[') {
				std::string tmpstr = "";
				for(int i = 1; i < line.length() && line[i] != ']'; i++) {
					tmpstr += line[i];
				}
				if(tmpstr != "name" && tmpstr != "directory" && tmpstr != "user" && tmpstr !="group" && tmpstr != "end") {
					std::string err = "";
					err += "Found: ";
					err += tmpstr;
					err += " but expected: name, directory, user or group!";
					throw ParseException(err);
				}
				action = tmpstr;
			} else {
				throw ParseException("Expected name, directory, user or group in []!");
			}
		} else if(action == "name") {
			if(line == "" || line[0] == '[') {
				throw ParseException("Expected repository name!");
			}
			_reponame = line;
			action = "parse";
		} else if(action == "directory") {
			if(line == "" || line[0] == '[') {
				throw ParseException("Expected repository directory path!");
			}
			_repodir = line;
			action = "parse";
		} else if(action == "user") {
			if(line == "" || line[0] == '[') {
				throw ParseException("Expected repository owning user!");
			}
			_userown = line;
			action = "parse";
		} else if(action == "group") {
			if(line == "" || line[0] == '[') {
				throw ParseException("Expected repository owning group!");
			}
			_groupown = line;
			action = "parse";
		} else if(action == "end") {
			if(_reponame == "" || _repodir == "" || _userown == "" || _groupown == "") {
				throw ParseException("Data error!");
			} else {
				break;
			}
		} else {
			throw ParseException("Unknown action: " + action + "!");
		}
	}
	in.close();
}

std::string RepositoryConfigFile::getRepositoryName() {
	return _reponame;
}

std::string RepositoryConfigFile::getRepositoryPath() {
	return _repodir;
}

std::string RepositoryConfigFile::getOwningUser() {
	return _userown;
}

std::string RepositoryConfigFile::getOwningGroup() {
	return _groupown;
}
