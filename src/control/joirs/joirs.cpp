#include "NodeManager.h"
#include "x_mem_pool.h"
#include <ddraw.h>
#include <pcap.h>

bool bRun = true;
int main(int argc, char **argv)
{
	printf("%x\n", DDERR_UNSUPPORTEDFORMAT);
	pcap_if_t * allAdapters;//适配器列表
	pcap_if_t * adapter;
	pcap_t           * adapterHandle;//适配器句柄
	struct pcap_pkthdr * packetHeader;
	const u_char       * packetData;
	char errorBuffer[ PCAP_ERRBUF_SIZE ];//错误信息缓冲区
	if( pcap_findalldevs_ex( PCAP_SRC_IF_STRING, NULL, 
		&allAdapters, errorBuffer ) == -1 )
	{
		//检索机器连接的所有网络适配器
		fprintf( stderr, "Error in pcap_findalldevs_ex function: %s\n", errorBuffer );
		return -1;
	}
	if( allAdapters == NULL )
	{
		//不存在任何适配器
		printf( "\nNo adapters found! Make sure WinPcap is installed.\n" );
		return 0;
	}
	int crtAdapter = 0;
	for( adapter = allAdapters; adapter != NULL; adapter = adapter->next)
	{
		//遍历输入适配器信息(名称和描述信息)
		printf( "\n%d.%s ", ++crtAdapter, adapter->name ); 
		printf( "-- %s\n", adapter->description );
	}
	printf( "\n" );
	//选择要捕获数据包的适配器
	int adapterNumber;
	printf( "Enter the adapter number between 1 and %d:", crtAdapter );
	scanf_s( "%d", &adapterNumber );
	if( adapterNumber < 1 || adapterNumber > crtAdapter )
	{
		printf( "\nAdapter number out of range.\n" );
		// 释放适配器列表
		pcap_freealldevs( allAdapters );
		return -1;
	}
	adapter = allAdapters;
	for( crtAdapter = 0; crtAdapter < adapterNumber - 1; crtAdapter++ )
		adapter = adapter->next;
	// 打开指定适配器
	adapterHandle = pcap_open( adapter->name, // name of the adapter
		65536,			// portion of the packet to capture
							// 65536 guarantees that the whole 
							// packet will be captured
		PCAP_OPENFLAG_PROMISCUOUS, // promiscuous mode
		1000,            // read timeout - 1 millisecond
		NULL,			// authentication on the remote machine
		errorBuffer   // error buffer
		);
	if( adapterHandle == NULL )
	{
		//指定适配器打开失败
		fprintf( stderr, "\nUnable to open the adapter\n", adapter->name );
		// 释放适配器列表
		pcap_freealldevs( allAdapters );
		return -1;
	}
	else
	{
		bpf_u_int32 netmask;
		bpf_program fcode;
		if (allAdapters->addresses != NULL)
			/* 获取接口第一个地址的掩码 */
			netmask=((struct sockaddr_in *)(allAdapters->addresses->netmask))->sin_addr.S_un.S_addr;
		else
			/* 如果这个接口没有地址，那么我们假设这个接口在C类网络中 */
			netmask=0xffffff;


		//compile the filter
		if (pcap_compile(adapterHandle, &fcode, "tcp port 1935", 1, netmask) < 0)
		{
			fprintf(stderr, "nUnable to compile the packet filter. Check the syntax.n");
			/* 释放设备列表 */
			pcap_freealldevs(allAdapters);
			return -1;
		}

		//set the filter
		if (pcap_setfilter(adapterHandle, &fcode) < 0)
		{
			fprintf(stderr,"nError setting the filter.n");
			/* 释放设备列表 */
			pcap_freealldevs(allAdapters);
			return -1;
		} 
	}
	printf( "\nCapture session started on  adapter %s\n", adapter->name );
	pcap_freealldevs( allAdapters );//释放适配器列表
	// 开始捕获数据包
	int retValue;
	while( ( retValue = pcap_next_ex( adapterHandle, 
		&packetHeader, 
		&packetData ) ) >= 0 )
	{
		// timeout elapsed if we reach this point
		if( retValue == 0 )
			continue;
		//打印捕获数据包的信息
		//if (packetHeader->len > 60)
		{
			static FILE * fp = NULL;
			if (fp == NULL)
				fp = fopen("F://test.amf", "wb+");
			fwrite(packetData, 1, packetHeader->len, fp);
			fflush(fp);
		}

		printf( "length of packet: %d\n", packetHeader->len );
	}
	// if we get here, there was an error reading the packets
	if( retValue == -1 )
	{
		printf( "Error reading the packets: %s\n", pcap_geterr( adapterHandle ) );
		return -1;
	}
	system( "PAUSE" );
	return 0;

	CXMemPool memPool;
	int nTotleSize = 0;
	memPool.Create(1024*1024);

	//printf("begin %d\n", GetTickCount());
	//for (int n=0; n<100000; ++n)
	//{
	//	//void *p = malloc(10);
	//	//free(p);
	//	void *p = memPool.Alloc(10);
	//	memPool.Free(p);
	//}
	//printf("end %d\n", GetTickCount());
	//return 0;
	j_void_t *p[1000] = {0};
	while (true)
	{
		for (int i=0; i<1000; ++i)
		{
			p[i] = NULL;
			int size = rand() % 256;
			p[i] = memPool.Alloc(size);
			printf("%d %d %d\n", p[i], size, i);
		}

		int n = 1000;
		while (true)
		{
			if (n == 0)
				break;
			int m = rand() % 1000;
			if (p[m] != NULL)
			{
					memPool.Free(p[m]);
					printf("free %d %d\n", p[m], m);
					p[m] = NULL;
					--n;
			}
		}
		//for (int i=9999; i>0; --i)
		//{
		//	memPool.Free(p[i]);
		//	printf("free %d %d\n", p[i], i);
		//}
	}
	//while (true)
	//{
	//	int size = rand() % 1024;
	//	j_void_t *p = memPool.Alloc(size);
	//	printf("%d %d %d\n", p, size, nTotleSize);
	//	if (p == NULL)
	//		break;
	//	nTotleSize += size;
	//	//if ((size % 2) == 0)
	//	{
	//		memPool.Free(p);
	//		nTotleSize -= size;
	//		printf("free %d %d\n", p, size);
	//	}
	//}
	memPool.Destroy();
	/// 节点管理服务器
	//CNodeManager nodeManager;
	//nodeManager.Start(8925);
	/// 内容管理服务器
	//while(bRun)
	//{
	//	j_sleep(10);
	//}
	//nodeManager.Stop();

	return 0;
}