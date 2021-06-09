#pragma once
#include "sdk_util.h"

class CMeetingServiceEvent
{
public:
	virtual void onQuitApp() = 0;
};

class CInitSDKWorkFlowEvent
{
public:
	virtual void onSDKInited(ZOOM_SDK_NAMESPACE::SDKError err) = 0;
};

class CAuthSDKWorkFlowEvent
{
public:
	virtual void onSDKAuthed(ZOOM_SDK_NAMESPACE::AuthResult ret) = 0;
};

class CJoinMeetingFlowEvent
{
public:
	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0) = 0;
	//virtual void onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type) = 0;
	//virtual void onMeetingSecureKeyNotification(const char* key, int len, ZOOM_SDK_NAMESPACE::IMeetingExternalSecureKeyHandler* pHandler) = 0;
	//virtual void onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param) = 0;

};
