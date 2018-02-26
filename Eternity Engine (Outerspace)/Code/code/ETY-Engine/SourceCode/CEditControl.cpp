///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CEDITCONTROL.CPP							///////////
///////////////////////////////////////////////////////////////////////////////////////////////

//Eternity-Includes
#include "CEditControl.hpp"
#include "CButton.hpp"
#include "CLabel.hpp"
#include "CPictureControl.hpp"
#include <sstream>



										ety::CEditControl::CEditControl							(void)
{
	mp_c_etyPictureControlBackground	=	NULL;
	mp_c_etyLabelText					=	NULL;
	mp_c_etyDialogitemParentDialogitem	=	NULL;
	mp_c_etyDialogParentDialog			=	NULL;
}

										ety::CEditControl::~CEditControl						(void)
{
	if(mp_c_etyPictureControlBackground	!=	NULL)
	{
		delete	mp_c_etyPictureControlBackground;
		mp_c_etyPictureControlBackground = NULL;
	}

	if(mp_c_etyLabelText	!=	NULL)
	{
		delete	mp_c_etyLabelText;
		mp_c_etyLabelText = NULL;
	}
}
																
								
//�berladene Konstruktoren
										ety::CEditControl::CEditControl							(
																								  std::string strCustomID, const sf::Texture& c_sfTextureBackgroundSprite, 
																								  bool bDeleteContentbyFirstFocus, float fWidth, float fHeight, 
																								  sf::Vector2f c_sfVector2fPosition, sf::IntRect c_sfIntRectSubRect, std::string strContent,
																								  float fCharactersize, ety::Color c_etyColorTextcolor, 
																								  CDialogitem* p_c_etyDialogitemParent, CDialog* p_c_etyDialogParentDialog
																								)
						
						:m_bDeleteContentbyFirstFocus							(bDeleteContentbyFirstFocus)
						,m_iTextCursorPosition									(-1)
						,m_en_etyVariableTypePossibleInputType					(VariableType::enSTRING)
{
	m_bFocused									=	false;
	mp_c_etyPictureControlBackground			=	NULL;
	mp_c_etyLabelText							=	NULL;

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

	m_en_etyDialogitemType						=	DialogitemType::enEDITCONTROL;

	m_fWidth									=	c_sfVideoModeGamesettings.width*float(fWidth/1680.f);
	m_fHeight									=	c_sfVideoModeGamesettings.height*float(fHeight/1050.f);

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

	mp_c_etyLabelText							=	new CLabel(strCustomID + "Label", strContent, fCharactersize, c_etyColorTextcolor, sf::Vector2f(0,0), this, mp_c_etyDialogParentDialog);

	mp_c_etyLabelText->set_Anchor(Anchor::enALIGNEDLEFT);
	mp_c_etyLabelText->set_AnchorCentered(false);
	mp_c_etyLabelText->set_TextwriteoutStyle(TextwriteoutStyle::enEDITCONTROLCURSORBLINK);
	mp_c_etyLabelText->set_TextwriteoutDuration(500.f);
		
		
		/*strCustomID + "Label", strContent, mp_c_etyDialogParentDialog->get_DialogManager()->get_StandardFont(), fCharactersize, 
		c_etyColorTextcolor, 0, Affinity::enSTANDARD, true, true,  en_etyTextAnchor,bTextAnchorCentered,c_sfVector2fTextPosition,false,false,TextwriteoutStyle::enEDITCONTROLCURSORBLINK,
		500.f,false,this,NULL, AttachedType::enCHILDREN, p_c_etyDialogParentDialog, c_sfCurrentVideoMode);*/


	mp_c_etyPictureControlBackground			=	new CPictureControl(strCustomID + "Background", c_sfTextureBackgroundSprite, fWidth, fHeight, sf::Vector2f(0,0), c_sfIntRectSubRect,
																		this, mp_c_etyDialogParentDialog);
		
		/*strCustomID + "Background", c_sfTextureBackgroundSprite, 0, Affinity::enSTANDARD, true, true,
		c_etyColorBackgroundColors, fWidth, fHeight, Anchor::enTOPLEFT, false, sf::Vector2f(0,0), 0, false, c_sfVector2iBackgroundSubRect_Position, c_sfVector2iBackgroundSubRect_Size,
		false, this, NULL, AttachedType::enCHILDREN, p_c_etyDialogParentDialog, c_sfCurrentVideoMode);*/

	
	m_mapEventSounds = mp_c_etyDialogParentDialog->get_DialogManager()->get_StandardSounds(m_en_etyDialogitemType);
}


						
bool									ety::CEditControl::check_MouseCoordinates				(void)
{
	if(m_bVisibility == true && m_bActive == true)
	{
		if(mp_c_etyPictureControlBackground != NULL)
		{
			if(mp_c_etyPictureControlBackground->check_MouseCoordinates() == false)
			{
				if(mp_c_etyLabelText != NULL)
				{
					return mp_c_etyLabelText->check_MouseCoordinates();
				}
			}
			else
			{
				return true;
			}
		}
		else
		{
			if(mp_c_etyLabelText != NULL)
			{
				return mp_c_etyLabelText->check_MouseCoordinates();
			}
		}
	}
	

	return false;
}



