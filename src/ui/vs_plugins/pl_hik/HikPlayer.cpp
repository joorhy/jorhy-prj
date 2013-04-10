#include "StdAfx.h"
#include "HikPlayer.h"
#include "PlayM4.h"
#include <fstream>

static
char hikhead[] = {0x49,0x4d,0x4b,0x48,0x01,0x01,0x00,0x00,0x02,0x00,
				0x01,0x00,0x21,0x72,0x01,0x10,0x00,0x7d,0x00,0x00,
				0x00,0x7d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,};

extern std::ofstream hikFile;
/***********************ÀàÊµÏÖ**********************************/
HikPlayer::HikPlayer(int nWorkMode,void *pFactorUser)
{
	m_port		= -1;
	m_Model		= nWorkMode;
	m_hPlayWnd	= NULL;
	m_pBuff		= NULL;
	m_pRecv		= NULL;
	m_bStart	= TRUE;
	m_bPause	= FALSE;
}

HikPlayer::~HikPlayer(void)
{
	Stop();
	if(m_pBuff != NULL)
	{
		delete m_pBuff;
		m_pBuff = NULL;
	}
}

BOOL HikPlayer::InitPlay(char *pHeader,int nHeadLen)
{
	if(!PlayM4_GetPort(&m_port))
		return FALSE;
	if(m_Model == STREAME_REALTIME)
	{
		if(!PlayM4_SetStreamOpenMode(m_port,STREAME_REALTIME))
			return FALSE;
		if(!PlayM4_OpenStream(m_port,(PBYTE)pHeader,nHeadLen,REAL_PLAYERSIZE))
			return FALSE;
		if (!PlayM4_SetDisplayBuf(m_port,REAL_FRAMENUM))
			return FALSE;
	}
	else
	{
		if(!PlayM4_SetStreamOpenMode(m_port,STREAME_FILE))
			return FALSE;
		if(!PlayM4_OpenStream(m_port,(PBYTE)pHeader,nHeadLen,VOD_PLAYERSIZE))
			return FALSE;
		if (!PlayM4_SetDisplayBuf(m_port,VOD_FRAMENUM))
			return FALSE;
	}
	if(!PlayM4_Play(m_port, m_hPlayWnd))
		return FALSE;
	return TRUE;
	
}

BOOL HikPlayer::Play(HWND hPlayWnd, const PL_PlayInfo &playInfo)
{
	m_hPlayWnd = hPlayWnd;
	if(m_pBuff == NULL)
	{
		m_pBuff = new BeyondBuffer();
	}
	if(m_pRecv == NULL)
	{
		m_pRecv = new BeyondRecv();
	}
	BOOL bRet = StartPlay();
	if(!bRet)
	{
		if(m_pRecv)
		{
			delete m_pRecv;
			m_pRecv = NULL;
		}
		if(m_pBuff)
		{
			delete m_pBuff;
			m_pBuff = NULL;
		}
		return FALSE;
	}
	/*bRet = m_pRecv->StartRecv(psz_mrl,m_pBuff);
	if(!bRet)
	{
		if(m_pRecv)
		{
			m_pRecv->StopRecv();
			delete m_pRecv;
			m_pRecv = NULL;
		}
		if(m_pBuff)
		{
			delete m_pBuff;
			m_pBuff = NULL;
		}
		return FALSE;
	}*/

	return TRUE;
}

void HikPlayer::Play()
{
	
}

void HikPlayer::Stop()
{
	if(m_port != -1)
	{
		PlayM4_Stop(m_port);
		PlayM4_CloseStream(m_port);
		PlayM4_FreePort(m_port);
		m_port = -1;
	}
	if(m_pRecv)
	{
		m_pRecv->StopRecv();
		delete m_pRecv;
		m_pRecv = NULL;
	}
	if(m_pBuff)
	{
		delete m_pBuff;
		m_pBuff = NULL;
	}
}

void HikPlayer::Pause()
{
	if(m_Model == STREAME_REALTIME)
		return;
	if(m_pRecv)
		m_pRecv->PauseRecv(!m_bPause);
	if(m_port != -1)
		PlayM4_Pause(m_port,!m_bPause);
	m_bPause = !m_bPause;
}

