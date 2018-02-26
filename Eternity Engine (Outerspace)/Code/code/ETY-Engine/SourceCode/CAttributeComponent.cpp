#include "CAttributeComponent.hpp"
#include "CIniFile.hpp"

#include <SFML\System\Vector2.hpp>

#include <string>

//#########################################################################################################//
//#########################################################################################################//
//#########################################################################################################//

									ety::CAttributeComponent::CAttributeComponent							( const std::string& c_stdStringEntityKey )
									{
										m_c_etyAttributes.add_Attribute<unsigned int>	( "uiStructureStability"	, new unsigned int( 0 )						, true	);
										m_c_etyAttributes.add_Attribute<float>			( "fRotationSpeed"			, new float( 0.f )							, true	);
										m_c_etyAttributes.add_Attribute<float>			( "fMass"					, new float( 0.f )							, true	);
										m_c_etyAttributes.add_Attribute<std::string>	( "c_stdStringEntityType"	, new std::string( c_stdStringEntityKey )	, true	);
										m_c_etyAttributes.add_Attribute<sf::Vector2f>	( "c_sfVectorVelocity"		, new sf::Vector2f( 0.f, 0.f )				, true	);
									}
									ety::CAttributeComponent::~CAttributeComponent							( void )
									{
									}

const		std::string				ety::CAttributeComponent::get_FamilyID									( void )
			{
				return "AttributeComponent";
			}

//#########################################################################################################//
//#########################################################################################################//
//#########################################################################################################//

									ety::CSpaceshipAttributeComponent::CSpaceshipAttributeComponent			( const std::string& c_stdStringEntityKey )
										: CAttributeComponent( c_stdStringEntityKey )
									{
										ety::CIniFile c_etyIniFile;
										c_etyIniFile.set_IniFileDirectory( "Initialisation/Entities/Entities.ini" );

										m_c_etyAttributes.add_Attribute<float>				( "fShipMass"				, new float( c_etyIniFile.read_Float( c_stdStringEntityKey, "fMass", 0.f ) ), true	);

										m_c_etyAttributes.change_Attribute<unsigned int>	( "uiStructureStability"	, new unsigned int( c_etyIniFile.read_Integer( c_stdStringEntityKey, "uiStructureStability", 0 ) )	, true );
										m_c_etyAttributes.change_Attribute<float>			( "fMass"					, new float( c_etyIniFile.read_Float( c_stdStringEntityKey, "fMass", 0.f) )							, true );	
										m_c_etyAttributes.change_Attribute<float>			( "fRotationSpeed"			, new float( c_etyIniFile.read_Float( c_stdStringEntityKey, "fRotationSpeed", 0.f ) )				, true );
									}
									ety::CSpaceshipAttributeComponent::~CSpaceshipAttributeComponent		( void )
									{
									}

			void					ety::CSpaceshipAttributeComponent::update_Component						( const sf::Uint32& uiFrameTime )
			{
			}

const		std::string				ety::CSpaceshipAttributeComponent::get_ComponentID						( void )
			{
				return "SpaceshipAttributeComponent";
			}

//#########################################################################################################//
//#########################################################################################################//
//#########################################################################################################//

									ety::CEnvironmentAttributeComponent::CEnvironmentAttributeComponent		( const std::string& c_stdStringEntityKey )
										: CAttributeComponent( c_stdStringEntityKey )
									{
										ety::CIniFile c_etyIniFile;
										c_etyIniFile.set_IniFileDirectory( "Initialisation/Entities/Entities.ini" );

										m_c_etyAttributes.change_Attribute<unsigned int>	( "uiStructureStability"	, new unsigned int( c_etyIniFile.read_Integer( c_stdStringEntityKey, "uiStructureStability", 0 ) )	, true	);
										m_c_etyAttributes.change_Attribute<float>			( "fMass"					, new float( c_etyIniFile.read_Float( c_stdStringEntityKey, "fMass", 0 ) )							, true	);
									}
									ety::CEnvironmentAttributeComponent::~CEnvironmentAttributeComponent	( void )
									{
									}

			void					ety::CEnvironmentAttributeComponent::update_Component					( const sf::Uint32& uiFrameTime )
			{
			}

const		std::string				ety::CEnvironmentAttributeComponent::get_ComponentID					( void )
			{
				return "EnvironmentAttributeComponent";
			}

//#########################################################################################################//
//#########################################################################################################//
//#########################################################################################################//
