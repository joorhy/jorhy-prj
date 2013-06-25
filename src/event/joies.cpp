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

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		CPcap pCap;
		pCap.InitialPcap();
		signal(SIGINT, OnSignal);
		while(bRun)
		{
			usleep(10000);
		}
		pCap.DestroyPcap();
	}
	else
	{
		for (int i=1; i<argc; ++i)
		{
			if (memcmp("-h", argv[i], 2) == 0)
			{
				printf("-h:test goose\n");
				printf("-c:create goose config by xxx.sdl\n");
			}
			else if (memcmp("-c", argv[i], 2) == 0)
			{
				CXGseScd gseHelper;
				gseHelper.Init();
				gseHelper.GetAllCtrlBlock();
				gseHelper.Deinit();
			}
			else if(memcmp("-t", argv[i], 2) == 0)
			{
				CXGooseCap gseCap;
				gseCap.TestGoose();
			}
			else
			{
				printf("%s command illegal\n");
			}
		}
	}

	return 0;
}
