#include "x_rcd_slider.h"		
#include "jo_frame.h"
#include "x_rcdctl.h"
#include "x_video.h"
#include "x_tree.h"
#include "x_catalog.h"
#include "x_window.h"

#define INTERVAL_NUM	6

BEGIN_EVENT_TABLE(CXRcdSlider, wxWindow)
	EVT_PAINT(CXRcdSlider::OnPaint)
    EVT_SIZE(CXRcdSlider::OnSize)
	EVT_MOUSEWHEEL(CXRcdSlider::OnMouseWheel)
	EVT_MOTION(CXRcdSlider::OnMouseMotion)
    EVT_LEFT_DOWN(CXRcdSlider::OnMouseLeftDown)
    EVT_LEFT_UP(CXRcdSlider::OnMouseLeftUp)
	EVT_LEAVE_WINDOW(CXRcdSlider::OnMouseLeaveWindow)
END_EVENT_TABLE()

CXRcdSlider::CXRcdSlider(wxWindow *parent)
: wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED | wxBORDER_DOUBLE)
{
	SetBackgroundColour(wxColor(197, 210, 227));
	m_beginSecond = 0;
	m_curBeginSecond = 0;
	m_oldCurSecond = 0;
	m_state = 5;
	m_bSelected = false;
	m_nOffset = 20;
	m_curOffset = m_nOffset;
	m_nAutoOffset = m_nOffset;
	m_mediaObj = NULL;
}

CXRcdSlider::~CXRcdSlider()
{
	
}

