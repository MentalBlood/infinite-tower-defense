Map *mapEditorMap;
float mapEditorCellRelativeSize;

bool mapEditorMapDragging;
float mapEditorMapDraggingMouseX1,
	  mapEditorMapDraggingMouseY1;
sf::Vector2f mapEditorMapDraggingMapInitialCoordinates;

#include "mapEditorButtons.cpp"

void updateMapEditorVariables()
{
	for (int i = 0; i < mapEditorButtons.size(); i++)
		mapEditorButtons[i].updatePositionAndSize();
}

void setMapEditorVariables(int mapEditorMapWidth, int mapEditorMapHeight)
{
	mapEditorMap = new Map(	mapEditorMapWidth, mapEditorMapHeight,
							sf::Color(150, 150, 64, 196), sf::Color(0, 0, 196, 128), sf::Color(128, 0, 196));
	mapEditorCellRelativeSize = 0.9;
	mapEditorMap->setTextures(mapEditorCellRelativeSize);
	mapEditorMap->setPosition(0, 0);
	mapEditorMapDragging = false;

	windowSize = window.getSize();
	setMapEditorButtons();

	updateMapEditorVariables();
}
