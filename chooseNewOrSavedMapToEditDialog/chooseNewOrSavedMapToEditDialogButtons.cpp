TwoConditionButton *chooseNewOrSavedMapToEditDialogNewMapButton,
				   *chooseNewOrSavedMapToEditDialogSavedMapButton;

void chooseNewOrSavedMapToEditDialogTryOpenMap(std::string fileName)
{
	
}

void chooseNewOrSavedMapToEditDialogSavedMapButtonPress()
{
	if (chooseNewOrSavedMapToEditDialogSavedMapFileNameDialog)
		delete chooseNewOrSavedMapToEditDialogSavedMapFileNameDialog;
	chooseNewOrSavedMapToEditDialogSavedMapFileNameDialog = 
		new EnterFileNameDialog("Enter file name:", startMapEditor,
								0.3, 0.4, 0.4, 0.2, "fonts/enterFileNameFont.otf",
								sf::Color(255, 128, 255), sf::Color(196, 64, 196),
								sf::Color(0, 64, 0, 128), sf::Color(64, 128, 64));
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
								"New map", "fonts/chooseNewOrSavedMapToEditDialogFont.otf",
								sf::Color(255, 255, 255), sf::Color(128, 128, 128, 128), sf::Color(32, 32, 32),
								0.05, 0.05, 0.425, 0.90);
	chooseNewOrSavedMapToEditDialogSavedMapButton = 
		new TwoConditionButton(	nothing, chooseNewOrSavedMapToEditDialogSavedMapButtonPress,
								"Load map", "fonts/chooseNewOrSavedMapToEditDialogFont.otf",
								sf::Color(196, 196, 128), sf::Color(196, 196, 64, 128), sf::Color(128, 128, 0),
								0.525, 0.05, 0.425, 0.90);
}
