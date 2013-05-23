#include "x_errtype.h"
#include "x_gse_scd.h"
#include "gse_config.h"

GES_TAG(GSE_TYPE, G1)
GES_TAG(GSE_GOOSE, IECGOOSE)

static int atohex(const char *str, u_char *hex)
{
    int n = strlen(str);
    for (int i=0; i<n; i+=2)
    {
        if (str[i] >= '0' && str[i] <= '9')
            hex[i/2] = (str[i] - '0') << 4;
        else if(str[i] >= 'a' && str[i] <= 'f')
            hex[i/2] = (str[i] - 'a' + 10) << 4;
        else if(str[i] >= 'A' && str[i] <= 'F')
            hex[i/2] = (str[i] - 'A' + 10) << 4;
        else
        {
            assert(false);
            return -1;
        }

        if (str[i+1] >= '0' && str[i+1] <= '9')
            hex[i/2] += str[i+1] - '0';
        else if(str[i+1] >= 'a' && str[i+1] <= 'f')
            hex[i/2] += str[i+1] - 'a' + 10;
        else if(str[i+1] >= 'A' && str[i+1] <= 'F')
            hex[i/2] = str[i+1] - 'A' + 10;
        else
        {
            assert(false);
            return -1;
        }
    }
    return n;
}

CXGseScd::CXGseScd()
{
    m_pCommNode = NULL;
    m_pDatTypeNode = NULL;
}

CXGseScd::~CXGseScd()
{

}

int CXGseScd::Init()
{
    if (!m_xmlDoc.LoadFile(GetSCDName()))
    {
        //assert(false);
        printf("CXGseScd::Init faild, file = %s\n", GetSCDName());
        return J_XML_FLIE_ERROR;
    }

    TiXmlNode *pRootNode = m_xmlDoc.FirstChild("SCL");
    if (pRootNode == NULL)
    {
        assert(false);
        printf("CXGseScd::Init faild, methord = m_xmlDoc.FirstChild(\"SCL\")\n");
        return J_XML_FLIE_ERROR;
    }

    m_pCommNode = pRootNode->FirstChild("Communication");
    if (m_pCommNode == NULL)
    {
        assert(false);
        printf("CXGseScd::Init faild, methord = m_xmlDoc.FirstChild(\"Communication\")\n");
        return J_XML_FLIE_ERROR;
    }

    m_pDatTypeNode = pRootNode->FirstChild("DataTypeTemplates");
    if (m_pDatTypeNode == NULL)
    {
        assert(false);
        printf("CXGseScd::Init faild, methord = m_xmlDoc.FirstChild(\"DataTypeTemplates\")\n");
        return J_XML_FLIE_ERROR;
    }

    if (ParseIEDs(pRootNode) != J_OK)
    {
        assert(false);
        printf("CXGseScd::Init faild, methord = ParseIEDs()\n");
        return J_XML_FLIE_ERROR;
    }
    return J_OK;
}

void CXGseScd::Deinit()
{

}

int CXGseScd::GetAllCtrlBlock()
{
    //生成发送数据
	json_object *gse_json = json_object_new_array();
    GSE_GocbMap::iterator it = m_gocbMap.begin();
    for (; it!=m_gocbMap.end(); it++)
    {
		if (it->first == 1337 || it->first == 1338 || 
			it->first == 1339 || it->first == 1340 || it->first == 1341)
		{
			json_object *gocb_json = json_object_new_object();
			json_object_object_add(gocb_json, (char *)"cid", json_object_new_int(it->first));
			char str_appid[4] = {0};
			sprintf(str_appid, "%02x%02x", ((it->first-1000) >> 8) &0xFF, (it->first-1000) & 0xFF);
			json_object_object_add(gocb_json, (char *)"appid", json_object_new_string(str_appid));
			json_object_object_add(gocb_json, (char *)"desc", json_object_new_string((char *)it->second->desc.c_str()));
			json_object *gocb_array = json_object_new_array();
			int n = it->second->all_data.size();
			for (int i=0; i<n; i++)
			{
				if ((it->second->all_data[i]->data_type == "Dbpos" || it->second->all_data[i]->data_type == "BOOLEAN")
					&& it->second->all_data[i]->fc == "ST")
				{
					json_object *data_json = json_object_new_object();
					json_object_object_add(data_json, (char *)"node", json_object_new_int(i + 1));
					json_object_object_add(data_json, (char *)"desc", json_object_new_string((char *)it->second->all_data[i]->desc.c_str()));
					//json_object_object_add(data_json, (char *)"type", json_object_new_string((char *)it->second->all_data[i]->data_type.c_str()));
					//json_object_object_add(data_json, (char *)"fc", json_object_new_string((char *)it->second->all_data[i]->fc.c_str()));
					json_object_array_add(gocb_array, data_json);
				}
			}
			json_object_object_add(gocb_json, (char *)"allData", gocb_array);
			json_object_array_add(gse_json, gocb_json);
		}
    }

    FILE *fp = fopen("gse_config.json", "wb+");
    fwrite(json_object_to_json_string(gse_json), 1, strlen(json_object_to_json_string(gse_json)), fp);
    fclose(fp);

    json_object_put(gse_json);

    return J_OK;
}

