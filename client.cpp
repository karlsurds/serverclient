#include <iostream>
#include <WS2tcpip.h>
#include <string>
#pragma comment (lib, "ws2_32.lib")
using namespace std;

void main(int argc, char* argv[]) {
	WSADATA data;
	WORD vr = MAKEWORD(2, 2);
	int wsok = WSAStartup(vr, &data);
	if (wsok != 0) {
		cout << "Can't Open Winsock!" << wsok;
		return;
	}
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(54000);
	inet_pton(AF_INET, "127.0.1.1", &server.sin_addr);
	SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);
	char user;
	string s;
	do {
		cout << "Enter Your Message: ";
		getline(cin, s);
		int sendok = sendto(out, s.c_str(), s.size() + 1, 0, (sockaddr*)&server, sizeof(server));
		if (sendok == SOCKET_ERROR) {
			cout << "Unable to Reach the Server! " << WSAGetLastError() << endl;
		}
		cout << "Try Another Message? [y/n]: ";
		cin >> user;
		getline(cin, s);
	} while (user == 'y' || user == 'Y');
	closesocket(out);
	WSACleanup();
	system("pause");
}
