#ifndef PTZ_H_H
#define PTZ_H_H

enum PROTOCOL_TYPE
{
	PROTOCOL_NULL = 0,
	PROTOCOL_PELCOP,
	PROTOCOL_PELCOD,
	PROTOCOL_LILIN,
	PROTOCOL_MINKING,
	PROTOCOL_NEON,
	PROTOCOL_STAR,
	PROTOCOL_VIDO,
	PROTOCOL_DSCP,
	PROTOCOL_VISCA,
	PROTOCOL_SAMSUNG,
	PROTOCOL_RM110,
	PROTOCOL_HY,
	PROTOCOL_END
};

typedef enum protocol_support_action
{
	PROTOCOL_SUPPORT_CURISE		= 0x0001,
	PROTOCOL_SUPPORT_TRACK		= 0x0002,
	PROTOCOL_SUPPORT_PRESET		= 0x0004,
	PROTOCOL_SUPPORT_AUTOSCAN	= 0x0008,
}PROTOCOL_SUPPORT_ACTION;

const char PTZ_PROTOCL_NAME [][64] = { "NULL","PELCOP", "PELCOD", "LILIN", "MINKING", "NEON", "STAR", "VIDO", "DSCP", "VISCA", "SAMSUNG", "RM110", "HY"};

inline unsigned long PTZSupportMask( unsigned long ProtocolID)
{
	unsigned long mask = 0;


	switch( ProtocolID )
	{
		//支持巡航的协议
	case PROTOCOL_PELCOP:
		{
			mask = PROTOCOL_SUPPORT_CURISE | PROTOCOL_SUPPORT_TRACK | PROTOCOL_SUPPORT_PRESET | PROTOCOL_SUPPORT_AUTOSCAN;
			break;
		}
	case PROTOCOL_PELCOD:
		{
			mask = PROTOCOL_SUPPORT_CURISE | PROTOCOL_SUPPORT_TRACK | PROTOCOL_SUPPORT_PRESET | PROTOCOL_SUPPORT_AUTOSCAN;
			break;
		}
	case PROTOCOL_LILIN:
		{
			mask = PROTOCOL_SUPPORT_PRESET;
			break;
		}
	case PROTOCOL_MINKING:
		{
			mask = PROTOCOL_SUPPORT_CURISE | PROTOCOL_SUPPORT_PRESET;
			break;
		}
	case PROTOCOL_NEON:
		{
			mask = PROTOCOL_SUPPORT_CURISE | PROTOCOL_SUPPORT_PRESET;
			break;
		}
	case PROTOCOL_STAR:
		{
			mask = PROTOCOL_SUPPORT_CURISE | PROTOCOL_SUPPORT_PRESET;
			break;
		}
	case PROTOCOL_VIDO:
		{
			mask = PROTOCOL_SUPPORT_CURISE | PROTOCOL_SUPPORT_PRESET;
			break;
		}
	case PROTOCOL_DSCP:
		{
			mask = PROTOCOL_SUPPORT_TRACK | PROTOCOL_SUPPORT_PRESET;
			break;
		}
	case PROTOCOL_VISCA:
		{
			mask = PROTOCOL_SUPPORT_PRESET;
			break;
		}
	case PROTOCOL_SAMSUNG:
		{
			mask = PROTOCOL_SUPPORT_CURISE | PROTOCOL_SUPPORT_TRACK | PROTOCOL_SUPPORT_PRESET | PROTOCOL_SUPPORT_AUTOSCAN;
			break;
		}
	case PROTOCOL_RM110:
		{
			mask = 0;
			break;
		}
	case PROTOCOL_HY:
		{
			mask = 0;
			break;
		}
	default:
		break;
	}

	return mask;
}

