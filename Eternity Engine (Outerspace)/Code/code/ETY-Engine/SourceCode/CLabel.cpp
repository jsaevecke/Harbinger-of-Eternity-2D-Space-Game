///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CLABEL.CPP									///////////
///////////////////////////////////////////////////////////////////////////////////////////////

//Eternity-Includes
#include "CLabel.hpp"
#include "CEditControl.hpp"


														ety::CLabel::CLabel						(void)
														:mp_iAllocatedIndices					(NULL)
{	
	mp_c_etyDialogitemParentDialogitem	=	NULL;
	mp_c_etyDialogParentDialog			=	NULL;
}

														ety::CLabel::~CLabel					(void)
{
}


														ety::CLabel::CLabel						(
																								  std::string strCustomID, std::string strContent, float fCharactersize, 
																								  ety::Color c_etyColorTextcolor, sf::Vector2f c_sfVector2fPosition, 
																								  CDialogitem* p_c_etyDialogitemParent, 
																								  CDialog* p_c_etyDialogParentDialog
																								)				
				:m_en_etyTextwriteoutStyle														(TextwriteoutStyle::enNONE)
				,m_fTextwriteoutDuration														(0.f)
				,m_strContent																	(strContent)
				,m_c_etyColorTextcolor															(c_etyColorTextcolor)
				,m_bTextwriteout																(false)
				,m_iDrawnCharacter																(0)
				,m_iPastFrametime																(0)
				,m_iPastFrames																	(0)
{
	sf::VideoMode c_sfVideoModeGamesettings	=	p_c_etyDialogParentDialog->get_VideoMode();

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

	m_en_etyDialogitemType						=	DialogitemType::enLABEL;

	m_c_sfTextLabelText.setFont(p_c_etyDialogParentDialog->get_DialogManager()->get_StandardFont());
	mp_iAllocatedIndices = NULL;

	c_sfVector2fPosition.x						=	c_sfVideoModeGamesettings.width*float(c_sfVector2fPosition.x/1680.f);
	c_sfVector2fPosition.y						=	c_sfVideoModeGamesettings.height*float(c_sfVector2fPosition.y/1050.f);

	m_c_sfVector2uCharactersize.y				=	unsigned int(c_sfVideoModeGamesettings.height*float(fCharactersize/1050.f));
	m_c_sfVector2uCharactersize.x				=	unsigned int(c_sfVideoModeGamesettings.width*float(fCharactersize/1680.f));

	m_c_sfVector2fPosition						=	c_sfVector2fPosition;
	/*if(bRealPosition == true)
	{
		m_c_sfVector2fRealPosition			=	c_sfVector2fPosition;
	}
	else
	{
		m_c_sfVector2fPosition				=	c_sfVector2fPosition;
	}*/

	calculate_Positions(false);
		

	//Sollte der Textwriteoutstyle COD sein , wird der Aufruf der Funktion set_AllocatedIndices
	//ben�tigt um eine richtige Darstellung des Textwriteouts zu garantieren
	//N�heres in der write_Text-Funktion
	if(m_bTextwriteout == true && m_en_etyTextwriteoutStyle == TextwriteoutStyle::enCOD)
	{
			set_AllocatedIndices();
	}
	else
	{
		mp_iAllocatedIndices = NULL;
	}

	m_mapEventSounds = mp_c_etyDialogParentDialog->get_DialogManager()->get_StandardSounds(m_en_etyDialogitemType);

	m_c_sfTextLabelText.setString(m_strContent);

	//Die H�he und Breite des Labels wird an das Rectangle des sf::Text angepasst
	m_fHeight					=	m_c_sfTextLabelText.getGlobalBounds().height;
	m_fWidth					=	m_c_sfTextLabelText.getGlobalBounds().width;
}


void													ety::CLabel::adjust_SizeToResolution	( const sf::VideoMode& c_sfVideoModeNewSettings, const sf::VideoMode& c_sfVideoModeOldSettings )
{
	m_c_sfVector2uCharactersize.x	=	check_ValuesAfterDecimalPoint(m_c_sfVector2uCharactersize.x * (float(c_sfVideoModeNewSettings.width)/float(c_sfVideoModeOldSettings.width)));
	m_c_sfVector2uCharactersize.y	=	check_ValuesAfterDecimalPoint(m_c_sfVector2uCharactersize.y * (float(c_sfVideoModeNewSettings.height)/float(c_sfVideoModeOldSettings.height)));

	m_c_sfVector2fPosition.x	=	m_c_sfVector2fPosition.x * (float(c_sfVideoModeNewSettings.width)/float(c_sfVideoModeOldSettings.width));
	m_c_sfVector2fPosition.y	=	m_c_sfVector2fPosition.y * (float(c_sfVideoModeNewSettings.height)/float(c_sfVideoModeOldSettings.height));

	update_Dialogitem(0);
}


