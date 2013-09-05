#include "NotifyEngine.h"
#include "Exceptions.h"
using namespace MPDNotifier;

NotifyEngine::NotifyEngine(int normaltimeout, int errortimeout) {
	if(notify_init("MPDNotifier")) {
		_statuschangenn = notify_notification_new("MPD Status Change", "Unknown", "dialog-question");
		_errornn = notify_notification_new("MPDNotifier encountered an error!", "Unknown", "dialog-error");
		notify_notification_set_timeout(_statuschangenn, normaltimeout);
		notify_notification_set_timeout(_errornn, errortimeout);
	} else {
		NotifyException exc("Could not initialize notify engine!");
		throw exc;
	}
}

NotifyEngine::~NotifyEngine() {
	GError* error = NULL;
	notify_notification_close(_statuschangenn, &error);
	error = NULL;
	notify_notification_close(_errornn, &error);
	notify_uninit();
}

void NotifyEngine::displayStatusChange(std::string description, std::string status) {
	std::string message = "";
	message += status;
	message += '\n';
	message += description;
	if(status == "Playing") {
		if(!notify_notification_update(_statuschangenn, "MPD Status Change", message.c_str(), "media-playback-start")) {
			NotifyException exc("Bad notification update argument!");
			throw exc;
		}
		GError* error = NULL;
		if(!notify_notification_show(_statuschangenn, &error)) {
			NotifyException exc(error->message);
			throw exc;
		}
	} else if(status == "Paused") {
		if(!notify_notification_update(_statuschangenn, "MPD Status Change", message.c_str(), "media-playback-pause")) {
			NotifyException exc("Bad notification update argument!");
			throw exc;
		}
		GError* error = NULL;
		if(!notify_notification_show(_statuschangenn, &error)) {
			NotifyException exc(error->message);
			throw exc;
		}
	} else if(status == "Stopped") {
		if(!notify_notification_update(_statuschangenn, "MPD Status Change", message.c_str(), "media-playback-stop")) {
			NotifyException exc("Bad notification update argument!");
			throw exc;
		}
		GError* error = NULL;
		if(!notify_notification_show(_statuschangenn, &error)) {
			NotifyException exc(error->message);
			throw exc;
		}
	} else {
		if(!notify_notification_update(_statuschangenn, "MPD Status Change", message.c_str(), "dialog-question")) {
			NotifyException exc("Bad notification update argument!");
			throw exc;
		}
		GError* error = NULL;
		if(!notify_notification_show(_statuschangenn, &error)) {
			NotifyException exc(error->message);
			throw exc;
		}
	}
}

void NotifyEngine::displayError(std::string error) {
	if(!notify_notification_update(_errornn, "MPDNotifier encountered an error!", error.c_str(), "dialog-error")) {
			NotifyException exc("Bad notification update argument!");
			throw exc;
		}
		GError* gerror = NULL;
		if(!notify_notification_show(_errornn, &gerror)) {
			NotifyException exc(gerror->message);
			throw exc;
		}
}
void NotifyEngine::reload(int normaltimeout, int errortimeout) {
	GError* error = NULL;
	notify_notification_close(_statuschangenn, &error);
	error = NULL;
	notify_notification_close(_errornn, &error);
	notify_uninit();
	if(notify_init("MPDNotifier")) {
		_statuschangenn = notify_notification_new("MPD Status Change", "Unknown", "dialog-question");
		_errornn = notify_notification_new("MPDNotifier encountered an error!", "Unknown", "dialog-error");
		notify_notification_set_timeout(_statuschangenn, normaltimeout);
		notify_notification_set_timeout(_errornn, errortimeout);
	} else {
		NotifyException exc("Could not reload notify engine!");
		throw exc;
	}
}

