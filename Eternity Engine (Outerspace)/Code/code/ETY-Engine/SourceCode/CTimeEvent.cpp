#include "CTimeEvent.hpp"


															ety::CTimeEvent::CTimeEvent			(void)
															:m_fTimeBuffer						(0.f)
{
}


															ety::CTimeEvent::~CTimeEvent		(void)
{
}



															ety::CTimeEvent::CTimeEvent			(enum TimeEventType::en_etyTimeEventType en_etyTimeEventType, float fTime, bool bActive, 
																								CTrigger* p_c_etyTriggerParent)
															:m_en_etyTimeEventType				(en_etyTimeEventType)
															,m_fTime							(fTime)
															,m_fTimeBuffer						(0.f)
{
	m_bActive					=	bActive;
	mp_c_etyTriggerParent		=	p_c_etyTriggerParent;
	m_en_etyTriggerEventType	=	TriggerEventType::enTIMEEVENT;
}


bool														ety::CTimeEvent::update_Event		( const sf::Uint32& uiFrameTime )
{
	m_fTimeBuffer	+=	uiFrameTime/1000.f;

	if(m_fTimeBuffer >= m_fTime)
	{
		if(m_en_etyTimeEventType == TimeEventType::enELAPSEDTIME)
		{
			m_bActive = false;

			return true;
		}
		else if(m_en_etyTimeEventType == TimeEventType::enPERIODIC)
		{
			m_fTimeBuffer = 0;

			return true;
		}
	}

	return false;
}


const	float&												ety::CTimeEvent::get_Time			(void)
{
	return m_fTime;
}
const	enum ety::TimeEventType::en_etyTimeEventType		ety::CTimeEvent::get_TimeEventType	(void)
{
	return m_en_etyTimeEventType;
}