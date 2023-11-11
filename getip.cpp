#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>
#include <arpa/inet.h>
#include <iostream>

int main(int argc, char* argv[]){
	if(argc > 2 || argc < 2) {
		std::cout << "Incorrect number of arguments. Usage: getip <domain name>" << std::endl;
		return 0;
	};

	int status;
	struct addrinfo hints;
	struct addrinfo *servinfo;
	struct addrinfo *p;
	char ipstr[INET6_ADDRSTRLEN];

	std::memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if((status = getaddrinfo(argv[1], "3490", &hints, &servinfo)) != 0){
		std::cout << "Failed to getInfo" << std::endl;
		return 0;
	};

	for(p = servinfo; p != NULL; p = p->ai_next){
		void *addr;
		char *ipver;
		if(p->ai_family == AF_INET){
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
		} else {
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
			addr = &(ipv6->sin6_addr);
			ipver = "IPv6";
		};
		inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
		std::cout << ipver << " " << ipstr << std::endl;
	};
	freeaddrinfo(servinfo);
	return 0;
}
