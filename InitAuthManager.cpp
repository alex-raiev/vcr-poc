#include "pch.h"
#include "InitAuthManager.h"

#include <future>

#include "resource.h"

CInitAuthManager::CInitAuthManager()
{
	m_pServiceEvent = NULL;
	m_pInitSDKEvent = NULL;
	m_pAuthUIEvent = NULL;
}

CInitAuthManager::~CInitAuthManager()
{
	m_pServiceEvent = NULL;
	m_pInitSDKEvent = NULL;
	m_pAuthUIEvent = NULL;
}

void CInitAuthManager::SetServiceEvent(CMeetingServiceEvent* pServiceEvent)
{
	m_pServiceEvent = pServiceEvent;
}

void CInitAuthManager::SetInitEvent(CInitSDKWorkFlowEvent* pInitSDKEvent)
{
	m_pInitSDKEvent = pInitSDKEvent;
}

void CInitAuthManager::SetAuthEvent(CAuthSDKWorkFlowEvent* pAuthUIEvent)
{
	m_pAuthUIEvent = pAuthUIEvent;
}

void CInitAuthManager::Init()
{
	ZOOM_SDK_NAMESPACE::InitParam initParam;
	initParam.strWebDomain = L"https://zoom.us";
	initParam.strSupportUrl = L"https://zoom.us";
	initParam.emLanguageID = ZOOM_SDK_NAMESPACE::LANGUAGE_English;
	initParam.uiWindowIconSmallID = IDR_MAINFRAME;
	initParam.uiWindowIconBigID = IDR_MAINFRAME;
	initParam.hResInstance = GetModuleHandle(NULL);
	initParam.enableLogByDefault = true;
	initParam.enableGenerateDump = true;

	//bool customiezed_ui_mode = false;
	//if (m_chkCustomizedUI)
	//	customiezed_ui_mode = m_chkCustomizedUI->GetCheck();
	//if (customiezed_ui_mode)
	//	initParam.obConfigOpts.optionalFeatures = ENABLE_CUSTOMIZED_UI_FLAG;

	if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS != InitSDK(initParam))
	{
		//if (m_mainFrame)
		//	m_mainFrame->ShowErrorMessage(L"init sdk failed");
		
	}
	else
	{
		::MessageBox(NULL, L"wait - 0", L"info", MB_OK);

		//m_mainFrame->SwitchToWaitingPage(L"waiting proxy detecting...", true);
	}	
}

ZOOM_SDK_NAMESPACE::SDKError CInitAuthManager::InitSDK(ZOOM_SDK_NAMESPACE::InitParam& param)
{
	ZOOM_SDK_NAMESPACE::SDKError err = SDKInterfaceWrap::GetInst().Init(param);

	if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS != err)
	{
		if (m_pInitSDKEvent)
		{
			m_pInitSDKEvent->onSDKInited(err);
		}
	}
	else
	{
		if (SDKInterfaceWrap::GetInst().GetNetworkConnectionHelper())
		{
			SDKInterfaceWrap::GetInst().GetNetworkConnectionHelper()->RegisterNetworkConnectionHandler(this);
		}
	}

	return err;
}

void CInitAuthManager::Auth()
{
	if (NULL == m_pAuthService)
	{
		m_pAuthService = SDKInterfaceWrap::GetInst().GetAuthService();
		SDKInterfaceWrap::GetInst().ListenAuthServiceEvent(this);
	}
	
	if (m_pAuthService)
	{
		ZOOM_SDK_NAMESPACE::AuthParam authParam;
		authParam.appKey = L"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"; // anonimized for email
		authParam.appSecret = L"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"; // anonimized for email
		
		if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS != m_pAuthService->SDKAuth(authParam))
		{
			//if (m_mainFrame)
			//	m_mainFrame->ShowErrorMessage(L"auth sdk failed");
		}
		else
		{
			//m_mainFrame->SwitchToWaitingPage(L"waiting auth result...", true);
		}
	}
}

void CInitAuthManager::onProxySettingNotification(ZOOM_SDK_NAMESPACE::IProxySettingHandler* handler)
{
	//todo
}
void CInitAuthManager::onSSLCertVerifyNotification(ZOOM_SDK_NAMESPACE::ISSLCertVerificationHandler* handler)
{
	//todo
}

void CInitAuthManager::onProxyDetectComplete()
{
	//static bool doOnce = true;
	if (m_pInitSDKEvent /*&& doOnce*/)
	{
		//doOnce = false;
		m_pInitSDKEvent->onSDKInited(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS);
	}
}

void CInitAuthManager::onAuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret)
{
	if (m_pAuthUIEvent)
	{
		m_pAuthUIEvent->onSDKAuthed(ret);
	}
}
