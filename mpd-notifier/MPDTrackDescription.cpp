#include "MPDTrackDescription.h"
#include "Exceptions.h"
using namespace MPDNotifier;

MPDTrackDescription::MPDTrackDescription(std::string host, int port, int timeout) {
	_connection = mpd_connection_new(host.c_str(), port, timeout);
	if(mpd_connection_get_error(_connection) != MPD_ERROR_SUCCESS) {
		ConnectionException exc(mpd_connection_get_error_message(_connection));
		throw exc;
	}
	_description = "";
	_status = "Undefined";
	_host = host;
	_port = port;
	_timeout = timeout;
}

MPDTrackDescription::~MPDTrackDescription() {
	mpd_connection_free(_connection);
	_description = "";
	_status = "Undefined";
}

void MPDTrackDescription::update() {
	mpd_song *current_track;
	mpd_status *current_status;
	current_status = mpd_run_status(_connection);
	if(current_status != NULL) {
	if(mpd_status_get_state(current_status) == MPD_STATE_UNKNOWN) {
		_status = "Unknown";
	} else if(mpd_status_get_state(current_status) == MPD_STATE_STOP) {
		_status = "Stopped";
	} else if(mpd_status_get_state(current_status) == MPD_STATE_PLAY) {
		_status = "Playing";
	} else if(mpd_status_get_state(current_status) == MPD_STATE_PAUSE) {
		_status = "Paused";
	} else {
		_status = "Undefined";
	}
	int current_track_id = mpd_status_get_song_id(current_status);
	if(current_track_id == -1) {
		_description = "";
	} else {
	if(mpd_send_command(_connection, "currentsong", NULL)) {
	do {
	current_track = mpd_recv_song(_connection);
	} while(current_track != NULL && mpd_song_get_id(current_track) != current_track_id);
	if(current_track != NULL) {
	const char* artist = mpd_song_get_tag(current_track, MPD_TAG_ARTIST, 0);
		const char* album = mpd_song_get_tag(current_track, MPD_TAG_ALBUM, 0);
		const char* title = mpd_song_get_tag(current_track, MPD_TAG_TITLE, 0);
		const char* uri = mpd_song_get_uri(current_track);
		if(artist == NULL && album == NULL && title == NULL) {
			_description = "";
			_description += uri;
		} else {
			_description = "";
			if(title != NULL) {
			_description += title;
			}
			_description += " by ";
			if(artist != NULL) {
			_description += artist;
			}
			_description += "\n";
			if(album != NULL) {
			_description += album;
			}
			_description += "\n";
			if(uri != NULL) {
			_description += uri;
			}
		}
	mpd_song_free(current_track);	
	} else {
		_status = "Null track error";
		_description = "";
		ConnectionException exc(mpd_connection_get_error_message(_connection));
		throw exc;
	}
	} else {
		ConnectionException exc("Command currentsong failed!");
		throw exc;
	}
	}
	mpd_status_free(current_status);
	} else {
		_status = "Null status error";
		_description = "";
		ConnectionException exc(mpd_connection_get_error_message(_connection));
		throw exc;
	}
	mpd_connection_free(_connection);
	_connection = mpd_connection_new(_host.c_str(), _port, _timeout);
	if(mpd_connection_get_error(_connection) != MPD_ERROR_SUCCESS) {
		ConnectionException exc(mpd_connection_get_error_message(_connection));
		throw exc;
	}
}

std::string MPDTrackDescription::getDescription() {
	return _description;
}

std::string MPDTrackDescription::getStatus() {
	return _status;
}
