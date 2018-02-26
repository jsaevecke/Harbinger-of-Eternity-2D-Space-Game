///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CBUTTON.CPP									///////////
///////////////////////////////////////////////////////////////////////////////////////////////

//Eternity-Includes
#include "CButton.hpp"
#include "CLabel.hpp"
#include "CPictureControl.hpp"


										ety::CButton::CButton								(void)
{
	mp_c_etyLabelCaptionLabel					=	NULL;
	mp_c_etyDialogitemParentDialogitem			=	NULL;
	mp_c_etyDialogParentDialog					=	NULL;
	mp_c_etyLabelTooltipText					=	NULL;
	mp_c_etyPictureControlTooltipBackground		=	NULL;
}

										ety::CButton::~CButton								(void)
{
	if(mp_c_etyLabelCaptionLabel != NULL)
	{
		delete mp_c_etyLabelCaptionLabel;
		mp_c_etyLabelCaptionLabel = NULL;
	}
}



											//Normaler Button
										ety::CButton::CButton								(
																							std::string strCustomID, const sf::Texture& c_sfTextureButtonSet, 
																							float fWidth, float fHeight, sf::Vector2f c_sfVector2fPosition, 
																							sf::IntRect c_sfIntRectButtonSubRect, CDialogitem* p_c_etyDialogitemParent, 
																							CDialog* p_c_etyDialogParentDialog
																							)

						:m_bTextButton											(false)
						,m_bAnimatedCaption										(true)
						,m_bHoverSprite_Visibility								(true)
						,m_bCaptionHighlighted									(false)
						,m_c_sfIntRectButtonSubRect								(c_sfIntRectButtonSubRect)
						,mp_c_etyLabelTooltipText								(NULL)
						,mp_c_etyPictureControlTooltipBackground				(NULL)
{
	sf::VideoMode c_sfVideoModeGamesettings		=	p_c_etyDialogParentDialog->get_VideoMode();

	m_strCustomID								=	strCustomID;
	m_bVisibility								=	true;
	m_bActive									=	true;
	m_bInternActive								=	true;
	m_bAnchorCentered							=	false;
	m_bRealPosition								=	false;
	m_uiDrawPosition							=	0;
	m_en_etyAffinity							=	Affinity::enSTANDARD;
	m_en_etyAnchor								=	Anchor::enTOPLEFT;
	mp_c_etyDialogitemParentDialogitem			=	p_c_etyDialogitemParent;
	mp_c_etyDialogParentDialog					=	p_c_etyDialogParentDialog;
	mp_c_etyDialogitemAnchorOrientation			=	NULL;
	m_en_etyAttachedType						=	AttachedType::enNOTATTACHED;	
	m_fWidth									=	c_sfVideoModeGamesettings.width*float(fWidth/1680.f);
	m_fHeight									=	c_sfVideoModeGamesettings.height*float(fHeight/1050.f);
	
	if(p_c_etyDialogitemParent != NULL)
	{
		m_en_etyAttachedType					=	AttachedType::enCHILDREN;
	}

	m_en_etyDialogitemType						=	DialogitemType::enBUTTON;

	mp_c_etyLabelCaptionLabel						=	NULL;
	m_fHoverSprite_Height						=	m_fHeight;
	m_fHoverSprite_Width						=	m_fWidth;
	m_bCaptionHighlighted						=	false;
	m_c_sfVector2uCharactersize_highlighted.x	=	0;
	m_c_sfVector2uCharactersize_highlighted.y	=	0;
	m_c_sfIntRectHoverSpriteSubRect				=	m_c_sfIntRectButtonSubRect;
	m_c_sfIntRectHoverSpriteSubRect.left		+=	m_c_sfIntRectHoverSpriteSubRect.width;

	

	c_sfVector2fPosition.x						=	c_sfVideoModeGamesettings.width*float(c_sfVector2fPosition.x/1680.f);
	c_sfVector2fPosition.y						=	c_sfVideoModeGamesettings.height*float(c_sfVector2fPosition.y/1050.f);

	m_c_sfVector2fPosition						=	c_sfVector2fPosition;
	/*if(bRealPosition == true)
	{
		m_c_sfVector2fRealPosition				=	c_sfVector2fPosition;
	}
	else
	{
		m_c_sfVector2fPosition					=	c_sfVector2fPosition;
	}*/
	
	calculate_Positions(false);


	//Da sich alle Bilder f�r Steuerelemente auf einem sf::Texture befinden, muss erst das Richtige auf diesem Image gesucht und dem Sprite hinzugef�gt werden
	m_c_sfSpriteButton.setTexture((c_sfTextureButtonSet));
	m_c_sfSpriteButton.setTextureRect(m_c_sfIntRectButtonSubRect);
	m_c_sfSpriteButton.setScale(m_fWidth/m_c_sfSpriteButton.getLocalBounds().width,m_fHeight/m_c_sfSpriteButton.getLocalBounds().height);

	
	/*if(c_sfTextureBackgroundSprite != NULL)
	{
		m_c_sfSpriteButton.setTexture((*c_sfTextureBackgroundSprite));
		m_c_sfSpriteButton.setTextureRect(sf::IntRect(m_c_sfVector2iBackgroundSubRect_Position.x,m_c_sfVector2iBackgroundSubRect_Position.y,m_c_sfVector2iBackgroundSubRect_Size.x,m_c_sfVector2iBackgroundSubRect_Size.y));
		m_c_sfSpriteButton.setScale(m_fWidth/m_c_sfSpriteButton.getLocalBounds().width,m_fHeight/m_c_sfSpriteButton.getLocalBounds().height);
	}
	

	if(p_c_sfTextureHoverSprite != NULL)
	{
		m_c_sfSpriteButton.setTexture((*p_c_sfTextureHoverSprite));
		m_c_sfSpriteButton.setTextureRect(sf::IntRect(m_c_sfVector2iHoverSpriteSubRect_Position.x,m_c_sfVector2iHoverSpriteSubRect_Position.y,m_c_sfVector2iHoverSpriteSubRect_Size.x,m_c_sfVector2iHoverSpriteSubRect_Size.y));
		m_c_sfSpriteButton.setScale(m_fHoverSprite_Width/m_c_sfSpriteButton.getLocalBounds().width,m_fHoverSprite_Height/m_c_sfSpriteButton.getLocalBounds().height);
	}*/

	m_mapEventSounds = mp_c_etyDialogParentDialog->get_DialogManager()->get_StandardSounds(m_en_etyDialogitemType);
}



										//TextButton
										ety::CButton::CButton								(
																							std::string strCustomID, sf::Vector2f c_sfVector2fPosition, 
																							std::string strContent, float fCharactersize, ety::Color c_etyColorTextcolor, 
																							 ety::Color c_etyColorCaptionColor_highlighted, CDialogitem* p_c_etyDialogitemParent, 
																							CDialog* p_c_etyDialogParentDialog
																							)

						:m_bTextButton											(true)
						,m_bAnimatedCaption										(true)
						,m_bHoverSprite_Visibility								(false)
						,m_bCaptionHighlighted									(false)
						,m_c_etyColorCaptionColor_highlighted					(c_etyColorCaptionColor_highlighted)
						,mp_c_etyLabelTooltipText								(NULL)
						,mp_c_etyPictureControlTooltipBackground				(NULL)
{
	sf::VideoMode c_sfVideoModeGamesettings		=	p_c_etyDialogParentDialog->get_VideoMode();

	m_strCustomID								=	strCustomID;
	m_bVisibility								=	true;
	m_bActive									=	true;
	m_bInternActive								=	true;
	m_bAnchorCentered							=	false;
	m_bRealPosition								=	false;
	m_uiDrawPosition							=	0;
	m_en_etyAffinity							=	Affinity::enSTANDARD;
	m_en_etyAnchor								=	Anchor::enTOPLEFT;
	mp_c_etyDialogitemParentDialogitem			=	p_c_etyDialogitemParent;
	mp_c_etyDialogParentDialog					=	p_c_etyDialogParentDialog;
	mp_c_etyDialogitemAnchorOrientation			=	NULL;
	m_en_etyAttachedType						=	AttachedType::enNOTATTACHED;	
	
	if(p_c_etyDialogitemParent != NULL)
	{
		m_en_etyAttachedType					=	AttachedType::enCHILDREN;
	}

	m_en_etyDialogitemType						=	DialogitemType::enBUTTON;

	//Da die Caption nicht in die Dialogitemliste eines Dialogs aufgenommen wird, obliegt die Zeichenreihenfolge dem Parentdialogitem, also dem Button
	mp_c_etyLabelCaptionLabel						=	new CLabel( m_strCustomID + "Caption", strContent, fCharactersize, c_etyColorTextcolor, sf::Vector2f(0,0), this, 
																mp_c_etyDialogParentDialog);

	mp_c_etyLabelCaptionLabel->set_Anchor(Anchor::enMID);
	mp_c_etyLabelCaptionLabel->set_AnchorCentered(true);
	m_c_sfVector2uCharactersize_highlighted		=	mp_c_etyLabelCaptionLabel->get_Charactersize();
	m_bCaptionHighlighted						=	false;

	m_fWidth									=	mp_c_etyLabelCaptionLabel->get_Width();
	m_fHeight									=	mp_c_etyLabelCaptionLabel->get_Height();
	

	c_sfVector2fPosition.x						=	c_sfVideoModeGamesettings.width*float(c_sfVector2fPosition.x/1680.f);
	c_sfVector2fPosition.y						=	c_sfVideoModeGamesettings.height*float(c_sfVector2fPosition.y/1050.f);

	m_c_sfVector2fPosition					=	c_sfVector2fPosition;
	/*if(bRealPosition == true)
	{
		m_c_sfVector2fRealPosition				=	c_sfVector2fPosition;
	}
	else
	{
		m_c_sfVector2fPosition					=	c_sfVector2fPosition;
	}*/
	
	calculate_Positions(false);


	m_mapEventSounds = mp_c_etyDialogParentDialog->get_DialogManager()->get_StandardSounds(m_en_etyDialogitemType);
}
		
		
		void							ety::CButton::change_SpriteStyle					(bool bHoverSprite)
{
	if(bHoverSprite == false)
	{
		m_c_sfSpriteButton.setTextureRect(m_c_sfIntRectButtonSubRect);
		m_c_sfSpriteButton.setColor(m_c_etyColorBackgroundColors.get_sfColor());
		m_c_sfSpriteButton.setScale(m_fWidth/m_c_sfSpriteButton.getLocalBounds().width,m_fHeight/m_c_sfSpriteButton.getLocalBounds().height);
		m_c_sfSpriteButton.setPosition(m_c_sfVector2fRealPosition);
	}
	else
	{
		m_c_sfSpriteButton.setTextureRect(m_c_sfIntRectHoverSpriteSubRect);
		m_c_sfSpriteButton.setColor(m_c_etyColorHoverSpriteColors.get_sfColor());
		m_c_sfSpriteButton.setScale(m_fHoverSprite_Width/m_c_sfSpriteButton.getLocalBounds().width,m_fHoverSprite_Height/m_c_sfSpriteButton.getLocalBounds().height);

		if(m_fHeight == m_fHoverSprite_Height && m_fWidth == m_fHoverSprite_Width)
		{
			m_c_sfSpriteButton.setPosition(m_c_sfVector2fRealPosition);
		}
		else
		{
			m_c_sfSpriteButton.setPosition(m_c_sfVector2fRealPosition.x - (m_fHoverSprite_Width - m_fWidth) /2,m_c_sfVector2fRealPosition.y - (m_fHoverSprite_Height- m_fHeight) /2);
		}	
	}
}

		void							ety::CButton::set_CaptionHighlighted				(bool bCaptionHighlighted)
{
	m_bCaptionHighlighted		=	bCaptionHighlighted;
}



		void							ety::CButton::adjust_SizeToResolution				( const sf::VideoMode& c_sfVideoModeNewSettings, const sf::VideoMode& c_sfVideoModeOldSettings )
{
	m_fWidth	=	m_fWidth * (float(c_sfVideoModeNewSettings.width)/float(c_sfVideoModeOldSettings.width));
	m_fHeight	=	m_fHeight * (float(c_sfVideoModeNewSettings.height)/float(c_sfVideoModeOldSettings.height));

	m_fHoverSprite_Width	=	m_fHoverSprite_Width * (float(c_sfVideoModeNewSettings.width)/float(c_sfVideoModeOldSettings.width));
	m_fHoverSprite_Height	=	m_fHoverSprite_Height * (float(c_sfVideoModeNewSettings.height)/float(c_sfVideoModeOldSettings.height));

	m_c_sfVector2uCharactersize_highlighted.x	=	check_ValuesAfterDecimalPoint(m_c_sfVector2uCharactersize_highlighted.x * (float(c_sfVideoModeNewSettings.width)/float(c_sfVideoModeOldSettings.width)));
	m_c_sfVector2uCharactersize_highlighted.y	=	check_ValuesAfterDecimalPoint(m_c_sfVector2uCharactersize_highlighted.y * (float(c_sfVideoModeNewSettings.height)/float(c_sfVideoModeOldSettings.height)));

	if(mp_c_etyLabelCaptionLabel != NULL)
	{
		mp_c_etyLabelCaptionLabel->adjust_SizeToResolution(c_sfVideoModeNewSettings,c_sfVideoModeOldSettings);
	}

	if(mp_c_etyLabelTooltipText != NULL)
	{
		mp_c_etyLabelTooltipText->adjust_SizeToResolution(c_sfVideoModeNewSettings,c_sfVideoModeOldSettings);
	}

	if(mp_c_etyPictureControlTooltipBackground != NULL)
	{
		mp_c_etyPictureControlTooltipBackground->adjust_SizeToResolution(c_sfVideoModeNewSettings,c_sfVideoModeOldSettings);
	}

	m_c_sfVector2fPosition.x	=	m_c_sfVector2fPosition.x * (float(c_sfVideoModeNewSettings.width)/float(c_sfVideoModeOldSettings.width));
	m_c_sfVector2fPosition.y	=	m_c_sfVector2fPosition.y * (float(c_sfVideoModeNewSettings.height)/float(c_sfVideoModeOldSettings.height));
}


		bool							ety::CButton::check_MouseCoordinates				(void)
{	
	//Falls es sich um einen Textbutton handelt, m�ssen die Mauskoordinaten anhand des Labels und nicht des Buttons �berpr�ft werden
	if(m_bTextButton == true && mp_c_etyLabelCaptionLabel != NULL)
	{
		if(mp_c_etyLabelCaptionLabel->get_Visibility() == true)
		{
			//Nochmal �berarbeiten!
			return mp_c_etyLabelCaptionLabel->check_MouseCoordinates();
		}
		else
		{
			return false;
		}
	}

	if(m_bVisibility == true)
	{
		sf::Vector2i c_sfVector2iMouseCoordinates = ety::CMouse::get_Position();

		if(c_sfVector2iMouseCoordinates.x >= m_c_sfVector2fRealPosition.x && c_sfVector2iMouseCoordinates.x <= m_c_sfVector2fRealPosition.x + m_fWidth && c_sfVector2iMouseCoordinates.y >= m_c_sfVector2fRealPosition.y && c_sfVector2iMouseCoordinates.y <= m_c_sfVector2fRealPosition.y + m_fHeight)
		{
			return true;
		}
	}

	return false;
}

		bool							ety::CButton::create_CaptionLabel					(
																							 ety::Color c_etyColorCaptionColor_highlighted, std::string strContent, float fCharactersize, 
																							 ety::Color c_etyColorTextcolor
																							)
{
	//Diese Funktion f�gt dem Button seine Caption/Label hinzu
	if(mp_c_etyLabelCaptionLabel == NULL)
	{
		m_c_etyColorCaptionColor_highlighted		=	c_etyColorCaptionColor_highlighted;

		//Da die Caption nicht in die Dialogitemliste eines Dialogs aufgenommen wird, obliegt die Zeichenreihenfolge dem Parentdialogitem, also dem Button
		mp_c_etyLabelCaptionLabel						=	new CLabel( m_strCustomID + "Caption", strContent, fCharactersize, c_etyColorTextcolor, sf::Vector2f(0,0), 
																	this, mp_c_etyDialogParentDialog);

		m_c_sfVector2uCharactersize_highlighted		=	mp_c_etyLabelCaptionLabel->get_Charactersize();
		mp_c_etyLabelCaptionLabel->set_Anchor(Anchor::enMID);
		mp_c_etyLabelCaptionLabel->set_AnchorCentered(true);

		return true;
	}

	return false;
}

		bool							ety::CButton::create_Tooltip						( std::string strContent, float fCharactersize, ety::Color c_etyColorTextcolor )
{
	//Diese Funktion f�gt dem Button ein Tooltip hinzu
	if(mp_c_etyLabelTooltipText == NULL)
	{
		mp_c_etyPictureControlTooltipBackground			=	new CPictureControl( 
			m_strCustomID + "TooltipBackground", *mp_c_etyDialogParentDialog->get_DialogManager()->get_StandardTooltipTexture(), 0.f, 0.f, sf::Vector2f(0,0), 
			mp_c_etyDialogParentDialog->get_DialogManager()->get_StandardTooltipSubRect(), this, mp_c_etyDialogParentDialog);

		mp_c_etyLabelTooltipText						=	new CLabel( m_strCustomID + "Tooltip", strContent, fCharactersize, c_etyColorTextcolor, sf::Vector2f(0,0), 
																	mp_c_etyPictureControlTooltipBackground, mp_c_etyDialogParentDialog);

		mp_c_etyLabelTooltipText->set_Anchor(Anchor::enMID);
		mp_c_etyLabelTooltipText->set_AnchorCentered(true);
		mp_c_etyLabelTooltipText->update_Dialogitem(0);

		mp_c_etyPictureControlTooltipBackground->set_Width(float(mp_c_etyLabelTooltipText->get_Width() * 1.05));
		mp_c_etyPictureControlTooltipBackground->set_Height(float(mp_c_etyLabelTooltipText->get_Height() * 1.2));

					

		return true;
	}

	return false;
}


		bool							ety::CButton::delete_CaptionLabel					(void)
{
	//L�schen der Caption/Labels
	if(mp_c_etyLabelCaptionLabel != NULL)
	{
		delete mp_c_etyLabelCaptionLabel;
		mp_c_etyLabelCaptionLabel = NULL;
		
		return true;
	}
	else
	{
		return false;
	}
}

		bool							ety::CButton::draw_Dialogitem						(sf::RenderTexture* p_c_sfRenderTextureScene)
{
	if(m_bVisibility == true)
	{
		if(m_bTextButton == true && mp_c_etyLabelCaptionLabel != NULL)
		{
			if(mp_c_etyLabelCaptionLabel->get_Visibility() == true)
			{
				mp_c_etyLabelCaptionLabel->draw_Dialogitem(p_c_sfRenderTextureScene);

				return true;
			}
		}
		else if(m_bTextButton == false)
		{
			(*p_c_sfRenderTextureScene).draw(m_c_sfSpriteButton);

			if(mp_c_etyLabelCaptionLabel != NULL)
			{
				if(mp_c_etyLabelCaptionLabel->get_Visibility() == true)
				{
					mp_c_etyLabelCaptionLabel->draw_Dialogitem(p_c_sfRenderTextureScene);
				}
			}

			return true;
		}
	}

	return false;
}

		void							ety::CButton::handle_InternEvents					(const sf::Event& c_sfEvent)
{
	if(c_sfEvent.type	==	sf::Event::MouseButtonPressed)
	{
		if(c_sfEvent.mouseButton.button == sf::Mouse::Left)
		{
			if(mp_c_etyDialogitemParentDialogitem != NULL && m_en_etyAttachedType == AttachedType::enCHILDREN)
			{
				mp_c_etyDialogitemParentDialogitem->handle_InternEvents(c_sfEvent);
			}
		}	
	}
	else if(c_sfEvent.type	==	sf::Event::MouseButtonReleased || c_sfEvent.type	==	sf::Event::MouseButtonNoFocusReleased)
	{
		if(c_sfEvent.mouseButton.button == sf::Mouse::Left)
		{
			if(mp_c_etyDialogitemParentDialogitem != NULL && m_en_etyAttachedType == AttachedType::enCHILDREN)
			{
				mp_c_etyDialogitemParentDialogitem->handle_InternEvents(c_sfEvent);
			}
			else
			{
				if(get_EventSound(ety::SoundType::enCLICK) != NULL)
				{
					get_EventSound(ety::SoundType::enCLICK)->play();
				}
			}
		}
	}
	else if(c_sfEvent.type	==	sf::Event::MouseButtonDoubleClick)
	{
		if(c_sfEvent.mouseButton.button == sf::Mouse::Left)
		{
			if(mp_c_etyDialogitemParentDialogitem != NULL && m_en_etyAttachedType == AttachedType::enCHILDREN)
			{
				mp_c_etyDialogitemParentDialogitem->handle_InternEvents(c_sfEvent);
			}
			else
			{
				if(get_EventSound(ety::SoundType::enCLICK) != NULL)
				{
					get_EventSound(ety::SoundType::enCLICK)->play();
				}
			}
		}
	}
	else if(c_sfEvent.type	==	sf::Event::MouseMoved)
	{
		if(m_bVisibility == true)
		{
			if(check_MouseCoordinates() == true)
			{					
				if(m_bHoverSprite_Visibility == true || m_bTextButton == true)
				{
					
					if(m_bHoverSoundPlayed == false)
					{
						if(get_EventSound(SoundType::enHOVER) != NULL)
						{
							//�NDERN/ANPASSEN!
							if(get_EventSound(SoundType::enHOVER)->getStatus() != sf::Sound::Playing)
							{
								get_EventSound(SoundType::enHOVER)->play();
								m_bHoverSoundPlayed = true;
							}
						}
					}
				}
				else
				{
					if(m_bHoverSoundPlayed == false)
					{
						if(get_EventSound(SoundType::enHOVER) != NULL)
						{
							if(get_EventSound(SoundType::enHOVER)->getStatus() != sf::Sound::Playing)
							{
								get_EventSound(SoundType::enHOVER)->play();
								m_bHoverSoundPlayed = true;
							}
						}
					}
				}	
			}
			else
			{
				if(m_bHoverSoundPlayed == true)
				{
					m_bHoverSoundPlayed = false;
				}
			}					
		}
	}
}

		void							ety::CButton::modificate_Colorfilter				(sf::Vector3f c_sfVector3fFactors)
{
	m_c_etyColorBackgroundColors.r			*= c_sfVector3fFactors.x;
	m_c_etyColorBackgroundColors.g			*= c_sfVector3fFactors.y;
	m_c_etyColorBackgroundColors.b			*= c_sfVector3fFactors.z;

	m_c_etyColorCaptionColor_highlighted.r	*= c_sfVector3fFactors.x;
	m_c_etyColorCaptionColor_highlighted.g	*= c_sfVector3fFactors.y;
	m_c_etyColorCaptionColor_highlighted.b	*= c_sfVector3fFactors.z;

	m_c_etyColorHoverSpriteColors.r			*= c_sfVector3fFactors.x;
	m_c_etyColorHoverSpriteColors.g			*= c_sfVector3fFactors.y;
	m_c_etyColorHoverSpriteColors.b			*= c_sfVector3fFactors.z;


	if(mp_c_etyLabelCaptionLabel != NULL)
	{
		mp_c_etyLabelCaptionLabel->modificate_Colorfilter(c_sfVector3fFactors);
	}

	update_Dialogitem(0);
}

		void							ety::CButton::swap_HighlightInformation				(void)
{
	//Die im Button gespeicherten HighlightInformationen werden mit denen des Labels getauscht
	if(m_bCaptionHighlighted == true)
	{
		m_bCaptionHighlighted = false;
	}
	else
	{
		m_bCaptionHighlighted = true;
	}

	sf::Vector2u c_sfVector2uTmpCharactersize		=	m_c_sfVector2uCharactersize_highlighted;
	m_c_sfVector2uCharactersize_highlighted			=	mp_c_etyLabelCaptionLabel->get_Charactersize();
	mp_c_etyLabelCaptionLabel->set_Charactersize(c_sfVector2uTmpCharactersize);

	ety::Color c_etyColorTmpCaptionColor			=	m_c_etyColorCaptionColor_highlighted;
	m_c_etyColorCaptionColor_highlighted			=	mp_c_etyLabelCaptionLabel->get_Textcolor();
	mp_c_etyLabelCaptionLabel->set_Textcolor(c_etyColorTmpCaptionColor);
	
}
			
		void							ety::CButton::update_Dialogitem						(const sf::Uint32& uiFrameTime)
{
	//Aktualisiert den Button und �bertr�gt seine Attribute an seine Sprites bzw. sein Label
	if(mp_c_etyDialogParentDialog->get_DialogManager()->check_IsDialogitemActive(this) == false)
	{
		m_bActive = false;
	}
	else
	{
		m_bActive = m_bInternActive;
	}

	

	if(m_bRealPosition == false)
	{
		if(mp_c_etyDialogitemParentDialogitem == NULL)
		{
			m_c_sfVector2fRealPosition.x = (mp_c_etyDialogParentDialog->get_Anchor(m_en_etyAnchor,false).x) +  m_c_sfVector2fPosition.x;
			m_c_sfVector2fRealPosition.y = (mp_c_etyDialogParentDialog->get_Anchor(m_en_etyAnchor,false).y) -  m_c_sfVector2fPosition.y;
		}
		else
		{
			if(mp_c_etyDialogitemAnchorOrientation != NULL)
			{
				m_c_sfVector2fRealPosition.x = (mp_c_etyDialogitemAnchorOrientation->get_Anchor(m_en_etyAnchor).x) +  m_c_sfVector2fPosition.x;
				m_c_sfVector2fRealPosition.y = (mp_c_etyDialogitemAnchorOrientation->get_Anchor(m_en_etyAnchor).y) -  m_c_sfVector2fPosition.y;
			}
			else
			{
				m_c_sfVector2fRealPosition.x = (mp_c_etyDialogitemParentDialogitem->get_Anchor(m_en_etyAnchor).x) +  m_c_sfVector2fPosition.x;
				m_c_sfVector2fRealPosition.y = (mp_c_etyDialogitemParentDialogitem->get_Anchor(m_en_etyAnchor).y) -  m_c_sfVector2fPosition.y;
			}
		}


		if(m_en_etyAnchor == Anchor::enALIGNEDMIDTOP)
		{
			m_c_sfVector2fRealPosition.x = m_c_sfVector2fRealPosition.x - (m_fWidth / 2);
		}
		else if(m_en_etyAnchor == Anchor::enALIGNEDLEFT)
		{
			m_c_sfVector2fRealPosition.y = m_c_sfVector2fRealPosition.y - (m_fHeight / 2);
		}
		else if(m_bAnchorCentered == true)
		{
			m_c_sfVector2fRealPosition.x		=	m_c_sfVector2fRealPosition.x - (m_fWidth / 2);
			m_c_sfVector2fRealPosition.y		=	m_c_sfVector2fRealPosition.y - (m_fHeight / 2);
		}
	}

	m_c_sfSpriteButton.setPosition(m_c_sfVector2fRealPosition);

	
	if(mp_c_etyLabelCaptionLabel != NULL)
	{
		if(m_bActive == true && m_bAnimatedCaption == true || m_bInternActive == true && m_bAnimatedCaption == true )
		{
			if(check_MouseCoordinates() == true && m_bCaptionHighlighted == false && m_bActive == true)
			{
				swap_HighlightInformation();
				m_bCaptionHighlighted = true;
			}
			else if(check_MouseCoordinates() == false && m_bCaptionHighlighted == true && m_bActive == true)
			{
				swap_HighlightInformation();
				m_bCaptionHighlighted = false;
			}
			else if(check_MouseCoordinates() == true && m_bCaptionHighlighted == true && m_bActive == false && m_bAnimatedCaption == true)
			{
				swap_HighlightInformation();
				m_bCaptionHighlighted = false;
			}
		}

		mp_c_etyLabelCaptionLabel->update_Dialogitem(uiFrameTime);
	}

	if(mp_c_etyPictureControlTooltipBackground != NULL)
	{
		

		//std::cout << "MOUSE: " << c_sfVector2fMousePosition.x << " :: " << c_sfVector2fMousePosition.y << std::endl;

		//mp_c_etyPictureControlTooltipBackground->set_RealPosition(c_sfVector2fMousePosition);
		mp_c_etyPictureControlTooltipBackground->update_Dialogitem(uiFrameTime);

		//std::cout << "BACKGROUND: " << mp_c_etyPictureControlTooltipBackground->get_RealPosition().x << " :: " << mp_c_etyPictureControlTooltipBackground->get_RealPosition().y << std::endl;
	}

	if(mp_c_etyLabelTooltipText != NULL)
	{
		mp_c_etyLabelTooltipText->update_Dialogitem(uiFrameTime);
	}
	
	if(m_bActive == true && check_MouseCoordinates() == true)
	{
		if(m_bHoverSprite_Visibility == true)
		{
			change_SpriteStyle(true);
			mp_c_etyDialogParentDialog->set_TooltipButton(this);
		}
		else
		{
			change_SpriteStyle(false);
		}
	}
	else
	{
		change_SpriteStyle(false);
	}
}



