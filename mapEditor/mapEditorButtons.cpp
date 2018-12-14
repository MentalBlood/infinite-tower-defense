void mapEditorResetButtonPress()
{ mapEditorMap->reset(); }

bool checkFileWithSuchNameExistance(std::string fileNameToCheck)
{
	const char path[128] = "maps";
	DIR *dir = opendir(path);
	if (!dir) Closed();

	struct dirent *entery;
	char fileName[256];
	while ((entery = readdir(dir)) != NULL)
	{
		sprintf(fileName,"%s/%s", path, entery->d_name);
		char *c = fileName;
		while (*c) ++c;
		while (*c != '.') --c;
		++c;
		if (*c != 't') continue;
		++c;
		if (*c != 'd') continue;
		++c;
		if (*c != 'm') continue;
		++c;
		if (*c) continue;

		if (checkMapFile(fileName))
		{
			//making user friendly name of map (without path and extension)
			char userFriendlyMapName[128];
			strcpy(userFriendlyMapName, entery->d_name);
			c = userFriendlyMapName;
			while (*c) ++c;
			while (*c != '.') --c;
			*c = 0;
			if (!strcmp(fileNameToCheck.data(), userFriendlyMapName))
				return true;
		}
	}

	closedir(dir);
	return false;
}

void mapEditorCloseFileAlreadyExistsQuestion()
{
	delete mapEditorFileAlreadyExistsQuestion;
	mapEditorFileAlreadyExistsQuestion = NULL;
}

void mapEditorCloseFileNameDialog()
{
	delete mapEditorFileNameDialog;
	mapEditorFileNameDialog = NULL;
}

std::string saveFileName;

void mapEditorSaveMap()
{
	mapEditorMap->save(("maps/" + saveFileName + ".tdm").data());
	mapEditorCloseFileNameDialog();
	if (mapEditorFileAlreadyExistsQuestion)
		mapEditorCloseFileAlreadyExistsQuestion();
	if (mapEditorFileNameDialog)
		mapEditorCloseFileNameDialog();
}

void mapEditorTryToSaveMap(std::string fileName)
{
	saveFileName = fileName;
	if (checkFileWithSuchNameExistance(fileName))
		mapEditorFileAlreadyExistsQuestion =
			new Question(mapEditorSaveMap, mapEditorCloseFileAlreadyExistsQuestion, "file with such name\n\nalready exists",
						 "Overwrite", "Cancel",
						 messageFont,
						 0.3, 0.3, 0.4, 0.4, 4,
						 sf::Color(255, 255, 255), sf::Color(192, 64, 64), sf::Color(0, 0, 0), 2);
	else
		mapEditorSaveMap();
}

void mapEditorCloseWrongMapMessage()
{
	delete mapEditorWrongMapMessage;
	mapEditorWrongMapMessage = NULL;
}

void mapEditorSaveButtonPress()
{
	if (!mapEditorMap->check())
	{
		mapEditorWrongMapMessage = new Message(	mapEditorCloseWrongMapMessage, "wrong map\n\ncan not save", "OK",
												messageFont,
												0.3, 0.3, 0.4, 0.4, 4,
												sf::Color(255, 255, 255), sf::Color(192, 64, 64), sf::Color(0, 0, 0));
		return;
	}
	if (mapEditorFileNameDialog) delete mapEditorFileNameDialog;
	mapEditorFileNameDialog = new EnterFileNameDialog(	"Enter file name:", mapEditorTryToSaveMap, 0.3, 0.4, 0.4, 0.2, enterFileNameFont,
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
	mapEditorButtons.push_back(TwoConditionButton(	nothing, mapEditorResetButtonPress, "reset", mapEditorButtonsFont,
													sf::Color(255, 196, 64), sf::Color(0, 0, 64, 128), sf::Color(64, 64, 128),
													0.75, 0.05, 0.15, 0.08, 2));
	mapEditorButtons.push_back(TwoConditionButton(	nothing, mapEditorSaveButtonPress, "save", mapEditorButtonsFont,
													sf::Color(255, 128, 255), sf::Color(0, 64, 0, 128), sf::Color(64, 128, 64),
													0.75, 0.15, 0.15, 0.08, 2));
	mapEditorButtons.push_back(TwoConditionButton(	nothing, mapEditorShowHelpScreen, "?", helpButtonFont,
													sf::Color(255, 196, 64), sf::Color(0, 0, 64, 128), sf::Color(64, 64, 128),
													0.01, 0.01, 0.03, 0.06, 1, 4));
}
