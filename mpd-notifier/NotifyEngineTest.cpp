#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "NotifyEngine.h"
using namespace std;

int main() {
	try {
		MPDNotifier::NotifyEngine notify(15000, 60000);
		cout << "NotifyEngine initialized!" << endl;
		try {
			notify.displayStatusChange("Test", "Unknown");
			sleep(5);
			notify.displayStatusChange("Test", "Playing");
			sleep(5);
			notify.displayStatusChange("Test", "Paused");
			sleep(5);
			notify.displayStatusChange("Test", "Stopped");
			sleep(5);
			notify.displayError("Test");
			sleep(10);
		} catch(std::exception &exc) {
			cout << "Exception: " << exc.what() << endl;
		}
	} catch(std::exception &exc) {
			cout << "Exception: " << exc.what() << endl;
			return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