void									ety::CEditControl::adjust_SizeToResolution				( const sf::VideoMode& c_sfVideoModeNewSettings, const sf::VideoMode& c_sfVideoModeOldSettings )
{
	m_fWidth	=	m_fWidth * (float(c_sfVideoModeNewSettings.width)/float(c_sfVideoModeOldSettings.width));
	m_fHeight	=	m_fHeight * (float(c_sfVideoModeNewSettings.height)/float(c_sfVideoModeOldSettings.height));

	mp_c_etyPictureControlBackground->adjust_SizeToResolution(c_sfVideoModeNewSettings,c_sfVideoModeOldSettings);

	mp_c_etyLabelText->adjust_SizeToResolution(c_sfVideoModeNewSettings,c_sfVideoModeOldSettings);

	m_c_sfVector2fPosition.x	=	m_c_sfVector2fPosition.x * (float(c_sfVideoModeNewSettings.width)/float(c_sfVideoModeOldSettings.width));
	m_c_sfVector2fPosition.y	=	m_c_sfVector2fPosition.y * (float(c_sfVideoModeNewSettings.height)/float(c_sfVideoModeOldSettings.height));

	mp_c_etyPictureControlBackground->set_Position(m_c_sfVector2fPosition);

	update_Dialogitem(0);
}
		
bool									ety::CEditControl::draw_Dialogitem						(sf::RenderTexture* p_c_sfRenderTextureScene)
{
	if(m_bVisibility == true)
	{
		if(mp_c_etyPictureControlBackground != NULL)
		{
			mp_c_etyPictureControlBackground->draw_Dialogitem(p_c_sfRenderTextureScene);
		}

		if(mp_c_etyLabelText != NULL)
		{
			mp_c_etyLabelText->draw_Dialogitem(p_c_sfRenderTextureScene);	
		}

		return true;
	}

	return false;
}

