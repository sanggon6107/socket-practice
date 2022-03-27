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
	SOCKADDR_IN serv_addr; // ���� �ּҸ� ��Ÿ���� ����ü.

	// 1. ���� �ʱ�ȭ
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) cout << "failed to call SWAStartup()" << endl; // makeword ��ſ� 

	// 2. socket ����
	h_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	// ���⸦ ������ �� 220V, 110V ���ڰ� �ٸ�����, ��Ʈ��ũ������ ������ ���ڷ� Ÿ���� �����Ѵ�.
	// socket�� ù ��° ���� :
	// af (address family). �ּ��� falimy�� ���Ѵ�.
	// ���� ���, AF_INET�� ���ͳ� �������� ���� 4(IPv4) �ּ� �иȸ��� ���ڴٴ� ��. AF_INET6�� IPv6�� ���ڴٴ� ��.
	// ����� IPv4�� '�� ����Ʈ . �� ����Ʈ . �� ����Ʈ . �� ����Ʈ'�� �����̴�.
	// PF_INET�� AF_INET�� #define �س��� ��.
	// 
	// �� ��° ���ڴ� type. ������ Ÿ��.
	// SOCK_STREAM : OOB ������ ���� ��Ŀ������ ����Ͽ� �������̰� �ŷ��� �� �ִ� ����� ���� ��� ����Ʈ ��Ʈ���� �����ϴ� ���� ����.
	// �� ���� ������ AF_INET �Ǵ� AF_INET6�� �ּ� �йи��� ���Ͽ� TCP(���� ���� ��������)�� ����Ѵ�.
	// ������ Ŭ���̾�Ʈ�� ����������, ��ȣ�� ������, ���� ���� ��ȣ�� �޾����� �޾Ҵٰ� �˷��ش�(ACK). �׷��� �ŷ��� �� �ִ�.
	// ��ȣ�� �ְ� �޴� ���� 1, 2, 3, 4 ��ȣ�� ������� ó���ȴ�.
	//
	// SOCK_DGRAM : ��ǥ��(�Ϲ������� ����) �ִ� ������ �� �������̰� �ŷ��� �� ���� ���� �� ������ �׷��� �����ϴ� ���� ����.
	// �� ���� ������ AF_INET �Ǵ� AF_INET6�� �ּ� �йи��� ���Ͽ� ����� ������ �׷� ��������(UDP)�� ����Ѵ�.
	// ���� ������ Ȯ������ �ʴ´�. ����������� �ʴ�. ���� ���� ��ȣ�� Ȯ������ �����Ƿ� ��ȣ ������ �ٲ� �� �ִ�.


	if (h_socket == INVALID_SOCKET)
	{
		cout << "Invalid socket!" << endl;
		WSACleanup();
	}


	// 3. ���� ����
	// 3-1. ������ ���� �ּ� ����
	memset(&serv_addr, 0, sizeof(serv_addr)); // serv_addr ũ�⸸ŭ ��� 0����.
	// memset �� �ϴ°�?
	// -> SOCKADDR_IN�� ���ڷ� �� ���� ���� �ִ� ��ó�� ��������, ����� �� ����. �׷��� connect�� binding��
	// �ȵǴ� ���� ������ ���� ���� ��� 0���� �ʱ�ȭ���ִ� ��.

	serv_addr.sin_family = AF_INET;                       // ���� �ּ��� ü�谡 AF_INET(ipv4)
	inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr); // ���� �ּ�(ip) ����. 127.0.0.1 : ������ ������ ������ �ʰ� �ڱ� �ڽ� �ּҷ�.
	serv_addr.sin_port = htons(30002);					  // ���� port.
	// htons(host to network) �� �ǹ� : �����͸� ��Ʈ��ũ ����Ʈ ������ ��ȯ�Ѵ�. ��������� ������ ���� ��ǻ���̰�, �Ϲ� ������ ��ǻ�Ϳ� ������ �ٸ�.
	// ���� �����Ͱ� ����Ǵ� ��ĵ� �ٸ�. �̰��� �������ִ� �Լ�. �������� �������� ������ ��ȯ���ش�.

	// 3-2. ������ ���� �õ�.
	if (connect(h_socket, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
		// connect�� ���ŷ �Լ��̴�. ������ �� ������ �� ���� ����� �ʰ�
		// ��� ������ �õ��ϴٰ�, ��� �ȵǸ� �ᱹ ���� ����Ʈ.
	{
		cout << "connection failure" << endl;
	}

	// 4. �����κ��� ��� ���
	int recieve_size;
	char recieve_data[255];
	recieve_size = recv(h_socket, recieve_data, sizeof(recieve_data), 0); // ���⵵ �����͸� ���� �� ������ ������ �������� �ʴ´�. ���缭 ��� ���.
																		  // �񵿱� ó���� �ϴ� �Լ��� �ִ�.
	if (recieve_size == -1) cout << "recv error" << endl;

	cout << "recv " << recieve_size << " message : " << recieve_data << endl;

	// 5. ���� ���� -> ���� ����
	closesocket(h_socket); // socket()�Լ��� ��.
	WSACleanup();          // WSAStartup()�Լ��� ��.

	system("pause");

}