#ifndef __X_ERROR_TYPE_H_
#define __X_ERROR_TYPE_H_

#define J_OK							 0	//成功
#define J_UNKNOW				-1	//未知错误
#define J_EXIST						-2	//已经存在
#define J_PARAM_ERROR				-3	//参数错误
#define J_MEMORY_ERROR			-4	//内存错误
#define J_SOCKET_ERROR				-5	//套接字错误

#define J_INVALID_DEV				-6	//无效设备
#define J_DEV_PARAM_ERROR		-7	//设备参数错误

#define J_STREAM_ERROR				-8	//流错误
#define J_NO_MEMORY				-9	//内存不足
#define J_NOT_EXIST					-10//不存在
#define J_NO_REF							-11//引用计数为0
#define J_DB_ERROR						-12//数据库错误

#define J_MSGQ_ERROR				-13//消息队列错误
#define J_FILE_ERROR					-14//文件错误
#define J_FILE_BROKEN					-15//

#define J_NOT_IMPLEMENT			-16//没有实现
#define J_WS_ERROR					-17//websocket错误
#define J_ON_CLOSE						-18	
#define J_TRY_AGAIN					-19//重试

#define J_MSG_ERROR				-20	//消息错误
#define J_SORT_CONN				-21	//短连接
#define J_TABLE_NULL          	-22	//空表
#define J_DEV_BROKEN				-23	//设备断线
#define J_DB_PROCESS_FAIL		-24	//数据库操作错误

#define J_SOCK_TIMEO				-25	//网络超时
#define J_SOCK_INTR				-26	//网络中断

#define J_JSON_UNKOWN			-27	//未知json格式
#define J_NOT_COMPLATE			-28	//未完成
#define J_NO_RESOURCE				-29	//资源不存在
#define J_OUT_RANGE					-30	//越界
#define J_FILE_END						-31	//文件结束

#define J_DEV_ERROR				-32	//设备错误
#define J_OPR_ERROR          		-33	//操作错误
#define J_XML_FLIE_ERROR     	-34	//xml文件错误
#define J_XML_NODE_ERROR     -35	//xml节点错误
#define J_NOT_FOUND        		-36	//查询失败

#define J_THREAD_CREATE_ERROR	-37//创建线程失败
#define J_DATA_NOT_READY		-38//数据未就绪
#define J_WIAT_NEXT_CMD			-39//等待下一条指令

#define J_DECODER_INIT_ERROR	-40//初始化Decoder错误
#define J_RENDER_INIT_ERROR		-41//初始化显示设备错误
#define J_INVALID_HANDLE			-42//无效句柄
#define J_ERROR_NO_CAPS			-43
#define J_ERROR_NO_CLIPPER		-44
#define J_ERROR_PRIMARY_SURFACE	-45
#define J_ERROR_CREATE_SURFACE		-46
#define J_ERROR_PTR							-47
#define J_ERROR_SURFACE_LOCK			-48
#define J_ERROR_MISMATCH_PLANE	-49
#define J_ERROR_SURFACE_BLT			-50
#define J_ERROR_LIBPNG						-51

#endif //~__X_ERROR_TYPE_H_
