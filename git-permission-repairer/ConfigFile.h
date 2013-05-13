#ifndef _CONFIGFILE_H
#define _CONFIGFILE_H
#include <string>
#include <vector>
/// \file ConfigFile.h
/// \brief A class that represents Git Permission Repairer' s config file.
/// \author Phitherek_
/// \date 2013
/// \version 0.1

/// \namespace GitPermissionRepairer
/// \brief A global namespace for Git Permission Repairer
namespace GitPermissionRepairer {
/// \struct ConfigFileEntry
/// \brief A structure that represents a config file entry.
struct ConfigFileEntry {
	std::string reponame; ///< Name of the repository.
	std::string repoconfpath; ///< Path to repository config file.
	ConfigFileEntry(); ///< A constructor for initializing the structure.
	bool empty(); ///< \brief A function that checks if the structure is empty.
	///< \return True if the structure is empty, false otherwise.
};
/// \class ConfigFile
/// \brief A class that represents Git Permission Repairer' s config file.
class ConfigFile {
private:
	std::vector<ConfigFileEntry> _content;
	int _contentIterator;
	bool _contentEnd;
	std::string _confpath;
public:
	ConfigFile(std::string confpath); ///< \brief A constructor with parameter.
	///< It tries to load and parse config file from given path. Throws FileException or ParseException.
	///< \param confpath Config path.
	ConfigFileEntry getNextConfigFileEntry(); ///< \brief A function that returns next ConfigFileEntry.
	///< \return Next ConfigFileEntry object.
	ConfigFileEntry getConfigFileEntryByRepositoryName(std::string reponame); ///< \brief A function that returns a ConfigFileEntry for a repository of given name or empty ConfigFileEntry object on failure.
	///< \param reponame Repository name.
	///< \return A ConfigFileEntry for a repository of given name or empty ConfigFileEntry object on failure
	void resetContentIterator(); ///< A function resetting content iterator.
	bool contentAtEnd(); ///< \brief A function checking if a content iterator is at the end.
	///< \return True if content iterator is at the end, false otherwise.
};
}
#endif
