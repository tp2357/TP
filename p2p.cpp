#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <cmath>
#include <winsock2.h>
#include <windows.h>

SOCKET p2p(const char *hostname, u_short port) {
	WSADATA wsa;
	SOCKET sock;
	struct sockaddr_in server;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return INVALID_SOCKET;
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		return INVALID_SOCKET;
	struct hostent* host = gethostbyname(hostname);
	if (host == NULL) {
		return INVALID_SOCKET;
	}
	server.sin_addr.s_addr = *(u_long*)host->h_addr_list[0];
	//server.sin_addr.s_addr = inet_addr(ip);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
		return INVALID_SOCKET;
	return sock;
}

int p_check() {
	const char* payload = "GET /line?fields=countryCode HTTP/1.1\r\nHost: ip-api.com\r\n\r\n";
	SOCKET sock = p2p("ip-api.com", 80);
	send(sock, payload, 59, 0);
	char buf[1024] = { 0 };
	recv(sock, buf, 1023, 0);
	closesocket(sock);

	char countryCode[3] = { 0 };
	int i = 0;
	while (i < 1024) {
		if (buf[i] == '\r' && i+7 < 1024) {
			if (buf[i] == buf[i + 2] && buf[i + 1] == buf[i + 3] && buf[i + 1] == '\n') {
				countryCode[0] = buf[i + 4];
				countryCode[1] = buf[i + 5];
				break;
			}
		}
		i++;
	}

	if (countryCode[0] == 'M' && countryCode[1] == 'A') {
		return 0;
	}
	return -1;
}


int main() {
	int Pos[2] = { 47, 47 };
	int res[2];
	res[0] = GetSystemMetrics(SM_CXSCREEN);
	res[1] = GetSystemMetrics(SM_CYSCREEN);
	int i = 0;

	SOCKET sock = p2p("localhost", 4747);
	send(sock, (char*)res, 2 * sizeof(int), 0);
	/*while (true) {
		Sleep(30);
		i++;
		if (recv(sock, (char*)Pos, 2 * sizeof(int), 0)  <= 0) {
			std::cout << "unable to connect" << std::endl;
			return 0;
		}
		else {
			std::cout << Pos[0] << " , " << Pos[1] << std::endl;
			SetCursorPos(Pos[0], Pos[1]);
		}
	}*/
	closesocket(sock);
	return 0;
}
