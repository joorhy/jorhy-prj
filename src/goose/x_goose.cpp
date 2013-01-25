#include "x_goose.h"
#include "gse_config.h"
#include "json.h"
#include "ghttp.h"
#include "assert.h"
#include "errno.h"

const char *gse_filter_exp = "ether proto 0x88B8";

CXGooseCap::CXGooseCap()
{
    m_dev = NULL;
    memset(m_errBuff, 0, sizeof(m_errBuff));
    m_mask = 0;
    m_net = 0;
    m_handle = NULL;
    m_thread = 0;
    m_stNum = 0;

    //m_sdlParser.LoadXMLFile("20120728.scd");
}

CXGooseCap::~CXGooseCap()
{

}

int CXGooseCap::GSE_InitialPcap()
{
    m_dev = pcap_lookupdev(m_errBuff);
    if (m_dev == NULL)
    {
        printf("CXGooseCap::GSE_InitialPcap Could not find default device:%s\n", m_errBuff);
        return J_DEV_ERR;
    }
    printf("CXGooseCap::GSE_InitialPcap device:%s\n", m_dev);

    if (pcap_lookupnet(m_dev, &m_net, &m_mask, m_errBuff) == -1)
    {
        printf("CXGooseCap::GSE_InitialPcap Counld not get netmask for device %s;%s\n", m_dev ,m_errBuff);
        m_net = 0;
        m_mask = 0;
    }

    m_handle = pcap_open_live(m_dev, PCAP_SNAPLEN, 1, 1000, m_errBuff);
    if (m_handle == NULL)
    {
        printf("CXGooseCap::GSE_InitialPcap Could not open device %s;%s", m_dev, m_errBuff);
        return J_DEV_ERR;
    }

    if (pcap_compile(m_handle, &m_bf, gse_filter_exp, 0, m_net) == -1)
    {
        printf("CXGooseCap::GSE_InitialPcap Counld not parse filter %s;%s\n", gse_filter_exp, pcap_geterr(m_handle));
        return J_DEV_ERR;
    }

    if (pcap_setfilter(m_handle, &m_bf) == -1)
    {
        printf("CXGooseCap::GSE_InitialPcap Counld not install filter %s;%s\n", gse_filter_exp, pcap_geterr(m_handle));
        return J_DEV_ERR;
    }
    pcap_freecode(&m_bf);

    if (pthread_create(&m_thread, NULL, CXGooseCap::GSE_Thread, this) != 0)
    {
        printf("CXGooseCap::GSE_InitialPcap Counld not create thread\n");
        return J_DEV_ERR;
    }
    pthread_detach(m_thread);

    return J_OK;
}

int CXGooseCap::GSE_DestroyPcap()
{
    if (pthread_cancel(m_thread) != 0)
    {
        printf("CXGooseCap::GSE_DestroyPcap Counld not cancel thread\n");
        return J_OPR_ERR;
    }

    if (m_handle)
    {
        pcap_close(m_handle);
        m_handle = NULL;
    }

    return J_OK;
}

int CXGooseCap::TestGoose()
{
    struct pcap_pkthdr packet_header = {0};
    FILE *f_gsecap = fopen("goose.cap_2", "rb");
    assert(f_gsecap != NULL);
    u_char packet_data[1500] = {0};
    u_char *test = packet_data;
    int nReadRet = 0;
    int nHeaderLen = sizeof(GSE_Ether_Header) + sizeof (GSE_MAC_Header);
    while (true)
    {
        memset(packet_data, 0, sizeof(packet_data));
        nReadRet = fread(packet_data, 1, nHeaderLen, f_gsecap);
        if (nReadRet != nHeaderLen)
        {
            break;
        }
        GSE_Ether_Header *pHeader = (GSE_Ether_Header *)(packet_data + sizeof(GSE_MAC_Header));
        int asduLength = (pHeader->ether_length[0] << 8) + pHeader->ether_length[1] - 8;
        nReadRet = fread(packet_data + nHeaderLen, 1, asduLength, f_gsecap);
        if (nReadRet != asduLength)
        {
            break;
        }
        GSE_AnalyzePacket(packet_header, packet_data);
        //usleep(20 * 1000);
    }

    return J_OK;
}