//Set-Methoden
		void							ety::CButton::set_AnimatedCaption					(bool bAnimatedCaption)
{
	m_bAnimatedCaption	=	bAnimatedCaption;
}		
		void							ety::CButton::set_TextButton						(bool bTextButton)
{
	m_bTextButton			=	bTextButton;
}
		void							ety::CButton::set_HoverSprite_Visibility			(bool bHoverSprite_Visibility)
{
	m_bHoverSprite_Visibility			=	bHoverSprite_Visibility;
}
		void							ety::CButton::set_HoverSprite_Width					(float fHoverSprite_Width)
{
	m_fHoverSprite_Width	=	fHoverSprite_Width;
}
		void							ety::CButton::set_HoverSprite_Height				(float fHoverSprite_Height)
{
	m_fHoverSprite_Height	=	fHoverSprite_Height;
}	 
		void							ety::CButton::set_Charactersize_highlighted			(sf::Vector2u c_sfVector2uCharactersize_highlighted)
{
	m_c_sfVector2uCharactersize_highlighted			=	c_sfVector2uCharactersize_highlighted;
}
		void							ety::CButton::set_BackgroundColors					(ety::Color c_etyColorBackgroundColors)
{
	m_c_etyColorBackgroundColors		=	c_etyColorBackgroundColors;
}
		void							ety::CButton::set_CaptionColor_highlighted			(ety::Color c_etyColorCaptionColor_highlighted)
{
	m_c_etyColorCaptionColor_highlighted	=	c_etyColorCaptionColor_highlighted;
}
		void							ety::CButton::set_HoverSpriteColors					(ety::Color c_etyColorHoverSpriteColors)
{
	m_c_etyColorHoverSpriteColors	=	c_etyColorHoverSpriteColors;
}
		void							ety::CButton::set_Background_SubRect				(sf::IntRect c_sfIntRectButtonSubRect, bool bUpdateSprite)
{
	m_c_sfIntRectButtonSubRect	=	c_sfIntRectButtonSubRect;

	if(bUpdateSprite == true)
	{
		m_c_sfSpriteButton.setTextureRect(m_c_sfIntRectButtonSubRect);
		m_c_sfSpriteButton.setScale(m_fWidth/m_c_sfSpriteButton.getLocalBounds().width,m_fHeight/m_c_sfSpriteButton.getLocalBounds().height);
	}
}
		void							ety::CButton::set_HoverSprite_SubRect				(sf::IntRect c_sfIntRectHoverSpriteSubRect, bool bUpdateSprite)
{
	m_c_sfIntRectHoverSpriteSubRect	=	c_sfIntRectHoverSpriteSubRect;

	if(bUpdateSprite == true)
	{
		m_c_sfSpriteButton.setTextureRect(m_c_sfIntRectHoverSpriteSubRect);
		m_c_sfSpriteButton.setScale(m_fHoverSprite_Width/m_c_sfSpriteButton.getLocalBounds().width,m_fHoverSprite_Height/m_c_sfSpriteButton.getLocalBounds().height);
	}
}
		void							ety::CButton::set_Active							(bool bActive)
{
	m_bActive		=	bActive;
	m_bInternActive	=	bActive;

	if(m_bActive == false && m_bCaptionHighlighted == true  && m_bAnimatedCaption == true)
	{
		swap_HighlightInformation();
	}
}
		void							ety::CButton::set_Visibility						(bool bVisibility)
{
	m_bVisibility		=	bVisibility;

	if(m_bVisibility == false && m_bCaptionHighlighted == true && m_bAnimatedCaption == true)
	{
		swap_HighlightInformation();
	}
}	
		void							ety::CButton::set_RealPosition						(sf::Vector2f c_sfVector2fRealPosition)
{
	m_c_sfVector2fRealPosition	=	c_sfVector2fRealPosition;
}



