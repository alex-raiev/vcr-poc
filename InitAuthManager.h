#pragma once
#include "vcr_common.h"

class CInitAuthManager :
	public ZOOM_SDK_NAMESPACE::INetworkConnectionHandler,
	public ZOOM_SDK_NAMESPACE::IAuthServiceEvent
{
public:
	CInitAuthManager();
	virtual ~CInitAuthManager();

	void SetInitEvent(CInitSDKWorkFlowEvent* pInitSDKEvent);
	void SetServiceEvent(CMeetingServiceEvent* pServiceEvent);
	void SetAuthEvent(CAuthSDKWorkFlowEvent* pAuthUIEvent);
	
	void Init();
	void Auth();

	// INetworkConnectionHandler
	virtual void onProxyDetectComplete();
	virtual void onProxySettingNotification(ZOOM_SDK_NAMESPACE::IProxySettingHandler* handler);
	virtual void onSSLCertVerifyNotification(ZOOM_SDK_NAMESPACE::ISSLCertVerificationHandler* handler);
	// IAuthServiceEvent
	virtual void onAuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret);
	virtual void onLoginRet(ZOOM_SDK_NAMESPACE::LOGINSTATUS ret, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo) {};
	virtual void onLoginReturnWithReason(ZOOM_SDK_NAMESPACE::LOGINSTATUS ret, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo, ZOOM_SDK_NAMESPACE::LoginFailReason reason) {}
	virtual void onLogout() {};
	virtual void onZoomIdentityExpired() {};
	virtual void onZoomAuthIdentityExpired() {}

protected:
	ZOOM_SDK_NAMESPACE::SDKError InitSDK(ZOOM_SDK_NAMESPACE::InitParam& param);

private:
	CMeetingServiceEvent* m_pServiceEvent;
	CInitSDKWorkFlowEvent* m_pInitSDKEvent;
	CAuthSDKWorkFlowEvent* m_pAuthUIEvent;
	
	ZOOM_SDK_NAMESPACE::IAuthService* m_pAuthService;
};



