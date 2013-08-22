#include "Exceptions.h"
#include "ConfigFile.h"
#include "RepositoryConfigFile.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <unistd.h>
using namespace std;

int main(int argc, char** argv) {
cout << "Git Permission Repairer v. 0.1.1 (C) 2013 by Phitherek_" << endl;
string home = getenv("HOME");
string confdir;
confdir = home + "/.git-permission-repairer/global.config";
try {
cout << "Reading config..." << endl;
GitPermissionRepairer::ConfigFile conf(confdir);
cout << "Config read successfully!" << endl;
vector<GitPermissionRepairer::RepositoryConfigFile> rcfvec;
if(argc < 1) {
	cout << "Usage: " << argv[0] << " [repository names ...]" << endl;
	return EXIT_SUCCESS;
} else if(argc == 1) {
	cout << "Starting full repair..." << endl;
	while(!conf.contentAtEnd()) {
		GitPermissionRepairer::ConfigFileEntry cfe;
		cfe = conf.getNextConfigFileEntry();
		if(!cfe.empty()) {
			cout << "Adding: " << cfe.reponame << endl;
			GitPermissionRepairer::RepositoryConfigFile rcf(cfe.repoconfpath);
			cout << "Repository config read successfully!" << endl;
			rcfvec.push_back(rcf);
		}
	}
	cout << "Done adding!" << endl;
} else {
	cout << "Starting repair of repositories:" << endl;
	for(int i = 1; i < argc; i++) {
		cout << argv[i] << endl;
	}
	for(int i = 1; i < argc; i++) {
		GitPermissionRepairer::ConfigFileEntry cfe;
		cfe = conf.getConfigFileEntryByRepositoryName(argv[i]);
		if(!cfe.empty()) {
			cout << "Adding: " << cfe.reponame << endl;
			GitPermissionRepairer::RepositoryConfigFile rcf(cfe.repoconfpath);
			cout << "Repository config read successfully!" << endl;
			rcfvec.push_back(rcf);
		} else {
			cerr << "Repository " << argv[i] << " not found!" << endl;
		}
	}
	cout << "Done adding!" << endl;
}
for(unsigned int i = 0; i < rcfvec.size(); i++) {
cout << "Processing: " << rcfvec[i].getRepositoryName() << "..." << endl;
string cmd = "";
cout << "cd..." << endl;
chdir(rcfvec[i].getRepositoryPath().c_str());
cout << "git checkout master..." << endl;
cmd = "git checkout master";
system(cmd.c_str());
cmd = "";
cout << "chown..." << endl;
cmd += "chown ";
cmd += rcfvec[i].getOwningUser();
cmd += ":";
cmd += rcfvec[i].getOwningGroup();
cmd += " -R *";
system(cmd.c_str());
cmd = "";
cout << "chmod..." << endl;
cmd += "chmod ug+rwx -R *";
system(cmd.c_str());
cmd = "";
cout << "cd .git..." << endl;
chdir(".git");
cout << "chown..." << endl;
cmd += "chown ";
cmd += rcfvec[i].getOwningUser();
cmd += ":";
cmd += rcfvec[i].getOwningGroup();
cmd += " -R *";
system(cmd.c_str());
cmd = "";
cout << "chmod..." << endl;
cmd += "chmod ug+rwx -R *";
system(cmd.c_str());
cmd = "";
cout << "cd .. ..." << endl;
chdir("..");
cout << "git commit..." << endl;
cmd = "git commit -a -m 'auto-commit by git-permission-repairer'";
system(cmd.c_str());
cmd = "";
cout << "chown..." << endl;
cmd += "chown ";
cmd += rcfvec[i].getOwningUser();
cmd += ":";
cmd += rcfvec[i].getOwningGroup();
cmd += " -R *";
system(cmd.c_str());
cmd = "";
cout << "cd .git..." << endl;
chdir(".git");
cout << "chown..." << endl;
cmd += "chown ";
cmd += rcfvec[i].getOwningUser();
cmd += ":";
cmd += rcfvec[i].getOwningGroup();
cmd += " -R *";
system(cmd.c_str());
cmd = "";
cout << "cd .. ..." << endl;
chdir("..");
cout << "git checkout local..." << endl;
cmd = "git checkout local";
system(cmd.c_str());
cmd = "";
cout << "cd..." << endl;
chdir("");
cout << "Done!" << endl;
}
cout << "All done! Thank you for using Git Permission Repairer!" << endl;
return EXIT_SUCCESS;
} catch(GitPermissionRepairer::FileException& exc) {
	cerr << "FileException occured: " << exc.what() << endl;
	return 1;
} catch(GitPermissionRepairer::ParseException& exc) {
	cerr << "ParseException occured: " << exc.what() << endl;
	return 2;
}
}
