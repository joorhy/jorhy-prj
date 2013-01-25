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
    printf("**************************************\n");
    printf("* Please enter 1-4 to select service *\n");
    printf("* 1:Generate config file             *\n");
    printf("* 2:Local Test                       *\n");
    printf("* 3:Capture GOOSE data               *\n");
    printf("* 4:Quit                             *\n");
    printf("**************************************\n");

    int c = getchar();
    if (c == '1')
    {
        CXGseScd gseHelper;
        gseHelper.Init();
        gseHelper.GetAllCtrlBlock();
        gseHelper.Deinit();
        return 0;
    }
    else if (c == '2')
    {
        CXGooseCap gseCap;
        gseCap.TestGoose();
        return 0;
    }
    else if (c == '3')
    {
        CXGooseCap gseCap;
        gseCap.GSE_InitialPcap();
        signal(SIGINT, OnSignal);
        while(bRun)
        {
            usleep(10000);
        }
        gseCap.GSE_DestroyPcap();
    }

	return 0;
}
