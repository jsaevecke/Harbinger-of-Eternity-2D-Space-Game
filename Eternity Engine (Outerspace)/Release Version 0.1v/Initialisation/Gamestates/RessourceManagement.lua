--|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
--|||																																																								|||
--|||	|||||> Verf?gbare Methoden f?r das Objekt -> "c_etyRessourceManager"																																						|||
--|||																																																								|||
--|||	 0: void				add_Directory	( string strDirectory, enum en_etyRessourceType );																																				|||
--|||    1:	sfFont				get_Font		( string strFontname )																																											|||
--|||	 2:	sfTexture			get_Texture		( string strTexturename );																																																						|||
--|||	 3:	sfMusic*			get_Music		( string strMusicname );																																																						|||
--|||	 4:	sfSound*			get_Sound		( string strSoundname );																																																						|||
--|||	 5: sf:SoundBuffer		get_Soundbuffer	( string strSoundbuffername );																																																							|||
--|||																																																								|||
--|||	|||||> Verf?gbare Enums f?r die Methoden des Objektes.																																										|||
--|||	||> RessourceType	= { enTEXTURE	=0	, enFONT	=1	, enSOUND	=2	, enMUSIC	=3	, enSOUNDBUFFER	=4	, enERROR	=5 } 																								|||
--|||																																																								|||
--|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

--	||	?berpr?fung, ob die Ressourceverwaltung erfolgreich
--		an den virtuellen Stack von Lua ?bergeben wurde.  ||

if c_etyRessourceManager ~= nil then

	c_etyRessourceManager:add_Directory	( "Media/Textures/Dialog/Backgrounds/"			,	0	);
	c_etyRessourceManager:add_Directory	( "Media/Textures/Dialog/Buttons/"				,	0	);
	c_etyRessourceManager:add_Directory	( "Media/Textures/Dialog/Checkboxes/"			,	0	);
	c_etyRessourceManager:add_Directory	( "Media/Textures/Dialog/ComboBoxes/"			,	0	);
	c_etyRessourceManager:add_Directory	( "Media/Textures/Dialog/EditControls/"			,	0	);
	c_etyRessourceManager:add_Directory	( "Media/Textures/Dialog/PictureControls/"		,	0	);
	c_etyRessourceManager:add_Directory	( "Media/Textures/Dialog/Progressbar/"			,	0	);
	c_etyRessourceManager:add_Directory	( "Media/Textures/Dialog/Scrollbars/"			,	0	);
	c_etyRessourceManager:add_Directory	( "Media/Textures/Dialog/SlideControls/"		,	0	);
	c_etyRessourceManager:add_Directory	( "Media/Textures/Effects/Shots/"				,	0	);
	c_etyRessourceManager:add_Directory	( "Media/Textures/Cursor/"						,	0	);
	c_etyRessourceManager:add_Directory	( "Media/Textures/Entities/Planets/"			,	0	);
	c_etyRessourceManager:add_Directory	( "Media/Textures/Entities/Spaceships/"			,	0	);
	c_etyRessourceManager:add_Directory	( "Media/Textures/Entities/Meteors/"			,	0	);
	c_etyRessourceManager:add_Directory	( "Media/Textures/Entities/Weapons/"			,	0	);
	
	c_etyRessourceManager:add_Directory	( "Media/Fonts/"								,	1	);
	
	c_etyRessourceManager:add_Directory	( "Media/Audio/Music/"							,	3	);
	
	c_etyRessourceManager:add_Directory	( "Media/Audio/Sounds/"							,	4	);

end

--|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
--|||																																																								|||
--|||	|||||> Verf?gbare Methoden f?r das Objekt -> "c_etyFilemanager"																																								|||
--|||																																																								|||
--|||	 0: void add_FileToLoad				( string strGamestatename, enum en_etyFileToLoadType, string strFileToLoad, string strDirectoryKey );																					|||
--|||	 1: void add_StandardSoundToLoad	( string strGamestatename, enum en_etyDialogitemType, enum en_etySoundType, string strFileToLoad, string strDirectoryKey, bool bLoadSound );											|||
--|||																																																								|||
--|||	|||||> Verf?gbare Enums f?r die Methoden des Objektes.																																										|||
--|||	||> RessourceType	= { enTEXTURE	=0	, enFONT		=1	, enSOUND		=2	, enMUSIC		=3	, enSOUNDBUFFER	=4	, enERROR			=5 } 																			|||
--|||	||> DialogitemTypes = { enBUTTON	=0	, enCHECKBOX	=1	, enCOMBOBOX	=2	, enEDITCONTROL	=3	, enLABEL		=4	, enPICTURECONTROL	=5	, enSCROLLBAR =6	, enSLIDECONTROL =7	, enALL		=8	, enERROR = 9 }		|||
--|||	||> Soundtypes      = { enCLICK		=0	, enDOUBLECLICK	=1	, enHOVER		=2	, enWRITEOUT	=3	, enSCROLL		=4	, enAPPEAR			=5	, enDISAPPEAR =6	, enINPUT		 =7	, enERROR	=8 }					|||
--|||																																																								|||
--|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