inline bool PTZSupportAction( unsigned long ProtocolID, PROTOCOL_SUPPORT_ACTION PTZAction )
{
	bool SupportAction = false;
	
	if( PROTOCOL_SUPPORT_CURISE == PTZAction )
	{
		switch( ProtocolID )
		{
		//支持巡航的协议
		case PROTOCOL_PELCOP:
		case PROTOCOL_PELCOD:
		case PROTOCOL_MINKING:
		case PROTOCOL_NEON:
		case PROTOCOL_STAR:
		case PROTOCOL_VIDO:
		case PROTOCOL_SAMSUNG:
				SupportAction = true;
				break;
		default:
				break;
		}
	}
	else if( PROTOCOL_SUPPORT_TRACK == PTZAction )
	{
		switch( ProtocolID )
		{
			//支持轨迹的协议
		case PROTOCOL_PELCOP:
		case PROTOCOL_PELCOD:
		case PROTOCOL_DSCP:
		case PROTOCOL_SAMSUNG:
			SupportAction = true;
			break;
		default:
			break;
		}
	}
	else if( PROTOCOL_SUPPORT_PRESET == PTZAction )
	{
		switch( ProtocolID )
		{
			//不支持预置点的协议
		case PROTOCOL_NULL:
		case PROTOCOL_RM110:
		case PROTOCOL_HY:
			SupportAction = false;
			break;
		default:
			SupportAction = true;
			break;
		}
	}
	else if( PROTOCOL_SUPPORT_AUTOSCAN == PTZAction )
	{
		switch( ProtocolID )
		{
			//支持自动扫描的协议
		case PROTOCOL_PELCOP:
		case PROTOCOL_PELCOD:
		case PROTOCOL_SAMSUNG:
			SupportAction = true;
			break;
		default:
			break;
		}
	}
	else
	{
		//assert(false);
	}

	return SupportAction;
}

typedef enum _ptz_com_type
{
	PTZ_CMD_STOP			=0,	//停止

	PTZ_CMD_LEFT,				//左
	PTZ_CMD_RIGHT,				//右
	PTZ_CMD_UP,					//上
	PTZ_CMD_DOWN,				//下

	PTZ_CMD_LEFT_UP,			//左上
	PTZ_CMD_LEFT_DOWN,			//左下
	PTZ_CMD_RIGHT_UP,			//右上
	PTZ_CMD_RIGHT_DOWN,			//右下

	PTZ_CMD_NEAR,				//拉近
	PTZ_CMD_FAR,				//调远

	PTZ_CMD_ZOOM_OUT,			//缩小
	PTZ_CMD_ZOOM_IN,			//放大

	PTZ_CMD_IRIS_OPEN,			//开启光圈
	PTZ_CMD_IRIS_CLOSE,			//关闭光圈

	PTZ_CMD_PRESET_SET,			//设置预置点
	PTZ_CMD_PRESET_GO,			//到第几个预置点
	PTZ_CMD_PRESET_DEL,			//删除预置点

	PTZ_CMD_CRUISE_CFG,			//设置巡航线,相当于执行Enter、Set、Leave三个命令
	PTZ_CMD_ENTER_CURISE_MODE,	//进入巡航模式,此后可以设置巡航的预置点
	PTZ_CMD_CRUISE_SET,			//设置巡航线的预置点
	PTZ_CMD_LEAVE_CURISE_MODE,	//退出设置巡航
	PTZ_CMD_CRUISE_RUN,			//选择一个巡航线进行巡航
	PTZ_CMD_CRUISE_STOP,		//停止巡航
	PTZ_CMD_CRUISE_DEL,			//删除巡航线

	PTZ_CMD_TRACK_START,		//开始轨迹
	PTZ_CMD_TRACK_STOP,			//停止轨迹
	PTZ_CMD_TRACK_START_RECORD,	//开始保存轨迹
	PTZ_CMD_TRACK_STOP_RECORD,	//停止保存轨迹

	PTZ_CMD_AUTO_SCAN_START,	//开始自动扫描
	PTZ_CMD_AUTO_SCAN_STOP,		//停止自动扫描

	PTZ_CMD_RESET = 0xF0,		//复位云台状态
}PTZ_CMD_TYPE;

//串口类型值定义
enum PORT_BAUDRATE
{
	SBR_110 = 0,
	SBR_300,
	SBR_600,
	SBR_1200,
	SBR_2400,
	SBR_4800,
	SBR_9600,
	SBR_19200,
	SBR_38400,
	SBR_57600,
	SBR_115200,
	SBR_230400,
	SBR_460800,
	SBR_921600
};

enum PARITYTYPE
{
	PARITYEVEN = 'E',		//偶校验
	PARITYODD = 'O',		//奇校验
	PARITYMARK = 'M',		//
	PARITYSPACE = 'S',		//
	PARITYNONE = 'N'		//不校验
};

enum DATABITS
{
	DATABITS7 = 7,
	DATABITS8
};

