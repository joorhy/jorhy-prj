#include "x_scd.h"
#include "x_errtype.h"

GES_TAG(MMS, 8-MMS)
GES_TAG(GOOSE, IECGOOSE)
GES_TAG(SMV, SMV)

GES_TAG(IP, IP)
GES_TAG(IP_SUBNET, IP-SUBNET)

GES_TAG(MAC_ADDR, MAC-Address)
GES_TAG(VLAN_ID, VLAN-ID)
GES_TAG(VLAN_PROC, VLAN-PRIORITY)
GES_TAG(APPID, APPID)

GES_TAG(MMS_TYPE, S1)
GES_TAG(GOOSE_TYPE, G1)
GES_TAG(SMV_TYPE, M1)

CXSdl::CXSdl()
{

}

CXSdl::~CXSdl()
{

}

int CXSdl::LoadXMLFile(const char *filePath)
{
    if (!m_xmlDoc.LoadFile(filePath))
    {
        assert(false);
        printf("CXSdl::LoadXMLFile faild, file = %s\n", filePath);
        return J_XML_FLIE_ERROR;
    }
    m_pRootNode = NULL;
    m_pRootNode = m_xmlDoc.FirstChild("SCL");
    if (m_pRootNode == NULL)
    {
        assert(false);
        printf("CXSdl::LoadXMLFile faild, methord = m_xmlDoc.FirstChild(\"SCL\")\n");
        return J_XML_FLIE_ERROR;
    }

    if (PaserCommunication() != J_OK)
    {
        assert(false);
        printf("CXSdl::LoadXMLFile faild, methord = PaserCommunication()\n");
        return J_XML_FLIE_ERROR;
    }

    if (PaserIEDs() != J_OK)
    {
        assert(false);
        printf("CXSdl::LoadXMLFile faild, methord = PaserIEDs()\n");
        return J_XML_FLIE_ERROR;
    }

    if (PaserDataTypeTemplates() != J_OK)
    {
        assert(false);
        printf("CXSdl::LoadXMLFile faild, methord = PaserDataTypeTemplates()\n");
        return J_XML_FLIE_ERROR;
    }

    return J_OK;
}

int CXSdl::PaserCommunication()
{
    TiXmlNode *pCommNode = NULL;
    pCommNode = m_pRootNode->FirstChild("Communication");
    if (pCommNode == NULL)
    {
        assert(false);
        printf("CXSdl::PaserCommunication faild, methord = pRootNode.FirstChild(\"Communication\"))\n");
        return J_XML_NODE_ERROR;
    }

    TiXmlNode *pSubNetwork = NULL;
    pSubNetwork = pCommNode->FirstChild("SubNetwork");
    if (pSubNetwork == NULL)
    {
        assert(false);
        printf("CXSdl::PaserCommunication faild, methord = pCommNode->FirstChild(\"SubNetwork\")\n");
        return J_XML_NODE_ERROR;
    }

    int nRetVal = J_OK;
    TiXmlElement *pElement = NULL;
    while(pSubNetwork != NULL)
    {
        pElement = pSubNetwork->ToElement();
        if (GES_MEMCMP(pElement->Attribute("type"), MMS_TAG))
        {
            nRetVal = ProcMMS(pSubNetwork);
        }
        else if (GES_MEMCMP(pElement->Attribute("type"), GOOSE_TAG))
        {
            nRetVal = ProcGOOSE(pSubNetwork);
        }
        else if (GES_MEMCMP(pElement->Attribute("type"), SMV_TAG))
        {
            nRetVal = ProcSMV(pSubNetwork);
        }
        else
        {
            assert(false);
            printf("CXSdl::PaserCommunication faild, tag = %s\n", pElement->Attribute("type"));
        }
        pSubNetwork = pSubNetwork->NextSibling();
    }

    return nRetVal;
}

