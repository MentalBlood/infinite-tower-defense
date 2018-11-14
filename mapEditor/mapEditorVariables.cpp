#include "../map/MapForEditing.cpp"
MapForEditing *mapEditorMap;

bool mapEditorMapDragging,
	 editingNewMap;
float mapEditorMapDraggingMouseX1,
	  mapEditorMapDraggingMouseY1;
sf::Vector2f mapEditorMapDraggingMapInitialCoordinates;

EnterFileNameDialog *mapEditorFileNameDialog = NULL;
Message *mapEditorWrongMapMessage = NULL;

#include "mapEditorButtons.cpp"

void updateMapEditorVariables()
{
	updateMapEditorButtons();
	
	if (mapEditorFileNameDialog)
		mapEditorFileNameDialog->updatePositionAndSize();
	if (mapEditorWrongMapMessage)
		mapEditorWrongMapMessage->updatePositionAndSize();
}

//creating new map
void setMapEditorVariables(int mapEditorMapWidth, int mapEditorMapHeight)
{
	editingNewMap = true;
	mapEditorMap = new MapForEditing(mapEditorMapWidth, mapEditorMapHeight,
					sf::Color(150, 150, 64, 196), sf::Color(0, 0, 196, 128), sf::Color(128, 0, 196));
	mapEditorMap->setTextures(0.9);
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
	editingNewMap = false;
	mapEditorMap = new MapForEditing(fileName.data(), sf::Color(150, 150, 64, 196),
									sf::Color(0, 0, 196, 128), sf::Color(128, 0, 196));
	mapEditorMap->setTextures(0.9);
	mapEditorMap->setPosition(0, 0);
	mapEditorMapDragging = false;

	windowSize = window.getSize();
	setMapEditorButtons();
	if (mapEditorFileNameDialog) delete mapEditorFileNameDialog;
	mapEditorFileNameDialog = NULL;

	updateMapEditorVariables();
}