void									ety::CEditControl::handle_InputEvents					(sf::Event sfEventLastEvent)
{
	if(mp_c_etyLabelText == NULL)
	{
		return ;
	}
	
	std::string strInput = " ";
	strInput[0] = sfEventLastEvent.text.unicode;

	std::string strNewContent = mp_c_etyLabelText->get_Content();


	if(sfEventLastEvent.key.code == sf::Keyboard::Left && sfEventLastEvent.size.height == 0)
	{
		if(m_iTextCursorPosition != 0)
		{
			strNewContent.erase(m_iTextCursorPosition,1);
			m_iTextCursorPosition--;

			strNewContent.insert(m_iTextCursorPosition,"|");
			mp_c_etyLabelText->set_Content(strNewContent);
		}
	}
	else if(sfEventLastEvent.key.code == sf::Keyboard::Right && sfEventLastEvent.size.height == 0)
	{
		if(m_iTextCursorPosition != strNewContent.size() - 1)
		{
			strNewContent.erase(m_iTextCursorPosition,1);
			m_iTextCursorPosition++;
			strNewContent.insert(m_iTextCursorPosition,"|");

			mp_c_etyLabelText->set_Content(strNewContent);
		}
	}
	else if(sfEventLastEvent.key.code == sf::Keyboard::Delete && sfEventLastEvent.size.height == 0)
	{
		if(m_iTextCursorPosition != mp_c_etyLabelText->get_Content().size())
		{
			strNewContent.erase(m_iTextCursorPosition + 1,1);
		}		
	}
	else if(sfEventLastEvent.key.code == sf::Keyboard::End && sfEventLastEvent.size.height == 0)
	{
		if(m_iTextCursorPosition != mp_c_etyLabelText->get_Content().size())
		{
			strNewContent.erase(m_iTextCursorPosition,1);
			mp_c_etyLabelText->set_Content(mp_c_etyLabelText->get_Content().erase(m_iTextCursorPosition,1));
			m_iTextCursorPosition = mp_c_etyLabelText->get_Content().size();
		}
	}
	else if(sfEventLastEvent.key.code == sf::Keyboard::Home && sfEventLastEvent.size.height == 0)
	{
		if(m_iTextCursorPosition != 0)
		{
			mp_c_etyLabelText->set_Content(mp_c_etyLabelText->get_Content().erase(m_iTextCursorPosition,1));
			strNewContent = "|" + mp_c_etyLabelText->get_Content();
		}

		m_iTextCursorPosition = 0;
	}
	else if(strInput[0] == 8)
	{
		if(strNewContent.size() > 1 && m_iTextCursorPosition != 0)
		{
			strNewContent.erase(m_iTextCursorPosition,1);
			m_iTextCursorPosition--;
			strNewContent[m_iTextCursorPosition] = '|';
		}
	}
	else if(strInput[0] == 13)
	{
		//Enter
	}
	else if(strInput[0] == 27)
	{
		//Escape
	}
	else if(strInput[0] == 124)
	{
		// '|' (Bar)
	}
	else
	{
		if(m_en_etyVariableTypePossibleInputType == VariableType::enFLOAT)
		{
			if(strInput[0] < 48 && strInput[0] != 46 || strInput[0] > 57 && strInput[0] != 46)
			{
				return ;
			}
			else if(strNewContent.find('.') < strNewContent.size() && strInput[0] == 46)
			{
				return ;
			}
		}
		else if(m_en_etyVariableTypePossibleInputType == VariableType::enINT)
		{
			if(strInput[0] < 48 || strInput[0] > 57)
			{
				return ;
			}
		}
		else if(m_en_etyVariableTypePossibleInputType == VariableType::enBYTE)
		{
			strNewContent.insert(m_iTextCursorPosition,strInput);

			std::stringstream ssStream(strNewContent);
			int iTmp;
			ssStream >> iTmp;

			if(iTmp > 255)
			{
				return ;
			}

			m_iTextCursorPosition++;

			if(get_EventSound(ety::SoundType::enINPUT) != NULL)
			{
				get_EventSound(ety::SoundType::enINPUT)->play();
			}

			mp_c_etyLabelText->set_Content(strNewContent);

			return ;
		}
		

		strNewContent.insert(m_iTextCursorPosition,strInput);
		m_iTextCursorPosition++;

		if(get_EventSound(ety::SoundType::enINPUT) != NULL)
		{
			get_EventSound(ety::SoundType::enINPUT)->play();
		}
	}

	mp_c_etyLabelText->set_Content(strNewContent);
}

void									ety::CEditControl::modificate_Colorfilter				(sf::Vector3f c_sfVector3fFactors)
{
	if(mp_c_etyLabelText != NULL)
	{
		mp_c_etyLabelText->modificate_Colorfilter(c_sfVector3fFactors);
	}

	if(mp_c_etyPictureControlBackground != NULL)
	{
		mp_c_etyPictureControlBackground->modificate_Colorfilter(c_sfVector3fFactors);
	}

	update_Dialogitem(0);
}

void									ety::CEditControl::reset_FocusedDialogitem				(void)
{
	m_bFocused = false;
	mp_c_etyLabelText->set_Textwriteout(false);

	if(mp_c_etyLabelText->get_Content().size() == 1)
	{
		mp_c_etyLabelText->set_Content("");
		m_iTextCursorPosition = -1;
	}
	else
	{
		if(m_iTextCursorPosition > -1)
		{
			mp_c_etyLabelText->set_Content( mp_c_etyLabelText->get_Content().erase(m_iTextCursorPosition,1) );
		}
		m_iTextCursorPosition = -1;
	}
}