void CXGooseCap::GSE_CaptureData()
{
    struct pcap_pkthdr *packet_header = NULL;
    const u_char *packet_data = NULL;
    int ret_val = 0;

    pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, NULL);
    while ((ret_val = pcap_next_ex(m_handle, &packet_header, &packet_data)) >= 0)
    {
        if (ret_val == 0)
        {
            usleep(10000);
            continue;
        }

        GSE_AnalyzePacket(*packet_header, packet_data);
    }
}

int CXGooseCap::GSE_AnalyzePacket(struct pcap_pkthdr &packet_header, const u_char *packet_data)
{
    //static FILE *fp = NULL;
    //if (fp == NULL)
    //    fp = fopen("goose.cap_2", "wb+");
    //fwrite(packet_data, 1, packet_header.len, fp);

    memset(&m_gseHeader, 0, sizeof(m_gseHeader));
    GSE_MAC_Header *macHeader = (GSE_MAC_Header *)packet_data;
    /*printf("源地址:%02X:%02X:%02X:%02X:%02X:%02X\n",
                            (macHeader->ether_shost)[0],
                            (macHeader->ether_shost)[1],
                            (macHeader->ether_shost)[2],
                            (macHeader->ether_shost)[3],
                            (macHeader->ether_shost)[4],
                            (macHeader->ether_shost)[5]);
    printf("目的地址:%02X:%02X:%02X:%02X:%02X:%02X\n",
                            (macHeader->ether_dhost)[0],
                            (macHeader->ether_dhost)[1],
                            (macHeader->ether_dhost)[2],
                            (macHeader->ether_dhost)[3],
                            (macHeader->ether_dhost)[4],
                            (macHeader->ether_dhost)[5]);*/

    GSE_Ether_Header *etherHeader = (GSE_Ether_Header *)(packet_data + sizeof(GSE_MAC_Header));
    //assert((etherHeader->ether_tpid[0]==0x81) && (etherHeader->ether_tpid[1]==0x00));
    //assert((etherHeader->ether_tci[0]==0x40) && (etherHeader->ether_tci[1]==0x00));
    assert((etherHeader->ether_type[0]==0x88) && (etherHeader->ether_type[1]==0xB8));
    //解析APPID
    m_gseHeader.gse_appid = (etherHeader->ether_appid[0] << 8) + etherHeader->ether_appid[1] + 1000;
    //if (!(etherHeader->ether_appid[0] == 0x01 && etherHeader->ether_appid[1] == 0x52))
    //    return J_OK;

    //printf("APPID:%02X%02X\n", etherHeader->ether_appid[0], etherHeader->ether_appid[1]);
    //printf("LENGTH:%02X%02X\n", etherHeader->ether_length[0], etherHeader->ether_length[1]);

    //解析GOOSE头信息
    u_short asduLength = (etherHeader->ether_length[0] << 8) + etherHeader->ether_length[1] - 8;
    const u_char *gseHeadInfo = packet_data + sizeof(GSE_MAC_Header) + sizeof(GSE_Ether_Header);
    assert(gseHeadInfo[0] == 0x61);
    u_short gseInfoLen = GSE_AnalyzeHead(gseHeadInfo, asduLength);
    //解析GOOSE开关量
    u_short gseDataLen = asduLength - gseInfoLen;
    const u_char *gseData = gseHeadInfo + gseInfoLen;
    assert(gseData[0] == 0xAB);
    GSE_AnalyzeData(gseData, gseDataLen);

    return J_OK;
}

