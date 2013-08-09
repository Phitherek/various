#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include "SettingsFile.h"
#include "Exceptions.h"
using namespace std;

int main() {
cout << "MPDNotifier Configuration v. 0.1 (c) 2013 by Phitherek_" << endl;
std::string home = getenv("HOME");
std::string path = home + "/.mpd-notifier/config";
cout << "Config path: " << path << endl;
try {
MPDNotifier::SettingsFile settings;
settings.setPath(path);
cout << "Default configuration: " << endl;
settings.display();
char sel;
cout << "Do you want to write it? (y/N) ";
cin >> sel;
if(sel == 'y') {
	settings.write();
} else {
	do {
	std::string host;
	int port;
	int connectionTimeout;
	int statusChangeTimeout;
	int errorTimeout;
	cout << "Enter MPD hostname: ";
	cin >> host;
	cout << "Enter MPD port: ";
	cin >> port;
	cout << "Enter MPD connection timeout [in ms]: ";
	cin >> connectionTimeout;
	cout << "Enter status change notification timeout [in ms]: ";
	cin >> statusChangeTimeout;
	cout << "Enter error notification timeout [in ms]: ";
	cin >> errorTimeout;
	settings.setHost(host);
	settings.setPort(port);
	settings.setConnectionTimeout(connectionTimeout);
	settings.setStatusChangeTimeout(statusChangeTimeout);
	settings.setErrorTimeout(errorTimeout);
	cout << "Entered settings:" << endl;
	settings.display();
	cout << "Is this OK? (y/N) ";
	cin >> sel;
	} while(sel != 'y');
	settings.write();
}
} catch(MPDNotifier::SettingsException &exc) {
	cout << "SettingsException occured: " << exc.what() << endl;
	return EXIT_FAILURE;
}
cout << "Your configuration has been successfully written! You can now start using MPDNotifier." << endl;
return EXIT_SUCCESS;
}
