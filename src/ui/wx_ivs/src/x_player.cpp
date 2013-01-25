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
	if (m_pDecoder)
	{
		m_pDecoder->DeinitDecoder();
		delete m_pDecoder;
	}
		
	if (m_pRender)
		delete m_pRender;
		
	if (m_pReciver)
		delete m_pReciver;
}

int CXPlayer::Start(const char *pResid, const XWindowInfo &winInfo)
{
    m_resid = pResid;
    m_winInfo = winInfo;
	
	m_nMode = m_winInfo.mode;
	if (m_nMode == 1)
	{
		m_pReciver->Connect(m_svrAddr.c_str(), 8002);
		m_pReciver->Create();
		m_pReciver->StartView(pResid, 0);
		m_pReciver->Run();
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
	if (m_nMode == 2)
		m_timer.Stop();
	
	m_pReciver->Disconnect();
	m_pReciver->Delete();

    return 0;
}

int CXPlayer::AspectRatio(int w, int h)
{
    m_winInfo.w = w;
    m_winInfo.h = h;

    return 0;
}

void CXPlayer::RegistCallback(void *func, void *pUser)
{
	m_cbFunc = func;
	m_pUser = pUser;
}

int CXPlayer::Init()
{
	m_pDecoder = new CXDecoder(m_pRender);
	m_pDecoder->InitDecoder();
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
