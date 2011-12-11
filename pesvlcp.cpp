#include <iostream>
#include <cstdlib>
#include "vlc/vlc.h"
using namespace std;

int main(int argc, char** argv) {
cout << "Phitherek_' s Experimental Simple VLCLib Player v. 0.1 (c) 2011 by Phitherek_" << endl;
for(int i = 1; i < argc; i++) {
libvlc_instance_t* inst;
libvlc_time_t time;
libvlc_time_t length;
inst = libvlc_new(argc, argv);
libvlc_media_t* muzyczka;
muzyczka = libvlc_media_new_path(inst, argv[i]);
libvlc_media_player_t* plr;
plr = libvlc_media_player_new_from_media(muzyczka);
libvlc_media_player_play(plr);
sleep(1);
while(libvlc_media_player_is_playing(plr)) {
	time = libvlc_media_player_get_time(plr);
	length = libvlc_media_player_get_length(plr);
cout << "Playing: " << argv[i] << " (" << time << "/" << length << ")\r";
sleep(1);
}
cout << endl;
~time;
~length;
libvlc_media_player_release(plr);
libvlc_media_release(muzyczka);
libvlc_release(inst);
}
cout << "Done! Thank you for using Phitherek_' s Experimental Simple VLCLib Player!" << endl;
return EXIT_SUCCESS;
}
