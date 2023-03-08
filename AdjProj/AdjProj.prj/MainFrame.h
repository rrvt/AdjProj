// MainFrame.h : interface of the MainFrame class


#pragma once
#include "CMainFrm.h"
#include "WinPos.h"


class MainFrame : public CMainFrm {

CMFCMenuBar   m_wndMenuBar;
CMFCToolBar   m_wndToolBar;
CMFCStatusBar m_wndStatusBar;

bool          isInitialized;
WinPos        winPos;                               // Position of Window

protected:                                          // create from serialization only

  MainFrame() noexcept;


  DECLARE_DYNCREATE(MainFrame)

public:                                             // Overrides

  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

  virtual ~MainFrame();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:                                          // Generated message map functions

  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  DECLARE_MESSAGE_MAP()
public:
  afx_msg void    OnMove(int x, int y);
  afx_msg void    OnSize(UINT nType, int cx, int cy);
  };