bool													ety::CLabel::check_MouseCoordinates		(void)
{
	//Es wird gepr�ft ob die Maus in dem Rect des sf::Text-Objekt ist
	if(m_bVisibility == true)
	{
		sf::Vector2f c_sfVector2fMouseCoordinates;
		c_sfVector2fMouseCoordinates.x = float(ety::CMouse::get_Position().x);
		c_sfVector2fMouseCoordinates.y = float(ety::CMouse::get_Position().y);

		return m_c_sfTextLabelText.getGlobalBounds().contains(c_sfVector2fMouseCoordinates);
	}
	
	return false;
}


bool													ety::CLabel::draw_Dialogitem			(sf::RenderTexture* p_c_sfRenderTextureScene)
{
	if(m_strCustomID == "SelectedProfileLabel")
	{
		int i = 0;
	}

	if(m_bVisibility == true)
	{
		(*p_c_sfRenderTextureScene).draw(m_c_sfTextLabelText);
		
		return true;
	}

	return false;
}


void													ety::CLabel::modificate_Colorfilter		(sf::Vector3f c_sfVector3fFactors)
{
	m_c_etyColorTextcolor.r	*= c_sfVector3fFactors.x;
	m_c_etyColorTextcolor.g	*= c_sfVector3fFactors.y;
	m_c_etyColorTextcolor.b	*= c_sfVector3fFactors.z;

	update_Dialogitem(0);
}


void													ety::CLabel::update_Dialogitem			(const sf::Uint32& uiFrameTime)
{
	if(mp_c_etyDialogParentDialog->get_DialogManager()->check_IsDialogitemActive(this) == false)
	{
		m_bActive = false;
	}
	else
	{
		m_bActive = m_bInternActive;
	}


	//Aktualisieren der Attribute
	m_c_sfTextLabelText.setColor(m_c_etyColorTextcolor.get_sfColor());

	//Das Label wird nur skaliert und nicht die Charactersize angegeben, da es sonst bei manchen Aufl�sungen
	//Zu Darstellungsfehlern kommen kann
	m_c_sfTextLabelText.setScale((m_c_sfVector2uCharactersize.x/30.f),(m_c_sfVector2uCharactersize.y/30.f));
	//m_c_sfTextLabelText.setCharacterSize(m_uiCharactersize);
	
	std::string strSFContent	=	m_c_sfTextLabelText.getString();
	m_c_sfTextLabelText.setString(strSFContent + "�");
	m_fHeight					=	m_c_sfTextLabelText.getGlobalBounds().height;
	m_c_sfTextLabelText.setString(strSFContent);
	m_fWidth					=	m_c_sfTextLabelText.getGlobalBounds().width;


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

	m_c_sfTextLabelText.setPosition(m_c_sfVector2fRealPosition);

	if(m_bTextwriteout == true && m_fTextwriteoutDuration > 0)
	{
		write_Text(uiFrameTime);
	}
}


