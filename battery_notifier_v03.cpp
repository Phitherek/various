#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <csignal>
#include <vector>
#include <cctype>
#include <unistd.h>
#include <libnotify/notify.h>
using namespace std;

string lang="pl", snd="on", sndfile="/home/phitherek/zyn/low_battery.wav", sndplr="mplayer", adinfo="on", battinfo="on", errdelay="30", infodelay="10", lowlev="10", critlev="5", emptylev="1";
NotifyNotification *notific, *batnotif, *adnotif1, *adnotif2;

void sigterm (int param) {
	notific = notify_notification_new("battery_notifier: Terminated. Thanks for using!", NULL, NULL);
notify_notification_set_timeout(notific, atoi(infodelay.c_str()));
notify_notification_show(notific, NULL);
	notify_uninit();
	exit(0);	
}

void sigint (int param) {
	notific = notify_notification_new("battery_notifier: Interrupted. Thanks for using!", NULL, NULL);
notify_notification_set_timeout(notific, atoi(infodelay.c_str()));
notify_notification_show(notific, NULL);
	cout << endl;
	notify_uninit();
	exit(0);	
}

string strip(string s) {
	string stripped;
	for(int i=1; s[i] != ']'; i++) {
		stripped += s[i];
	}
	return stripped;
}

int confparse() {
string home, conffile, tmp;
string action = "check";
home = getenv("HOME");
conffile = home + "/.battery_notifier/config";
ifstream conf(conffile.c_str());
if(!conf) {
	return 1;
}
while(!conf.eof()) {
conf >>	tmp;
if(conf) {
	if(tmp[0] == '[' && tmp[tmp.length()-1] == ']') {
		if(action == "check") {
		tmp = strip(tmp);
		if(tmp == "config_start") {
		action = "parse";	
		} else {
		conf.close();
		return 2;
		}
		} else if(action == "parse") {
		tmp = strip(tmp);
		if(tmp == "lang") {
		action = "lang";	
		} else if(tmp == "snd") {
		action = "snd";	
		} else if(tmp == "sndfile") {
		action = "sndfile";	
		} else if(tmp == "sndplr") {
		action = "sndplr";	
		} else if(tmp == "adinfo") {
		action = "adinfo";	
		} else if(tmp == "battinfo") {
		action = "battinfo";	
		} else if(tmp == "errdelay") {
		action = "errdelay";	
		} else if(tmp == "infodelay") {
		action = "infodelay";
		} else if(tmp == "lowlev") {
		action = "lowlev";	
		} else if(tmp == "critlev") {
		action = "critlev";	
		} else if(tmp == "emptylev") {
		action = "emptylev";	
		} else if (tmp == "config_end") {
		conf.close();
		return 0;	
		} else {
		conf.close();
		return 3;	
		}
		}
	} else {
		if(action == "lang") {
			if(tmp == "en" || tmp == "pl") {
			lang = tmp;
			action = "parse";
			} else {
			conf.close();
			return 4;	
			}
		} else if(action == "snd") {
			if(tmp == "on" || tmp == "off") {
			snd = tmp;
			action = "parse";
			} else {
			conf.close();
			return 4;
			}
		} else if(action == "sndfile") {
		sndfile = tmp;
		action = "parse";
		} else if(action == "sndplr") {
		sndplr = tmp;
		action = "parse";
		} else if(action == "adinfo") {
			if(tmp == "on" || tmp == "off") {
			adinfo = tmp;
			action = "parse";
			} else {
			conf.close();
			return 4;
			}
		} else if(action == "battinfo") {
			if(tmp == "on" || tmp == "off") {
			battinfo = tmp;
			action = "parse";
			} else {
			conf.close();
			return 4;
			}
		} else if(action == "errdelay") {
			for(int i=0; i < tmp.length(); i++) {
				if(!isdigit(tmp[i])) {
				conf.close();
				return 4;
				}
			}
			errdelay = tmp;
			action = "parse";
		} else if(action == "infodelay") {
			for(int i=0; i < tmp.length(); i++) {
				if(!isdigit(tmp[i])) {
				conf.close();
				return 4;
				}
			
			}
			infodelay = tmp;
			action = "parse";
		} else if(action == "lowlev") {
			for(int i=0; i < tmp.length(); i++) {
				if(!isdigit(tmp[i])) {
				conf.close();
				return 4;
				}
			}
			if(atoi(tmp.c_str()) <= 100 && atoi(tmp.c_str()) >= 0) {
				lowlev = tmp;
				action = "parse";
			} else {
				conf.close();
				return 4;
			}
		} else if(action == "critlev") {
			for(int i=0; i < tmp.length(); i++) {
				if(!isdigit(tmp[i])) {
				conf.close();
				return 4;
				}
			}
			if(atoi(tmp.c_str()) <= 100 && atoi(tmp.c_str()) >= 0) {
				critlev = tmp;
				action = "parse";
			} else {
				conf.close();
				return 4;
			}
		} else if(action == "emptylev") {
			for(int i=0; i < tmp.length(); i++) {
				if(!isdigit(tmp[i])) {
				conf.close();
				return 4;
				}
			}
			if(atoi(tmp.c_str()) <= 100 && atoi(tmp.c_str()) >= 0) {
				emptylev = tmp;
				action = "parse";
			} else {
				conf.close();
				return 4;
			}
		} else {
		conf.close();
		return 3;
		}
	}
}
}
}