u_short CXGooseCap::GSE_AnalyzeHead(const u_char *gse_head, u_short gse_totle_len)
{
    //头信息可占3位,也可占4位
    u_short nOffset = 2;//gse_data[1] == 数据长度
    if (gse_head[1] == 0x81)
        nOffset = 3;//gse_head[1] == 0x81
    else if (gse_head[1] == 0x82)
        nOffset = 4;
    //else
    //   printf("ASDUHeadLen = %d\n", gse_head[1]);

    u_short gse_len = 0;
    const u_char *gse_ptr = NULL;
    //解析GOCB_REF
    gse_ptr = gse_head + nOffset;
    assert((*gse_ptr & 0xFF) == GSE_TAG_GOCBREF);

    gse_len = GSE_GetString(gse_ptr, m_gseHeader.gse_gocbRef.data);
    m_gseHeader.gse_gocbRef.len = gse_len;
    nOffset += gse_len + 2;
    //解析有效时间
    gse_ptr = gse_head + nOffset;
    assert((*gse_ptr & 0xFF) == GSE_TAG_TIMEALLOWEDTOLIVE);
    gse_len = GSE_GetUINT32(gse_ptr, m_gseHeader.gse_tmAllowToLive);
    nOffset += gse_len + 2;
    //解析DataSet名字
    gse_ptr = gse_head + nOffset;
    assert((*gse_ptr & 0xFF) == GSE_TAG_DATASET);
    gse_len = GSE_GetString(gse_ptr, m_gseHeader.gse_dataSetName.data);
    m_gseHeader.gse_dataSetName.len = gse_len;
    nOffset += gse_len + 2;
    //解析GOID
    gse_ptr = gse_head + nOffset;
    assert((*gse_ptr & 0xFF) == GSE_TAG_GOID);
    gse_len = GSE_GetString(gse_ptr, m_gseHeader.gse_goid.data);
    m_gseHeader.gse_goid.len = gse_len;
    nOffset += gse_len + 2;
    //解析变位时间,精确到毫秒
    gse_ptr = gse_head + nOffset;
    assert((*gse_ptr & 0xFF) == GSE_TAG_EVENTTIME);
    gse_len = GSE_GetUINT64(gse_ptr, m_gseHeader.gse_tmStateChange);
    nOffset += gse_len + 2;
    //解析StNum
    gse_ptr = gse_head + nOffset;
    assert((*gse_ptr & 0xFF) == GSE_TAG_STNUM);
    gse_len = GSE_GetUINT32(gse_ptr, m_gseHeader.gse_stNum);
    nOffset += gse_len + 2;
    //解析SqNum
    gse_ptr = gse_head + nOffset;
    assert((*gse_ptr & 0xFF) == GSE_TAG_SQNUM);

    gse_len = GSE_GetUINT32(gse_ptr, m_gseHeader.gse_sqNum);
    nOffset += gse_len + 2;
    //解析测试标志
    gse_ptr = gse_head + nOffset;
    assert((*gse_ptr & 0xFF) == GSE_TAG_TEST);
    gse_len = GSE_GetBoolean(gse_ptr, m_gseHeader.gse_testFlag);
    nOffset += gse_len + 2;
    //解析配置版本号(配置次数)
    gse_ptr = gse_head + nOffset;
    assert((*gse_ptr & 0xFF) == GSE_TAG_CONFREF);
    u_int32_t gse_confRef;
    gse_len = GSE_GetUINT32(gse_ptr, gse_confRef);
    nOffset += gse_len + 2;
    //解析未配置好标志
    gse_ptr = gse_head + nOffset;
    assert((*gse_ptr & 0xFF) == GSE_TAG_NDSCOM);
    gse_len = GSE_GetBoolean(gse_ptr, m_gseHeader.gse_ndsCom);
    nOffset += gse_len + 2;
    //解析数据总个数
    gse_ptr = gse_head + nOffset;
    assert((*gse_ptr & 0xFF) == GSE_TAG_TOTLENUM);
    gse_len = GSE_GetUINT32(gse_ptr, m_gseHeader.gse_totleNum);
    nOffset += gse_len + 2;

    return nOffset;
}