void HikPlayer::PlayOneByOne()
{
	if(m_Model == STREAME_REALTIME)
		return;
	if(m_port != -1)
		PlayM4_OneByOne(m_port);
}

int HikPlayer::GetVolume()
{
	if(m_port == -1)
		return 0;
	return PlayM4_GetVolume(m_port);
}

BOOL HikPlayer::SetVolume(int nVolume)
{
	if(m_port == -1)
		return TRUE;
	return PlayM4_SetVolume(m_port,nVolume);
}

BOOL HikPlayer::IsPlaying()
{
	return 0;
}

BOOL HikPlayer::SetSpeed(BOOL bSpeedUp)
{
	if(m_Model == STREAME_REALTIME)
		return TRUE;
	if(m_pRecv)
		m_pRecv->SetSpeedRecv(bSpeedUp);
	if(m_port != -1)
	{
		if(bSpeedUp)
			PlayM4_Fast(m_port);
		else
			PlayM4_Slow(m_port);
	}
	return TRUE;
}

BOOL HikPlayer::Capture(char *path)
{
	return 0;
}

BOOL HikPlayer::Record(char *path)
{
	return 0;
}

int HikPlayer::GetPlayStatus()
{
	return 0;
}

HWND HikPlayer::GetPlayHwnd()
{
	return 0;
}

BOOL HikPlayer::VodStreamJump(const PL_PlayInfo &playInfo)
{
	if(m_port == -1)
		return FALSE;

	if(m_pRecv)
	{
		m_pRecv->VodJumpRecv((char *)playInfo.pUrl);
		m_pBuff->FlushBuff();
		PlayM4_ResetSourceBuffer(m_port);
	}
	return true;
}

BOOL HikPlayer::StartPlay()
{
	if(!m_bStart)
		return TRUE;
	CreateThread(NULL,0,HikPlayer::PlayThread,this,0,NULL);
	return TRUE;
}

DWORD WINAPI HikPlayer::PlayThread(void *parm)
{
	HikPlayer *pThis = reinterpret_cast<HikPlayer*>(parm);
	if(pThis)
		pThis->InputData();
	return TRUE;
}

void HikPlayer::InputData()
{
	char *pDataBuff = new char[DEFAULT_RECVBUFFSIZE];
	memset(pDataBuff,0,DEFAULT_RECVBUFFSIZE);
	BOOL bRet;
	hikFile.write(hikhead,sizeof(hikhead));
	//bRet = InitPlay(hikhead,sizeof(hikhead));
	//TRACE("Hik Play: %s\n",bRet==0?"FALSE":"TRUE");

	while(m_bStart)
	{
		if(m_pBuff != NULL)
		{
			StreamHeader header;
			if(m_pBuff->PopBuffer(pDataBuff,header))
			{
				if(header.datatype == VIDEO_HEAD)
				{
					bRet = InitPlay(pDataBuff,header.datalen);
					TRACE("Hik Play: %s\n",bRet==0?"FALSE":"TRUE");
					continue;
				}
				else
				{
					if(!PlayM4_InputData(m_port,(PBYTE)pDataBuff,(DWORD)header.datalen))
					{
						TRACE("HIK Input DATA error:\n");
						int nError = PlayM4_GetLastError(m_port);
						if (PLAYM4_BUF_OVER == nError)
						{
							PlayM4_ResetSourceBuffer(m_port);
							continue;
						}
						break;
					}
				}
			}
			else
			{
				Sleep(100);
			}
		}
	}
	TRACE("HikPlay thread exit\n");
}

BOOL HikPlayer::SetOSDText(int stime,char *osdText)
{
	return TRUE;
}

BOOL HikPlayer::IsPaused()
{
	return FALSE;
}

void HikPlayer::AspectRatio(int width,int height)
{

}

void HikPlayer::SleepPlayer(bool bSleep)
{

}

PLAYER_BEGIN_MAKER(pl_hik)
	PLAYER_ENTER_MAKER("pl_hik", HikPlayer::Maker)
PLAYER_END_MAKER()