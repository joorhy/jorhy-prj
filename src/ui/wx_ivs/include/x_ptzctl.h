#ifndef __X_PTZCTL_H_
#define __X_PTZCTL_H_

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class CXPtzCtl : public wxWindow
{
    public:
        CXPtzCtl(wxWindow *parent);
        ~CXPtzCtl();

    private:
        void OnSize(wxSizeEvent& event);
        DECLARE_EVENT_TABLE()

    private:
        void Init();
        void PtzStart(int nCmd);
        void PtzStop(int nCmd);
        void SetSpeed(int nSpeed) { m_nSpeed = nSpeed; }
        void SetPreset(int nPreset) { m_nPreset = nPreset; }
        void SetAux(int nAux) { m_nAux = nAux; }

    private:
        wxWindow *m_pTitleWin;
        class CPtz : public wxWindow
        {
            public:
                CPtz(wxWindow *parent);
                ~CPtz();

            private:
                void OnPaint(wxPaintEvent& event);
                void OnSize(wxSizeEvent& event);
                void OnMouseMotion(wxMouseEvent &event);
                void OnMouseLeftDown(wxMouseEvent &event);
                void OnMouseLeftUp(wxMouseEvent &event);
                void OnMouseLeaveWindow(wxMouseEvent &event);
                DECLARE_EVENT_TABLE()

            private:
                void Init();
                int GetBmpIndex(float x, float y);
                void RefreshBmp(int x, int y, int state);

            private:
                wxBitmap m_ptzBmp;
                wxBitmap m_CurBmp;
                int m_width;
                int m_height;
        } *m_ptz;
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
        class CBtn : public wxWindow
        {
            public:
                CBtn(wxWindow *parent, int flag, const wxString &lbmp, const wxString &rbmp);
                ~CBtn();

            private:
                void OnPaint(wxPaintEvent &event);
                void OnMouseMotion(wxMouseEvent &event);
                void OnMouseLeftDown(wxMouseEvent &event);
                void OnMouseLeftUp(wxMouseEvent &event);
                void OnMouseLeaveWindow(wxMouseEvent &event);
                DECLARE_EVENT_TABLE()

            private:
                void Init();
                void RefreshBmp(int x, int y, int state);

            private:
                wxBitmap m_bmpBg;
                wxBitmap m_lbmp;
                wxBitmap m_rbmp;
                wxBitmap m_lCurBmp;
                wxBitmap m_rCurBmp;

                int m_lWidth;
                int m_rWidth;
                int m_height;
                int m_flag;
        } *m_zoom, *m_focus, *m_iris;
        class CBox : public wxWindow
        {
            public:
                CBox(wxWindow *parent, int flag, const wxString &lbmp, const wxString &rbmp);
                ~CBox();

            private:
                void OnPaint(wxPaintEvent &event);
                void OnMouseMotion(wxMouseEvent &event);
                void OnMouseLeftDown(wxMouseEvent &event);
                void OnMouseLeftUp(wxMouseEvent &event);
                void OnMouseLeaveWindow(wxMouseEvent &event);
                void OnComboBox(wxCommandEvent &event);
                void OnText(wxCommandEvent &event);
                DECLARE_EVENT_TABLE()

            private:
                void Init();
                void RefreshBmp(int x, int y, int state);
                void UpdatePramValue();

            private:
                wxComboBox *m_comboBox;
                wxBitmap m_lbmp;
                wxBitmap m_rbmp;
                wxBitmap m_lCurBmp;
                wxBitmap m_rCurBmp;

                int m_width;
                int m_height;
                int m_comboxWidth;
                int m_flag;
        } *m_preset, *m_aux;
        wxStaticText *m_ptzSpeedText;

    private:
        int m_nSpeed;
        int m_nPreset;
        int m_nAux;
};

#endif // __X_PTZCTL_H_
