void drawMapEditor()
{
	printf("drawMapEditor\n");
	window.clear();
	mapEditorMap->draw();
//	for (int i = 0; i < mapEditorButtons.size(); i++)
//		mapEditorButtons[i].draw();
	window.display();
}
