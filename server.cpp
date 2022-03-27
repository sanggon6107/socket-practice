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

	// 1. ���� �ʱ�ȭ
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) cout << "WSAStartup() failed" << endl;

	// 2. socket ����
	h_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (h_socket == INVALID_SOCKET)
	{
		WSACleanup();
		cout << "socket() failed" << endl;
	}

	// 3. ���� �ڽ��� �ּҸ� ����
	// 3-1. ���� �ּ� ����
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_port = htons(30002);
	if (bind(h_socket, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
		// bind : ������ ���ϰ� ip�� �������ִ� �Լ�. �� SOCKET ��ü h_socket�� SOCKETADDR_IN ��ü serv_addr�� �������ش�.
	{
		cout << "binding error" << endl;
	}
	if (listen(h_socket, 5) == SOCKET_ERROR) 
		// listen�� ���� �ּҰ� �ԷµǾ��ִ� ����, ���ÿ� ó���� �� �ִ� ����
		// listen�� �����ν�, ���ú긦 �� �� �ִ� ������ �� ��.
	{
		cout << "listend error " << endl;
	}

	// 3-2. Ŭ���̾�Ʈ ���� ��ٸ���
	SOCKADDR_IN client_addr;
	SOCKET client_socket;
	int size_client_addr = sizeof(client_addr);
	client_socket = accept(h_socket, (SOCKADDR*)&client_addr, &size_client_addr); // blocking �Լ�. Ŭ���̾�Ʈ���� connect�� ������ ��ٸ���.
	// accept�� ��� client_socket�̶�� socket�� �ϳ� ���ϵȴ�. Ŭ���̾�Ʈ ���� ���ϰ� �� client_socket�� ����Ǵ� ��.
	// h_socket�� listen�� �ϱ� ���� ������ ����. connect���� ���.
	// ���� <-> Ŭ���̾�Ʈ ���� ������ ������ client_socket�� ���� Ŭ���̾�Ʈ�� �ִ� ������ �Ѵ�.
	if (client_socket == SOCKET_ERROR) cout << "accept() failed" << endl;

	// 4. Ŭ���̾�Ʈ���� send
	char send_data[255] = "hello";
	send(client_socket, send_data, strlen(send_data) + 1, 0);

	// 5. ���� ���� -> ���� ����
	closesocket(client_socket);
	closesocket(h_socket);
	WSACleanup();



}