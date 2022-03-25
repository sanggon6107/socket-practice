#include <stdio.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <iostream>

using namespace std;

#pragma comment (lib, "ws2_32.lib")

int main()
{
	WSADATA wsa_data;
	SOCKET h_socket;
	SOCKADDR_IN serv_addr;

	// 1. 윈속 초기화
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) cout << "WSAStartup() failed" << endl;

	// 2. socket 생성
	h_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (h_socket == INVALID_SOCKET) cout << "socket() failed" << endl;


	
}