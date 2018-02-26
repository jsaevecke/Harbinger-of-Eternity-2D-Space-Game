#include "CArmor.hpp"

						ety::CArmor::CArmor									( const std::string& strDirectory, const std::string& strItemname, ety::CRessourceManager* const p_c_etyCurrentRessourceManager )
							: CItem( strDirectory, strItemname, p_c_etyCurrentRessourceManager )
{
	m_en_etyModuleType = ety::ModuleType::enARMOR;
}
						ety::CArmor::~CArmor								( void )
{
}

		void			ety::CArmor::update_Item							( const sf::Uint32& uiFrameTime )
		{
		}

//Get-Methoden
const	float&			ety::CArmor::get_TotalArmor							( void )
{
	return m_fTotalArmor;
}
const	float&			ety::CArmor::get_CurrentArmor						( void )
{
	return m_fCurrentArmor;
}
const	float&			ety::CArmor::get_ReparationPerSecond				( void )
{
	return m_fReparationPerSecond;
}
const	float&			ety::CArmor::get_DamageReductionPerShot				( void )
{
	return m_fDamageReductionPerShot;
}
const	std::string		ety::CArmor::get_SpecificInformation				( void )
{
	std::stringstream ssStream;
	//String noch �ndern
	std::string strInformation = m_strName + "\n\n\nKlasse: ";
	ssStream << m_uiClass;
	strInformation += ssStream.str() + "\n\nMasse: ";
	ssStream.str("");
	ssStream << m_fMass;
	strInformation += ssStream.str() + " ME\n\nPrice: ";
	ssStream.str("");
	ssStream << m_fPrice;
	strInformation += ssStream.str() + "$\n\nTotal Armor: ";
	ssStream.str("");
	ssStream << m_fTotalArmor;
	strInformation += ssStream.str() + "\n\nDmgRedctn.: ";
	ssStream.str("");
	ssStream << m_fDamageReductionPerShot;
	strInformation += ssStream.str();
	ssStream.str("");

	return strInformation;
}