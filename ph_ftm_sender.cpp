#include <iostream>
#include <cstdlib>
#include <sys/socket.h> // For sockets
#include <sys/types.h> // For getaddrinfo
#include <arpa/inet.h> // For inet addr conversion
#include <netdb.h> // For getaddrinfo
#include <cstring> // For memset
#include <cerrno>
#include <unistd.h>
#include <string>
#include <iomanip>

using namespace std;

int socdesc;

int main() {
cout << "Phitherek_' s Fire-To-Me UDP Message Packet Sender v. 0.1 (c) 2012 by Phitherek_" << endl;
addrinfo hints, *servinfo, *p; // Hints, servinfo and iterator p
int rv, numbytes; // Return value, bytes sent
memset(&hints, 0, sizeof(hints)); // Zero the hints!
hints.ai_family=AF_UNSPEC; // IPv4, IPv6, I don' t care
hints.ai_socktype=SOCK_DGRAM; // I want DATAGRAM UDP sockets!
cout << "WARNING: The packets are not guaranteed to arrive to listener!" << endl << "This program is working on port 4950." << endl;
char option;
while(option != 'q') {
	cout << "Select option: send a packet with message (s), quit (q)" << endl;
	cin >> option;
	if(option == 'q') {
		break;
	} else if(option == 's') {
		string hostname;
		cout << "Enter hostname: ";
		cin >> hostname;
if((rv = getaddrinfo(hostname.c_str(), "4950", &hints, &servinfo)) == -1) {
// Here is FAIL
cerr << "Getaddrinfo FAILED: " << gai_strerror(rv) << endl;
return EXIT_FAILURE;
}
// Socket on the first getaddrinfo result you find - check loop
for(p = servinfo; p != NULL; p = p->ai_next) { // Loop through the result list
	// Try to open the SOCKET!
	if((socdesc = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
		cerr << "Socket FAILED: " << errno << endl;
	continue;	
	}
	break;
}
if(p == NULL) {
	cerr << "Socket FAILED PERMANENTLY!" << endl;
	return EXIT_FAILURE;
}
cout << "Socket ready to send packets. Now enter your message (100 characters max): " << endl;
cin.get();
string msg;
char tmp;
do {
tmp = cin.get();
msg += tmp;
} while(tmp != '\n');
msg.erase(msg.length()-1);
if((numbytes = sendto(socdesc, msg.c_str(), msg.length(), 0, p->ai_addr, p->ai_addrlen)) == -1) {
		cerr << "sendto FAILED: " << errno << endl;
		return EXIT_FAILURE;		
}
cout << "Fired a packet of " << numbytes << " bytes to " << hostname << "!" << endl;
close(socdesc);
	} else {
	cout << "I don' t know such an action!" << endl;	
	}
}
return EXIT_SUCCESS;
}
