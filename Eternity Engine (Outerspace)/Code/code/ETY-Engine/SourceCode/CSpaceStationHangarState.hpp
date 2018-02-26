#pragma once
#include "CDialogGameState.hpp"
#include "CItemManagement.hpp"
#include "CItem.hpp"
#include "CModule.hpp"

namespace ety
{
	class CRessourceManager;
	class CShop;

	class CSpaceStationHangarState : public CDialogGameState
	{
	private:
				bool													m_bShopOpen;
				ety::CItemManagement									m_c_etyItemManagement;
				CShop*													mp_c_etyCShop;

	protected:

	public:
																		CSpaceStationHangarState			( const std::string& strStateName );
																		~CSpaceStationHangarState			( void );

				void													on_Enter							( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );
				void													on_Exit								( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );

				void													init_GameState						( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );

				void													update_GameState					( const sf::Uint32& uiFrameTime );

				void													render_GameState					( sf::RenderTexture* const p_c_sfRenderTextureGameScene );

		const	ety::GameStateRunning::en_etyGameStateRunning			handle_GameStateEvents				( const sf::Event& sfEventLastEvent  );

		static  ety::GameStateRunning::en_etyGameStateRunning			event_closeShop						( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning			event_exitHangar					( int iAmount, ... );
		static  ety::GameStateRunning::en_etyGameStateRunning			event_enterIngame					( int iAmount, ... );
		static  ety::GameStateRunning::en_etyGameStateRunning			event_showButtonTooltip				( int iAmount, ... );
		static  ety::GameStateRunning::en_etyGameStateRunning			event_openShop						( int iAmount, ... );

				void													set_ShopVisiblity					( bool bShopVisible );
	};
}

