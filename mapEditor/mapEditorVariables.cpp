Map *mapEditorMap;
float mapEditorCellRelativeSize;

bool mapEditorMapDragging;
float mapEditorMapDraggingMouseX1,
	  mapEditorMapDraggingMouseY1;
sf::Vector2f mapEditorMapDraggingMapInitialCoordinates;

EnterFileNameDialog *mapEditorFileNameDialog = NULL;

#include "mapEditorButtons.cpp"

void updateMapEditorVariables()
{
	updateMapEditorButtons();
	
	if (mapEditorFileNameDialog)
		mapEditorFileNameDialog->updatePositionAndSize();
}

//creating new map
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
	if (mapEditorFileNameDialog) delete mapEditorFileNameDialog;
	mapEditorFileNameDialog = NULL;

	updateMapEditorVariables();
}

//loading and editing saved map
void setMapEditorVariables(std::string &fileName)
{
	printf("setMapEditorVariables\n");
	mapEditorMap = new Map(	fileName.data(),
							sf::Color(150, 150, 64, 196), sf::Color(0, 0, 196, 128), sf::Color(128, 0, 196));
	mapEditorCellRelativeSize = 0.9;
	mapEditorMap->setTextures(mapEditorCellRelativeSize);
	mapEditorMap->setPosition(0, 0);
	mapEditorMapDragging = false;

	windowSize = window.getSize();
	setMapEditorButtons();
	if (mapEditorFileNameDialog) delete mapEditorFileNameDialog;
	mapEditorFileNameDialog = NULL;

	updateMapEditorVariables();
}
