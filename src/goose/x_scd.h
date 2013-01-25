#ifndef __X_SCD_H_
#define __X_SCD_H_

#include "tinyxml.h"
#include "x_scd_def.h"

class CXSdl
{
    public:
        CXSdl();
        ~CXSdl();

    public:
        int LoadXMLFile(const char *filePath);

    private:
        int PaserHeader() { return 0; }
        int PaserSubstation() { return 0; }

        int PaserCommunication();
        int ProcMMS(TiXmlNode *pNode);
        int ProcGOOSE(TiXmlNode *pNode);
        int MakeGSECB(TiXmlNode *pNode, GSECB *pGsecb);
        int ProcSMV(TiXmlNode *pNode);

        int PaserIEDs();
        int ProcS1LD(TiXmlNode *pNode, LDInstMap &ldInstMap);

        int ProcG1LD(TiXmlNode *pNode, LDInstMap &ldInstMap);
        int ProcG1LN0(TiXmlNode *pNode, LN0Node *ln0Node);
        int MakeFCDAList(TiXmlNode *pNode, FCDAList &fcdaList);
        int ProcG1LN(TiXmlNode *pNode, LNMap &lnMap);
        int MakeDOMap(TiXmlNode *pNode, DOMap &doMap);

        int ProcM1LD(TiXmlNode *pNode, LDInstMap &ldInstMap);

        int PaserDataTypeTemplates();

    private:
        TiXmlDocument m_xmlDoc;
        TiXmlNode *m_pRootNode;

        //Communication 数据集
        MMSMap m_mmsCommMap;
        GOOSEMap m_gooseCommMap;
        SamValMap m_smvCommMap;

        //IED 数据集
        IEDMap m_iedMap;

        //DataTypeTemplages 数据集

};

#endif // __X_SCD_H_
