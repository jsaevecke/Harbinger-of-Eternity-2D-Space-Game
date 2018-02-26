#include "CRenderComponentsystem.hpp"
#include "CRenderComponent.hpp"
#include "CCameraComponent.hpp"
#include "CItemModulesComponent.hpp"
#include "CEntitymanager.hpp"

		bool	sort_EntityPredicate									( boost::weak_ptr<ety::CEntity> p_c_etyEntity1, boost::weak_ptr<ety::CEntity> p_c_etyEntity2 )
		{
			return p_c_etyEntity1.lock()->get_Component<ety::CRenderComponent>("RenderComponent")->get_Layer() < p_c_etyEntity2.lock()->get_Component<ety::CRenderComponent>("RenderComponent")->get_Layer();
		}

				ety::CRenderComponentsystem::CRenderComponentsystem		( ety::CEntitymanager* const p_c_etyEntitymanager )
					: CComponentsystem( p_c_etyEntitymanager )
				{
				}
				ety::CRenderComponentsystem::~CRenderComponentsystem	( void )
				{
				}

		void	ety::CRenderComponentsystem::update_Components			( const sf::Uint32& uiFrameTime )
		{
			std::vector< boost::weak_ptr<ety::CEntity> > c_stdVectorCameraEntities			= mp_c_etyEntitymanager->get_Entities( "CameraComponent" );
			std::vector< boost::weak_ptr<ety::CEntity> > c_stdVectorItemModulesEntities		= mp_c_etyEntitymanager->get_Entities( "ItemModulesComponent" );

			ety::CCenteredCameraComponent* p_c_etyCenteredCameraComponent = NULL;

			if( c_stdVectorCameraEntities.empty() == false )
			{
				p_c_etyCenteredCameraComponent = c_stdVectorCameraEntities[0].lock()->get_Component<CCenteredCameraComponent>( "CameraComponent" );
			}

			if( p_c_etyCenteredCameraComponent != NULL )
			{
				p_c_etyCenteredCameraComponent->update_Component( uiFrameTime );
			}

			for( std::vector< boost::weak_ptr<ety::CEntity> >::iterator itEntity = c_stdVectorItemModulesEntities.begin(); itEntity != c_stdVectorItemModulesEntities.end(); ++itEntity )
			{
				ety::CItemModulesComponent* p_c_etyItemModulesComponent = itEntity->lock()->get_Component<ety::CItemModulesComponent>( "ItemModulesComponent" );

				if( p_c_etyItemModulesComponent != NULL )
				{
					p_c_etyItemModulesComponent->update_Component( uiFrameTime );
				}
			}
		}
		void	ety::CRenderComponentsystem::render_Components			( sf::RenderTexture* const p_c_sfRenderTextureGameScene )
		{
			std::vector< boost::weak_ptr<ety::CEntity> > c_stdVectorLayerEntities	= mp_c_etyEntitymanager->get_Entities( "RenderComponent" );
			std::vector< boost::weak_ptr<ety::CEntity> > c_stdVectorCameraEntities	= mp_c_etyEntitymanager->get_Entities( "CameraComponent" );

			std::vector< boost::weak_ptr<ety::CEntity> >::iterator itEntity = c_stdVectorLayerEntities.begin();

			std::sort( c_stdVectorLayerEntities.begin(), c_stdVectorLayerEntities.end(), sort_EntityPredicate );

			ety::CCenteredCameraComponent* p_c_etyCenteredCameraComponent = NULL;

			if( c_stdVectorCameraEntities.empty() == false )
			{
				p_c_etyCenteredCameraComponent = c_stdVectorCameraEntities[0].lock()->get_Component<CCenteredCameraComponent>( "CameraComponent" );
			}

			if( c_stdVectorLayerEntities.empty() == false && c_stdVectorLayerEntities.begin()->lock()->get_UniqueID() == "StaticBackground" )
			{
				ety::CStaticRenderComponent* p_c_etyRenderComponent = c_stdVectorLayerEntities.begin()->lock()->get_Component<ety::CStaticRenderComponent>( "RenderComponent" );
			
				if( p_c_etyRenderComponent != NULL )
				{
					p_c_etyRenderComponent->render_Component( p_c_sfRenderTextureGameScene );
				}

				itEntity++;
			}

			if( p_c_etyCenteredCameraComponent != NULL )
			{
				p_c_sfRenderTextureGameScene->setView( p_c_etyCenteredCameraComponent->get_View() );
			}

			for( itEntity; itEntity != c_stdVectorLayerEntities.end(); itEntity++ )
			{
				ety::CRenderComponent*		p_c_etyRenderComponent		= itEntity->lock()->get_Component<ety::CRenderComponent>( "RenderComponent" );
				ety::CItemModulesComponent* p_c_etyItemModulesComponent = itEntity->lock()->get_Component<ety::CItemModulesComponent>( "ItemModulesComponent" );

				if( p_c_etyRenderComponent != NULL )
				{
					if( p_c_etyCenteredCameraComponent->get_IntersectionRect().intersects( p_c_etyRenderComponent->get_Appearance()->getGlobalBounds() ) == true )
					{
						p_c_etyRenderComponent->render_Component( p_c_sfRenderTextureGameScene );

						if( p_c_etyItemModulesComponent != NULL )
						{
							p_c_etyItemModulesComponent->render_Component( p_c_sfRenderTextureGameScene );
						}
					}
				}
			}
		}