int main() {
int check = 0;
string state = "run";
string notif = "none";
notify_init("battery_notifier");
int parseret;
parseret = confparse();
if(parseret == 0) {
errdelay += "000";
infodelay += "000";                                                
notific = notify_notification_new("battery_notifier v. 0.3.1 (C) 2012-2014 by Phitherek_: Started", NULL, NULL);
notify_notification_set_timeout(notific, atoi(infodelay.c_str()));
notify_notification_show(notific, NULL);
while(true) {
signal(SIGTERM, sigterm);
signal(SIGINT, sigint);
FILE* pipe = popen("acpi -b", "r");
string info;
string slevel;
int level;
if(!pipe) {
	if(lang == "pl") {
cout << "Błąd! Nie można otworzyć pipy." << endl;
notific = notify_notification_new("battery_notifier: Błąd! Nie można otworzyć pipy.", NULL, NULL);
notify_notification_set_timeout(notific, atoi(errdelay.c_str()));
notify_notification_show(notific, NULL);
	} else if(lang == "en") {
		cout << "Error! Could not open pipe." << endl;
notific = notify_notification_new("battery_notifier: battery_notifier: Error! Could not open pipe.", NULL, NULL);
notify_notification_set_timeout(notific, atoi(errdelay.c_str()));
notify_notification_show(notific, NULL);
	}
	notify_uninit();
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
		if(state == "cha") {
			if(adinfo == "on") {
				if(lang == "pl") {	
					string cmd = "";
					cmd += "battery_notifier: ";
					cmd += "Zasilacz został odłączony.";
					adnotif1 = notify_notification_new(cmd.c_str(), NULL, NULL);
notify_notification_set_timeout(adnotif1, atoi(infodelay.c_str()));
notify_notification_show(adnotif1, NULL);
				} else if(lang == "en") {
					string cmd = "";
					cmd += "battery_notifier: ";
					cmd += "AC adapter disconnected.";
					adnotif1 = notify_notification_new(cmd.c_str(), NULL, NULL);
notify_notification_set_timeout(adnotif1, atoi(infodelay.c_str()));
notify_notification_show(adnotif1, NULL);	
				}
			}
		}
		state = "dis";
	} else if(info[i] == 'C') {
		if(state == "dis") {
			if(adinfo == "on") {
				if(lang == "pl") {
					string cmd = "";
					cmd += "battery_notifier: ";
					cmd += "Zasilacz został podłączony.";
					adnotif2 = notify_notification_new(cmd.c_str(), NULL, NULL);
notify_notification_set_timeout(adnotif2, atoi(infodelay.c_str()));
notify_notification_show(adnotif2, NULL);
				} else if(lang == "en") {
					string cmd = "";
					cmd += "battery_notifier: ";
					cmd += "AC adapter connected.";
					adnotif2 = notify_notification_new(cmd.c_str(), NULL, NULL);
notify_notification_set_timeout(adnotif2, atoi(infodelay.c_str()));
notify_notification_show(adnotif2, NULL);	
				}
			}
		}
	state = "cha";	
	}
	if(state == "dis") {	
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
		if(level < atoi(emptylev.c_str()) && notif != "empty") {
			if(battinfo == "on") {
				string cmd = "";
					cmd += "battery_notifier: ";
				if(lang == "pl") {
					cmd += "Stan baterii: WYŁADOWANA (poniżej ";
					cmd += emptylev;
					cmd += "%)! Zapisz swoją pracę!";
					batnotif = notify_notification_new(cmd.c_str(), NULL, NULL);
notify_notification_set_timeout(batnotif, atoi(errdelay.c_str()));
notify_notification_show(batnotif, NULL);
				} else if(lang == "en") {
					cmd += "Battery state: EMPTY (below ";
					cmd += emptylev;
					cmd += "%)! Save all your work!";
					batnotif = notify_notification_new(cmd.c_str(), NULL, NULL);
notify_notification_set_timeout(batnotif, atoi(errdelay.c_str()));
notify_notification_show(batnotif, NULL);
				}
			}
			notif = "empty";
			if(snd == "on") {
			string cmd = "";
			cmd += sndplr;
			cmd += " ";
			cmd += sndfile;
			cmd += " &";
			system(cmd.c_str());
			}
		} else if(level < atoi(critlev.c_str()) && notif != "crit" && notif != "empty") {
			if(battinfo == "on") {
				string cmd = "";
					cmd += "battery_notifier: ";
				if(lang == "pl") {
					cmd += "Stan baterii: KRYTYCZNY (poniżej ";
					cmd += critlev;
					cmd += "%)";
					batnotif = notify_notification_new(cmd.c_str(), NULL, NULL);
notify_notification_set_timeout(batnotif, atoi(errdelay.c_str()));
notify_notification_show(batnotif, NULL);
				} else if(lang == "en") {
					cmd += "Battery level: CRITICAL (below ";
					cmd += critlev;
					cmd += "%)";
					batnotif = notify_notification_new(cmd.c_str(), NULL, NULL);
notify_notification_set_timeout(batnotif, atoi(errdelay.c_str()));
notify_notification_show(batnotif, NULL);
				}
			}
			notif = "crit";
			if(snd == "on") {
			string cmd = "";
			cmd += sndplr;
			cmd += " ";
			cmd += sndfile;
			cmd += " &";
			system(cmd.c_str());
			}
		} else if(level < atoi(lowlev.c_str()) && notif != "low" && notif != "crit" && notif != "empty") {
			if(battinfo == "on") {
				string cmd = "";
					cmd += "battery_notifier: ";
				if(lang == "pl") {
					cmd += "Stan baterii: NISKI (poniżej ";
					cmd += lowlev;
					cmd += "%)";
					batnotif = notify_notification_new(cmd.c_str(), NULL, NULL);
notify_notification_set_timeout(batnotif, atoi(errdelay.c_str()));
notify_notification_show(batnotif, NULL);
				} else if(lang == "en") {
					cmd += "Battery level: LOW (below ";
					cmd += lowlev;
					cmd += "%)";	
					batnotif = notify_notification_new(cmd.c_str(), NULL, NULL);
notify_notification_set_timeout(batnotif, atoi(errdelay.c_str()));
notify_notification_show(batnotif, NULL);
				}
			}
			notif = "low";
			if(snd == "on") {
			string cmd = "";
			cmd += sndplr;
			cmd += " ";
			cmd += sndfile;
			cmd += " &";
			system(cmd.c_str());
			}
		}
	}
	}
}
sleep(5);
check++;
if(check == 50) {
    notify_uninit();
    notify_init("battery_notifier");
}
}
notify_uninit();
return EXIT_SUCCESS;
} else if(parseret == 1) {
	notific = notify_notification_new("battery_notifier: Config parse error: Could not open configuration file!", NULL, NULL);
notify_notification_set_timeout(notific, 10000);
notify_notification_show(notific, NULL);
notify_uninit();
	return EXIT_FAILURE;
} else if(parseret == 2) {
	notific = notify_notification_new("battery_notifier: Config parse error: Wrong file format!", NULL, NULL);
notify_notification_set_timeout(notific, 10000);
notify_notification_show(notific, NULL);
notify_uninit();
	return EXIT_FAILURE;
} else if(parseret == 3) {
	notific = notify_notification_new("battery_notifier: Config parse error: Key error!", NULL, NULL);
notify_notification_set_timeout(notific, 10000);
notify_notification_show(notific, NULL);
notify_uninit();
	return EXIT_FAILURE;
} else if(parseret == 4) {
	notific = notify_notification_new("battery_notifier: Config parse error: Value error!", NULL, NULL);
notify_notification_set_timeout(notific, 10000);
notify_notification_show(notific, NULL);
notify_uninit();
	return EXIT_FAILURE;
}
}
