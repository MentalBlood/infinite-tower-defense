void drawMapEditor()
{
	window.clear();
	mapEditorMap->draw();
	mapEditorMap->drawCellSelector();
	for (std::list<TwoConditionButton>::iterator i = mapEditorButtons.begin();
			i != mapEditorButtons.end(); i++)
		i->draw();
	if (mapEditorFileNameDialog)
		mapEditorFileNameDialog->draw();
	if (mapEditorWrongMapMessage)
		mapEditorWrongMapMessage->draw();
	if (mapEditorFileAlreadyExistsQuestion)
		mapEditorFileAlreadyExistsQuestion->draw();
	window.display();
}
