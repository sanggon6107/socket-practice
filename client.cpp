#include <stdio.h>
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>

#pragma comment( lib, "ws2_32.lib")

using namespace std;

int main()
{
	WSADATA wsa_data;
	SOCKET h_socket;
	SOCKADDR_IN serv_addr;

	// 1. 윈속 초기화
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) cout << "failed to call SWAStartup()" << endl; // makeword 대신에 

	// 2. socket 생성
	h_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	// 전기를 공급할 때 220V, 110V 단자가 다르듯이, 네트워크에서는 소켓의 인자로 타입을 결정한다.
	// socket의 첫 번째 인자 :
	// af (address family). 주소의 falimy를 뜻한다.
	// 예를 들어, AF_INET은 인터넷 프로토콜 버전 4(IPv4) 주소 패맬리를 쓰겠다는 뜻. AF_INET6는 IPv6를 쓰겠다는 뜻.
	// PF_INET은 AF_INET을 #define 해놓은 것.
	if (h_socket == INVALID_SOCKET)					cout << "Invalid socket!" << endl;
}