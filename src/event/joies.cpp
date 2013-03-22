#include "joies.h"
#include "jo_pcap.h"

bool bRun = true;

void OnSignal(int nSigNum)
{
	if (nSigNum == SIGINT)
	{
		printf("Quit CapServer\n");
		bRun = false;
	}
};

int main()
{
	CPcap pCap;
	pCap.InitialPcap();
	signal(SIGINT, OnSignal);
	while(bRun)
	{
		usleep(10000);
	}
	pCap.DestroyPcap();


	return 0;
}
