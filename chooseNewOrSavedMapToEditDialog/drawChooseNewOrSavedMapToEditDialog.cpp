void drawChooseNewOrSavedMapToEditDialog()
{
	window.clear(sf::Color::Black);
	chooseNewOrSavedMapToEditDialogNewMapButton->draw();
	chooseNewOrSavedMapToEditDialogSavedMapButton->draw();
	if (chooseNewOrSavedMapToEditDialogSavedMapChooseFileDialog)
		chooseNewOrSavedMapToEditDialogSavedMapChooseFileDialog->draw();
	if (chooseNewOrSavedMapToEditDialogWrongFileNameMessage)
		chooseNewOrSavedMapToEditDialogWrongFileNameMessage->draw();
	window.display();
}
