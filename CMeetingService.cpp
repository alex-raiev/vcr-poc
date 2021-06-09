#include "pch.h"
#include "MeetingService.h"

CMeetingService::CMeetingService()
{
	m_MeetingManager = NULL;

	SetMeetingParameters();
}

CMeetingService::~CMeetingService()
{
	m_MeetingManager = NULL;
}

void CMeetingService::SetMeetingParameters()
{
	//TODO: Get this paremeters from the request to DataServer REST API
	m_MeetingNumber = L"1234567890";
	m_MeetingPassword = L"0000000";
	m_ScreenName = L"Video Classroom #1";
}

void CMeetingService::Run(HINSTANCE hInstance)
{
	m_initAuthManager = new CInitAuthManager();
	if(!m_initAuthManager)
	{
		return;
	}

	m_MeetingManager = new CMeetingManager();
	m_MeetingManager->SetMeetingEvent(this);
	
	m_initAuthManager->SetInitEvent(this);
	m_initAuthManager->SetAuthEvent(this);
	m_initAuthManager->SetServiceEvent(this);

	m_initAuthManager->Init();

	if(isInited)
	{
		m_initAuthManager->Auth();
	}
	else
	{
		return;
	}
}

void CMeetingService::onQuitApp()
{
	
}

void CMeetingService::onSDKInited(ZOOM_SDK_NAMESPACE::SDKError err)
{
	if (ZOOM_SDK_NAMESPACE::AUTHRET_SUCCESS != err)
	{
		isInited = false;
	}
	else
	{
		isInited = true;
	}
	
	//if (m_mainFrame)
	//{
	//	m_mainFrame->SwitchToWaitingPage(NULL, false);
	//	if (ZOOM_SDK_NAMESPACE::AUTHRET_SUCCESS != ret)
	//	{
	//		m_mainFrame->ShowErrorMessage(CSDKMessInfo::GetInst().GetErrorMessInfo());
	//	}
	//	else if (m_mainFrame->GetAppEvent())
	//	{
	//		m_mainFrame->GetAppEvent()->onSwitchToLoginUI(SwitchToLoginUIType_AUTHDONE);
	//	}
	//}

}

void CMeetingService::onSDKAuthed(ZOOM_SDK_NAMESPACE::AuthResult ret)
{
	if (ZOOM_SDK_NAMESPACE::AUTHRET_SUCCESS != ret)
	{
		isAuthed = false;
	}
	else
	{
		isAuthed = true;
	}
	
	//m_mainFrame->SwitchToWaitingPage(NULL, false);
	//if (ZOOM_SDK_NAMESPACE::AUTHRET_SUCCESS != ret)
	//{
	//	m_mainFrame->ShowErrorMessage(CSDKMessInfo::GetInst().GetErrorMessInfo());
	//}
	//else if (m_mainFrame->GetAppEvent())
	//{
	//	m_mainFrame->GetAppEvent()->onSwitchToLoginUI(SwitchToLoginUIType_AUTHDONE);
	//}
	
	if (isAuthed)
	{
		ZOOM_SDK_NAMESPACE::tagJoinParam joinParam;
		joinParam.userType = ZOOM_SDK_NAMESPACE::SDK_UT_WITHOUT_LOGIN;
		ZOOM_SDK_NAMESPACE::JoinParam4WithoutLogin& withoutloginParam = joinParam.param.withoutloginuserJoin;

		withoutloginParam.meetingNumber = _wtoi64(m_MeetingNumber.c_str());
		withoutloginParam.vanityID = NULL;
		withoutloginParam.userName = m_ScreenName.c_str();
		withoutloginParam.psw = m_MeetingPassword.c_str();
		withoutloginParam.hDirectShareAppWnd = NULL;

		withoutloginParam.participantId = NULL;
		withoutloginParam.webinarToken = NULL;
		withoutloginParam.isDirectShareDesktop = false;
		withoutloginParam.isVideoOff = false;
		withoutloginParam.isAudioOff = false;

		m_MeetingManager->JoinMeeting(joinParam);
	}
}

void CMeetingService::onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult)
{
	
}