int CXGseScd::ParseIEDs(TiXmlNode *pRootNode)
{
    TiXmlNode *pIEDNode = pRootNode->FirstChild("IED");
    std::string ied_name;
    TiXmlElement *pIEDElement = NULL;
    while (pIEDNode != NULL)//IED
    {
        ied_name = pIEDNode->ToElement()->Attribute("name");
        TiXmlNode *pAPNode = pIEDNode->FirstChildElement("AccessPoint");
        while (pAPNode != NULL)//G1
        {
            TiXmlNode *pLDNode = NULL;
            if (GES_MEMCMP(pAPNode->ToElement()->Attribute("name"), GSE_TYPE_TAG))
            {
                pLDNode = pAPNode->FirstChild("Server")->FirstChild("LDevice");
                std::string ld_inst;
                TiXmlNode *pLN0Node = NULL;
                while (pLDNode != NULL)//LDevice
                {
                    ld_inst = pLDNode->ToElement()->Attribute("inst");
                    pLN0Node = pLDNode->FirstChild("LN0");
                    //TiXmlNode *pDataSetNode = NULL;
                    TiXmlNode *pGSECtrlNode = NULL;
                    if (pLN0Node != NULL)
                    {
                        std::string gocb_name;
                        std::string datset_name;
                        pGSECtrlNode = pLN0Node->FirstChild("GSEControl");
                        while (pGSECtrlNode != NULL)
                        {
                            TiXmlElement *pGSECtrlElement = pGSECtrlNode->ToElement();
                            gocb_name = pGSECtrlElement->Attribute("name");
                            datset_name = pGSECtrlElement->Attribute("datSet");

                            //生成一条记录
                            u_int32_t appid = 0;
                            //查找对应的APPID
                            if (FindAppid(ied_name, ld_inst, gocb_name, appid) != J_OK)
                            {
                                //没有对应的APPID
                                printf("CXGseScd::ParseIEDs %s Is not a GOOSE IED\n", ied_name.c_str());
                                pGSECtrlNode = pGSECtrlNode->NextSibling();
                                continue;

                            }
                            GSE_DataSetInfo *pDataSetInfo = new GSE_DataSetInfo;
                            if (MakeDataSetInfo(pLN0Node, datset_name, pDataSetInfo) != J_OK)
                            {
                                //数据解析有错误
                                assert(false);
                            }
                            m_gocbMap[appid] = pDataSetInfo;

                            pGSECtrlNode = pGSECtrlNode->NextSibling("GSEControl");
                        }
                    }
                    pLDNode = pLDNode->NextSibling();
                }
            }
            pAPNode = pAPNode->NextSibling();
        }
        pIEDNode = pIEDNode->NextSibling("IED");
    }
    return J_OK;
}

int CXGseScd::FindAppid(const std::string &ied_name, const std::string &ld_inst, const std::string &gocb, u_int32_t &appid)
{
    TiXmlNode *pSubNetNode = m_pCommNode->FirstChild("SubNetwork");
    while (pSubNetNode != NULL)
    {
        if (GES_MEMCMP(pSubNetNode->ToElement()->Attribute("type"), GSE_GOOSE_TAG))
        {
            TiXmlNode *pConnAPNode = pSubNetNode->FirstChild("ConnectedAP");
            while (pConnAPNode != NULL)
            {
                if (ied_name == pConnAPNode->ToElement()->Attribute("iedName"))
                {
                    TiXmlNode *pGSENode = pConnAPNode->FirstChild("GSE");
                    TiXmlElement *pGSEElement = NULL;
                    while (pGSENode != NULL)
                    {
                        pGSEElement = pGSENode->ToElement();
                        if (ld_inst == pGSEElement->Attribute("ldInst") &&
                            gocb == pGSEElement->Attribute("cbName"))
                        {
                            TiXmlNode *pAddrPNode = pGSENode->FirstChild("Address")->FirstChild("P");
                            while (pAddrPNode != NULL)
                            {
                                if (pAddrPNode->ToElement()->Attribute("type") == std::string("APPID"))
                                {
                                    u_char strAppid[4] = {0};
                                    atohex(pAddrPNode->ToElement()->GetText(), strAppid);
                                    appid = (strAppid[0] << 8) + strAppid[1] + 1000;
                                    break;
                                }
                                pAddrPNode = pAddrPNode->NextSibling();
                            }
                            return J_OK;
                        }
                        pGSENode = pGSENode->NextSibling();
                    }
                }
                pConnAPNode = pConnAPNode->NextSibling();
            }
        }
        pSubNetNode = pSubNetNode->NextSibling();
    }
    return J_NOT_FOUND;
}

