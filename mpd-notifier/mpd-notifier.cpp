#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include "Exceptions.h"
#include "SettingsFile.h"
#include "MPDTrackDescription.h"
#include "NotifyEngine.h"
using namespace std;

int main() {
	cout << "MPDNotifier v. 0.2 (c) 2013 by Phitherek_" << endl;
	try {
		std::string home = getenv("HOME");
		std::string path = home + "/.mpd-notifier/config";
		MPDNotifier::SettingsFile settings(path);
		cout << "Configuration loaded successfully!" << endl;
		MPDNotifier::MPDTrackDescription track(settings.getHost(), settings.getPort(), settings.getConnectionTimeout());
		cout << "MPD connection initiated successfully!" << endl;
		MPDNotifier::NotifyEngine notify(settings.getStatusChangeTimeout(), settings.getErrorTimeout());
		cout << "NotifyEngine initiated successfully!" << endl;
		cout << "Starting..." << endl;
		std::string lastDescription = "";
		std::string lastStatus = "";
		int i = 0;
		while(true) {
			track.update();
			if(track.getDescription() != lastDescription || track.getStatus() != lastStatus) {
				notify.displayStatusChange(track.getDescription(), track.getStatus());
			}
			lastDescription = track.getDescription();
			lastStatus = track.getStatus();
			if(i == 450) {
				notify.reload(settings.getStatusChangeTimeout(), settings.getErrorTimeout());
				i = 0;
			} else {
				i++;
			}
			sleep(2);
		}
	} catch(MPDNotifier::SettingsException &exc) {
		cout << "Settings exception occured: " << exc.what() << endl;
		return EXIT_FAILURE;
	} catch(MPDNotifier::NotifyException &exc) {
		cout << "Notify engine exception occured: " << exc.what() << endl;
		return EXIT_FAILURE;
	} catch(MPDNotifier::ConnectionException &exc) {
		cout << "MPD connection exception occured: " << exc.what() << endl;
		return EXIT_FAILURE;
	} catch(exception &exc) {
		cout << "Exception occured: " << exc.what() << endl;
		return EXIT_FAILURE;
	}
	cout << "Ouch, the program finished, while it should not! My fault probably, sorry... Report this to phitherek [at] gmail [dot] com" << endl;
	return EXIT_SUCCESS;
}
