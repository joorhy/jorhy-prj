#ifndef __X_RCD_SLIDER_H_
#define __X_RCD_SLIDER_H_

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "jo_media_obj.h"
#include "jo_sdk.h"

#define STATE_4H	0
#define STATE_2H	1
#define STATE_1H	2
#define STATE_30M	3
#define STATE_10M	4
#define STATE_5M	5

class CXRcdSlider : public wxWindow
{
    public:
        CXRcdSlider(wxWindow *parent);
        ~CXRcdSlider();
		
	public:
		void RefreshRecordInfo(const RcdTimeList &timeList,  CMediaObj *pMediaObj, wxTreeItemId itemId);

    private:
        void OnPaint(wxPaintEvent& event);
        void OnSize(wxSizeEvent& event);
		void OnMouseWheel(wxMouseEvent &event);
		void OnMouseMotion(wxMouseEvent &event);
		void OnMouseLeftDown(wxMouseEvent &event);
		void OnMouseLeftUp(wxMouseEvent &event);
		void OnMouseLeaveWindow(wxMouseEvent &event);
        DECLARE_EVENT_TABLE()
		
	private:
		void CalculteTime(int index, int interval, int &h, int &m);
		void CalculteDateTime(int x, int interval);
		int GetTimeInterval();
		void DrawRecord(wxPaintDC *pDC);
		static void TimeFunc(void *pUser)
		{
			((CXRcdSlider *)pUser)->OnTime();
		}
		void OnTime();
		void InitMoveInterval();
		
	private:
		int m_beginSecond;		//启始刻度时间
		int m_curBeginSecond;	//当前启始刻度时间
		int m_oldCurSecond;		//当前显示时间
		int m_state;
		int m_nOffset;
		int m_curOffset;
		int m_nAutoOffset;
		int m_secondsPerpix;
		int m_seconds;
		bool m_bSelected;
		
		wxPoint m_pst;
		wxDateTime m_dateTime;
		time_t m_beginTime;
		time_t m_endTime;
		
		RcdTimeList m_curTimeList;
		CMediaObj *m_mediaObj;
		wxTreeItemId m_treeItemId;
		
		typedef std::map<CMediaObj *, wxWindow *> MediaObjMap;
        MediaObjMap m_mediaObjMap;
};

#endif //~__X_RCD_SLIDER_H_