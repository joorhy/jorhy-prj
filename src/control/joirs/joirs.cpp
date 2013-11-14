#include "NodeManager.h"

bool bRun = true;
int main(int argc, char **argv)
{
	/// 节点管理服务器
	CNodeManager nodeManager;
	nodeManager.Start(8925);
	/// 内容管理服务器
	while(bRun)
	{
		j_sleep(10);
	}
	nodeManager.Stop();

	return 0;
}