void drawMapEditor()
{
	window.clear();
	mapEditorMap->draw();
	for (int i = 0; i < mapEditorButtons.size(); i++)
		mapEditorButtons[i].draw();
	if (mapEditorFileNameDialog)
		mapEditorFileNameDialog->draw();
	window.display();
}
