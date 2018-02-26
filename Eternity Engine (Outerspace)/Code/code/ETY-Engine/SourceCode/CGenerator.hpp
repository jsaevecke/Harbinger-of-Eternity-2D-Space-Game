#pragma once
#include "CItem.hpp"

namespace ety
{
	class CGenerator : public CItem
	{
	private:

					float				m_fCurrentEnergy;
					float				m_fEnergyCapacity;
					float				m_fRechargedEnergyPerSecond;

	public:
										CGenerator							( const std::string& strDirectory, const std::string& strItemname, ety::CRessourceManager* const p_c_etyCurrentRessourceManager );
										~CGenerator							( void );

	virtual			void				update_Item							( const sf::Uint32& uiFrameTime );

		//Set-Methoden
					void				set_CurrentEnergy					( const float& fCurrentEnergy );
					void				set_EnergyCapacity					( const float& fEnergyCapacity );
					void				set_RechargedEnergyPerSecond		( const float& fRechargedEnergyPerSecond );


		//Get-Methoden
			const	float&				get_CurrentEnergy					( void );
			const	float&				get_EnergyCapacity					( void );
			const	float&				get_RechargedEnergyPerSecond		( void );
			const	std::string			get_SpecificInformation				( void );
	};
}