int CXGseScd::MakeDataSetInfo(TiXmlNode *pLN0Node, const std::string &ds_name, GSE_DataSetInfo *pDsInfo)
{
    TiXmlNode *pDataSetNode = pLN0Node->FirstChild("DataSet");
    while (pDataSetNode != NULL)
    {
        if (pDataSetNode->ToElement()->Attribute("name") == ds_name)
        {
            pDsInfo->desc = pDataSetNode->ToElement()->Attribute("desc");
            TiXmlNode *pXmlFCDA = pDataSetNode->FirstChild("FCDA");
            TiXmlElement *pFCDAElement = NULL;
            while (pXmlFCDA != NULL)
            {
                pFCDAElement = pXmlFCDA->ToElement();
                const char *pStrVal = pFCDAElement->Attribute("prefix");
                std::string prefix = (pStrVal == NULL) ? "" : pStrVal;
                std::string ln_class = pFCDAElement->Attribute("lnClass");
                std::string ln_inst = pFCDAElement->Attribute("lnInst");
                std::string do_name = pFCDAElement->Attribute("doName");
                std::string da_name = pFCDAElement->Attribute("daName");
                std::string ln_type;
                //生成数据信息
                GSE_DataInfo *pDataInfo = new GSE_DataInfo;
                pDataInfo->fc = pFCDAElement->Attribute("fc");
                if (FindLNType(pLN0Node, prefix, ln_class, ln_inst, do_name, pDataInfo->desc, ln_type) != J_OK)
                {
                    //未找到逻辑节点类型
                    assert(false);
                }
                if (FindDAType(ln_type, do_name, da_name, pDataInfo->data_type) != J_OK)
                {
                    //未找到数据类型
                    assert(false);
                }

                pDsInfo->all_data.push_back(pDataInfo);
                pXmlFCDA = pXmlFCDA->NextSibling();
            }
        }
        pDataSetNode = pDataSetNode->NextSibling("DataSet");
    }
    return J_OK;
}

int CXGseScd::FindLNType(TiXmlNode *pLN0Node, const std::string &prefix, const std::string &ln_class, const std::string &ln_inst, const std::string &do_name, std::string &ds_desc, std::string &ln_type)
{
    TiXmlNode *pXmlLNNode = pLN0Node->NextSibling("LN");
    TiXmlElement *pLNElement = NULL;
    while (pXmlLNNode != NULL)
    {
        pLNElement = pXmlLNNode->ToElement();
        if ((ln_class == pLNElement->Attribute("lnClass"))
            && (ln_inst == pLNElement->Attribute("inst"))
            && ((prefix == "")
            || (prefix == pLNElement->Attribute("prefix"))))
        {
            ln_type = pLNElement->Attribute("lnType");
            TiXmlNode *pDONode = pXmlLNNode->FirstChild("DOI");
            while (pDONode != NULL)
            {
                if (pDONode->ToElement()->Attribute("name") == do_name)
                {
                    TiXmlNode *pDANode = pDONode->FirstChild("DAI");
                    while (pDANode != NULL)
                    {
                        if (pDANode->ToElement()->Attribute("name") == std::string("dU"))
                        {
                            ds_desc = pDANode->FirstChildElement("Val")->GetText();
                            break;
                        }
                        pDANode = pDANode->NextSibling();
                    }
                    return J_OK;
                }
                pDONode = pDONode->NextSibling();
            }
        }
        pXmlLNNode = pXmlLNNode->NextSibling("LN");
    }
    return J_NOT_FOUND;
}

int CXGseScd::FindDAType(const std::string &ln_type, const std::string &do_name, const std::string &da_name, std::string &data_type)
{
    TiXmlNode *pXmlNodeType = m_pDatTypeNode->FirstChild("LNodeType");
    while (pXmlNodeType != NULL)
    {
        if (pXmlNodeType->ToElement()->Attribute("id") == ln_type)
        {
            TiXmlNode *pXmlDOType =  pXmlNodeType->FirstChild("DO");
            while (pXmlDOType != NULL)
            {
                if (pXmlDOType->ToElement()->Attribute("name") == do_name)
                {
                    std::string do_type = pXmlDOType->ToElement()->Attribute("type");
                    if (FindType(do_type, da_name, data_type) != J_OK)
                    {
                        //未找到类型
                        assert(false);
                    }
                    return J_OK;
                }
                pXmlDOType = pXmlDOType->NextSibling();
            }
        }
        pXmlNodeType = pXmlNodeType->NextSibling("LNodeType");
    }
    return J_NOT_FOUND;
}

int CXGseScd::FindType(const std::string &do_type, const std::string &da_name, std::string &data_type)
{
    TiXmlNode *pXmlDOType = m_pDatTypeNode->FirstChild("DOType");
    while (pXmlDOType != NULL)
    {
        if (pXmlDOType->ToElement()->Attribute("id") == do_type)
        {
            TiXmlNode *pXmlDAType = pXmlDOType->FirstChild("DA");
            std::string find_str = da_name;
            int pos;
            if ((pos = da_name.find('.')) != std::string::npos)
                find_str = da_name.substr(0, pos);
            while (pXmlDAType != NULL)
            {
                if (pXmlDAType->ToElement()->Attribute("name") == find_str)
                {
                    data_type = pXmlDAType->ToElement()->Attribute("bType");
                    return J_OK;
                }
                pXmlDAType = pXmlDAType->NextSibling();
            }
        }
        pXmlDOType = pXmlDOType->NextSibling("DOType");
    }
    return J_NOT_FOUND;
}
