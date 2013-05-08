#include "x_player.h"
#include <assert.h>
#include <sstream>
#include <stdio.h>
#include "jo_sdk.h"
#include "x_reciver.h"
#include "x_decoder.h"
#include "x_render.h"

CXPlayer::CXPlayer(const char *pSvrAddr)
{
    m_timer.SetOwner(this);
    m_svrAddr = pSvrAddr;
	m_nMode = 1;
	m_cbFunc = NULL;
	m_pUser = NULL;
	m_pReciver = NULL;
	m_pDecoder = NULL;
	m_pRender = NULL;
	
    Init();
}

CXPlayer::~CXPlayer()
{
	if (m_pReciver)
	{
		m_pReciver->Disconnect();
		delete m_pReciver;
	}
	
	if (m_pDecoder)
	{
		m_pDecoder->Stop();
		//delete m_pDecoder;
	}
		
	if (m_pRender)
	{
		m_pRender->Stop();
		//delete m_pRender;
	}
}

int CXPlayer::Start(const char *pResid, const XWindowInfo &winInfo)
{
    m_resid = pResid;
    m_winInfo = winInfo;
	
	m_nMode = m_winInfo.mode;
	if (m_nMode == 1)
	{
		m_pRender->Start(winInfo.window);
		m_pReciver->Connect("192.168.1.6"/*m_svrAddr.c_str()*/, 8002);
		m_pDecoder->Start();
		m_pReciver->StartView(pResid, 0);
	}
	else if (m_nMode == 2)
	{
		m_timer.Start(1000);
	}

    AspectRatio(m_winInfo.w, m_winInfo.h);

    return 0;
}

int CXPlayer::Stop()
{
	m_pRender->Stop();
	if (m_nMode == 2)
		m_timer.Stop();
	
	m_pReciver->Disconnect();

    return 0;
}

int CXPlayer::AspectRatio(int w, int h)
{
    m_winInfo.w = w;
    m_winInfo.h = h;
	m_pDecoder->AspectRatio(w, h);
	m_pRender->AspectRatio(w, h);

    return 0;
}

void CXPlayer::RegistCallback(void *func, void *pUser)
{
	m_cbFunc = func;
	m_pUser = pUser;
}

int CXPlayer::Init()
{
	m_pRender = new CXRender();
	m_pDecoder = new CXDecoder(m_pRender);
	m_pReciver = new CXReciver(m_pDecoder);
    return 0;
}

bool CXPlayer::IsPlaying()
{
    return true;
}

bool CXPlayer::ProcessEvent(wxEvent& event)
{
    //wxEVT_COMMAND_BUTTON_CLICKED
    if (wxEVT_TIMER == event.GetEventType())
    {
		if (m_nMode == 1)
		{
			if (IsPlaying())
			{
				m_timer.Stop();
				return true;
			}
		}
		else if (m_nMode == 2)
		{
			if (m_cbFunc != NULL)
				((PlayerCallbackFunc)m_cbFunc)(m_pUser);
		}
    }

    return true;
}
