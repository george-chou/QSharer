#pragma once

#include<iostream>
using namespace std;

#include <Sensapi.h>
#pragma comment(lib, "Sensapi.lib")

#include <Wlanapi.h>
#pragma comment(lib, "wlanapi.lib")

class HostNetlib
{
public:  
	
	int InitHostedNetWork(void);
	int ExitHostedNetWork(void);
	int StartHostedNetWork(void);
	int StopHostedNetWork(void); 
	int HostedNetworkOn(void); 
	int AllowHostedNetWork(bool);
	int SetKEY(const char *);
	int SetSSID(const char *);
	int GetPeerNumber(void);
	QString GetMacAt(int);
	QString GetKEY(void);
	QString GetSSID(void);

private:
	 
	HANDLE hClient;

};