int CXSdl::ProcMMS(TiXmlNode *pNode)
{
    TiXmlNode *pConnAPNode = NULL;
    pConnAPNode = pNode->FirstChild("ConnectedAP");
    if (pConnAPNode == NULL)
    {
        assert(false);
        printf("CXSdl::ProcMMS faild, methord = pNode->FirstChild(\"ConnectedAP\")\n");
        return J_XML_NODE_ERROR;
    }

    TiXmlElement *pAPElement = NULL;
    std::string iedName;
    MMSIed *mmsIed = NULL;
    while (pConnAPNode != NULL)
    {
        pAPElement = pConnAPNode->ToElement();
        iedName = pAPElement->Attribute("iedName");
        TiXmlNode *pAddrNode = NULL;
        TiXmlNode *pPNode = NULL;
        pAddrNode = pConnAPNode->FirstChild("Address");
        if (pAddrNode == NULL)
        {
            pConnAPNode = pConnAPNode->NextSibling();
            continue;
        }
        pPNode = pAddrNode->FirstChild("P");
        if (pPNode == NULL)
        {
            pConnAPNode = pConnAPNode->NextSibling();
            continue;
        }
        TiXmlElement *pPElement = NULL;
        mmsIed = new MMSIed;
        while (pPNode != NULL)
        {
            pPElement = pPNode->ToElement();
            if (GES_MEMCMP(pPElement->Attribute("type"), IP_SUBNET_TAG))
            {
                mmsIed->ip_subnet = pPElement->GetText();
            }
            else if (GES_MEMCMP(pPElement->Attribute("type"), IP_TAG))
            {
                mmsIed->ip = pPElement->GetText();
            }
            else
            {
                assert(false);
                printf("CXSdl::ProcMMS faild, tag = %s\n", pPElement->Attribute("type"));
            }
            pPNode = pPNode->NextSibling();
        }
        m_mmsCommMap[iedName] = mmsIed;
        pConnAPNode = pConnAPNode->NextSibling();
    }
    return J_OK;
}

int CXSdl::ProcGOOSE(TiXmlNode *pNode)
{
    TiXmlNode *pConnAPNode = NULL;
    pConnAPNode = pNode->FirstChild("ConnectedAP");
    if (pConnAPNode == NULL)
    {
        assert(false);
        printf("CXSdl::ProcGOOSE faild, methord = pNode->FirstChild(\"ConnectedAP\")\n");
        return J_XML_NODE_ERROR;
    }

    TiXmlElement *pAPElement = NULL;
    std::string iedName;
    GOOSEIed gooseIed;
    GSEMap *gseMap = new GSEMap;
    while (pConnAPNode != NULL)
    {
        pAPElement = pConnAPNode->ToElement();
        iedName = pAPElement->Attribute("iedName");
        gooseIed.ap_name = pAPElement->Attribute("apName");
        TiXmlNode *pGSENode = NULL;
        pGSENode = pConnAPNode->FirstChild("GSE");
        if (pGSENode == NULL)
        {
            pConnAPNode = pConnAPNode->NextSibling();
            continue;
        }

        TiXmlElement *pGSEElement = NULL;
        while (pGSENode != NULL)
        {
            pGSEElement = pGSENode->ToElement();
            GSE gse(pGSEElement->Attribute("cbName"), pGSEElement->Attribute("ldInst"));
            GSECB *pGsecb = new GSECB;
            MakeGSECB(pGSENode, pGsecb);
            (*gseMap)[gse] = pGsecb;
            pGSENode = pGSENode->NextSibling();
        }

        gooseIed.gse_map = gseMap;
        m_gooseCommMap[iedName] = gooseIed;
        pConnAPNode = pConnAPNode->NextSibling();
    }

    return J_OK;
}

