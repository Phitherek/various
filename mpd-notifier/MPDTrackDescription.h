#ifndef _MPDTRACKDESCRIPTION_H
#define _MPDTRACKDESCRIPTION_H
#include "mpd/client.h"
#include <string>
/// \file MPDTrackDescription.h
/// \brief A class that implements an updating-capable MPD Track Description.
/// \author Phitherek_
/// \date 2013
/// \version 0.1

/// \namespace MPDNotifier
/// \brief A global namespace for MPDNotifier.
namespace MPDNotifier {
/// \class MPDTrackDescription
/// \brief A class that implements an updating-capable MPD Track Description.
class MPDTrackDescription {
private:
	std::string _host;
	int _port;
	int _timeout;
	std::string _description;
	std::string _status;
	mpd_connection* _connection;
public:
	MPDTrackDescription(std::string host, int port, int timeout); ///< \brief A constructor, that connects to MPD.
	///< \param host A host, where the MPD is running.
	///< \param port A port, on which the MPD is running.
	///< \param timeout Connection timeout.
	~MPDTrackDescription(); ///< A destructor.
	void update(); ///< A function, that updates the MPD description.
	std::string getDescription(); ///< \brief A function, that returns a track description.
	///< \return Track description.
	std::string getStatus(); ///< \brief A function, that returns a track status.
	///< \return Track status.
};
}
#endif
