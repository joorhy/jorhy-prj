

#include "stdafx.h"
#include "pl_button.h"

// CPngButton
IMPLEMENT_DYNAMIC(CPlButton, CButton)
CPlButton::CPlButton(HINSTANCE hIns,CWnd *Parent,UINT nBtnId)
{
	
	//m_hInstance = hIns;
	Create(NULL,
		WS_EX_LAYERED | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW | WS_CLIPSIBLINGS,
		CRect(0,0,0,0),Parent,nBtnId);
	m_bTrack = TRUE;
	m_ButtonStatus = Status_Nromal;
	m_NormalBitmap.Attach(NULL);
	m_OverBitmap.Attach(NULL);
	m_DownBitmap.Attach(NULL);
	m_DisableBitmap.Attach(NULL);
	m_bChanged = TRUE;
}

CPlButton::~CPlButton()
{
}


BEGIN_MESSAGE_MAP(CPlButton, CButton)
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER,OnMouseHover)
	ON_WM_MOUSEMOVE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CPngButton message handlers
void CPlButton::LoadPng(UINT nNormalID,UINT nOverId,UINT nDownId,UINT nDisableId,
						 UINT nExNorID,UINT nExOverID,UINT nExDownId,UINT nExDisID)
{
	//normal
	LoadImageFromResource(&m_NormalBitmap,nNormalID,"PNG");
	//over
	if(NULL == nOverId)
		LoadImageFromResource(&m_OverBitmap,nNormalID,"PNG");
	else
		LoadImageFromResource(&m_OverBitmap,nOverId,"PNG");
	//down
	if(NULL == nDownId)
		LoadImageFromResource(&m_DownBitmap,nNormalID,"PNG");
	else
		LoadImageFromResource(&m_DownBitmap,nDownId,"PNG");
	//disable
	if(NULL == nDisableId)
		LoadImageFromResource(&m_DisableBitmap,nNormalID,"PNG");
	else
		LoadImageFromResource(&m_DisableBitmap,nDisableId,"PNG");
	//status change normal
	if(NULL == nExNorID)
		LoadImageFromResource(&m_NormalBitmap_EX,nNormalID,"PNG");
	else
		LoadImageFromResource(&m_NormalBitmap_EX,nExNorID,"PNG");
	//status change over
	if(NULL == nExOverID)
	{
		if(NULL == nExNorID)
			LoadImageFromResource(&m_OverBitmap_EX,nNormalID,"PNG");
		else
			LoadImageFromResource(&m_OverBitmap_EX,nExNorID,"PNG");
	}
	else
		LoadImageFromResource(&m_OverBitmap_EX,nExOverID,"PNG");
	//status change down
	if(NULL == nExDownId)
	{
		if(NULL == nExNorID)
			LoadImageFromResource(&m_DownBitmap_EX,nNormalID,"PNG");
		else
			LoadImageFromResource(&m_DownBitmap_EX,nExNorID,"PNG");
	}
	else
		LoadImageFromResource(&m_DownBitmap_EX,nExDownId,"PNG");
	//status change disable
	if(NULL == nExDisID)
	{
		if(NULL == nExNorID)
			LoadImageFromResource(&m_DisableBitmap_EX,nNormalID,"PNG");
		else
			LoadImageFromResource(&m_DisableBitmap_EX,nExNorID,"PNG");
	}
	else
		LoadImageFromResource(&m_DisableBitmap_EX,nExDisID,"PNG");
	ReSizeButton();
}

