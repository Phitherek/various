#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
using namespace std;

int main() {
cout << "battery_check v. 0.1 (C) 2012 by Phitherek_" << endl;
FILE* pipe = popen("acpi", "r");
string info;
string slevel;
int level;
if(!pipe) {
cout << "Błąd! Nie można otworzyć pipy." << endl;
system("notify-send --expire-time=10000 'battery_notifier: Błąd! Nie można otworzyć pipy.'");
return EXIT_FAILURE;
} else {
char buffer[128];
while(!feof(pipe)) {
if(fgets(buffer, 128, pipe) != NULL) {
info += buffer;
}
}
}
pclose(pipe);
for(int i = 0; i < info.length(); i++) {
	if(info[i] == 'D') {
			cout << "Zasilacz: Odłączony" << endl;
	} else if(info[i] == 'C') {
			cout << "Zasilacz: Podłączony" << endl;
	}
		if(info[i] == '%') {
		if(info[i-3] == '1') {
			slevel = info.substr(i-3, 3);
			level = atoi(slevel.c_str());
		} else {
			if(info[i-2] != ' ') {
			slevel = info.substr(i-2, 2);
			level = atoi(slevel.c_str());	
			} else {
			slevel = info.substr(i-1, 1);
			level = atoi(slevel.c_str());	
			}
		}
		cout << "Stan baterii: " << level << "%" << endl << "Dziękuję, że użyłeś battery_check!" << endl;
	}
	}
return EXIT_SUCCESS;
}
