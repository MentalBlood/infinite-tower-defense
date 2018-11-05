void mapEditorResetButtonPress()
{ mapEditorMap->reset(); }

void mapEditorSaveMap(std::string fileName)
{ mapEditorMap->save(fileName.data()); }

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
												0.3, 0.3, 0.4, 0.4,
												sf::Color(255, 255, 255), sf::Color(255, 0, 0, 128), sf::Color(0, 0, 0));
		return;
	}
	if (mapEditorFileNameDialog) delete mapEditorFileNameDialog;
	mapEditorFileNameDialog = new EnterFileNameDialog(	"Enter file name:", mapEditorSaveMap, 0.3, 0.4, 0.4, 0.2, "fonts/enterFileNameFont.otf",
														sf::Color(255, 128, 255), sf::Color(196, 64, 196),
														sf::Color(0, 64, 0, 128), sf::Color(64, 128, 64));
	mapEditorFileNameDialog->updatePositionAndSize();
}

std::vector<TwoConditionButton> mapEditorButtons;

void updateMapEditorButtons()
{
	for (unsigned int i = 0; i < mapEditorButtons.size(); i++)
		mapEditorButtons[i].updatePositionAndSize();
}

void setMapEditorButtons()
{
	mapEditorButtons.push_back(TwoConditionButton(	nothing, mapEditorResetButtonPress, "reset", "fonts/mapEditorButtonsFont.otf",
													sf::Color(255, 196, 64), sf::Color(0, 0, 64, 128), sf::Color(64, 64, 128),
													0.75, 0.05, 0.15, 0.08));
	mapEditorButtons.push_back(TwoConditionButton(	nothing, mapEditorSaveButtonPress, "save", "fonts/mapEditorButtonsFont.otf",
													sf::Color(255, 128, 255), sf::Color(0, 64, 0, 128), sf::Color(64, 128, 64),
													0.75, 0.15, 0.15, 0.08));
}
