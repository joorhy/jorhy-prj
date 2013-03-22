#ifndef __X_SCD_DEF_H_
#define __X_SCD_DEF_H_

#include <map>
#include <string>
#include <vector>

#define GES_TAG(x, y)\
    const char *x##_TAG = #y;\
    const int x##_TAG_LEN = strlen(#y);

#define GES_MEMCMP(x, y)\
    ((memcmp(x, y, y##_LEN) == 0) ? true : false)

//定义dataSet
struct FCDAInfo
{
    std::string ld_inst;
    std::string prefix;
    std::string ln_class;
    std::string ln_inst;
    std::string do_name;
    std::string da_name;
};
typedef std::vector<FCDAInfo *> FCDAList;
struct DatasetNode
{
    FCDAList fcdaList;
};
//定义gocb
struct GocbNode
{
    std::string go_appid;
    std::string conf_rev;
    std::string ds_name;
    std::string type;
};
typedef std::map<std::string, DatasetNode *> DatasetMap;
typedef std::map<std::string, GocbNode *> GocbMap;

//定义LN0节点
struct LN0Node
{
    std::string ln_type;
    DatasetMap datasetMap;
    GocbMap gocbMap;
};

//定义LN节点
struct LN
{
    std::string lnClass;
    std::string lnInst;
    LN(const std::string ln_class, const std::string ln_inst)
    {
        lnClass = ln_class;
        lnInst = ln_inst;
    }
    bool operator < (const LN& other) const
    {
        if (lnClass == other.lnClass)
            return lnInst < other.lnInst;

        return lnClass < other.lnClass;
    }
};
typedef std::map<std::string, std::string> DAMap;
struct DOInfo
{
    DAMap daMap;
};
typedef std::map<std::string, DOInfo *> DOMap;
struct LNNode
{
    std::string ln_type;
    DOMap doMap;
};
typedef std::map<LN, LNNode *> LNMap;

//定义LD节点
struct LDInstNode
{
    LN0Node *ln0Node;
    LNMap lnMap;
};
typedef std::map<std::string, LDInstNode *> LDInstMap;

struct IEDNode
{
    LDInstMap s1LdInstMap;//MMS
    LDInstMap g1LdInstMap;//GOOSE
    LDInstMap m1LdInstMap;//SMV
};
typedef std::map<std::string, IEDNode *> IEDMap;

//定义MMS Communication信息
struct MMSIed
{
    std::string ap_name;
    std::string ip;
    std::string ip_subnet;
};
typedef std::map<std::string, MMSIed *> MMSMap;//Key为iedName

//定义GOOSE Communication信息
struct GSE
{
    std::string cbName;
    std::string ldInst;
    GSE(const std::string cb_name, const std::string ld_inst)
    {
        cbName = cb_name;
        ldInst = ld_inst;
    }
    bool operator < (const GSE& other) const
    {
        if (cbName == other.cbName)
            return ldInst < other.ldInst;

        return cbName < other.cbName;
    }
};
struct GSECB
{
    std::string mac_addr;
    std::string vlan_id;
    std::string vlan_priotity;
    std::string appid;
    int min_time;
    int max_time;
};
typedef std::map<GSE, GSECB *> GSEMap;
struct GOOSEIed
{
    std::string ap_name;
    GSEMap *gse_map;
};
typedef std::map<std::string, GOOSEIed> GOOSEMap;//Key为iedName

//定义SMV Communication信息
typedef GSE SMV;
typedef GSECB SMVCB;
typedef std::map<SMV, SMVCB *> SMVMap;
typedef GOOSEIed SMVIed;
typedef std::map<std::string, SMVIed> SamValMap;//Key为iedName

//定义DataTypeTemplates信息
struct DOTypeInfo
{
    std::string type;
};
typedef std::map<std::string, DOTypeInfo *> DOTypeInfoMap;
struct LNodeType
{
    DOTypeInfoMap doTypeMap;
};
typedef std::map<std::string, LNodeType *> LNodeTypeMap;

struct DATypeInfo
{
    std::string b_type;
    std::string type;
};
typedef std::map<std::string, DATypeInfo *> DATypeInfoMap;
struct DOType
{
    DATypeInfoMap daTypeMap;
};
typedef std::map<std::string, DOType *> DOTypeMap;

struct BDAInfo
{
    std::string b_type;
    std::string type;
};
typedef std::map<std::string, BDAInfo *> BDAInfoMap;
struct DAType
{
    BDAInfoMap bdaMap;
};
typedef std::map<std::string, DAType *> DATypeMap;

#endif // __X_SCD_DEF_H_
