// CH9326SetCfg.h : main header file for the CH9326SETCFG application
//

#if !defined(AFX_CH9326SETCFG_H__F4C88590_1665_47D6_B76F_8F681F92CB21__INCLUDED_)
#define AFX_CH9326SETCFG_H__F4C88590_1665_47D6_B76F_8F681F92CB21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCH9326SetCfgApp:
// See CH9326SetCfg.cpp for the implementation of this class
//

class CCH9326SetCfgApp : public CWinApp
{
public:
	CCH9326SetCfgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCH9326SetCfgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCH9326SetCfgApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CH9326SETCFG_H__F4C88590_1665_47D6_B76F_8F681F92CB21__INCLUDED_)
