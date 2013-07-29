/**
*  Copyright (c) 2013, 成都荣耀科技有限公司(http://www.ronyao.com/)
*  All rights reserved.
*
*  @file        DelObj.h
*  @author      雷银春(yo7@foxmail.com)
*  @date        2013/07/25 17:36
*  @version     ver 1.0.0.1
*
*  @brief       专有释放资源类
*  @note        使用时包含头文件，先用宏FRIEND_CLASS将本模板类定义为友元，然后直接调用宏DEL_OBJ、DEL_OBJ_ARRAY。
*
*    v1.0.0.1    2013/07/25 17:36    完成基础代码并测试
*    v1.0.0.2    2013/07/26 10:27    添加宏FRIEND_CLASS
*/
#ifndef __DelObj_head__
#define __DelObj_head__

/**
*  @author      雷银春(yo7@foxmail.com)
*  @date        2013/07/25 17:37
*  @class       CDelObj
*  @brief       释放资源类
*/
template<typename ObjType>
class CDelObj
{
public:
	static void DelObj(ObjType *& pObj)
	{
		if (NULL != pObj)
		{
			delete pObj;
			pObj = NULL;
		}
	}

	static void DelObjArray(ObjType *& pObj)
	{
		if (NULL != pObj)
		{
			delete[] pObj;
			pObj = NULL;
		}
	}

private:
	CDelObj(void) {
	}

	virtual ~CDelObj(void) {
	}
};


#define DEL_OBJ(OBJ_TYPE, pObj) (CDelObj<OBJ_TYPE>::DelObj(pObj))
#define DEL_OBJ_ARRAY(OBJ_TYPE, pObjArr) (CDelObj<OBJ_TYPE>::DelObjArray(pObjArr))

#define FRIEND_CLASS(classname) (friend class CDelObj<classname>)

#endif // __DelObj_head__
