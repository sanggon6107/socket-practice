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

	// 1. ���� �ʱ�ȭ
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) cout << "failed to call SWAStartup()" << endl; // makeword ��ſ� 

	// 2. socket ����
	h_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	// ���⸦ ������ �� 220V, 110V ���ڰ� �ٸ�����, ��Ʈ��ũ������ ������ ���ڷ� Ÿ���� �����Ѵ�.
	// socket�� ù ��° ���� :
	// af (address family). �ּ��� falimy�� ���Ѵ�.
	// ���� ���, AF_INET�� ���ͳ� �������� ���� 4(IPv4) �ּ� �иȸ��� ���ڴٴ� ��. AF_INET6�� IPv6�� ���ڴٴ� ��.
	// PF_INET�� AF_INET�� #define �س��� ��.
	if (h_socket == INVALID_SOCKET)					cout << "Invalid socket!" << endl;
}