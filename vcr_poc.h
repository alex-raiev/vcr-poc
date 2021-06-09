
// vcr_poc.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CvcrpocApp:
// See vcr_poc.cpp for the implementation of this class
//

class CvcrpocApp : public CWinApp
{
public:
	CvcrpocApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CvcrpocApp theApp;
