TwoConditionButton *chooseNewOrSavedMapToEditDialogNewMapButton,
				   *chooseNewOrSavedMapToEditDialogSavedMapButton;

void chooseNewOrSavedMapToEditDialogCloseWrongFileNameMessage()
{
	delete chooseNewOrSavedMapToEditDialogWrongFileNameMessage;
	chooseNewOrSavedMapToEditDialogWrongFileNameMessage = NULL;
}

void chooseNewOrSavedMapToEditDialogCloseSavedMapFileNameDialog()
{
	delete chooseNewOrSavedMapToEditDialogSavedMapFileNameDialog;
	chooseNewOrSavedMapToEditDialogSavedMapFileNameDialog = NULL;
}

void chooseNewOrSavedMapToEditDialogTryOpenMap(std::string fileName)
{
	if (checkMapFile(("maps/" + fileName + ".tdm").data()))
	{
		chooseNewOrSavedMapToEditDialogCloseSavedMapFileNameDialog();
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
	if (chooseNewOrSavedMapToEditDialogSavedMapFileNameDialog)
		delete chooseNewOrSavedMapToEditDialogSavedMapFileNameDialog;
	chooseNewOrSavedMapToEditDialogSavedMapFileNameDialog = 
		new EnterFileNameDialog("Enter file name:", chooseNewOrSavedMapToEditDialogTryOpenMap,
								0.3, 0.4, 0.4, 0.2, enterFileNameFont,
								sf::Color(255, 128, 255), sf::Color(196, 64, 196),
								sf::Color(0, 64, 0), sf::Color(64, 128, 64));
	chooseNewOrSavedMapToEditDialogSavedMapFileNameDialog->updatePositionAndSize();
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
								sf::Color(255, 255, 255), sf::Color(128, 128, 128, 128), sf::Color(32, 32, 32),
								0.05, 0.05, 0.425, 0.90, 1);
	chooseNewOrSavedMapToEditDialogSavedMapButton = 
		new TwoConditionButton(	nothing, chooseNewOrSavedMapToEditDialogSavedMapButtonPress,
								"Load map", chooseNewOrSavedMapToEditDialogFont,
								sf::Color(196, 196, 128), sf::Color(196, 196, 64, 128), sf::Color(128, 128, 0),
								0.525, 0.05, 0.425, 0.90, 1);
}
