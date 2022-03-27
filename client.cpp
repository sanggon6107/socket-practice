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
	SOCKADDR_IN serv_addr; // 서버 주소를 나타내는 구조체.

	// 1. 윈속 초기화
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) cout << "failed to call SWAStartup()" << endl; // makeword 대신에 

	// 2. socket 생성
	h_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	// 전기를 공급할 때 220V, 110V 단자가 다르듯이, 네트워크에서는 소켓의 인자로 타입을 결정한다.
	// socket의 첫 번째 인자 :
	// af (address family). 주소의 falimy를 뜻한다.
	// 예를 들어, AF_INET은 인터넷 프로토콜 버전 4(IPv4) 주소 패맬리를 쓰겠다는 뜻. AF_INET6는 IPv6를 쓰겠다는 뜻.
	// 참고로 IPv4는 '한 바이트 . 한 바이트 . 한 바이트 . 한 바이트'의 형태이다.
	// PF_INET은 AF_INET을 #define 해놓은 것.
	// 
	// 두 번째 인자는 type. 소켓의 타입.
	// SOCK_STREAM : OOB 데이터 전송 메커니즘을 사용하여 순차적이고 신뢰할 수 있는 양방향 연결 기반 바이트 스트림을 제공하는 소켓 유형.
	// 이 소켓 유형은 AF_INET 또는 AF_INET6의 주소 패밀리에 대하여 TCP(전송 제어 프로토콜)을 사용한다.
	// 서버와 클라이언트가 지속적으로, 신호를 보내고, 받은 측은 신호를 받았으면 받았다고 알려준다(ACK). 그러니 신뢰할 수 있다.
	// 신호를 주고 받다 보니 1, 2, 3, 4 신호가 순서대로 처리된다.
	//
	// SOCK_DGRAM : 비표준(일반적으로 작은) 최대 길이의 비 연결적이고 신뢰할 수 없는 버퍼 인 데이터 그램을 지원하는 소켓 유형.
	// 이 소켓 유형은 AF_INET 또는 AF_INET6의 주소 패밀리에 대하여 사용자 데이터 그램 프로토콜(UDP)을 사용한다.
	// 서로 전달을 확인하지 않는다. 양방향적이지 않다. 또한 서로 신호를 확인하지 않으므로 신호 순서가 바뀔 수 있다.


	if (h_socket == INVALID_SOCKET)
	{
		cout << "Invalid socket!" << endl;
		WSACleanup();
	}


	// 3. 서버 연결
	// 3-1. 연결할 서버 주소 세팅
	memset(&serv_addr, 0, sizeof(serv_addr)); // serv_addr 크기만큼 모두 0으로.
	// memset 왜 하는가?
	// -> SOCKADDR_IN은 인자로 세 개를 쓰고 있는 것처럼 보이지만, 사실은 더 많다. 그래서 connect나 binding이
	// 안되는 등의 문제를 막기 위해 모두 0으로 초기화해주는 것.

	serv_addr.sin_family = AF_INET;                       // 서버 주소의 체계가 AF_INET(ipv4)
	inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr); // 서버 주소(ip) 설정. 127.0.0.1 : 공유기 밖으로 나가지 않고 자기 자신 주소로.
	serv_addr.sin_port = htons(30002);					  // 서버 port.
	// htons(host to network) 의 의미 : 데이터를 네트워크 바이트 순서로 변환한다. 통상적으로 서버는 대형 컴퓨터이고, 일반 가정의 컴퓨터와 구조가 다름.
	// 따라서 데이터가 저장되는 방식도 다름. 이것을 보정해주는 함수. 서버쪽의 기준으로 데이터 변환해준다.

	// 3-2. 서버에 연결 시도.
	if (connect(h_socket, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
		// connect는 블로킹 함수이다. 연결이 될 때까지 이 블럭을 벗어나지 않고
		// 계속 연결을 시도하다가, 계속 안되면 결국 실패 프린트.
	{
		cout << "connection failure" << endl;
	}

	// 4. 서버로부터 통신 대기
	int recieve_size;
	char recieve_data[255];
	recieve_size = recv(h_socket, recieve_data, sizeof(recieve_data), 0); // 여기도 데이터를 받을 때 까지는 밑으로 내려가지 않는다. 멈춰서 계속 대기.
																		  // 비동기 처리를 하는 함수도 있다.
	if (recieve_size == -1) cout << "recv error" << endl;

	cout << "recv " << recieve_size << " message : " << recieve_data << endl;

	// 5. 소켓 종료 -> 윈속 종료
	closesocket(h_socket); // socket()함수와 쌍.
	WSACleanup();          // WSAStartup()함수와 쌍.

	system("pause");

}