--	|| ?berpr?fung, ob die Dateiverwaltung erfolgreich an den virtuellen Stack von Lua ?bergeben wurde. ||

if c_etyFilemanager ~= nil then

	--|||||||||||||||||||||||||||||||||||||||||||| PLAYSTATE RESSOURCES

	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "Crosshair.png"						, "Cursor"				);
	
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "Alpha-Centauri-System.jpg"			, "Backgrounds"			);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "Beta-Centauri-System.jpg"			, "Backgrounds"			);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "Minimap.jpg"							, "Backgrounds"			);
	
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "planet1.png"							, "Planets"				);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "planet2.png"							, "Planets"				);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "planet3.png"							, "Planets"				);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "planet4.png"							, "Planets"				);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "planet5.png"							, "Planets"				);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "planet6.png"							, "Planets"				);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "planet7.png"							, "Planets"				);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "planet10.png"						, "Planets"				);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "planet11.png"						, "Planets"				);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "planet12.png"						, "Planets"				);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "planet13.png"						, "Planets"				);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "planet14.png"						, "Planets"				);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "planet15.png"						, "Planets"				);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "planet16.png"						, "Planets"				);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "planet17.png"						, "Planets"				);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "planet18.png"						, "Planets"				);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "planet19.png"						, "Planets"				);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "planet20.png"						, "Planets"				);
	
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "AlienCarrier.png"					, "Spaceships"			);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "AlienCruiser.png"					, "Spaceships"			);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "AlienFighter.png"					, "Spaceships"			);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "AlienScorpion.png"					, "Spaceships"			);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "HumanCarrier.png"					, "Spaceships"			);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "HumanCruiser.png"					, "Spaceships"			);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "HumanFighter.png"					, "Spaceships"			);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "HumanPhalanx.png"					, "Spaceships"			);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "HumanSpacestation.png"				, "Spaceships"			);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "HumanDrone.png"						, "Spaceships"			);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "HumanDrone2.png"						, "Spaceships"			);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "Waypoint.png"						, "Spaceships"			);
	
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "MeteoriteBig.png"					, "Meteors"				);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "MeteoriteMedium.png"					, "Meteors"				);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "MeteoriteSmall.png"					, "Meteors"				);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "MeteoriteMephitic.png"				, "Meteors"				);
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "MeteoriteMephiticPustules.png"		, "Meteors"				);
	
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "Turret.png"							, "Weapons"				);
	
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "TinyRapid.png"						, "Shots"				);
	
	--||||||||||||||||||||||||||||||||||||||||||||> LOADINGSTATE RESSOURCES

	c_etyFilemanager:add_FileToLoad				( "LoadingState"			, 0		, "LoadingScreen.jpg"					, "Backgrounds"			);
	c_etyFilemanager:add_FileToLoad				( "LoadingState"			, 0		, "Cursor.png"							, "Cursor"				);
	c_etyFilemanager:add_FileToLoad				( "LoadingState"			, 0		, "IronProgressbar.png"					, "Progressbar"			);

	c_etyFilemanager:add_FileToLoad				( "LoadingState"			, 1		, "Standard.ttf"						, "Fonts"				);

	--||||||||||||||||||||||||||||||||||||||||||||> INTROSTATE RESSOURCES

	--||||||||||||||||||||||||||||||||||||||||||||> MENUSTATE RESSOURCES
	c_etyFilemanager:add_FileToLoad				( "IngameState"				, 0		, "ShipStatus.png"						, "Backgrounds"			);
	
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "ShopBackground.png"					, "Backgrounds"			);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "TooltipBackground.png"				, "Backgrounds"			);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "HUD-Backgrounds.png"					, "Backgrounds"			);
	
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "OptionenBackgroundAlpha.png"			, "Backgrounds"			);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "MainMenuBackground.jpg"				, "Backgrounds"			);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "MainMenuDialog.png"					, "Backgrounds"			);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "ProfileBackgroundAlpha.png"			, "Backgrounds"			);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "ExitMenuSet.png"						, "Backgrounds"			);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "transparentBackground.png"			, "Backgrounds"			);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "BarBackground.png"					, "Backgrounds"			);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "BarPad.png"							, "Backgrounds"			);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "HangarBackground.png"				, "Backgrounds"			);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "RepositoryShopBackground.png"		, "Backgrounds"			);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "MissionMenuBackground.png"			, "Backgrounds"			);
	
	
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "ShopButtonSet.png"					, "Buttons"				);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "HUD-Button.png"						, "Buttons"				);
	
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "PadStartButton.png"					, "Buttons"				);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "PadOptionsButton.png"				, "Buttons"				);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "PadProfilesButton.png"				, "Buttons"				);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "PadCreditsButton.png"				, "Buttons"				);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "PadExitButton.png"					, "Buttons"				);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "Zur�ck.png"							, "Buttons"				);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "Diskette.png"						, "Buttons"				);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "ProfileButtons.png"					, "Buttons"				);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "Hangar.png"							, "Buttons"				);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "Pad.png"								, "Buttons"				);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "ProfileDisplay.png"					, "Buttons"				);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "Missionen.png"						, "Buttons"				);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "PadBackButton.png"					, "Buttons"				);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "PadHangarButton.png"					, "Buttons"				);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "PadShopButton.png"					, "Buttons"				);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "PadMissionButton.png"				, "Buttons"				);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "PadLogbookButton.png"				, "Buttons"				);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "HangarSaalButton.png"				, "Buttons"				);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "HangarShopButton.png"				, "Buttons"				);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "HangarIngameButton.png"				, "Buttons"				);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "RSBackButton.png"					, "Buttons"				);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "RSSwitchButton.png"					, "Buttons"				);
	
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "MenuCheckbox.png"					, "Checkboxes"			);
	
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "StandardComboBoxSetAlphaSCRBTest.png", "ComboBoxes"			);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "TestListBox.png"						, "ComboBoxes"			);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "HangarListBox.png"					, "ComboBoxes"			);
	
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "ProfileStandardEC.png"				, "EditControls"		);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "ProfileBildschirmButton.png"			, "EditControls"		);
	
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "PlayerShipStatus.png"				, "PictureControls"		);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "PlayerShieldStatus.png"				, "PictureControls"		);
	
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "ReflektionErsterButtonLicht.png"		, "PictureControls"		);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "ReflektionZweiterButtonLicht.png"	, "PictureControls"		);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "ReflektionDritterButtonLicht.png"	, "PictureControls"		);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "ReflektionVierterButtonLicht.png"	, "PictureControls"		);
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "ReflektionFuenfterButtonLicht.png"	, "PictureControls"		);
	
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "TestScrollbar2.png"					, "Scrollbars"			);
	
	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 0		, "SlideControl.png"					, "SlideControl"		);

	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 1		,  "Standard.ttf"						, "Fonts"				);

	c_etyFilemanager:add_FileToLoad				( "MenuState"				, 3		,  "Menu.wav"							, "Music"				);

	c_etyFilemanager:add_StandardSoundToLoad	( "MenuState"				, 0		, 2										, "ButtonHoverWave.wav"			, "Sounds"		,	true		);
	c_etyFilemanager:add_StandardSoundToLoad	( "MenuState"				, 0		, 0										, "ButtonClickedWave.wav"		, "Sounds"		,	true		);
	c_etyFilemanager:add_StandardSoundToLoad	( "MenuState"				, 3		, 7										, "EditControlInputWave.wav"	, "Sounds"		,	true		);

	--||||||||||||||||||||||||||||||||||||||||||||> PROFILESTATE RESSOURCES

	c_etyFilemanager:add_StandardSoundToLoad	( "ProfileState"			, 0		, 2										, "ButtonHoverWave.wav"			, "Sounds"		,	false		);
	c_etyFilemanager:add_StandardSoundToLoad	( "ProfileState"			, 0		, 0										, "ButtonClickedWave.wav"		, "Sounds"		,	false		);
	c_etyFilemanager:add_StandardSoundToLoad	( "ProfileState"			, 3		, 7										, "EditControlInputWave.wav"	, "Sounds"		,	false		);

	--||||||||||||||||||||||||||||||||||||||||||||> OPTIONSTATE RESSOURCES

	c_etyFilemanager:add_StandardSoundToLoad	( "OptionState"				, 0		, 2										, "ButtonHoverWave.wav"			, "Sounds"		,	false		);
	c_etyFilemanager:add_StandardSoundToLoad	( "OptionState"				, 0		, 0										, "ButtonClickedWave.wav"		, "Sounds"		,	false		);
	c_etyFilemanager:add_StandardSoundToLoad	( "OptionState"				, 2		, 2										, "ButtonHoverWave.wav"			, "Sounds"		,	false		);
	c_etyFilemanager:add_StandardSoundToLoad	( "OptionState"				, 2		, 0										, "ButtonClickedWave.wav"		, "Sounds"		,	false		);

	--||||||||||||||||||||||||||||||||||||||||||||> GRAPHICOPTIONSTATE RESSOURCES

	c_etyFilemanager:add_StandardSoundToLoad	( "GraphicOptionState"		, 0		, 2										, "ButtonHoverWave.wav"			, "Sounds"		,	false		);
	c_etyFilemanager:add_StandardSoundToLoad	( "GraphicOptionState"		, 0		, 0										, "ButtonClickedWave.wav"		, "Sounds"		,	false		);
	c_etyFilemanager:add_StandardSoundToLoad	( "GraphicOptionState"		, 1		, 0										, "ButtonClickedWave.wav"		, "Sounds"		,	false		);
	c_etyFilemanager:add_StandardSoundToLoad	( "GraphicOptionState"		, 2		, 2										, "ButtonHoverWave.wav"			, "Sounds"		,	false		);
	c_etyFilemanager:add_StandardSoundToLoad	( "GraphicOptionState"		, 2		, 0										, "ButtonClickedWave.wav"		, "Sounds"		,	false		);

	--|||||||||||||||||||||||||||||||||||||||||||| AUDIOOPTIONSTATE RESSOURCES

	c_etyFilemanager:add_StandardSoundToLoad	( "AudioOptionState"		, 0		, 2										, "ButtonHoverWave.wav"			, "Sounds"		,	false		);
	c_etyFilemanager:add_StandardSoundToLoad	( "AudioOptionState"		, 0		, 0										, "ButtonClickedWave.wav"		, "Sounds"		,	false		);
	c_etyFilemanager:add_StandardSoundToLoad	( "AudioOptionState"		, 8		, 2										, "ButtonHoverWave.wav"			, "Sounds"		,	false		);
	c_etyFilemanager:add_StandardSoundToLoad	( "AudioOptionState"		, 8		, 0										, "ButtonClickedWave.wav"		, "Sounds"		,	false		);

	--|||||||||||||||||||||||||||||||||||||||||||| SPACESTATIONSTATE RESSOURCES

	c_etyFilemanager:add_StandardSoundToLoad	( "SpaceStationState"		, 0		, 2										, "ButtonHoverWave.wav"			, "Sounds"		,	false		);
	c_etyFilemanager:add_StandardSoundToLoad	( "SpaceStationState"		, 0		, 0										, "ButtonClickedWave.wav"		, "Sounds"		,	false		);
	c_etyFilemanager:add_StandardSoundToLoad	( "SpaceStationState"		, 8		, 2										, "ButtonHoverWave.wav"			, "Sounds"		,	false		);
	c_etyFilemanager:add_StandardSoundToLoad	( "SpaceStationState"		, 8		, 0										, "ButtonClickedWave.wav"		, "Sounds"		,	false		);
	
	
	--|||||||||||||||||||||||||||||||||||||||||||| SPACESTATIONHANGARSTATE RESSOURCES

	c_etyFilemanager:add_StandardSoundToLoad	( "SpaceStationHangarState"	, 0		, 2										, "ButtonHoverWave.wav"			, "Sounds"		,	false		);
	c_etyFilemanager:add_StandardSoundToLoad	( "SpaceStationHangarState"	, 0		, 0										, "ButtonClickedWave.wav"		, "Sounds"		,	false		);
	c_etyFilemanager:add_StandardSoundToLoad	( "SpaceStationHangarState"	, 2		, 2										, "ButtonHoverWave.wav"			, "Sounds"		,	false		);
	c_etyFilemanager:add_StandardSoundToLoad	( "SpaceStationHangarState"	, 2		, 0										, "ButtonClickedWave.wav"		, "Sounds"		,	false		);
	
	--|||||||||||||||||||||||||||||||||||||||||||| INGAMESTATE RESSOURCES

	c_etyFilemanager:add_StandardSoundToLoad	( "IngameState"				, 0		, 2										, "ButtonHoverWave.wav"			, "Sounds"		,	false		);
	c_etyFilemanager:add_StandardSoundToLoad	( "IngameState"				, 0		, 0										, "ButtonClickedWave.wav"		, "Sounds"		,	false		);
	c_etyFilemanager:add_StandardSoundToLoad	( "IngameState"				, 2		, 2										, "ButtonHoverWave.wav"			, "Sounds"		,	false		);
	c_etyFilemanager:add_StandardSoundToLoad	( "IngameState"				, 2		, 0										, "ButtonClickedWave.wav"		, "Sounds"		,	false		);

end