void									ety::CEditControl::update_Dialogitem					(const sf::Uint32& uiFrameTime)
{
	if(mp_c_etyDialogParentDialog->get_DialogManager()->check_IsDialogitemActive(this) == false)
	{
		m_bActive = false;
	}
	else
	{
		m_bActive = m_bInternActive;
	}


	//Die Positionen werden richtig angepasst
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

	//Der Background des EditControls wird ebenfalls geupdatet
	if(mp_c_etyPictureControlBackground != NULL)
	{
		mp_c_etyPictureControlBackground->update_Dialogitem(uiFrameTime);
	}

	//Sowie der Text
	if(mp_c_etyLabelText != NULL)
	{
		mp_c_etyLabelText->set_sfTextObjectContent("|" + mp_c_etyLabelText->get_Content());
		mp_c_etyLabelText->update_Dialogitem(uiFrameTime);
		mp_c_etyLabelText->set_sfTextObjectContent(mp_c_etyLabelText->get_Content());

		std::string strEditControlContent = "";
		std::string strTextCursor = "";
		if(m_iTextCursorPosition >= 0)
		{
			strEditControlContent = mp_c_etyLabelText->get_Content();
			strTextCursor = strEditControlContent[m_iTextCursorPosition];
			strEditControlContent.erase(m_iTextCursorPosition,1);
		}

		int iCounter = 0;
		int iTmpTextCursorPosition = m_iTextCursorPosition;

		while( mp_c_etyLabelText->get_RealPosition().x + mp_c_etyLabelText->get_sfTextObject()->getGlobalBounds().width > m_c_sfVector2fRealPosition.x + m_fWidth)
		{
			if(m_iTextCursorPosition > iCounter)
			{
				strEditControlContent.erase(0,1);
				iTmpTextCursorPosition--;
			}
			else
			{
				strEditControlContent.erase(strEditControlContent.size()-1,1);
			}

			mp_c_etyLabelText->set_sfTextObjectContent(strEditControlContent.insert(iTmpTextCursorPosition,strTextCursor));
			iCounter++;
			strEditControlContent.erase(iTmpTextCursorPosition,1);
		}
	}
}



//Set-Methoden	
void									ety::CEditControl::set_DeleteContentbyFirstFocus		(bool bDeleteContentbyFirstFocus)
{
	m_bDeleteContentbyFirstFocus	=	bDeleteContentbyFirstFocus;
}

void									ety::CEditControl::set_TextCursorPosition				(int iTextCursorPosition)
{
	m_iTextCursorPosition	=	iTextCursorPosition;
}

void									ety::CEditControl::set_EditControlContent				(std::string strEditControlContent)
{
	reset_FocusedDialogitem();
	mp_c_etyLabelText->set_Content(strEditControlContent);
}

void									ety::CEditControl::set_InputType						(enum VariableType::en_etyVariableType en_etyVariableType)
{
	m_en_etyVariableTypePossibleInputType	=	en_etyVariableType;
}