u_short CXGooseCap::GSE_AnalyzeData(const u_char *gse_data, u_short gse_data_len)
{
    //头信息可占3位,也可占4位
    u_short nOffset = 2;//gse_data[1] == 数据长度
    if (gse_data[1] == 0x81)
        nOffset = 3;
    else if (gse_data[1] == 0x82)
        nOffset = 4;
    //else
    //   printf("ALLDataLen = %d\n", gse_data[1]);

    u_short nDataLen = gse_data_len - nOffset;
    const u_char *gse_ptr = gse_data + nOffset;
    GSE_PacketMap::iterator it = m_packetMap.find(m_gseHeader.gse_appid);
    if (it == m_packetMap.end())
    {
        GSE_Goose_Packet *pGsePacket = (GSE_Goose_Packet *)new char[sizeof(GSE_Goose_Packet) + nDataLen];
        memcpy(&pGsePacket->header, &m_gseHeader, sizeof(GSE_Goose_Header));
        memcpy(pGsePacket->all_data, gse_ptr, nDataLen);
        m_packetMap[m_gseHeader.gse_appid] = pGsePacket;
    }
    else
    {
        //还会有其他状况
        if (m_gseHeader.gse_stNum > it->second->header.gse_stNum)
        {
            GSE_NotifyManager((const u_char *)it->second->all_data, (const u_char *)gse_ptr);
            memcpy(it->second->all_data, gse_ptr, nDataLen);
        }
        memcpy(&it->second->header, &m_gseHeader, sizeof(GSE_Goose_Header));
    }

    return gse_data_len;
}

void CXGooseCap::GSE_NotifyManager(const u_char *old, const u_char *cur)
{
    int nOffset = 0;
    const u_char *gse_old_ptr = NULL;
    const u_char *gse_cur_ptr = NULL;
    u_short gse_len = 0;
    for (int i=0; i<m_gseHeader.gse_totleNum; i++)
    {
        gse_old_ptr = old + nOffset;
        gse_cur_ptr = cur + nOffset;
        assert(gse_old_ptr[0] == gse_cur_ptr[0]);
        gse_len = GSE_GetDataLen(gse_old_ptr);
        assert(gse_len == GSE_GetDataLen(gse_cur_ptr));
        switch (gse_old_ptr[0])
        {
            case GSE_TAG_BOOL:
                if ((gse_old_ptr[2] & 0xFF) != (gse_cur_ptr[2] & 0xFF))
                {
                    //printf("old = %d, new = %d\n", gse_old_ptr[2], gse_cur_ptr[2]);
                    //printf("cid = %d, node = %d, type = 1, data = %02X\n"
                    //       , m_gseHeader.gse_appid, i + 1, gse_cur_ptr[2]);
                    GSE_SendJson(m_gseHeader.gse_appid, i + 1, GSE_TAG_BOOL, gse_cur_ptr + 2);
                }
                break;
            case GSE_TAG_DBPOS:
                /*if ((gse_old_ptr[2] != gse_cur_ptr[2]) || (gse_old_ptr[3] != gse_cur_ptr[3]))
                {
                    printf("cid = %d, node = %d, type = 2, data = %02X%02X\n"
                           , m_gseHeader.gse_appid, i, gse_cur_ptr[2], gse_cur_ptr[3]);
                }*/
                break;
            case GSE_TAG_INT32:
            case GSE_TAG_UTC_TIME:
                /*if (memcmp(gse_old_ptr + 2, gse_cur_ptr + 2, gse_len) != 0)
                {
                    printf("cid = %d, node = %d, type = 3, data = %02X%02X\n"
                           , m_gseHeader.gse_appid, i, gse_cur_ptr[2], gse_cur_ptr[3]);
                }*/
                break;
            default:
                printf("CXGooseCap::GSE_AnalyzeData() Error Type:%02X\n", gse_old_ptr[0]);
                break;
        }
        nOffset += gse_len + 2;
    }
}

