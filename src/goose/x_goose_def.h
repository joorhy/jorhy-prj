#ifndef __X_GOOSE_DEF_H_
#define __X_GOOSE_DEF_H_

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
#include <map>

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

#endif//~__X_GOOSE_DEF_H_