void													ety::CLabel::write_Text					(const sf::Uint32& uiFrameTime)
{
	//Diese Funktion sorgt f�r die richtige Darstellung des Textwriteouts
	//Ein Textwriteout ist sozusagen eine Animation f�r den darzustellenden Text
	if(m_iDrawnCharacter == m_strContent.size()+1)
	{
		m_bTextwriteout = false;
	}

	if(m_en_etyTextwriteoutStyle == TextwriteoutStyle::enSTANDARD)
	{		
		//Der STANDARD-Sytle zeichnet in bestimmten Zeitabschnitten (abh�ngig von der Frame-Time und der Textwriteout-Duration)
		//immer einen Buchstaben des Contents mehr, bis der Content komplett ausgeschrieben ist
		if(m_iDrawnCharacter < int(get_Content().length()))
		{
			//Die Frametime ist die Zeit, die das Programm f�r einen Durchlauf bis zum n�chsten Frame braucht/gebraucht hat
			if(uiFrameTime > 0)
			{
				m_iPastFrametime = (m_iPastFrametime + int(uiFrameTime));
				
				//Immer wenn eine gewi�e Zeit vorr�ber ist, soll dem Label ein weiterer Buchstabe
				//des Contents hinzugef�gt werden
				if(m_iPastFrametime >= get_TextwriteoutDuration()/m_strContent.length())
				{
					std::string strNewTextcontent;

					for(int iLoop = 0; iLoop <= m_iDrawnCharacter; iLoop++)
					{
						strNewTextcontent = strNewTextcontent + m_strContent[iLoop];
					}

					set_sfTextObjectContent(strNewTextcontent);
					
					//PastFrametime behandelt hier die vergangene Zeit
					m_iPastFrametime = 0;
					//DrawnCharacter behandelt hier die ausgeschriebenen Buchstaben
					m_iDrawnCharacter++;
				}
			}
		}
	}
	else if(m_en_etyTextwriteoutStyle == TextwriteoutStyle::enCOD)
	{
		//Der COD-Textwriteoutstyle, zeigt gleich alle Buchstaben des Contents an,
		//nur sie nehmen in rascher Reihenfolge zuf�llige Buchstaben/Werte an
		//Doch nach und nach kristallisieren sich die richtigen Buchstaben heraus
		//Welche Buchstaben sich herauskristallisieren sollen, wird per Zufall bestimmt
		//Weshalb die Funktion set_AllocatedIndices ben�tigt wird, denn diese legt vorher
		//per Zufallsprinzip diese Reihenfolge fest
		if(m_iDrawnCharacter <= int(m_strContent.length()))
		{
			if(uiFrameTime > 0)
			{
				m_iPastFrametime = (m_iPastFrametime + int(uiFrameTime));

				//Es sollen nicht bei jedem Durchlauf neue Zufallsbuchstaben gezeichnet werden
				//Da dies sonst viel zu schnell und dadurch unsch�n aussehen w�rde
				if( (m_iPastFrames % 6 != false) )
				{
					std::string strNewTextcontent = m_strContent;

					bool bContinue = false;

					for(int iOuterLoop = 0; iOuterLoop < int(m_strContent.length()); iOuterLoop++)
					{
						bContinue = false;
						//In dieser Schleife werden die "richtigen" Buchstaben in den String geschrieben
						for(int iInnerLoop = 0; iInnerLoop < m_iDrawnCharacter; iInnerLoop++)
						{
							if(mp_iAllocatedIndices[iInnerLoop] == iOuterLoop)
							{
								bContinue = true;
								break;
							}
						}

						if(bContinue == true)
						{
							continue;
						}
						else
						{
							//Hier werden die Zufallsbuchstaben in den String geschrieben
							strNewTextcontent[iOuterLoop] = (rand () % ((122 + 1) - 48)) + 48;
						}
					}

					set_sfTextObjectContent(strNewTextcontent);
				}
					
				//Zu einem bestimmten Zeitpunkt soll die Frametime zur�ckgesetzt und bei n�chsten Durchlauf
				//ein "richtiger" Buchstabe mehr gezeichnet werden
				if(m_iPastFrametime >= get_TextwriteoutDuration()/m_strContent.length())
				{
					m_iPastFrametime = 0;
					m_iDrawnCharacter++;
				}
				m_iPastFrames++;
			}
		}					
	}
	else if(m_en_etyTextwriteoutStyle == TextwriteoutStyle::enEDITCONTROLCURSORBLINK)
	{
		//Dies ist genau genommen kein richtiges Writeout, sondern eher nur das Blinken des TextCursors in einem EditControl
		CEditControl* p_c_etyEditControlParentEditControl	=	static_cast< CEditControl* >(mp_c_etyDialogitemParentDialogitem);

		m_iPastFrametime = m_iPastFrametime + int(uiFrameTime);

		if(m_iPastFrametime <= m_fTextwriteoutDuration)
		{
			if(m_strContent.size() < 1)
			{
				m_strContent = '|';
			}
			else
			{
				m_strContent.erase(p_c_etyEditControlParentEditControl->get_TextCursorPosition(),1);
				m_strContent.insert(p_c_etyEditControlParentEditControl->get_TextCursorPosition(),"|");
			}
		}
		else if(m_iPastFrametime >= m_fTextwriteoutDuration && m_iPastFrametime <= m_fTextwriteoutDuration * 2 )
		{
			if(m_strContent.size() < 1)
			{
				m_strContent = ' ';
			}
			else
			{
				m_strContent.erase(p_c_etyEditControlParentEditControl->get_TextCursorPosition(),1);
				m_strContent.insert(p_c_etyEditControlParentEditControl->get_TextCursorPosition()," ");
			}	
		}
		else
		{
			m_iPastFrametime = 0;
		}

		set_sfTextObjectContent(m_strContent);
	}
	else
	{
		//Ankerpunkt: M�glichkeit weitere TextwriteoutStyles austruformulieren
	}
}



