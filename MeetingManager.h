#pragma once
#include <zoom_sdk_def.h>
#include "vcr_common.h"

class CMeetingManager:public ZOOM_SDK_NAMESPACE::IMeetingServiceEvent
{
public:
	CMeetingManager();
	virtual ~CMeetingManager();
	void SetMeetingEvent(CJoinMeetingFlowEvent* pJoinMeetingFlowEvent);

	bool IsMeetingServiceReady();
	void JoinMeeting(ZOOM_SDK_NAMESPACE::JoinParam& param);

	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0);
	virtual void onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type);
	virtual void onMeetingSecureKeyNotification(const char* key, int len, ZOOM_SDK_NAMESPACE::IMeetingExternalSecureKeyHandler* pHandler);
	virtual void onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param);

private:
	CJoinMeetingFlowEvent* m_pJoinMeetingFlowEvent;
	ZOOM_SDK_NAMESPACE::IMeetingService *m_pMeetingService;
};
