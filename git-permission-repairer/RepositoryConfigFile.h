#ifndef _REPOSITORYCONFIGFILE_H
#define _REPOSITORYCONFIGFILE_H
#include <string>
/// \file RepositoryConfigFile.h
/// \brief A class that represents a repository config file.
/// \author Phitherek_
/// \date 2013
/// \version 0.1

/// \namespace GitPermissionRepairer
/// \brief A global namespace for Git Permission Repairer.
namespace GitPermissionRepairer {
/// \class RepositoryConfigFile
/// \brief A class that represents a repository config file.
class RepositoryConfigFile {
private:
	std::string _path;	
	std::string _reponame;
	std::string _repodir;
	std::string _userown;
	std::string _groupown;
public:
	RepositoryConfigFile(std::string path); ///< \brief A constructor with parameter.
	///< It tries to load and parse the repository config file. It throws FileException or ParseException.
	///< \param path A path to repository config file.
	std::string getRepositoryName(); ///< \brief A function returning repository name.
	///< \return Repository name.
	std::string getRepositoryPath(); ///< \brief A function returning repository path.
	///< \return Repository path.
	std::string getOwningUser(); ///< \brief A function returning repository owning user.
	///< \return Repository owning user.
	std::string getOwningGroup(); ///< \brief A function returning repository owning group.
	///< \return Repository owning group.
};
}
#endif
