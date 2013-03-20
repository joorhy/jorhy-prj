#ifndef __X_GSE_SCD_H_
#define __X_GSE_SCD_H_

#include "tinyxml.h"
#include "json.h"
#include "x_scd_def.h"

struct GSE_DataInfo
{
    std::string desc;
    std::string data_type;
    std::string fc;
};
typedef std::vector<GSE_DataInfo *> GSE_AllDataVec;
struct GSE_DataSetInfo
{
    std::string desc;
    GSE_AllDataVec all_data;
};
typedef std::map<u_int32_t, GSE_DataSetInfo *> GSE_GocbMap; //key为appid

class CXGseScd
{
    public:
        CXGseScd();
        ~CXGseScd();

    public:
        int Init();
        void Deinit();
        int GetAllCtrlBlock();

    private:
        int ParseIEDs(TiXmlNode *pRootNode);
        int FindAppid(const std::string &ied_name, const std::string &ld_inst, const std::string &gocb,  u_int32_t &appid);
        int MakeDataSetInfo(TiXmlNode *pLN0Node, const std::string &ds_name, GSE_DataSetInfo *pDsInfo);
        int FindLNType(TiXmlNode *pLN0Node, const std::string &prefix, const std::string &ln_class, const std::string &ln_inst, const std::string &do_name, std::string &ds_desc, std::string &ln_type);
        int FindDAType(const std::string &ln_type, const std::string &do_name, const std::string &da_name, std::string &data_type);
        int FindType(const std::string &do_type, const std::string &da_name, std::string &data_type);

    private:
        TiXmlDocument m_xmlDoc;
        TiXmlNode *m_pCommNode;
        TiXmlNode *m_pDatTypeNode;

        GSE_GocbMap m_gocbMap;
};
#endif // __X_GSE_SCD_H_
