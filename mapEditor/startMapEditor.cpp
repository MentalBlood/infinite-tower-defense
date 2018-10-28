void startMapEditor(int mapWidth, int mapHeight)
{
	setMapEditorVariables(mapWidth, mapHeight);
	setMapEditorEvents();
	updateFunction = updateMapEditor;
	drawFunction = drawMapEditor;
}