int CXSdl::MakeGSECB(TiXmlNode *pNode, GSECB *pGsecb)
{
    TiXmlNode *pAddrNode = pNode->FirstChild("Address");
    if (pAddrNode == NULL)
    {
        assert(false);
        printf("CXSdl::MakeGSECB faild, methord = pNode->FirstChild(\"Address\")\n");
        return J_XML_NODE_ERROR;
    }

    TiXmlNode *pPNode = pAddrNode->FirstChild("P");
    TiXmlElement *pPElement = NULL;
    while (pPNode != NULL)
    {
        pPElement = pPNode->ToElement();
        if (GES_MEMCMP(pPElement->Attribute("type"), MAC_ADDR_TAG))
        {
            pGsecb->mac_addr = pPElement->GetText();
        }
        else if (GES_MEMCMP(pPElement->Attribute("type"), VLAN_ID_TAG))
        {
            pGsecb->vlan_id = pPElement->GetText();
        }
        else if (GES_MEMCMP(pPElement->Attribute("type"), VLAN_PROC_TAG))
        {
            pGsecb->vlan_priotity = pPElement->GetText();
        }
        else if (GES_MEMCMP(pPElement->Attribute("type"), APPID_TAG))
        {
            pGsecb->appid = pPElement->GetText();
        }
        else
        {
            assert(false);
            printf("CXSdl::MakeGSECB faild, tag = %s\n", pPElement->Attribute("type"));
        }
        pPNode = pPNode->NextSibling();
    }

    TiXmlElement *pMinTimeElemet = pAddrNode->NextSiblingElement("MinTime");
    if (pMinTimeElemet)
        pGsecb->min_time = atoi(pMinTimeElemet->GetText());
    TiXmlElement *pMaxTimeElemet = pAddrNode->NextSiblingElement("MaxTime");
    if (pMaxTimeElemet)
        pGsecb->max_time = atoi(pMaxTimeElemet->GetText());

    return J_OK;
}

int CXSdl::ProcSMV(TiXmlNode *pNode)
{
    TiXmlNode *pConnAPNode = NULL;
    pConnAPNode = pNode->FirstChild("ConnectedAP");
    if (pConnAPNode == NULL)
    {
        assert(false);
        printf("CXSdl::ProcSMV faild, methord = pNode->FirstChild(\"ConnectedAP\")\n");
        return J_XML_NODE_ERROR;
    }

    TiXmlElement *pAPElement = NULL;
    std::string iedName;
    SMVIed smvIed;
    SMVMap *gseMap = new SMVMap;
    while (pConnAPNode != NULL)
    {
        pAPElement = pConnAPNode->ToElement();
        iedName = pAPElement->Attribute("iedName");
        smvIed.ap_name = pAPElement->Attribute("apName");
        TiXmlNode *pGSENode = NULL;
        pGSENode = pConnAPNode->FirstChild("SMV");
        if (pGSENode == NULL)
        {
            pConnAPNode = pConnAPNode->NextSibling();
            continue;
        }

        TiXmlElement *pGSEElement = NULL;
        while (pGSENode != NULL)
        {
            pGSEElement = pGSENode->ToElement();
            SMV gse(pGSEElement->Attribute("cbName"), pGSEElement->Attribute("ldInst"));
            SMVCB *pGsecb = new SMVCB;
            MakeGSECB(pGSENode, pGsecb);
            (*gseMap)[gse] = pGsecb;
            pGSENode = pGSENode->NextSibling();
        }
        smvIed.gse_map = gseMap;
        m_smvCommMap[iedName] = smvIed;
        pConnAPNode = pConnAPNode->NextSibling();
    }
    return J_OK;
}

int CXSdl::PaserIEDs()
{
    TiXmlNode *pXmlIEDNode = NULL;
    pXmlIEDNode = m_pRootNode->FirstChild("IED");
    if (pXmlIEDNode == NULL)
    {
        assert(false);
        printf("CXSdl::PaserIEDs faild, methord = pRootNode.FirstChild(\"IED\")\n");
        return J_XML_NODE_ERROR;
    }

    int nRetVal = J_OK;
    std::string iedName;
    TiXmlElement *pIEDElement = NULL;
    while (pXmlIEDNode != NULL)
    {
        pIEDElement = pXmlIEDNode->ToElement();
        iedName = pIEDElement->Attribute("name");

        TiXmlNode *pAccessPoint = NULL;
        pAccessPoint = pXmlIEDNode->FirstChild("AccessPoint");
        assert(pAccessPoint != NULL);
        TiXmlElement *pElement = NULL;
        IEDNode *pIEDNode = new IEDNode;
        while (pAccessPoint != NULL)
        {
            pElement = pAccessPoint->ToElement();
            if (GES_MEMCMP(pElement->Attribute("name"), MMS_TYPE_TAG))
            {
                nRetVal = ProcS1LD(pAccessPoint, pIEDNode->s1LdInstMap);
            }
            else if (GES_MEMCMP(pElement->Attribute("name"), GOOSE_TYPE_TAG))
            {
                nRetVal = ProcG1LD(pAccessPoint, pIEDNode->g1LdInstMap);
            }
            else if (GES_MEMCMP(pElement->Attribute("name"), SMV_TYPE_TAG))
            {
                nRetVal = ProcM1LD(pAccessPoint, pIEDNode->m1LdInstMap);
            }
            else
            {
                assert(false);
                printf("CXSdl::PaserIEDs faild, tag = %s\n", pElement->Attribute("name"));
            }
            pAccessPoint = pAccessPoint->NextSibling("AccessPoint");
        }
        m_iedMap[iedName] = pIEDNode;
        pXmlIEDNode = pXmlIEDNode->NextSibling("IED");
    }

    return nRetVal;
}

