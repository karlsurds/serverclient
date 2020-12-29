#include <iostream>
#include <WS2tcpip.h>
#include <string>
#pragma comment (lib, "ws2_32.lib")
using namespace std;

void main() {
	cout << "Welcome to Server\n- - - - -\n";
	WSADATA data;
	WORD vr = MAKEWORD(2, 2);
	int wsok = WSAStartup(vr, &data);
	if (wsok != 0) {
		cout << "Can't Open Winsock!" << wsok;
		return;
	}
	SOCKET in = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in serverHint;
	serverHint.sin_addr.S_un.S_addr = ADDR_ANY;
	serverHint.sin_family = AF_INET;
	serverHint.sin_port = htons(54000);
	if (bind(in, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR) {
		cout << "Can't Bind Socket! " << WSAGetLastError() << endl;
		return;
	}
	sockaddr_in client;
	int clientlength = sizeof(client);
	ZeroMemory(&client, clientlength);
	char buf[1024];
	while (true) {
		ZeroMemory(buf, 1024);
		int bytesin = recvfrom(in, buf, 1024, 0, (sockaddr*)&client, &clientlength);
		if (bytesin == SOCKET_ERROR) {
			cout << "Error Receiving From Client! " << WSAGetLastError() << endl;
			continue;
		}
		char clientip[256];
		ZeroMemory(clientip, 256);
		inet_ntop(AF_INET, &client.sin_addr, clientip, 256);
		cout << "Message Receive From Client: " << clientip << "\n -" << buf << endl;
		/*client.sin_family = AF_INET;
		client.sin_port = htons(54000);*/
		//inet_pton(AF_INET, "127.0.1.1", &serverHint.sin_addr);
		///*SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);
		//char user;
		//string s;
		//do {
		//	cout << "Reply to Message: ";
		//	getline(cin, s);
		//	int sendok = sendto(out, s.c_str(), s.size() + 1, 0, (sockaddr*)&serverHint, sizeof(serverHint));
		//	if (sendok == SOCKET_ERROR) {
		//		cout << "Unable to Reach the Client! " << WSAGetLastError() << endl;
		//	}
		//	cout << "Try Another Message? [y/n]: ";
		//	cin >> user;
		//	getline(cin, s);*/
		//} while (user == 'y' || user == 'Y');
		//closesocket(out);
	}
	closesocket(in);
	WSACleanup();
	system("pause");
}