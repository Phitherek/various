#ifndef _NOTIFYENGINE_H
#define _NOTIFYENGINE_H
#include <string>
#include "libnotify/notify.h"
/// \file NotifyEngine
/// \brief A class that implements a notifying engine via libnotify.
/// \author Phitherek_
/// \date 2013
/// \version 0.1

/// \namespace MPDNotifier
/// \brief A global namespace for MPDNotifier.
namespace MPDNotifier {
/// \class NotifyEngine
/// \brief A class that implements a notifying engine via libnotify.
class NotifyEngine {
private:
	NotifyNotification* _statuschangenn;
	NotifyNotification* _errornn;
public:
	NotifyEngine(int normaltimeout, int errortimeout); ///< \brief A constructor initializing notify engine.
	///< \param normaltimeout A timeout for normal status change notification [ms].
	///< \param errortimeout A timeout for error notification [ms].
	~NotifyEngine(); ///< A destructor uninitializing notify engine.
	void displayStatusChange(std::string description, std::string status); ///< \brief A function displaying MPD status change notification.
	///< \param description Track description.
	///< \param status Track status.
	void displayError(std::string error); ///< \brief A function displaying error notification.
	///< \param error Error message.
	void reload(int normaltimeout, int errortimeout); ///< \brief A function reloading NotifyEngine.
	///< \param normaltimeout A timeout for normal status change notification [ms].
	///< \param errortimeout A timeout for error notification [ms].
};
}
#endif
