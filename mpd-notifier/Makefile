PREFIX=/usr
all:
	g++ -o mpd-notifier-config mpd-notifier-config.cpp SettingsFile.cpp Exceptions.cpp
	g++ -o mpd-notifier mpd-notifier.cpp MPDTrackDescription.cpp Exceptions.cpp NotifyEngine.cpp SettingsFile.cpp -lmpdclient `pkg-config --cflags --libs libnotify`
tests:
	g++ -o MPDTrackDescriptionTest MPDTrackDescriptionTest.cpp Exceptions.cpp -lmpdclient
	g++ -o NotifyEngineTest NotifyEngineTest.cpp NotifyEngine.cpp Exceptions.cpp `pkg-config --cflags --libs libnotify`
install:
	cp mpd-notifier-config mpd-notifier $PREFIX/bin
clean:
	rm -rf mpd-notifier-config mpd-notifier NotifyEngineTest MPDTrackDescriptionTest
