#pragma once
#include "CItem.hpp"

namespace ety
{
	class CArmor : public CItem
	{
	private:

					float				m_fTotalArmor;
					float				m_fCurrentArmor;
					float				m_fReparationPerSecond;
					float				m_fDamageReductionPerShot;

	public:
										CArmor								( const std::string& strDirectory, const std::string& strItemname, ety::CRessourceManager* const p_c_etyCurrentRessourceManager );
										~CArmor								( void );

	virtual			void				update_Item							( const sf::Uint32& uiFrameTime );

		//Set-Methoden
					void				set_TotalArmor						( const float fTotalArmor );
					void				set_CurrentArmor					( const float fCurrentArmor );
					void				set_ReparationPerSecond				( const float fReparationPerSecond );
					void				set_DamageReductionPerShot			( const float fDamageReductionPerShot );


		//Get-Methoden
			const	float&				get_TotalArmor						( void );
			const	float&				get_CurrentArmor					( void );
			const	float&				get_ReparationPerSecond				( void );
			const	float&				get_DamageReductionPerShot			( void );
			const	std::string			get_SpecificInformation				( void );
	};
}


