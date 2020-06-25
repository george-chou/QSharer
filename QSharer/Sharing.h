#pragma once
#include "NetCon.h" 

class Sharing
{
public:
	Sharing();
	~Sharing();

	int StartSharing(void);
	int StopSharing(void); 

private:

	bool isDest(QString, int);
	bool isSource(QString, int);

	//void InitSharing(INetSharingManager *, INetSharingEveryConnectionCollection *, IUnknown *, IEnumVARIANT *, INetConnection *, INetSharingConfiguration  *, VARIANT);
	void InitCon(void);
	void ExitCon(void);

};