void									ety::CEditControl::set_Focus							(bool bFocus)
{
	//Diese �berladene set_Focus-Funktion verwaltet das Anklicken und richtige setzen des "Textcursors" des EditControls
	if(mp_c_etyLabelText == NULL)
	{
		return;
	}

	if(bFocus == true)
	{
		//Falls das EditControlangeklickt wurde wird der Focus standartm��ig auf dieses Dialogitem gesetzt
		mp_c_etyDialogParentDialog->get_DialogManager()->change_FocusedDialogitem(this);


		//Sollte "m_bDeleteContentbyFirstFocus" true sein und das EditControl noch nicht angeklickt wurde,
		//wird einfach der Inhalt dieses gel�scht
		if(m_bDeleteContentbyFirstFocus == true && m_bFocused == false)
		{
			mp_c_etyLabelText->set_Content("");
			//...
			m_iTextCursorPosition = 0;
		}
		else if(ety::CMouse::get_Position().x <= mp_c_etyLabelText->get_RealPosition().x)
		{
			//Falls die letzte Mausposition weiter links liegt als der Text im EditControl wird der Textcursor an die erste Stelle gesetzt
			if(m_iTextCursorPosition != 0)
			{
				if(m_iTextCursorPosition > -1 )
				{
					//Sollte der Textcursor schon gesetzt wurden sein, wird er erst heraus gel�scht
					mp_c_etyLabelText->set_Content(mp_c_etyLabelText->get_Content().erase(m_iTextCursorPosition,1));
				}
				mp_c_etyLabelText->set_Content("|" + mp_c_etyLabelText->get_Content());
				//...
			}

			m_iTextCursorPosition = 0;
		}
		else if(ety::CMouse::get_Position().x > (mp_c_etyLabelText->get_RealPosition().x + mp_c_etyLabelText->get_sfTextObject()->getGlobalBounds().width))
		{
			//Das Gleiche wie oben nur, dass die Mausposition weiter rechts liegt als der Text im EditControl
			if(m_iTextCursorPosition != mp_c_etyLabelText->get_Content().size() - 1)
			{
				if(m_iTextCursorPosition > -1 )
				{
					mp_c_etyLabelText->set_Content(mp_c_etyLabelText->get_Content().erase(m_iTextCursorPosition,1));
				}

				mp_c_etyLabelText->set_Content(mp_c_etyLabelText->get_Content() + "|");
				//...
			}

			m_iTextCursorPosition = mp_c_etyLabelText->get_Content().size() - 1;
		}
		else
		{
			//Der letzte Fall, das "in" den Text des EditControls geklickt wurde
			std::string strNewContent = mp_c_etyLabelText->get_Content();
			float fMouseLocalPosition = mp_c_etyLabelText->get_RealPosition().x;
			float fCurrentMousePostion = float(ety::CMouse::get_Position().x);
			int iLabelContentSize = mp_c_etyLabelText->get_Content().size() - 1;
			int iLoop = -1;
			bool bBold = false;

			if(mp_c_etyLabelText->get_TextStyle() % 2 == 1)
			{
				bBold = true;
			}

			//Es wird in einer Schleife einfach die Breite der Buchstaben im Text aufaddiert, bis sie zusammen mit der Position des Textes gr��er der Mausposition sind
			while(fMouseLocalPosition < fCurrentMousePostion && iLoop != iLabelContentSize)
			{
				iLoop++;
				fMouseLocalPosition = fMouseLocalPosition + 
					mp_c_etyLabelText->get_Textfont().getGlyph(mp_c_etyLabelText->get_Content()[iLoop],mp_c_etyLabelText->get_Charactersize().x,bBold).bounds.width;
			}

			if(m_bFocused == true)
			{
				strNewContent.erase(m_iTextCursorPosition,1);
			}
			
			m_iTextCursorPosition = iLoop;
			strNewContent.insert(m_iTextCursorPosition,"|");
			mp_c_etyLabelText->set_Content(strNewContent);
		}

		//Damit der Textcursor "blinkt" muss noch der Textwriteout f�r das Label des EditControls aktiviert werden
		mp_c_etyLabelText->set_Textwriteout(true);
	}
	else
	{
		// Falls der Focus auf false gesetzt wird, wird einfach das EditControl "abgew�hlt"
		mp_c_etyDialogParentDialog->get_DialogManager()->change_FocusedDialogitem(NULL);
		mp_c_etyLabelText->set_Textwriteout(false);
		if(mp_c_etyLabelText->get_Content().size() == 1)
		{
			mp_c_etyLabelText->set_Content("");
		}
		else
		{
			mp_c_etyLabelText->get_Content().erase(m_iTextCursorPosition,m_iTextCursorPosition + 1);
		}
	}

	m_bFocused	=	bFocus;
}



//Get-Methoden
int										ety::CEditControl::get_TextCursorPosition				(void)
{
	return m_iTextCursorPosition;
}
	
std::string								ety::CEditControl::get_EditControlContent				(void)
{
	if(m_iTextCursorPosition >= 0)
	{
		return mp_c_etyLabelText->get_Content().erase(m_iTextCursorPosition,1);
	}

	return mp_c_etyLabelText->get_Content();
}

ety::CLabel*							ety::CEditControl::get_Text								(void)
{
	return	mp_c_etyLabelText;
}

ety::CPictureControl*					ety::CEditControl::get_Background						(void)
{
	return mp_c_etyPictureControlBackground;
}

ety::VariableType::en_etyVariableType	ety::CEditControl::get_InputType						(void)
{
	return m_en_etyVariableTypePossibleInputType;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CEDITCONTROL.CPP							///////////
///////////////////////////////////////////////////////////////////////////////////////////////