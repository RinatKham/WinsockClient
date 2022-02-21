#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>

#pragma warning(disable: 4996)

using namespace std;

int main()
{
	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1703);
	addr.sin_family = AF_INET;

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		cout << "Error: failed connect to server.\n";
		return 1;
	}
	else
	{
		cout << "Connected!\n";
		char sum[256] = "0";
		int result;
		while (true)
		{
			if (send(Connection, NULL, NULL, NULL) != -1)
			{
				recv(Connection, sum, sizeof(sum), NULL);
				if (sum != NULL)
				{
					result = atoi(sum);
					if (result > 10 && result % 32 == 0)
					{
						cout << "Data received" << endl;
					}
					else
					{
						cout << "Error! Bad data" << endl;
					}
				}
			}
			else
			{
				closesocket(Connection);
				cout << "Please, start the first programm" << endl;
				system("pause");
				Connection = socket(AF_INET, SOCK_STREAM, NULL);
				connect(Connection, (SOCKADDR*)&addr, sizeof(addr));
			}
		}
	}
	return 0;
}