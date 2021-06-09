#pragma once

#include "InitAuthManager.h"
#include "MeetingManager.h"
#include "vcr_common.h"

class CMeetingService :
	CMeetingServiceEvent,
	CInitSDKWorkFlowEvent,
	CAuthSDKWorkFlowEvent,
	CJoinMeetingFlowEvent
{
public:
	CMeetingService();
	virtual ~CMeetingService();

	void SetMeetingParameters();
	void Run(HINSTANCE hInstance);
	
	void onQuitApp();
	
	void onSDKInited(ZOOM_SDK_NAMESPACE::SDKError err);
	void onSDKAuthed(ZOOM_SDK_NAMESPACE::AuthResult ret);
	void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0);
private:
	bool isInited;
	bool isAuthed;

	std::wstring m_MeetingNumber;
	std::wstring m_MeetingPassword;
	std::wstring m_ScreenName;

	CInitAuthManager* m_initAuthManager;
	CMeetingManager* m_MeetingManager;
};

