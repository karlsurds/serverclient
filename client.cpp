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
	/*SOCKET in = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in clientHint;
	clientHint.sin_addr.S_un.S_addr = ADDR_ANY;
	clientHint.sin_family = AF_INET;
	clientHint.sin_port = htons(54000);
	if (bind(in, (sockaddr*)&clientHint, sizeof(clientHint)) == SOCKET_ERROR) {
		cout << "Can't Bind Socket! " << WSAGetLastError() << endl;
		return;
	}*/
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(54000);
	inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
	SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);
	char user;
	string s;
	do {
		cout << "Enter Message: ";
		getline(cin, s);
		int sendok = sendto(out, s.c_str(), s.size() + 1, 0, (sockaddr*)&server, sizeof(server));
		if (sendok == SOCKET_ERROR) {
			cout << "Unable to Reach the Server! " << WSAGetLastError() << endl;
		}
		cout << "Try Another Message? [y/n]: ";
		cin >> user;
		getline(cin, s);
	} while (user == 'y' || user == 'Y');
	/*sockaddr_in serverm;
	int serverlength = sizeof(serverm);
	ZeroMemory(&serverm, serverlength);
	char buf[1024];
	while (true) {
		ZeroMemory(buf, 1024);
		int bytesin = recvfrom(out, buf, 1024, 0, (sockaddr*)&serverm, &serverlength);
		if (bytesin == SOCKET_ERROR) {
			cout << "Error Receiving From Client! " << WSAGetLastError() << endl;
			continue;
		}
		char serverip[256];
		ZeroMemory(serverip, 256);
		inet_ntop(AF_INET, &server.sin_addr, serverip, 256);
		cout << "Message Receive From Server: " << serverip << "\n *" << buf << endl;
	}*/
	closesocket(out);
	WSACleanup();
	system("pause");
}