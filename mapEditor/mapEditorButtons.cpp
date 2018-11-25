void mapEditorResetButtonPress()
{ mapEditorMap->reset(); }

void mapEditorSaveMap(std::string fileName)
{
	mapEditorMap->save(("maps/" + fileName + ".tdm").data());
}

void mapEditorCloseWrongMapMessage()
{
	delete mapEditorWrongMapMessage;
	mapEditorWrongMapMessage = NULL;
}

void mapEditorCloseFileNameDialog()
{
	delete mapEditorFileNameDialog;
	mapEditorFileNameDialog = NULL;
}

void mapEditorSaveButtonPress()
{
	if (!mapEditorMap->check())
	{
		mapEditorWrongMapMessage = new Message(	mapEditorCloseWrongMapMessage, "wrong map\n\ncan not save", "OK",
												"fonts/messageFont.otf",
												0.3, 0.3, 0.4, 0.4, 4,
												sf::Color(255, 255, 255), sf::Color(192, 64, 64), sf::Color(0, 0, 0));
		return;
	}
	if (mapEditorFileNameDialog) delete mapEditorFileNameDialog;
	mapEditorFileNameDialog = new EnterFileNameDialog(	"Enter file name:", mapEditorSaveMap, 0.3, 0.4, 0.4, 0.2, "fonts/enterFileNameFont.otf",
														sf::Color(255, 128, 255), sf::Color(196, 64, 196),
														sf::Color(16, 64, 16), sf::Color(64, 128, 64));
}

std::list<TwoConditionButton> mapEditorButtons;

void updateMapEditorButtons()
{
	for (std::list<TwoConditionButton>::iterator i = mapEditorButtons.begin();
			i != mapEditorButtons.end(); i++)
		i->updatePositionAndSize();
}

void setMapEditorButtons()
{
	mapEditorButtons.push_back(TwoConditionButton(	nothing, mapEditorResetButtonPress, "reset", "fonts/mapEditorButtonsFont.otf",
													sf::Color(255, 196, 64), sf::Color(0, 0, 64, 128), sf::Color(64, 64, 128),
													0.75, 0.05, 0.15, 0.08, 2));
	mapEditorButtons.push_back(TwoConditionButton(	nothing, mapEditorSaveButtonPress, "save", "fonts/mapEditorButtonsFont.otf",
													sf::Color(255, 128, 255), sf::Color(0, 64, 0, 128), sf::Color(64, 128, 64),
													0.75, 0.15, 0.15, 0.08, 2));
	mapEditorButtons.push_back(TwoConditionButton(	nothing, mapEditorShowHelpScreen, "?", "fonts/helpButtonFont.otf",
													sf::Color(255, 196, 64), sf::Color(0, 0, 64, 128), sf::Color(64, 64, 128),
													0.01, 0.01, 0.03, 0.06, 1, 4));
}
