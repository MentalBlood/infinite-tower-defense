void startMapEditor(int mapWidth, int mapHeight)
{
	printf("startMapEditor\n");
	setMapEditorVariables(mapWidth, mapHeight);
	setMapEditorEvents();
	updateFunction = updateMapEditor;
	drawFunction = drawMapEditor;
}
