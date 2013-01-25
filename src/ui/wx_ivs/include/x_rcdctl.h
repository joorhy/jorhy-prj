#ifndef __X_RCDCTRL_H_
#define __X_RCDCTRL_H_

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/datectrl.h>
#include <wx/calctrl.h>

class CXRcdCtl : public wxWindow
{
    public:
        CXRcdCtl(wxWindow *parent);
        ~CXRcdCtl();
		
	public:
		const wxDateTime &GetDateTime() const;
		void SetDateTime(const wxDateTime &dataTime);

	private:
		void OnSize(wxSizeEvent& event);
        void OnPaint(wxPaintEvent &event);
        DECLARE_EVENT_TABLE()

    private:
        void Init();

	private:
		wxWindow *m_pTitleWin;
		class RcdTime : public wxWindow
		{
			public:
				RcdTime(wxWindow* parent);
				~RcdTime();
			
			public:
				void SetDateTime(const wxDateTime &dataTime) { m_dateTime = dataTime; }
				
			private:	
				void Init();
				
			private:
                void OnPaint(wxPaintEvent& event);
                void OnSize(wxSizeEvent& event);
				DECLARE_EVENT_TABLE()
				
			private:
				wxBitmap m_lBmpDate;
				wxBitmap m_mBmpDate;
				wxBitmap m_rBmpDate;	
				
				int m_nBmpWidth;
				int m_nBmpHeight;
				wxDateTime m_dateTime;
		} *m_pRcdTime;
        class RcdCtrl : public wxWindow
        {
            public:
                RcdCtrl(wxWindow* parent);
                ~RcdCtrl();

            private:
                void Init();
				void RefreshRcdCtrl(int x, int y);

            private:
                void OnPaint(wxPaintEvent &event);
				void OnSize(wxSizeEvent& event);
				void OnMouseMotion(wxMouseEvent &event);
                void OnMouseLeftDown(wxMouseEvent &event);
                void OnMouseLeftUp(wxMouseEvent &event);
				void OnMouseLeaveWindow(wxMouseEvent &event);
                DECLARE_EVENT_TABLE()

            private:
                wxBitmap m_lbmpCtrl;
                wxBitmap m_mbmpCtrl;
                wxBitmap m_rbmpCtrl;
                wxBitmap m_bmpCtrl[8];
				wxBitmap m_bmpCurCtrl;
				
				int m_nWidth;
				int m_nHeight;
				int m_bgWidth;
				bool m_isSelected;
				int m_nCurIndex;
        } *m_pRcdCtrl;
        class CSlider : public wxControl
        {
            public:
                CSlider(wxWindow *parent);
                ~CSlider();

            private:
                void OnPaint(wxPaintEvent& event);
                void OnSize(wxSizeEvent& event);
                void OnMouseMotion(wxMouseEvent &event);
                void OnMouseLeftDown(wxMouseEvent &event);
                void OnMouseLeftUp(wxMouseEvent &event);
                DECLARE_EVENT_TABLE()

            private:
                void Init();
				void RefreshRcdSpeed(int x, int y);

            private:
                bool m_isSelected;
                int m_width;
                int m_height;
                int m_bgWidth;
                int m_bgHeight;
                int m_barWidth;
                wxBitmap m_leftBmp;
                wxBitmap m_rightBmp;
                wxBitmap m_centerBmp;
                wxBitmap m_barBmp;
                int m_pos;
                int m_speed;
        } *m_slider;
	private:
		wxCalendarCtrl *m_dateCtrl;
};

#endif // __X_RCDCTRL_H_