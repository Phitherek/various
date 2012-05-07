#include <iostream>
#include <cstdlib>
#include <sys/socket.h> // For sockets
#include <sys/types.h> // For getaddrinfo
#include <arpa/inet.h> // For inet addr conversion
#include <netdb.h> // For getaddrinfo
#include <cstring> // For memset
#include <cerrno>
#include <unistd.h>
#include <libnotify/notify.h>

using namespace std;

int socdesc;

void *get_in_addr(sockaddr *sa) {
	if(sa->sa_family == AF_INET) {
	return &(((sockaddr_in*)sa)->sin_addr);	
	}
	return &(((sockaddr_in6*)sa)->sin6_addr);
}

int main() {
cout << "Phitherek_' s Fire-To-Me UDP Message Packet Receiver v. 0.1 (C) 2012 by Phitherek_" << endl;
NotifyNotification *got_message;
addrinfo hints, *servinfo, *p; // hints, servinfo and iterator p
int rv, numbytes; // return value, bytes received
sockaddr_storage their_addr; // their addr
char buf[100]; // data buffer
socklen_t addr_len; // addr length
char s[INET6_ADDRSTRLEN]; // IP Address
memset(&hints, 0, sizeof(hints)); // Zero the hints!
hints.ai_family = AF_UNSPEC; // IPv4, IPv6, I don' t care...
hints.ai_socktype = SOCK_DGRAM; // And now for DATAGRAM sockets! And UDP!
hints.ai_flags = AI_PASSIVE; // Do it on localhost!
notify_init("Phitherek_' s Fire-To-Me Receiver");
// Get servinfo
if((rv = getaddrinfo(NULL, "4950", &hints, &servinfo)) == -1) {
// Here is FAIL
cerr << "Getaddrinfo FAILED: " << gai_strerror(rv) << endl;
return EXIT_FAILURE;
}
// Bind to the first getaddrinfo result you find - check loop
for(p = servinfo; p != NULL; p = p->ai_next) { // Loop through the result list
	// Try to open the SOCKET!
	if((socdesc = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
		cerr << "Socket FAILED: " << errno << endl;
	continue;	
	}
	// Try to BIND!
	if(bind(socdesc, p->ai_addr, p->ai_addrlen) == -1) {
	close(socdesc);
	cerr << "Bind FAILED: " << errno << endl;
	continue;	
	}
	break;
}
if(p == NULL) {
cerr << "Bind FAILED PERMANENTLY!" << endl;
return EXIT_FAILURE;
}
freeaddrinfo(servinfo); // We can free this now
cout << "Socket set up - Listening for packets on port 4950..." << endl;
// RECVFROM
while(true) {
addr_len = sizeof their_addr;
if((numbytes = recvfrom(socdesc, buf, 99, 0, (sockaddr *)&their_addr, &addr_len)) == -1) {
		cerr << "recvfrom FAILED: " << errno << endl;
		return EXIT_FAILURE;		
}
got_message = notify_notification_new("ph_ftm_receiver: Got message packet!", NULL, NULL);
notify_notification_show(got_message, NULL);
cout << "Got message packet! From: " << inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof(s)) << endl;
cout << "Length of packet: " << numbytes << " bytes." << endl;
buf[numbytes] = '\0';
cout << "Message: "  << endl << buf << endl;
}
close(socdesc);
notify_uninit();
return EXIT_SUCCESS;
}