int CXSdl::ProcS1LD(TiXmlNode *pNode, LDInstMap &ldInstMap)
{
    //MMS 暂不实现
    return J_OK;
}

int CXSdl::ProcG1LD(TiXmlNode *pNode, LDInstMap &ldInstMap)
{
    //GOOSE实现
    TiXmlNode *pServerNode = pNode->FirstChild("Server");
    if (pServerNode == NULL)
    {
        //进入下一AccessPoint
        return J_OK;
    }

    TiXmlNode *pLdNode = pServerNode->FirstChild("LDevice");
    TiXmlElement *pLdElement = NULL;
    std::string ldInst;
    LDInstNode *pLdInstNode = new LDInstNode;
    while (pLdNode != NULL)
    {
        pLdElement = pLdNode->ToElement();
        ldInst = pLdElement->Attribute("inst");
        //建立LN0节点
        pLdInstNode->ln0Node = new LN0Node;
        if (ProcG1LN0(pLdNode, pLdInstNode->ln0Node) != J_OK)
        {
            pLdNode = pLdNode->NextSibling("LDevice");
            continue;
        }
        //建立LN 映射表
        ProcG1LN(pLdNode, pLdInstNode->lnMap);

        ldInstMap[ldInst] = pLdInstNode;
        pLdNode = pLdNode->NextSibling("LDevice");
    }

    return J_OK;
}

int CXSdl::ProcG1LN0(TiXmlNode *pNode, LN0Node *ln0Node)
{
    TiXmlNode *pLN0Node = pNode->FirstChild("LN0");
    if (pLN0Node == NULL)
    {
        assert(false);
        printf("CXSdl::ProcG1LN0 faild, methord = pNode->FirstChild(\"LN0\")\n");
        return J_XML_NODE_ERROR;
    }
    ln0Node->ln_type = pLN0Node->ToElement()->Attribute("lnType");

    //建立Dataset数据集
    TiXmlNode *pXmlDatasetNode = pLN0Node->FirstChild("DataSet");
    std::string dsName;
    TiXmlElement *pDsElement = NULL;
    while (pXmlDatasetNode != NULL)
    {
        pDsElement = pXmlDatasetNode->ToElement();
        dsName = pDsElement->Attribute("name");
        DatasetNode *pDatasetNode = new DatasetNode;
        MakeFCDAList(pXmlDatasetNode, pDatasetNode->fcdaList);
        ln0Node->datasetMap[dsName] = pDatasetNode;

        pXmlDatasetNode = pXmlDatasetNode->NextSibling("DataSet");
    }

    //建立GOCB数据集
    TiXmlNode *pXmlGocbNode = pLN0Node->FirstChild("GSEControl");
    TiXmlElement *pGocbElement = NULL;
    std::string gocbName;
    while (pXmlGocbNode != NULL)
    {
        pGocbElement = pXmlGocbNode->ToElement();
        gocbName = pGocbElement->Attribute("name");
        GocbNode *pGocbNpde = new GocbNode;
        pGocbNpde->go_appid = pGocbElement->Attribute("appID");
        pGocbNpde->conf_rev = pGocbElement->Attribute("confRev");
        pGocbNpde->ds_name = pGocbElement->Attribute("datSet");
        pGocbNpde->type = pGocbElement->Attribute("type");

        ln0Node->gocbMap[gocbName] = pGocbNpde;
        pXmlGocbNode = pXmlGocbNode->NextSibling("GSEControl");
    }
    return J_OK;
}

