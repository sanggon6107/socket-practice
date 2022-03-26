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

	// 3. 서버 자신의 주소를 세팅
	// 3-1. 서버 주소 세팅
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_port = htons(30002);
	if (bind(h_socket, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
		// bind : 서버의 소켓과 ip를 연결해주는 함수. 즉 SOCKET 객체 h_socket과 SOCKETADDR_IN 객체 serv_addr를 연결해준다.
	{
		cout << "binding error" << endl;
	}
	if (listen(h_socket, 5) == SOCKET_ERROR)
		// listen의 인자 주소가 입력되어있는 소켓, 동시에 처리할 수 있는 숫자
		// listen을 함으로써, 리시브를 할 수 있는 서버가 된 것.
	{
		cout << "listend error " << endl;
	}


	// 3-2. 클라이언트 연결 기다리기
	SOCKADDR_IN client_addr;
	SOCKET client_socket;
	int size_client_addr = sizeof(client_addr);
	client_socket = accept(h_socket, (SOCKADDR*)&client_addr, &size_client_addr);
	if (client_socket == SOCKET_ERROR) cout << "accept() failed" << endl;

	// 4. 클라이언트에게 send
	char send_data[255] = "hello";
	send(client_socket, send_data, strlen(send_data) + 1, 0);

	// 5. 소켓 종료 -> 윈속 종료
	closesocket(client_socket);
	closesocket(h_socket);
	WSACleanup();



}