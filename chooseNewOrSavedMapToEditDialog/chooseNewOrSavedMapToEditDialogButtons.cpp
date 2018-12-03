TwoConditionButton *chooseNewOrSavedMapToEditDialogNewMapButton,
				   *chooseNewOrSavedMapToEditDialogSavedMapButton;

void chooseNewOrSavedMapToEditDialogCloseWrongFileNameMessage()
{
	delete chooseNewOrSavedMapToEditDialogWrongFileNameMessage;
	chooseNewOrSavedMapToEditDialogWrongFileNameMessage = NULL;
}

void chooseNewOrSavedMapToEditDialogCloseChooseMapDialog()
{
	delete chooseNewOrSavedMapToEditDialogSavedMapChooseFileDialog;
	chooseNewOrSavedMapToEditDialogSavedMapChooseFileDialog = NULL;
}

void chooseNewOrSavedMapToEditDialogTryOpenMap(std::string fileName)
{
	if (checkMapFile(("maps/" + fileName + ".tdm").data()))
	{
		chooseNewOrSavedMapToEditDialogCloseChooseMapDialog();
		startMapEditor(("maps/" + fileName + ".tdm").data());
	}
	else
	{
		chooseNewOrSavedMapToEditDialogWrongFileNameMessage =
			new Message(chooseNewOrSavedMapToEditDialogCloseWrongFileNameMessage, "wrong map file\n\ncan not load", "OK",
						messageFont,
						0.3, 0.3, 0.4, 0.4, 4,
						sf::Color(255, 255, 255), sf::Color(192, 64, 64), sf::Color(0, 0, 0));
	}
}

void chooseNewOrSavedMapToEditDialogSavedMapButtonPress()
{
	if (chooseNewOrSavedMapToEditDialogSavedMapChooseFileDialog)
		delete chooseNewOrSavedMapToEditDialogSavedMapChooseFileDialog;
	chooseNewOrSavedMapToEditDialogSavedMapChooseFileDialog = 
		new List("Select map to edit:", chooseNewOrSavedMapToEditDialogTryOpenMap,
				 selectMapScreenFont, selectMapScreenFont,
				 0.25, 0.25, 0.5, 0.5, 4,
				 sf::Color(192, 0, 0), sf::Color(215, 215, 215),
				 sf::Color(32, 32, 32), sf::Color(0, 0, 0), sf::Color(192, 0, 0)); ;
	fillMapsList(chooseNewOrSavedMapToEditDialogSavedMapChooseFileDialog);
	chooseNewOrSavedMapToEditDialogSavedMapChooseFileDialog->updateItems();
}

void updateChooseNewOrSavedMapToEditDialogButtons()
{
	chooseNewOrSavedMapToEditDialogNewMapButton->updatePositionAndSize();
	chooseNewOrSavedMapToEditDialogSavedMapButton->updatePositionAndSize();
}

void setChooseNewOrSavedMapToEditDialogButtons()
{
	chooseNewOrSavedMapToEditDialogNewMapButton = 
		new TwoConditionButton(	nothing, startNewMapSettings,
								"New map", chooseNewOrSavedMapToEditDialogFont,
								sf::Color(255, 255, 255), sf::Color(0, 0, 64), sf::Color(0, 0, 192),
								0.05, 0.05, 0.425, 0.90, 1);
	chooseNewOrSavedMapToEditDialogSavedMapButton = 
		new TwoConditionButton(	nothing, chooseNewOrSavedMapToEditDialogSavedMapButtonPress,
								"Load map", chooseNewOrSavedMapToEditDialogFont,
								sf::Color(255, 255, 255), sf::Color(64, 0, 0), sf::Color(192, 0, 0),
								0.525, 0.05, 0.425, 0.90, 1);
}