int CXSdl::MakeFCDAList(TiXmlNode *pNode, FCDAList &fcdaList)
{
    TiXmlNode *pFCDANode = pNode->FirstChild("FCDA");
    TiXmlElement *pFCDAElement = NULL;
    while (pFCDANode != NULL)
    {
        pFCDAElement = pFCDANode->ToElement();
        FCDAInfo *pFCDA = new FCDAInfo;
        const char *pStrVal = NULL;
        pStrVal = pFCDAElement->Attribute("ldInst");
        pFCDA->ld_inst = (pStrVal==NULL) ? "" : pStrVal;
        pStrVal = pFCDAElement->Attribute("prefix");
        pFCDA->prefix = (pStrVal==NULL) ? "" : pStrVal;
        pStrVal = pFCDAElement->Attribute("lnClass");
        pFCDA->ln_class = (pStrVal==NULL) ? "" : pStrVal;
        pStrVal = pFCDAElement->Attribute("lnInst");
        pFCDA->ln_inst = (pStrVal==NULL) ? "" : pStrVal;
        pStrVal = pFCDAElement->Attribute("doName");
        pFCDA->do_name = (pStrVal==NULL) ? "" : pStrVal;
        pStrVal = pFCDAElement->Attribute("daName");
        pFCDA->da_name = (pStrVal==NULL) ? "" : pStrVal;

        fcdaList.push_back(pFCDA);
        pFCDANode = pFCDANode->NextSibling();
    }
    return J_OK;
}

int CXSdl::ProcG1LN(TiXmlNode *pNode, LNMap &lnMap)
{
    TiXmlNode *pLNXmlNode = pNode->FirstChild("LN");
    TiXmlElement *pLNElement = NULL;
    while (pLNXmlNode != NULL)
    {
        pLNElement = pLNXmlNode->ToElement();
        LN lnKey(pLNElement->Attribute("lnClass"), pLNElement->Attribute("inst"));
        LNNode *pLNNode = new LNNode;
        pLNNode->ln_type = pLNElement->Attribute("lnType");
        MakeDOMap(pLNXmlNode, pLNNode->doMap);

        lnMap[lnKey] = pLNNode;
        pLNXmlNode = pLNXmlNode->NextSibling("LN");
    }
    return J_OK;
}

int CXSdl::MakeDOMap(TiXmlNode *pNode, DOMap &doMap)
{
    TiXmlNode *pDOXmlNode = pNode->FirstChild("DOI");
    TiXmlElement *pDOElememt = NULL;
    std::string doName;
    while (pDOXmlNode != NULL)
    {
        pDOElememt = pDOXmlNode->ToElement();
        doName = pDOElememt->Attribute("name");
        DOInfo *doInfo = new DOInfo;
        TiXmlNode *pDAXmlNode = pNode->FirstChild("DAI");
        TiXmlElement *pDAElememt = NULL;
        std::string daName;
        std::string val;
        TiXmlElement *pValElememt = NULL;
        while (pDAXmlNode != NULL)
        {
            pDAElememt = pDAXmlNode->ToElement();
            daName = pDAElememt->Attribute("name");
            pValElememt = pDAXmlNode->FirstChildElement();
            if (pValElememt)
            {
                val = pValElememt->GetText();
            }
            doInfo->daMap[daName] = val;
            pDAXmlNode = pDAXmlNode->NextSibling();
        }
        doMap[doName] = doInfo;
        pDOXmlNode = pDOXmlNode->NextSibling();
    }
    return J_OK;
}

int CXSdl::ProcM1LD(TiXmlNode *pNode, LDInstMap &ldInstMap)
{
    //SMV 暂不实现
    return J_OK;
}

int CXSdl::PaserDataTypeTemplates()
{
    //未完待续
    TiXmlNode *pDataTypeNode = NULL;
    pDataTypeNode = m_pRootNode->FirstChild("DataTypeTemplates");
    if (pDataTypeNode == NULL)
    {
        assert(false);
        printf("CXSdl::PaserDataTypeTemplates faild, methord = pRootNode.FirstChild(\"DataTypeTemplates\")\n");
        return J_XML_NODE_ERROR;
    }

    int nRetVal = J_OK;
    //nRetVal = MakeLNodeType();
    if (nRetVal != J_OK)
    {
        assert(false);
        return nRetVal;
    }
    return J_OK;
}
