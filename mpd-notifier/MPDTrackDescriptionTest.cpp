#include "MPDTrackDescription.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <exception>
using namespace std;

int main() {
	try {
		MPDNotifier::MPDTrackDescription track("localhost", 6600, 60000);
		track.update();
		cout << track.getStatus() << endl << track.getDescription() << endl;
		return EXIT_SUCCESS;
	} catch(std::exception &exc) {
		cout << "Exception: " << exc.what() << endl;
		return EXIT_FAILURE;
	}
}