//Get-Methoden
		bool							ety::CButton::get_AnimatedCaption					(void)
{
	return m_bAnimatedCaption;
}
		bool							ety::CButton::get_TextButton						(void)
{
	return	m_bTextButton;
}
		bool							ety::CButton::get_HoverSprite_Visibility			(void)
{
	return	m_bHoverSprite_Visibility;
}
		bool							ety::CButton::get_CaptionHighlighted				(void)
{
	return	m_bCaptionHighlighted;
}
		float							ety::CButton::get_HoverSprite_Width					(void)
{
	return m_fHoverSprite_Width;
}			
		float							ety::CButton::get_HoverSprite_Height				(void)
{
	return m_fHoverSprite_Height;
}	 
		sf::Vector2u					ety::CButton::get_Charactersize_highlighted			(void)
{
	return m_c_sfVector2uCharactersize_highlighted;
}
		ety::CLabel*			const	ety::CButton::get_CaptionLabel						(void)
{
	return mp_c_etyLabelCaptionLabel;
}
		ety::CLabel*			const	ety::CButton::get_TooltipLabel						(void)
{
	return mp_c_etyLabelTooltipText;
}
		ety::CPictureControl*	const	ety::CButton::get_TooltipBackground					(void)
{
	return mp_c_etyPictureControlTooltipBackground;
}
		ety::Color						ety::CButton::get_BackgroundColors					(void)
{
	return	m_c_etyColorBackgroundColors;
}
		ety::Color						ety::CButton::get_CaptionColor_highlighted			(void)
{
	return m_c_etyColorCaptionColor_highlighted;
}
		ety::Color						ety::CButton::get_HoverSpriteColors					(void)
{
	return	m_c_etyColorHoverSpriteColors;
}
		sf::Sprite						ety::CButton::get_BackgroundSprite					(void)
{
	sf::Sprite c_sfSpriteBackgroundSprite = m_c_sfSpriteButton;

	c_sfSpriteBackgroundSprite.setTextureRect(m_c_sfIntRectButtonSubRect);
	c_sfSpriteBackgroundSprite.setColor(m_c_etyColorBackgroundColors.get_sfColor());
	c_sfSpriteBackgroundSprite.setScale(m_fWidth/m_c_sfSpriteButton.getLocalBounds().width,m_fHeight/m_c_sfSpriteButton.getLocalBounds().height);
	c_sfSpriteBackgroundSprite.setPosition(m_c_sfVector2fRealPosition);

	return	c_sfSpriteBackgroundSprite;
}
		sf::Sprite						ety::CButton::get_HoverSprite						(void)
{
	sf::Sprite c_sfSpriteHoverSprite = m_c_sfSpriteButton;

	c_sfSpriteHoverSprite.setTextureRect(m_c_sfIntRectHoverSpriteSubRect);
	c_sfSpriteHoverSprite.setColor(m_c_etyColorHoverSpriteColors.get_sfColor());
	c_sfSpriteHoverSprite.setScale(m_fHoverSprite_Width/m_c_sfSpriteButton.getLocalBounds().width,m_fHoverSprite_Height/m_c_sfSpriteButton.getLocalBounds().height);

	if(m_fHeight == m_fHoverSprite_Height && m_fWidth == m_fHoverSprite_Width)
	{
		c_sfSpriteHoverSprite.setPosition(m_c_sfVector2fRealPosition);
	}
	else
	{
		c_sfSpriteHoverSprite.setPosition(m_c_sfVector2fRealPosition.x - (m_fHoverSprite_Width - m_fWidth) /2,m_c_sfVector2fRealPosition.y - (m_fHoverSprite_Height- m_fHeight) /2);
	}	
	return c_sfSpriteHoverSprite;
}
		sf::IntRect						ety::CButton::get_Background_SubRect				(void)
{
	return m_c_sfIntRectButtonSubRect;
}			
		sf::IntRect						ety::CButton::get_HoverSprite_SubRect				(void)
{
	return m_c_sfIntRectHoverSpriteSubRect;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CBUTTON.CPP									///////////
///////////////////////////////////////////////////////////////////////////////////////////////