typedef enum _ptz_speed
{
	PTZ_SPEED_1 = 1,
	PTZ_SPEED_2	= 2,
	PTZ_SPEED_3	= 3,
	PTZ_SPEED_4	= 4,
	PTZ_SPEED_5	= 5,
	PTZ_SPEED_6	= 6,
	PTZ_SPEED_7	= 7,
	PTZ_SPEED_8	= 8
}PTZ_SPEED;

enum STOPBITS
{
	STOPBITS1 = 2,
	STOPBITSONEHALF,
	STOPBITS2
};

inline unsigned long GetBaudRate(PORT_BAUDRATE rate)
{
	unsigned long ret = 0011;

	switch(rate)
	{
	case SBR_110:
		ret = 003;
		break;
	case SBR_300:
		ret = 007;
		break;
	case SBR_600:
		ret = 0010;
		break;
	case SBR_1200:
		ret = 0011;
		break;
	case SBR_2400:
		ret = 0013;
		break;
	case SBR_4800:
		ret = 0014;
		break;
	case SBR_9600:
		ret = 0015;
		break;
	case SBR_19200:
		ret = 0016;
		break;
	case SBR_38400:
		ret = 0017;
		break;
	case SBR_57600:
		ret = 0010001;
		break;
	case SBR_115200:
		ret = 0010002;
		break;
	case SBR_230400:
		ret = 0010003;
		break;
	case SBR_460800:
		ret = 0010004;
		break;
	case SBR_921600:
		ret = 0010007;
		break;
	default :
		ret = 0011;
		break;
	}

	return ret;
}

inline void  GetBaudRate(PORT_BAUDRATE rate, unsigned long *pBandRate )
{

	switch(rate)
	{
	case SBR_110:
		*pBandRate = 110;
		break;
	case SBR_300:
		*pBandRate = 300;
		break;
	case SBR_600:
		*pBandRate = 600; 
		break;
	case SBR_1200:
		*pBandRate = 1200;
		break;
	case SBR_2400:
		*pBandRate = 2400;
		break;
	case SBR_4800:
		*pBandRate = 4800;
		break;
	case SBR_9600:
		*pBandRate = 9600;
		break;
	case SBR_19200:
		*pBandRate = 19200;
		break;
	case SBR_38400:
		*pBandRate = 38400;
		break;
	case SBR_57600:
		*pBandRate = 57600;
		break;
	case SBR_115200:
		*pBandRate = 115200;
		break;
	case SBR_230400:
		*pBandRate = 230400;
		break;
	case SBR_460800:
		*pBandRate = 460800;
		break;
	case SBR_921600:
		*pBandRate = 921600;
		break;
	default :
		*pBandRate = 110;
		break;
	}

}

//////////////////////////////////////////////////////////////////////////

enum PTZ_STATE
{
	PTZ_ST_NULL = 0x0000,
	PTZ_ST_NORMAL = 0x0001, //普通状态,[Pan/Zoom]等
	PTZ_ST_TRACK = 0x0002, //轨迹
	PTZ_ST_AUTOSCAN = 0x0004, //自动扫描
	PTZ_ST_CRUISE = 0x0008, //巡航

	PTZ_ST_LOCK = 0x0100, //锁定、冻结;设置此标记将阻止其他命令
	PTZ_ST_CFG_PRESET = 0x0200, //配置预置点[目前没有使用]
	PTZ_ST_CFG_TRACK = 0x0400, // 配置轨迹
	PTZ_ST_CFG_CRUISE = 0x0800, //配置巡航线
};

enum PTZ_ERR
{
	PTZ_ERR_OK = 0,
	PTZ_ERR_WRITE_COM,			//写串口失败
	PTZ_ERR_UF_PROTOCOL,		//没有找到协议集

	PTZ_ERR_CHNN_LOCK,			//通道被锁定
	PTZ_ERR_CHNN_UN_INTERRUPT,	//不能打断通道操作
	PTZ_ERR_CHNN_UN_SET,		//没有找到相关通道设置
	PTZ_ERR_CHNN_UN_ENABLE,		//未启用通道
	PTZ_ERR_CHNN_WAITING,		//通道处于等待中
	PTZ_ERR_PRESET_DISABLE,		//预置点未启用
	PTZ_ERR_OPERATE_FAIL,		//操作云台失败,
};


#endif