//Set-Methoden
void													ety::CLabel::set_Textwriteout			(bool bTextwriteout)
{
	m_bTextwriteout				=	bTextwriteout;

	m_iDrawnCharacter			=	0;
	m_iPastFrametime			=	0;
	m_iPastFrames				=	0;

	if(mp_iAllocatedIndices != NULL)
	{
		delete [] mp_iAllocatedIndices;
		mp_iAllocatedIndices = NULL;
	}

	if(m_en_etyTextwriteoutStyle == TextwriteoutStyle::enCOD)
	{
		set_AllocatedIndices();
	}
}

void													ety::CLabel::set_TextwriteoutDuration	(float fDuration)
{
	m_fTextwriteoutDuration		=	fDuration;
	
	m_iDrawnCharacter			=	0;
	m_iPastFrametime			=	0;
	m_iPastFrames				=	0;

	if(mp_iAllocatedIndices != NULL)
	{
		delete [] mp_iAllocatedIndices;
		mp_iAllocatedIndices = NULL;
	}

	if(m_en_etyTextwriteoutStyle == TextwriteoutStyle::enCOD)
	{
		set_AllocatedIndices();
	}
}

void													ety::CLabel::set_AllocatedIndices		(void)
{
	//Aus dem Zeiger wird ein 1D-Array gemacht, mit der Gr��e des Contents und jedes Element wird mit einer
	//Zufallszahl zwischen 0 und der Gr��e des Contents belegt, jede Zahl darf aber nur einmal vorkommen
	//N�heres zum COD-Textwriteout in der write_Text-Funktion

	mp_iAllocatedIndices = new int [m_strContent.length()];

	for(int iOuterLoop = 0; iOuterLoop < int(m_strContent.length()); iOuterLoop++)
	{
		int iNewRandomIndex = 0;
		bool bContinue = false;
		while(bContinue == false)
		{
			iNewRandomIndex = (rand () % m_strContent.length());

			bContinue = true;

			for(int iLoop = 0; iLoop < int(m_strContent.length()); iLoop++)
			{
				if(iNewRandomIndex == get_AllocatedIndices()[iLoop] || m_strContent[iNewRandomIndex] == 10)
				{
					bContinue = false;
					break;
				}
			}
		}

		mp_iAllocatedIndices[iOuterLoop] = iNewRandomIndex;
	}
}

void													ety::CLabel::set_Charactersize			(sf::Vector2u c_sfVector2uCharactersize)
{
	m_c_sfVector2uCharactersize	=	c_sfVector2uCharactersize;

	m_fHeight					=	m_c_sfTextLabelText.getGlobalBounds().height;
	m_fWidth					=	m_c_sfTextLabelText.getGlobalBounds().width;
}

void													ety::CLabel::set_Textcolor				(ety::Color c_etyColorTextcolor)
{
	m_c_etyColorTextcolor			=	c_etyColorTextcolor;
	m_c_sfTextLabelText.setColor(m_c_etyColorTextcolor.get_sfColor());
}

void													ety::CLabel::set_Textfont				(sf::Font c_sfFontTextfont)
{
	m_c_sfTextLabelText.setFont(c_sfFontTextfont);

	m_fHeight					=	m_c_sfTextLabelText.getGlobalBounds().height;
	m_fWidth					=	m_c_sfTextLabelText.getGlobalBounds().width;
}

void													ety::CLabel::set_TextStyle				(sf::Uint32 sf_Uint32Textstyle)
{
	/*
	0	=	Regular
	1	=	Bold
	2	=	Italic
	3	=	Bold&Italic
	4	=	Underlined
	5	=	Bold&Underlined
	6	=	Italic&Underlined
	7	=	Bold&Italic&Underlined
	*/
	m_c_sfTextLabelText.setStyle(sf_Uint32Textstyle);
}

void													ety::CLabel::set_sfTextObject			(sf::Text c_sfTextContent)
{	
	m_c_sfTextLabelText				=	c_sfTextContent;

	m_fHeight					=	m_c_sfTextLabelText.getGlobalBounds().height;
	m_fWidth					=	m_c_sfTextLabelText.getGlobalBounds().width;

	m_iDrawnCharacter			=	0;
	m_iPastFrametime			=	0;
	m_iPastFrames				=	0;

	if(mp_iAllocatedIndices != NULL)
	{
		delete [] mp_iAllocatedIndices;
		mp_iAllocatedIndices = NULL;
	}

	if(m_en_etyTextwriteoutStyle == TextwriteoutStyle::enCOD)
	{
		set_AllocatedIndices();
	}
}

