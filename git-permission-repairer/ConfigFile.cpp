#include "ConfigFile.h"
#include "Exceptions.h"
#include <fstream>
using namespace GitPermissionRepairer;

ConfigFileEntry::ConfigFileEntry() {
	reponame = "";
	repoconfpath = "";
}

bool ConfigFileEntry::empty() {
	if(reponame == "" && repoconfpath == "") {
		return true;
	}
	return false;
}

ConfigFile::ConfigFile(std::string path) {
	_confpath = path;
	_contentIterator = -1;
	_contentEnd = false;                
	std::ifstream conf(_confpath.c_str());
	if(!conf) {
		std::string err = "";
		err += "Could not open file: ";
		err += _confpath;
		err += "!";
		throw FileException(err);
	}
	ConfigFileEntry tmpcfe;
	while(!conf.eof()) {
		std::string line = "";
		char c;
		do {
			conf.get(c);
			line += c;
		} while (c != '\n' && conf);
		if(!conf) {
			break;
		}
		if(line[0] == '[') {
			std::string tmpstr = "";
			for(int i = 1; i < line.length() && line[i] != ']'; i++) {
				tmpstr += line[i];
			}
			if(tmpstr != "") {
				if(tmpcfe.reponame != "") {
					throw ParseException("Expected repository config path without []!");
				}
				tmpcfe.reponame = tmpstr;
				tmpstr = "";
			} else {
				throw ParseException("Expected name of repository in []!");
			}
		} else {
			if(line == "") {
				throw ParseException("Expected repository config path!");
			}
			if(tmpcfe.reponame == "") {
				throw ParseException("Name of repository cannot be empty!");
			}
			tmpcfe.repoconfpath = line;
			_content.push_back(tmpcfe);
			tmpcfe.reponame = "";
			tmpcfe.repoconfpath = "";
		}
	}
	conf.close();
}

ConfigFileEntry ConfigFile::getNextConfigFileEntry() {
	if(_contentIterator+1 < _content.size()) {
		_contentIterator++;
		return _content[_contentIterator];
	} else {
		_contentEnd = true;
		static ConfigFileEntry emptycfe;
		return emptycfe;
	}
}

ConfigFileEntry ConfigFile::getConfigFileEntryByRepositoryName(std::string reponame) {
	for(int i = 0; i < _content.size(); i++) {
		if(_content[i].reponame == reponame) {
			return _content[i];
		}
	}
	static ConfigFileEntry emptycfe;
	return emptycfe;
}

void ConfigFile::resetContentIterator() {
	if(_contentEnd) {
		_contentEnd = false;
	}
	_contentIterator = -1;
}

bool ConfigFile::contentAtEnd() {
	return _contentEnd;
}