u_short CXGooseCap::GSE_GetString(const u_char *src, u_char *dst)
{
    assert(src!=NULL && dst!=NULL);
    //printf("GSE_TYPE:%02x\n", src[0]);
    u_short nLen = src[1];
    memcpy(dst, src + 2, nLen);

    /*printf("GSE_DATA:");
    for (int i=0; i<nLen; i++)
    {
        printf("%02x", dst[i]);
    }
    printf("\n");*/

    return nLen;
}

u_short CXGooseCap::GSE_GetUINT32(const u_char *src, u_int32_t &dst)
{
    assert(src != NULL);
    dst = 0;
    //printf("GSE_TYPE:%02x\n", src[0]);
    u_short nLen = src[1];
    //printf("GSE_DATA:");
    for (int i=1; i<=nLen; i++)
    {
        dst += src[i+1] << ((nLen-i)*8);
        //printf("%02x", src[i+1]);
    }
    //printf("\n");

    return nLen;
}

u_short CXGooseCap::GSE_GetUINT64(const u_char *src, u_int64_t &dst)
{
    assert(src != NULL);
    dst = 0;
    //printf("GSE_TYPE:%02x\n", src[0]);
    u_short nLen = src[1];
    //printf("GSE_DATA:");
    for (int i=1; i<=nLen; i++)
    {
        dst += src[i+1] << ((nLen-i)*8);
        //printf("%02x", src[i+1]);
    }
    //printf("\n");

    return nLen;
}

u_short CXGooseCap::GSE_GetBoolean(const u_char *src, bool &dst)
{
    assert(src != NULL);
    dst = 0;
    //printf("GSE_TYPE:%02x\n", src[0]);
    u_short nLen = src[1];
    assert(nLen == 1);
    //printf("GSE_DATA:%02X\n", src[2]);
    dst = src[2];

    return nLen;
}

u_short CXGooseCap::GSE_GetDataLen(const u_char *data)
{
    return data[1];
}

int CXGooseCap::GSE_SendJson(int cid, int nid, int type, const u_char *data)
{
    json_object *alm_body = json_object_new_object();
    json_object_object_add(alm_body, (char *)"cmd", json_object_new_int(103));
    json_object *alm_json = json_object_new_object();
    json_object_object_add(alm_json, (char *)"cid", json_object_new_int(cid));
    json_object_object_add(alm_json, (char *)"node", json_object_new_int(nid));
    switch (type)
    {
        case GSE_TAG_BOOL:
            json_object_object_add(alm_json, (char *)"type", json_object_new_int(1));
            json_object_object_add(alm_json, (char *)"ext", json_object_new_int(data[0]));
            break;
        default:
            assert(false);
            break;
    }
    json_object_object_add(alm_body, (char *)"parm", alm_json);
    printf("%s\n", json_object_to_json_string(alm_body));
    ghttp_request *p_conn = ghttp_request_new();
	ghttp_set_uri(p_conn, GetMCUrl());
	printf("%s\n", GetMCUrl());
	ghttp_set_type(p_conn, ghttp_type_post);
	ghttp_set_body(p_conn, json_object_to_json_string(alm_body), strlen(json_object_to_json_string(alm_body)));
	ghttp_prepare(p_conn);
	if (ghttp_process(p_conn) == ghttp_error)
	{
	    assert(false);
	}

    int i_state = ghttp_status_code(p_conn);
	switch(i_state)
	{
	case 200:
        break;
	default:
        assert(false);
		break;
	}
    ghttp_close(p_conn);
	ghttp_request_destroy(p_conn);

    json_object_put(alm_body);
    return J_OK;
}
