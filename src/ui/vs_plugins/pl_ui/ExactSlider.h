#pragma once


// CExactSlider

class CExactSlider : public CSliderCtrl
{
	DECLARE_DYNAMIC(CExactSlider)

public:
	CExactSlider(CWnd *parent,UINT nCtrlID);
	virtual ~CExactSlider();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

private:
	BOOL m_bDragging;
	BOOL m_bDragChanged;
	void PostMessageToParent(const int nTBCode) const;
	BOOL SetThumb(const CPoint& point);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