void CPlButton::LoadImageFromResource(CBitmap *pBitmap,UINT nResId,LPCSTR lpType)
{
	CImage pImage;
	HBITMAP hbitmap;
	HRSRC hRsrc = ::FindResource(AfxGetResourceHandle(),MAKEINTRESOURCE(nResId),lpType);
	HGLOBAL hImgData = ::LoadResource(AfxGetResourceHandle(),hRsrc);
	LPVOID lpVoid = ::LockResource(hImgData);
	LPSTREAM pStream = NULL;
	DWORD dwSize	= ::SizeofResource(AfxGetResourceHandle(),hRsrc);
	HGLOBAL hNew	= ::GlobalAlloc(GHND,dwSize);
	LPBYTE lpByte	= (LPBYTE)::GlobalLock(hNew);
	::memcpy(lpByte,lpVoid,dwSize);
	::GlobalUnlock(hNew);
	HRESULT hRet	= ::CreateStreamOnHGlobal(hNew,TRUE,&pStream);
	if(hRet == S_OK) 
		pImage.Load(pStream);
	::GlobalFree(hNew);
	 hbitmap = pImage.Detach();
	 pBitmap->Attach(hbitmap);
}
void CPlButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	BITMAP bitmap;
	CDC memdc;
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct -> hDC);
	memdc.CreateCompatibleDC(pDC);
	HGDIOBJ hOldSel;
	if(!m_bChanged)
	{
		switch(m_ButtonStatus)
		{
		case Status_Nromal:
			hOldSel= memdc.SelectObject(m_NormalBitmap_EX);
			m_NormalBitmap_EX.GetBitmap(&bitmap);
			break;
		case Status_Over:
			hOldSel= memdc.SelectObject(m_OverBitmap_EX);
			m_OverBitmap_EX.GetBitmap(&bitmap);
			break;
		case Status_Down:
			hOldSel= memdc.SelectObject(m_DownBitmap_EX);
			m_DownBitmap_EX.GetBitmap(&bitmap);
			break;
		case Status_Disable:
			hOldSel= memdc.SelectObject(m_DisableBitmap_EX);
			m_DisableBitmap_EX.GetBitmap(&bitmap);
			break;
		default:
			break;
		}
	}
	else
	{
		switch(m_ButtonStatus)
		{
		case Status_Nromal:
			hOldSel= memdc.SelectObject(m_NormalBitmap);
			m_NormalBitmap.GetBitmap(&bitmap);
			break;
		case Status_Over:
			hOldSel= memdc.SelectObject(m_OverBitmap);
			m_OverBitmap.GetBitmap(&bitmap);
			break;
		case Status_Down:
			hOldSel= memdc.SelectObject(m_DownBitmap);
			m_DownBitmap.GetBitmap(&bitmap);
			break;
		case Status_Disable:
			hOldSel= memdc.SelectObject(m_DisableBitmap);
			m_DisableBitmap.GetBitmap(&bitmap);
			break;
		default:
			break;
		}
	}
	pDC->StretchBlt(0,0,bitmap.bmWidth,bitmap.bmHeight,&memdc,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);
	SetLayeredWindowAttributes(RGB(128,128,128),0,LWA_COLORKEY);
	SelectObject(memdc,hOldSel);
	memdc.DeleteDC();
	ReleaseDC(pDC);
	DeleteObject(hOldSel);
}


void CPlButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_ButtonStatus = Status_Down;
	CButton::OnLButtonDown(nFlags, point);
}

LRESULT CPlButton::OnMouseLeave(WPARAM wParam,LPARAM lParam)
{
	if(m_ButtonStatus != Status_Nromal)
	{
		m_ButtonStatus = Status_Nromal;
		Invalidate();
	}
	//SendMessage(WM_DRAWITEM);
	return TRUE;
}

LRESULT CPlButton::OnMouseHover(WPARAM wParam,LPARAM lParam)
{
	if(m_ButtonStatus != Status_Over)
	{
		m_ButtonStatus = Status_Over;
		Invalidate();
	}
	//SendMessage(WM_DRAWITEM);
	return TRUE;
}

void CPlButton::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_bTrack)
	{
		TRACKMOUSEEVENT tmp;
		tmp.cbSize		= sizeof(tmp);
		tmp.dwFlags		= TME_HOVER | TME_LEAVE;
		tmp.dwHoverTime	= 1;
		tmp.hwndTrack	= this->m_hWnd;
		 m_bTrack =_TrackMouseEvent(&tmp);
	}
	CButton::OnMouseMove(nFlags, point);
}

BOOL CPlButton::EnableWindow(BOOL bEnable)
{
	if(bEnable)
	{
		m_ButtonStatus = Status_Nromal;
		Invalidate();
	}
	else
	{
		m_ButtonStatus = Status_Disable;
		Invalidate();
	}
	return ::EnableWindow(this->m_hWnd,bEnable);
}

void CPlButton::ReSizeButton()
{
	BITMAP bitmap;
	CRect rect;

	m_NormalBitmap.GetBitmap(&bitmap);
	GetWindowRect(&rect);
	MoveWindow(rect.left,rect.top,bitmap.bmWidth,bitmap.bmHeight,FALSE);
}

HBRUSH CPlButton::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CButton::OnCtlColor(pDC, pWnd, nCtlColor);
	switch(nCtlColor)
	{
	case CTLCOLOR_BTN:
		break;
		hbr = CreateSolidBrush(RGB(129,129,129)); 
	default:
		break;
	}
	return hbr;
}

void CPlButton::ChangePng(BOOL bInitStatus)
{
	m_bChanged = bInitStatus;
	Invalidate();
}

