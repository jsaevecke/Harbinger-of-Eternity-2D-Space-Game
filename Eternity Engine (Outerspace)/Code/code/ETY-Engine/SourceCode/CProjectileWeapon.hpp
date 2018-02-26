#pragma once

#include "CWeapon.hpp"

namespace ety
{
	class CProjectileWeapon : public CWeapon
	{
	private:
			
				float				m_fReloadTime;
				unsigned int		m_uiClipSize;
		

	public:
									CProjectileWeapon			( const std::string& strDirectory, const std::string& strItemname, ety::CRessourceManager* const p_c_etyCurrentRessourceManager );
									~CProjectileWeapon			( void );

		virtual	void				update_Item					( const sf::Uint32& uiFrameTime );

		//Set-Methoden	
				void				set_ReloadTime				( const float fReloadTime );
				void				set_ClipSize				( const unsigned int uiClipSize );

		//Get-Methoden
		const	float&				get_ReloadTime				( void );
		const	unsigned int&		get_ClipSize				( void );
		const	std::string			get_SpecificInformation		( void );
	};
}


