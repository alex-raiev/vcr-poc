#include "pch.h"
#include "MeetingManager.h"

CMeetingManager::CMeetingManager()
{
	
}

CMeetingManager::~CMeetingManager()
{
	
}

void CMeetingManager::SetMeetingEvent(CJoinMeetingFlowEvent* pJoinMeetingFlowEvent)
{
	m_pJoinMeetingFlowEvent = pJoinMeetingFlowEvent;
}


bool CMeetingManager::IsMeetingServiceReady()
{
	if (NULL == m_pMeetingService)
	{
		m_pMeetingService = SDKInterfaceWrap::GetInst().GetMeetingService();
		if (NULL == m_pMeetingService)
			return false;
		SDKInterfaceWrap::GetInst().ListenMeetingServiceEvent(this);
	}

	return true;
}

void CMeetingManager::JoinMeeting(ZOOM_SDK_NAMESPACE::JoinParam& param)
{
	if (IsMeetingServiceReady())
	{
		ZOOMSDK::MeetingStatus status = m_pMeetingService->GetMeetingStatus();

		/*some configurations about the meeting should be called here*/
		if (m_pMeetingService->GetMeetingConfiguration())
		{
			m_pMeetingService->GetMeetingConfiguration()->SetSharingToolbarVisibility(true);
		}
		ZOOM_SDK_NAMESPACE::ISettingService* pSettingService = SDKInterfaceWrap::GetInst().GetSettingService();
		if (pSettingService)
		{
			ZOOM_SDK_NAMESPACE::IAudioSettingContext* pAudioContext = pSettingService->GetAudioSettings();
			if (pAudioContext)
			{
				pAudioContext->EnableAutoJoinAudio(true);
			}
		}
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pMeetingService->Join(param);
		
		//return err;
	}
}

void CMeetingManager::onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult)
{
	if (NULL != m_pJoinMeetingFlowEvent)
		m_pJoinMeetingFlowEvent->onMeetingStatusChanged(status, iResult);
}

void CMeetingManager::onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type)
{
	//todo
}

void CMeetingManager::onMeetingSecureKeyNotification(const char* key, int len, ZOOM_SDK_NAMESPACE::IMeetingExternalSecureKeyHandler* pHandler)
{
	//todo
}

void CMeetingManager::onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param)
{
	//todo
}
