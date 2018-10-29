//creating new map
void startMapEditor(int mapWidth, int mapHeight)
{
	setMapEditorVariables(mapWidth, mapHeight);
	setMapEditorEvents();
	updateFunction = updateMapEditor;
	drawFunction = drawMapEditor;
}

//loading and editing saved map
void startMapEditor(std::string fileName)
{
	printf("startMapEditor\n");
	setMapEditorVariables(fileName);
	setMapEditorEvents();
	updateFunction = updateMapEditor;
	drawFunction = drawMapEditor;
}
