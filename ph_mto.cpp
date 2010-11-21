#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

int main() {
	cout << "Phitherek_' s MTO - Mic-To-Output for PulseAudio v. 0.1" << endl;
	system("echo $HOME > /tmp/ph_mto_homedir");
	ifstream home("/tmp/ph_mto_homedir");
	string houm;
	home >> houm;
	remove("/tmp/ph_mto_homedir");
	string path = houm + "/.ph_mto/module_id";
	ifstream test(path.c_str());
	if(test) {
			cout << "Disabling PulseAudio microphone output..." << endl;
			ifstream in(path.c_str());
			string id;
			in >> id;
			string cmd = "pactl unload-module " + id;
			system(cmd.c_str());
			cout << "Killing all instances of PAVUControl..." << endl;
			system("killall pavucontrol");
			cout << "Deleting the module_id data..." << endl;
			remove(path.c_str());
			cout << "Setting status..." << endl;
			path = houm + "/.ph_mto/status";
			remove(path.c_str());
			ofstream status(path.c_str());
			status << 0;
			status.close();
			in.close();
			cout << "Done! Thank you for using MTO!" << endl;
	} else {
	cout << "Enabling PulseAudio microphone output..." << endl;
	system("pactl load-module module-loopback > $HOME/.ph_mto/module_id");
	cout << "Starting PAVUControl - don' t exit from it! Exiting will cause delay to microphone output!" << endl;
	system("pavucontrol&");
	cout << "Setting status..." << endl;
	path = houm + "/.ph_mto/status";
	ofstream status(path.c_str());
	status << 1;
	status.close();
	cout << "Done! Thank you for using MTO! Run it again to disable PulseAudio microphone output!" << endl;	
	}
	test.close();
return EXIT_SUCCESS;
}