void													ety::CLabel::set_sfTextObjectContent	(std::string strTextContent)
{	
	if(strTextContent != m_c_sfTextLabelText.getString())
	{
		m_c_sfTextLabelText.setString(strTextContent);

		m_fHeight					=	m_c_sfTextLabelText.getGlobalBounds().height;
		m_fWidth					=	m_c_sfTextLabelText.getGlobalBounds().width;
	}
}

void													ety::CLabel::set_TextwriteoutStyle		(enum ety::TextwriteoutStyle::en_etyTextwriteoutStyle en_etyTextwriteoutStyle)
{
	m_en_etyTextwriteoutStyle		=	en_etyTextwriteoutStyle;

	if(en_etyTextwriteoutStyle != TextwriteoutStyle::enEDITCONTROLCURSORBLINK)
	{
		m_c_sfTextLabelText.setString("");
	}

	m_iDrawnCharacter			=	0;
	m_iPastFrametime			=	0;
	m_iPastFrames				=	0;

	if(mp_iAllocatedIndices != NULL)
	{
		delete [] mp_iAllocatedIndices;
		mp_iAllocatedIndices = NULL;
	}

	if(m_en_etyTextwriteoutStyle == TextwriteoutStyle::enCOD)
	{
		set_AllocatedIndices();
	}
}

void													ety::CLabel::set_Content				(std::string strContent)
{
	m_strContent					=	strContent;

	m_iDrawnCharacter				=	0;
	m_iPastFrametime				=	0;
	m_iPastFrames					=	0;

	if(mp_iAllocatedIndices != NULL)
	{
		delete [] mp_iAllocatedIndices;
		mp_iAllocatedIndices = NULL;
	}

	if(m_en_etyTextwriteoutStyle == TextwriteoutStyle::enCOD)
	{
		set_AllocatedIndices();
	}

	if(m_bTextwriteout == true && m_fTextwriteoutDuration > 0.f && m_en_etyTextwriteoutStyle != TextwriteoutStyle::enEDITCONTROLCURSORBLINK)
	{
		write_Text(100);
	}
	else
	{
		m_c_sfTextLabelText.setString(strContent);

		m_fHeight						=	m_c_sfTextLabelText.getGlobalBounds().height;
		m_fWidth						=	m_c_sfTextLabelText.getGlobalBounds().width;
	}
}

void													ety::CLabel::set_Transperancy			(sf::Uint8 sfUint8Transperancy)
{
	m_c_etyColorTextcolor.a		=	sfUint8Transperancy;
}

void													ety::CLabel::set_RealPosition			(sf::Vector2f c_sfVector2fRealPosition)
{
	m_c_sfVector2fRealPosition	=	c_sfVector2fRealPosition;

	m_c_sfTextLabelText.setPosition(m_c_sfVector2fRealPosition);
}



//Get-Methoden
bool													ety::CLabel::get_Textwriteout			(void)
{
	return	m_bTextwriteout;
}

float													ety::CLabel::get_TextwriteoutDuration	(void)
{
	return	m_fTextwriteoutDuration;
}

int*													ety::CLabel::get_AllocatedIndices		(void)
{
	return mp_iAllocatedIndices;
}

sf::Vector2u											ety::CLabel::get_Charactersize			(void)
{
	return m_c_sfVector2uCharactersize;
}

ety::Color												ety::CLabel::get_Textcolor				(void)
{
	return	m_c_etyColorTextcolor;
}

sf::Font												ety::CLabel::get_Textfont				(void)
{
	return	m_c_sfTextLabelText.getFont();
}

sf::Uint32												ety::CLabel::get_TextStyle				(void)
{
	return m_c_sfTextLabelText.getStyle();
}

sf::Text*	const										ety::CLabel::get_sfTextObject			(void)
{
	return	&m_c_sfTextLabelText;
}

std::string												ety::CLabel::get_Content				(void)	
{
	return	m_strContent;
}

enum ety::TextwriteoutStyle::en_etyTextwriteoutStyle	ety::CLabel::get_TextwriteoutStyle		(void)
{
	return	m_en_etyTextwriteoutStyle;
}
	

///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CLABEL.CPP									///////////
///////////////////////////////////////////////////////////////////////////////////////////////