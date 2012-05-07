#include <iostream>
#include <cstdlib>
#include <sys/socket.h> // For sockets
#include <sys/types.h> // For getaddrinfo
#include <arpa/inet.h> // For inet addr conversion
#include <netdb.h> // For getaddrinfo
#include <cstring> // For memset
#include <cerrno>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <libnotify/notify.h>

using namespace std;

int socdesc, newsocdesc;
char caddr[INET6_ADDRSTRLEN];

void sigchld_handler(int s) {
while(waitpid(-1, NULL, WNOHANG) > 0);	
}

void *get_in_addr(sockaddr *sa) {
	if(sa->sa_family == AF_INET) {
	return &(((sockaddr_in*)sa)->sin_addr);	
	}
	return &(((sockaddr_in6*)sa)->sin6_addr);
}

int main() {
	cout << "Phitherek_' s Stream-To-Me TCP Message Server v. 0.1 (c) 2012 by Phitherek_" << endl << "Program is using port 3490." << endl;
	NotifyNotification *got_message;
	int status;
	int yes=1;
	struct sigaction sa;
	addrinfo hints;
	addrinfo *servinfo, *p;
	sockaddr_storage their_addr;
	socklen_t addr_size;
	char buf[100];
	notify_init("Phitherek_' s Stream-To-Me Server");
	memset(&hints, 0, sizeof(hints)); // <- This is now empty
	hints.ai_family = AF_UNSPEC; // IPv4, IPv6, I don't care :P
	hints.ai_socktype = SOCK_STREAM; // We will do the stream socket, yeah!
	hints.ai_flags = AI_PASSIVE; // Connect me to localhost, dammit!
	// Start the REAL fun! Try to get servinfo!
	if((status = getaddrinfo(NULL, "3490", &hints, &servinfo)) != 0) {
		// Oh, fail!
		cerr << "getaddrinfo FAILED: " << gai_strerror(status) << endl;
		exit(EXIT_FAILURE);
	}
	// GOT SERVINFO MWAHAHAHA!
	// Now we get to the SOCKET!
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
	if(bindret == 1) {
		cout << "Bind FAILED: " << errno << endl;
		continue;
	}
	break;
	}
	if(p == NULL) {
	cout << "Bind FAILED completely!" << endl;
	return EXIT_FAILURE;	
	}
		freeaddrinfo(servinfo); // Free the memory!
		
	// LISTEN!
	int lr;
	lr = listen(socdesc, 5);
	if(lr == -1) {
		cerr << "Listen FAILED: " << errno << "!" << endl;
	return EXIT_FAILURE;	
	}
	sa.sa_handler=sigchld_handler; // Dead processes out!
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if(sigaction(SIGCHLD, &sa, NULL) == -1) {
	cerr << "Sigaction FAILED!" << endl;
	return EXIT_FAILURE;	
	}
	cout << "Server is listening for messages on 3490!" << endl;
	while(true) { // accept() loop
	addr_size = sizeof(their_addr);
	newsocdesc = accept(socdesc, (sockaddr*)&their_addr, &addr_size);
	if(newsocdesc == -1) {
		continue;
	}
	cout << "Got connection!" << endl;
	inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), caddr, sizeof(caddr));
	cout << "Connection from: " << caddr << endl;
	if(!fork()) {
	close(socdesc);
	int numbytes;
	if((numbytes = recv(newsocdesc, buf, 99, 0)) == -1) {
		cerr << "Recv FAILED:" << errno << endl;
		close(newsocdesc);
		exit(EXIT_FAILURE);
	}
	buf[numbytes] = '\0';
	got_message = notify_notification_new("Phitherek_' s Stream-To-Me Server: New message!", NULL, NULL);
	notify_notification_show(got_message, NULL);
	cout << "Got a message from: " << caddr << endl << "Got " << numbytes << " bytes" << endl << "Message: " << endl << buf << endl;
	}
	close(newsocdesc); // Close the socket!
	}
	notify_uninit();
return EXIT_SUCCESS;
}
