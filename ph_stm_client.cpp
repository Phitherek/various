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

using namespace std;

int socdesc;

void *get_in_addr(sockaddr *sa) {
	if(sa->sa_family == AF_INET) {
	return &(((sockaddr_in*)sa)->sin_addr);	
	}
	return &(((sockaddr_in6*)sa)->sin6_addr);
}



int main() {
	cout << "Phitherek_' s Stream-To-Me TCP Message Client v. 0.1 (c) 2012 by Phitherek_" << endl;
	int yes=1;
	int status;
	char caddr[INET6_ADDRSTRLEN];
	char buf[100];
	addrinfo hints;
	addrinfo *servinfo, *p;
	memset(&hints, 0, sizeof(hints)); // <- This is now empty
	hints.ai_family = AF_UNSPEC; // IPv4, IPv6, I don't care :P
	hints.ai_socktype = SOCK_STREAM; // We will do the stream socket, yeah!
	char action;
	while(action != 'q') {
		cout << "Enter action (s - send a message, q - quit): ";
		cin >> action;
		if(action == 'q') {
			break;
		} else if(action == 's') {
		string hostname;
		cout << "Enter hostname: ";
		cin >> hostname;
	// Start the REAL fun! CONNECT!
	if((status = getaddrinfo(hostname.c_str(), "3490", &hints, &servinfo)) != 0) {
		// Oh, fail!
		cerr << "getaddrinfo FAILED: " << gai_strerror(status) << endl;
		exit(EXIT_FAILURE);
	}
	// GOT SERVINFO MWAHAHAHA!
	for(p = servinfo; p != NULL; p = p->ai_next) {
		socdesc = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
		if(socdesc == -1) {
		cerr << "Socket FAILED!" << endl;
		return EXIT_FAILURE;
		}
		if((setsockopt(socdesc, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)) {
				cerr << "Setsockopt FAILED: " << errno << endl;		
		}
		// And finally - BIND!
		int bindret;
	bindret = bind(socdesc, servinfo->ai_addr, servinfo->ai_addrlen);
	int conret;
	conret = connect(socdesc, servinfo->ai_addr, servinfo->ai_addrlen);
	if(conret == -1) {
		cerr << "Connect error: " << errno << "!" << endl;
		continue;
	}
	break;
	}
	if(p == NULL) {
	cerr << "Connect COMPLETE error!" << endl;	
	}
	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), caddr, sizeof(caddr));
	cout << "Connection to: " << caddr << endl;
	freeaddrinfo(servinfo); // Free the memory!
	cout << "Connection successful - enter your message below:" << endl;
	cin.get();
string msg;
char tmp;
do {
tmp = cin.get();
msg += tmp;
} while(tmp != '\n');
msg.erase(msg.length()-1);
	int numbytes;
	numbytes = send(socdesc, msg.c_str(), msg.length(), 0);
	if(numbytes == -1) {
		cerr << "Send error: " << errno << endl;
		return EXIT_FAILURE;
	}
	cout << numbytes << " bytes sent." << endl;
	close(socdesc);
		} else {
		cout << "I don' t know such an action!" << endl;	
		}
	}
return EXIT_SUCCESS;
}