void CXRcdSlider::OnPaint(wxPaintEvent& event)
{
	int nWidth = GetSize().GetWidth();
	int nInterval = (nWidth) / INTERVAL_NUM;
	wxPaintDC *pDC = new wxPaintDC(this);
	pDC->SetPen(wxPen(wxColour(158, 176, 200), 1, wxSTIPPLE));
	
	wxFont font(6, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    pDC->SetFont(font);
    pDC->SetTextForeground(wxColour(75, 103, 140));
	
	for (int i=0; i<INTERVAL_NUM; i++)
	{
		int x = i * nInterval;
		if (m_bSelected)
			x += m_nOffset;
		else
			x += m_nAutoOffset;
		int nHour = 0;
		int nMinute = 0;
		CalculteTime(i, nInterval, nHour, nMinute);
		pDC->DrawLine(x, 0, x, 125);
		pDC->DrawText(wxString::Format(_("%02d:%02d"), nHour, nMinute), x - 11, 126);
	}
	
	//显示时间条
	int x = nWidth / 2;
	CalculteDateTime(x, nInterval);	
	//画录像区域
	DrawRecord(pDC);
	pDC->DrawText(wxString::Format(_("%04d-%02d-%02d %02d:%02d:%02d"), m_dateTime.GetYear(), 
			m_dateTime.GetMonth() + 1, m_dateTime.GetDay(), m_dateTime.GetHour(), 
			m_dateTime.GetMinute(), m_dateTime.GetSecond()), x - 49, 0);
	
	pDC->SetPen(wxPen(wxColour(237, 106, 15), 2, wxSTIPPLE));
	pDC->DrawLine(x - 1, 0, x -1, 151);
}

void CXRcdSlider::OnSize(wxSizeEvent& event)
{
    SetSize(251 + 1, GetParent()->GetSize().GetHeight() - 151, GetParent()->GetSize().GetWidth() - 251 - 2, 151 - 1);
    InitMoveInterval();
	Refresh();
}

void CXRcdSlider::OnMouseWheel(wxMouseEvent &event)
{
	m_state += event.GetWheelRotation() / event.GetWheelDelta();
	if (m_state < 0)
		m_state = 0;
	else if (m_state > 5)
		m_state = 5;
		
	InitMoveInterval();
	//int nInterval = GetTimeInterval();
	//m_beginSecond = m_beginSecond /  nInterval * nInterval;
	//m_curBeginSecond = m_beginSecond;
	//Refresh();
	//fprintf(stderr, "%d %d\n", event.GetWheelRotation(), event.GetWheelDelta());
}

void CXRcdSlider::OnMouseMotion(wxMouseEvent &event)
{
    wxPoint pst = event.GetPosition();
	if (m_bSelected)
	{
		int interval = GetSize().GetWidth() / INTERVAL_NUM;
		int dx = (pst.x - m_pst.x) % interval; 
		int timeInterval = GetTimeInterval();
		if (dx < 0)
		{
			m_nOffset = ((interval + m_curOffset + dx)  + interval) % interval;
			m_beginSecond = m_curBeginSecond - ((pst.x - m_pst.x - (interval - m_curOffset)) / interval * timeInterval);
		}
		else if (dx > 0)
		{
			m_nOffset = (m_curOffset + dx) % interval;
			m_beginSecond = m_curBeginSecond - ((pst.x - m_pst.x + m_curOffset) / interval * timeInterval);
		}
		if (m_beginSecond < 0)
		{
			m_beginSecond = 86400 + m_beginSecond;
		}
		m_beginSecond = m_beginSecond % 86400;
		Refresh();
		//fprintf(stderr, "m_curHour = %d::%d - %d > %d\n", m_firstHour, pst.x, m_pst.x, interval);
	}
}

void CXRcdSlider::OnMouseLeftDown(wxMouseEvent &event)
{
    m_pst = event.GetPosition();
	m_bSelected = true;
}

void CXRcdSlider::OnMouseLeftUp(wxMouseEvent &event)
{
	m_curBeginSecond = m_beginSecond;
	m_curOffset = m_nOffset;
	m_nAutoOffset = m_nOffset;
    m_bSelected = false;
	
	if (m_mediaObj != NULL)
	{
		CVideoDlg *pVideoDlg = dynamic_cast<CVideoDlg *>
			(((CBrFrame *)GetParent())->GetVideoDlg());
		if (pVideoDlg != NULL)
		{
			MediaObjMap::iterator it = m_mediaObjMap.find(m_mediaObj);
			if (it != m_mediaObjMap.end())
			{
				m_mediaObj->Invoke(it->second, 0);
				pVideoDlg->SetIdleWin(it->second);
				m_mediaObjMap.erase(it);
			}
			wxWindow *pWindow = pVideoDlg->GetIdleWin();
			if (pWindow != NULL && m_mediaObj->Invoke(pWindow, 2, m_dateTime.GetTicks()) == 0)
			{
				m_mediaObj->RegistCallback(pWindow, (void *)CXRcdSlider::TimeFunc, this);
				pVideoDlg->SetBusyWin(pWindow);
				m_mediaObjMap[m_mediaObj] = pWindow;
				((CVideoWin *)pWindow->GetParent())->SetResid(m_mediaObj->GetResid());
				CCatalogDlg *pCatalogDlg = dynamic_cast<CCatalogDlg *>
					(((CBrFrame *)GetParent())->GetCatalogDlg());
				if (pCatalogDlg != NULL)
				{
					((CXTree *)pCatalogDlg->GetTreeWindow())->StartVideo(pWindow, m_treeItemId);
				}
			}
		}
	}
}

void CXRcdSlider::OnMouseLeaveWindow(wxMouseEvent &event)
{
	m_curBeginSecond = m_beginSecond;
	m_curOffset = m_nOffset;
    m_bSelected = false;
}

void CXRcdSlider::CalculteTime(int index, int interval, int &h, int &m)
{
	int timeInterval = GetTimeInterval();
	int curSecond = (m_beginSecond / timeInterval * timeInterval) + GetTimeInterval() * index;
	curSecond = curSecond % 86400;
	h = (curSecond) / 3600;
	m = (curSecond % 3600) / 60;
}

void CXRcdSlider::CalculteDateTime(int x, int interval)
{
	int timeInterval = GetTimeInterval();
	m_dateTime = ((CXRcdCtl *)((CBrFrame *)GetParent())->GetRcdDlg())->GetDateTime();
	int curSecond = (m_beginSecond - (m_nOffset * timeInterval / interval)) + INTERVAL_NUM / 2 * timeInterval;
	
	fprintf(stderr, "%d + (%d - %d) / %d * %d\n", m_beginSecond, x, m_nOffset, interval, timeInterval);
	curSecond = curSecond % 86400;
	int nMinute = (curSecond % 3600) / 60;
	int nHour = curSecond / 3600;
	int nSecond = curSecond % 60;
	nMinute = nMinute % 60;
	
	fprintf(stderr, "%d - %d\n", curSecond, m_oldCurSecond);
	int dt = curSecond - m_oldCurSecond;
	if (abs(dt) > (timeInterval * INTERVAL_NUM / 2))
	{
		int dd = 1;
		if (dt > 0)
		{
			//减少一天
			dd = -1;
		}
		int d = m_dateTime.GetDay() + dd;
		int td = 31;
		switch (m_dateTime.GetMonth())
		{
			case 4:case 6:case 9:case 11:
				td = 30;
				break;
			case 2:
				if ((m_dateTime.GetYear() % 4) == 0)
					td = 29;
				else
					td = 28;
		}
		int dm = 0;
		if (d == 0)
		{
			//减少一月
			dm = -1; 
			d = td;
		}
		else
		{
			//增大一月
			if (d > td)
			{
				dm = 1;
				d = 1;
			}
		}

		int m = m_dateTime.GetMonth() + dm;
		int dy = 0;
		if (m < 0)
		{
			//减小一年
			dy = -1;
			m = 11;
		}
		else if (m > 11)
		{
			//增大一年
			dy = 1;
			m = 0;
		}
		
		int y = m_dateTime.GetYear() + dy;
		m_dateTime.SetYear(y);
		m_dateTime.SetMonth((wxDateTime::Month)m);
		m_dateTime.SetDay(d);
	}
	m_oldCurSecond = curSecond;
	
	m_dateTime.SetHour(nHour);
	m_dateTime.SetMinute(nMinute);
	m_dateTime.SetSecond(nSecond);

	((CXRcdCtl *)((CBrFrame *)GetParent())->GetRcdDlg())->SetDateTime(m_dateTime);
	m_beginTime = m_dateTime.GetTicks() - (timeInterval * INTERVAL_NUM / 2);
	m_endTime = m_dateTime.GetTicks() + (timeInterval * INTERVAL_NUM / 2);
}

int CXRcdSlider::GetTimeInterval()
{
	int timeInterval = 0;
	switch (m_state)
	{
		case STATE_4H:
			timeInterval = 14400;
			break;
		case STATE_2H:
			timeInterval = 7200;
			break;
		case STATE_1H:
			timeInterval = 3600;
			break;
		case STATE_30M:
			timeInterval = 1800;
			break;
		case STATE_10M:
			timeInterval = 600;
			break;
		case STATE_5M:
			timeInterval = 300;
			break;
	}
	
	return timeInterval;
}

void CXRcdSlider::RefreshRecordInfo(const RcdTimeList &timeList, CMediaObj *pMediaObj, wxTreeItemId itemId)
{
	m_curTimeList.Clear();
	m_curTimeList = timeList;
	m_mediaObj = pMediaObj;
	m_treeItemId = itemId;
	Refresh();
}

void CXRcdSlider::DrawRecord(wxPaintDC *pDC)
{
	//画录像区域
	int w = GetSize().GetWidth();// - 5;
	/*pDC->SetPen(wxPen(wxColour(62, 100, 157), 1, wxSTIPPLE));
	pDC->DrawLine(0, 50, w, 50);
	//pDC->DrawLine(0, 50, 0, 76);
	pDC->DrawLine(0, 76, w, 76);
	//pDC->DrawLine(w, 50, w, 76);
	
	pDC->SetBrush(wxBrush(wxColour(255, 255, 255)));
	pDC->DrawRectangle(0, 50, w, 27);*/
	
	pDC->SetBrush(wxBrush(wxColour(82, 93, 115)));
	int nTimeInterval = GetTimeInterval();
	RcdTimeInfo *pInfo;
	RcdTimeList::iterator iter;
	for (iter = m_curTimeList.begin(); iter != m_curTimeList.end(); ++iter)
	{
		pInfo = *iter;
		if (m_beginTime >= pInfo->begin_time && pInfo->end_time > m_beginTime)
		{
			if (pInfo->end_time <= m_endTime)
				pDC->DrawRectangle(0, 50, 
					(pInfo->end_time - m_beginTime) * w / (nTimeInterval * INTERVAL_NUM), 27);
			else
				pDC->DrawRectangle(0, 50, w, 27);
		}
		else if (pInfo->begin_time >= m_beginTime && pInfo->end_time <= m_endTime)
		{
			pDC->DrawRectangle((pInfo->begin_time - m_beginTime) * w / (nTimeInterval * INTERVAL_NUM), 50, 
				(pInfo->end_time - pInfo->begin_time) * w / (nTimeInterval * INTERVAL_NUM), 27);
		}
		else if (pInfo->begin_time < m_endTime && pInfo->end_time >= m_endTime)
		{
			if (pInfo->begin_time < m_beginTime)
				pDC->DrawRectangle(0, 50, w, 27);
			else
				pDC->DrawRectangle((pInfo->begin_time - m_beginTime) * w / (nTimeInterval * INTERVAL_NUM), 50, 
						(m_endTime - pInfo->begin_time) * w / (nTimeInterval * INTERVAL_NUM), 27);
		}
		
		//pDC->DrawRectangle(200, 50, 200, 27);
	}
}

void CXRcdSlider::OnTime()
{
	//m_dateTime.Set(m_dateTime.GetTicks() + 1);
	//((CXRcdCtl *)((CBrFrame *)GetParent())->GetRcdDlg())->SetDateTime(m_dateTime);
	++m_beginSecond;
	--m_seconds;
	if (m_seconds == 0)
	{
		int nInterval = GetSize().GetWidth() / INTERVAL_NUM;
		m_nAutoOffset = (m_nAutoOffset - 1 + nInterval) % nInterval;
		m_seconds = m_secondsPerpix;
	}
	Refresh();
}

void CXRcdSlider::InitMoveInterval()
{
	int nInterval = GetSize().GetWidth() / INTERVAL_NUM;
	int timeInterval = GetTimeInterval();
	m_secondsPerpix = timeInterval / nInterval;
	m_seconds = m_secondsPerpix;
}