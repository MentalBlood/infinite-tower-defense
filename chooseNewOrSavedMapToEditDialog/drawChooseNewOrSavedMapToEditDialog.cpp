void drawChooseNewOrSavedMapToEditDialog()
{
	window.clear(sf::Color::Black);
	chooseNewOrSavedMapToEditDialogNewMapButton->draw();
	chooseNewOrSavedMapToEditDialogSavedMapButton->draw();
	if (chooseNewOrSavedMapToEditDialogSavedMapFileNameDialog)
		chooseNewOrSavedMapToEditDialogSavedMapFileNameDialog->draw();
	window.display();
}
