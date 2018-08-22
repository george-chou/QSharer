#include "stdafx.h"
#include "Thread_Create.h"


Thread_Create::Thread_Create(QString ssid, QString key) : QThread()
{ 
	SSID = ssid;
	KEY = key;  

	//int t = sf.InitSharing();
}


Thread_Create::~Thread_Create()
{
	hf.ExitHostedNetWork();
	//sf.ExitSharing();
}

void Thread_Create::run(void)
{ 

	initHost();
	stopPrevHost();
	setHost(SSID, KEY);
	startHost();
	shareHost(); 
	  
	int PeerNum = hf.GetPeerNumber();
	if (PeerNum >= 0) emit cSuccess(PeerNum);

}

void Thread_Create::initHost(void)
{

	if (hf.InitHostedNetWork() != 0)
	{
		emit FailedList_Create(0);    //throw QString("Failed to initiate hosted network!");  
		terminate();

	}

	if (hf.HostedNetworkOn() == -2)
	{
		emit FailedList_Create(1);    //throw QString("Wlan hosted network unavailable!"); 
		terminate();
	} 

}

void Thread_Create::stopPrevHost(void)
{

	bool isIDLE = (hf.HostedNetworkOn() == -3);
	bool stopFailed = false;
	bool timeOut = false;
	int TryTimes = 0;
	int MaxTryTimes = 3;

	while (!isIDLE && !timeOut)
	{
		if (hf.StopHostedNetWork() != 0)
		{
			stopFailed = true;
			break;
		}
		TryTimes++;
		timeOut = (TryTimes > MaxTryTimes);
		isIDLE = (hf.HostedNetworkOn() == -3);
	}

	if (timeOut || stopFailed)
	{
		emit FailedList_Create(2);    //throw QString("Failed to stop previous hosted network!");
		terminate();
	}

}

void Thread_Create::setHost(QString ssid, QString key)
{
	const char *wifiname = QStrToChar(ssid);
	const char *password = QStrToChar(key);

	if (hf.AllowHostedNetWork(true) != 0)
	{
		emit FailedList_Create(3);		//throw QString("Failed to allow hosted network!");
		terminate();
	}

	if (hf.SetSSID(wifiname) != 0)
	{
		emit FailedList_Create(4);    //throw QString("Failed to get ssid!");
		terminate();
	}

	if (hf.SetKEY(password) != 0)
	{
		emit FailedList_Create(5);    //throw QString("Failed to get key!");
		terminate();
	}

}

void Thread_Create::startHost(void)
{
	if (hf.StartHostedNetWork() != 0)
	{
		emit FailedList_Create(6);    //throw QString("Failed to start hosted network!"); 
		terminate();
	}

}


//void Thread_Create::unsharePrevHost(void)
//{
//	if (false)
//	{
//		emit FailedList_Create(7);    //throw QString("Failed to sharer hosted network!"); 
//		terminate();
//	}
//
//}


void Thread_Create::shareHost(void)
{
	if (sf.StartSharing() != 0)
	{
		emit FailedList_Create(7);    //throw QString("Failed to sharer hosted network!"); 
		terminate();
	}
}
 