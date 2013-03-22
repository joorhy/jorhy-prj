#ifndef X_GOOSE_H_INCLUDED
#define X_GOOSE_H_INCLUDED

#include <vector>
#include "x_goose_def.h"
#include "x_scd.h"
#include "j_module.h"

class CXGooseCap : public J_EventParser
{
    public:
        CXGooseCap();
        ~CXGooseCap();

	public:
		//J_EventParser
        virtual int AnalyzePacket(const unsigned char *pEventData);

    private:
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
        GSE_Goose_Header m_gseHeader;
        GSE_PacketMap m_packetMap;

        int m_stNum;
        //CXSdl m_sdlParser;
};

#endif // X_GOOSE_H_INCLUDED
