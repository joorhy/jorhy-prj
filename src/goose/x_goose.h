#ifndef X_GOOSE_H_INCLUDED
#define X_GOOSE_H_INCLUDED

#include <sys/socket.h>
#include <sys/types.h>
#include <pcap.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#include <vector>

#include "x_scd.h"

#define ETHER_ADDR_LEN      6
#define PCAP_ERRBUF_SIZE    256
#define PCAP_SNAPLEN        65535

#define GSE_TAG_GOCBREF             0x80
#define GSE_TAG_TIMEALLOWEDTOLIVE   0x81
#define GSE_TAG_DATASET             0x82
#define GSE_TAG_GOID                0x83
#define GSE_TAG_EVENTTIME           0x84
#define GSE_TAG_STNUM               0x85
#define GSE_TAG_SQNUM               0x86
#define GSE_TAG_TEST                0x87
#define GSE_TAG_CONFREF             0x88
#define GSE_TAG_NDSCOM              0x89
#define GSE_TAG_TOTLENUM            0x8A

#define GSE_TAG_ACCESS_RESULT       0x80    //reserved
#define GSE_TAG_ARRAY               0x81
#define GSE_TAG_STRUCTURE           0x82
#define GSE_TAG_BOOL                0x83
#define GSE_TAG_DBPOS               0x84
#define GSE_TAG_INT32               0x85
#define GSE_TAG_UINT32              0x86
#define GSE_TAG_FLOATING_POINT      0x87
#define GSE_TAG_REAL                0x88
#define GSE_TAG_OCTET_STRING        0x89
#define GSE_TAG_VISBAL_STRING       0x8A
#define GSE_TAG_BINARY_TIME         0x8B
#define GSE_TAG_BCD                 0x8C
#define GSE_TAG_BOOLEAN_ARRAY       0x8D
#define GSE_TAG_UTC_TIME            0x91

struct GSE_MAC_Header
{
    u_char ether_dhost[ETHER_ADDR_LEN];     //MAC目的地址
    u_char ether_shost[ETHER_ADDR_LEN];     //MAC源地址
};

struct GSE_Ether_Header
{
    //u_char ether_tpid[2];                   //0x8100
    //u_char ether_tci[2];                    //0x4000
    u_char ether_type[2];                   //0x88B8
    u_char ether_appid[2];                  //0x0000~0x3FFF
    u_char ether_length[2];                 //8 + m
    u_char ether_reserved1[2];              //0x0000
    u_char ether_reserved2[2];              //0x0000
};

struct GSE_String
{
    u_short len;
    u_char data[65];
};

struct GSE_Goose_Header
{
    u_int32_t gse_appid;
    GSE_String gse_gocbRef;
    u_int32_t gse_tmAllowToLive;
    GSE_String gse_dataSetName;
    GSE_String gse_goid;
    u_int64_t gse_tmStateChange;
    u_int32_t gse_stNum;
    u_int32_t gse_sqNum;
    bool gse_testFlag;
    u_int32_t gse_confRev;
    bool gse_ndsCom;
    u_int32_t gse_totleNum;
};

struct GSE_Goose_Packet
{
    GSE_Goose_Header header;
    char *all_data[1];
};

typedef std::map<u_int32_t, GSE_Goose_Packet *> GSE_PacketMap;

class CXGooseCap
{
    public:
        CXGooseCap();
        ~CXGooseCap();

    public:
        int GSE_InitialPcap();
        int GSE_DestroyPcap();
        int TestGoose();

    private:
        static void *GSE_Thread(void *param)
        {
            CXGooseCap *pThis = (CXGooseCap *)param;
            if (pThis)
                pThis->GSE_CaptureData();

            return (void *)0;
        }
        void GSE_CaptureData();
        int GSE_AnalyzePacket(struct pcap_pkthdr &packet_header, const u_char *packet_data);
        u_short GSE_AnalyzeHead(const u_char *gse_head, u_short gse_totle_len);
        u_short GSE_AnalyzeData(const u_char *gse_data, u_short gse_data_len);
        void GSE_NotifyManager(const u_char *old, const u_char *cur);
        u_short GSE_GetString(const u_char *src, u_char *dst);
        u_short GSE_GetUINT32(const u_char *src, u_int32_t &dst);
        u_short GSE_GetUINT64(const u_char *src, u_int64_t &dst);
        u_short GSE_GetBoolean(const u_char *src, bool &dst);
        u_short GSE_GetDataLen(const u_char *data);
        int GSE_SendJson(int cid, int nid, int type, const u_char *data);

    private:
        char *m_dev;
        char m_errBuff[PCAP_ERRBUF_SIZE];
        bpf_u_int32 m_mask;
        bpf_u_int32 m_net;
        pcap_t *m_handle;
        struct bpf_program m_bf;
        pthread_t m_thread;

        GSE_Goose_Header m_gseHeader;
        GSE_PacketMap m_packetMap;

        int m_stNum;
        //CXSdl m_sdlParser;
};

#endif // X_GOOSE_H_INCLUDED
