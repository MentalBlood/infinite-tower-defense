void drawMapEditor()
{
	window.clear();
	mapEditorMap->draw();
	mapEditorMap->drawCellSelector();
	for (unsigned int i = 0; i < mapEditorButtons.size(); i++)
		mapEditorButtons[i].draw();
	if (mapEditorFileNameDialog)
		mapEditorFileNameDialog->draw();
	if (mapEditorWrongMapMessage)
		mapEditorWrongMapMessage->draw();
	window.display();
}
