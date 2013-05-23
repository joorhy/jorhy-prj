#include "joies.h"
#include "jo_pcap.h"
#include "x_goose.h"
#include "x_gse_scd.h"

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
#if 0
	CPcap pCap;
	pCap.InitialPcap();
	signal(SIGINT, OnSignal);
	while(bRun)
	{
		usleep(10000);
	}
	pCap.DestroyPcap();
#else
        //CXGseScd gseHelper;
        //gseHelper.Init();
        //gseHelper.GetAllCtrlBlock();
        //gseHelper.Deinit();
		CXGooseCap gseCap;
        gseCap.TestGoose();
#endif

	return 0;
}
