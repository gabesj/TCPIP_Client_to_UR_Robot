//if using MinGW, compile with g++ TCPIP_SocketClient.cpp -o TCPIP_SocketClient.exe -l ws2_32 -static-libgcc -static-libstdc++   
//allow this *.exe program through the firewall on the computer executing it.

#include <WinSock2.h>
#include <stdio.h>
#include <inttypes.h>  // To print unit64_t
//#include <string>   
//#include <iostream> 

#pragma warning(disable:4996)  // To use inet_addr()
#pragma comment(lib, "ws2_32.lib")

#define IP "192.168.1.140" 
#define PORT 29999
#define SIZE 10
#define DATATYPE uint64_t
#define MAX_BUF_LEN 2048



void error_handling(const char* msg); 



struct socketFrame {

	DATATYPE data[SIZE];

};



int main()

{

	WSADATA wsaData;
	
	SOCKET clientSocket;
	
	SOCKADDR_IN serverAddr;

	char data[MAX_BUF_LEN];

	struct socketFrame *socketData;

	int nRecv;

	int size = 0;

	int i;

	DATATYPE value;



	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)

		error_handling("Load Winsock 2.2 Error");



	clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (clientSocket == INVALID_SOCKET)

		error_handling("Socket Error");



	memset(&serverAddr, 0, sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;

	serverAddr.sin_addr.s_addr = inet_addr(IP);

	serverAddr.sin_port = htons(PORT);



	if (connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)

		error_handling("Connection Error");



	char command[] = "play"; /// "close safety popup" "power on" "brake release" "play" "unlock protective stop" "close popup"

	send(clientSocket, command, sizeof(command) - 1, 0);


/*
// This section is for receiving the response from the robot.  It is currently not used, but I may consider working it in later. 

	nRecv = recv(clientSocket, data, sizeof(data) - 1, 0);



	if (nRecv == SOCKET_ERROR)

		error_handling("Receive Error");

	data[nRecv] = '\0';

	socketData = (struct socketFrame*)data;

	for(i=0;i<SIZE;i++) {

		value = socketData->data[i];

	}

*/	

	
	closesocket(clientSocket);

	WSACleanup();



	return 0;

}



void error_handling(const char* msg) {

	MessageBox(NULL, msg, "Error", MB_OK);

	exit(1);

}