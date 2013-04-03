// MySlider.cpp : implementation file
//

#include "stdafx.h"
#include "ExactSlider.h"


// CExactSlider

IMPLEMENT_DYNAMIC(CExactSlider, CSliderCtrl)

CExactSlider::CExactSlider(CWnd *parent,UINT nCtrlID)
{
	Create(WS_VISIBLE | WS_CHILD,CRect(0,0,95,22),parent,nCtrlID);
	m_bDragging = FALSE;
	m_bDragChanged = FALSE;
}

CExactSlider::~CExactSlider()
{
}


BEGIN_MESSAGE_MAP(CExactSlider, CSliderCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CExactSlider message handlers



void CExactSlider::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bDragging = TRUE;
    m_bDragChanged = FALSE;
    SetCapture();
	SetFocus();
	if (SetThumb(point))
	{
       m_bDragChanged = TRUE;
       PostMessageToParent(TB_THUMBTRACK);
	}

	CSliderCtrl::OnLButtonDown(nFlags, point);
}

void CExactSlider::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(m_bDragging)
	{
	   m_bDragging = false;
	   ::ReleaseCapture();
	   if (SetThumb(point))
	   {
		 PostMessageToParent(TB_THUMBTRACK);
		   m_bDragChanged = true;
	   }
	  if (m_bDragChanged)
	   {
		  PostMessageToParent(TB_THUMBPOSITION);
		  m_bDragChanged = false;
	   }
	}
	else
	{
	   CSliderCtrl::OnLButtonUp(nFlags, point);
	}

	CSliderCtrl::OnLButtonUp(nFlags, point);
}

void CExactSlider::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bDragging)
	{	
	   if (SetThumb(point))
	   {
		  m_bDragChanged = true;
		   PostMessageToParent(TB_THUMBTRACK);
		}
	}
   else
   {
	   CSliderCtrl::OnMouseMove(nFlags, point);
   }

	CSliderCtrl::OnMouseMove(nFlags, point);
}

BOOL CExactSlider::SetThumb(const CPoint& point)
   {
       const int nMin = GetRangeMin();
       const int nMax = GetRangeMax()+1;
      CRect rc;
       GetChannelRect(rc);
       double dPos;
       double dCorrectionFactor = 0.0;
       if (GetStyle() & TBS_VERT) 
       {
           // note: there is a bug in GetChannelRect, it gets the orientation of the rectangle mixed up
           dPos = (double)(point.y - rc.left)/(rc.right - rc.left);
       }
     else
       {
          dPos = (double)(point.x - rc.left)/(rc.right - rc.left);
      }
     // This correction factor is needed when you click inbetween tick marks
      // so that the thumb will move to the nearest one
      dCorrectionFactor = 0.5 *(1-dPos) - 0.5 *dPos;
      int nNewPos = (int)(nMin + (nMax-nMin)*dPos + dCorrectionFactor);
      const bool bChanged = (nNewPos != GetPos());
      if(bChanged)
       {
           SetPos(nNewPos);
       }
      return bChanged;
  }

void CExactSlider::PostMessageToParent(const int nTBCode) const
{
    CWnd* pWnd = GetParent();
    if(pWnd) pWnd->PostMessage(WM_HSCROLL, (WPARAM)((GetPos() << 16) | nTBCode), (LPARAM)GetSafeHwnd());
}
