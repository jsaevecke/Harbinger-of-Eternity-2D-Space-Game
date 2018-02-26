#include "CEntity.hpp"
#include "CComponent.hpp"
#include <iostream>
#include "CMovableComponent.hpp"


														ety::CEntity::CEntity						( const std::string& c_stdStringUniqueID )
															: m_c_stdStringUniqueID ( c_stdStringUniqueID )
														{
														}
														ety::CEntity::~CEntity						( void )
														{
															std::cout << "Destruktor called from Entity : " << m_c_stdStringUniqueID << std::endl;

															clear_Components();
														}

		const	bool									ety::CEntity::add_Component					( CComponent* const p_c_etyComponent )
				{
					const std::string c_stdStringFamilyID = p_c_etyComponent->get_FamilyID();

					std::map< std::string, boost::shared_ptr<CComponent> >::iterator itComponentByFamilyID = m_c_stdMapComponentByFamilyID.find( c_stdStringFamilyID );

					if( itComponentByFamilyID != m_c_stdMapComponentByFamilyID.end() )
					{
						std::cout << "Component with family ID : " << c_stdStringFamilyID << " already exists in " << m_c_stdStringUniqueID << std::endl;

						return false;
					}

					m_c_stdMapComponentByFamilyID[ c_stdStringFamilyID ] = boost::shared_ptr<CComponent>( p_c_etyComponent );

					p_c_etyComponent->set_Owner( this );

					std::cout << "Component with family ID : " << c_stdStringFamilyID << " succesfully added in " << m_c_stdStringUniqueID << std::endl;

					return true;
				}

		const	bool									ety::CEntity::remove_Component				( const std::string& c_stdStringFamilyID )
				{
					std::map< std::string, boost::shared_ptr<CComponent> >::iterator itComponentByFamilyID = m_c_stdMapComponentByFamilyID.find( c_stdStringFamilyID );

					if( itComponentByFamilyID != m_c_stdMapComponentByFamilyID.end() )
					{
						m_c_stdMapComponentByFamilyID.erase( itComponentByFamilyID );

						std::cout << "Component with family ID : " << c_stdStringFamilyID << " succesfully erased in " << m_c_stdStringUniqueID << std::endl;

						return true;
					}

					std::cout << "Component with family ID : " << c_stdStringFamilyID << " does not exist in " << m_c_stdStringUniqueID << std::endl;

					return false;
				}

				void									ety::CEntity::clear_Components				( void )
				{
					m_c_stdMapComponentByFamilyID.clear();

					std::cout << "All components removed from entity " << m_c_stdStringUniqueID << " !" << std::endl;
				}

		const	bool									ety::CEntity::has_Component					( const std::string& c_stdStringFamilyID )
				{
					if( m_c_stdMapComponentByFamilyID.find( c_stdStringFamilyID ) != m_c_stdMapComponentByFamilyID.end() )
					{
						return true;
					}

					return false;
				}

				void									ety::CEntity::register_ClassToLuabind		( ety::CLua* const p_c_etyLuaScript )
				{
				}

		const	std::string&							ety::CEntity::get_UniqueID					( void )
				{
					return m_c_stdStringUniqueID;
				}