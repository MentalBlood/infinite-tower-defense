#include "../map/MapForEditing.cpp"
MapForEditing *mapEditorMap;

bool mapEditorMapDragging,
	 editingNewMap;
float mapEditorMapDraggingMouseX1,
	  mapEditorMapDraggingMouseY1;
sf::Vector2f mapEditorMapDraggingMapInitialCoordinates;

EnterFileNameDialog *mapEditorFileNameDialog = NULL;
Message *mapEditorWrongMapMessage = NULL;
Question *mapEditorFileAlreadyExistsQuestion;

void setMapEditorEvents();
void updateMapEditor();
void drawMapEditor();

void continueToMapEditor()
{
	setMapEditorEvents();
	updateFunction = updateMapEditor;
	drawFunction = drawMapEditor;
}

void mapEditorShowHelpScreen()
{
	helpScreenFunctionAfterExit = continueToMapEditor;
	startHelpScreen();
}

#include "mapEditorButtons.cpp"

void updateMapEditorVariables()
{
	updateMapEditorButtons();
	
	if (mapEditorFileNameDialog)
		mapEditorFileNameDialog->updatePositionAndSize();
	if (mapEditorWrongMapMessage)
		mapEditorWrongMapMessage->updatePositionAndSize();
	if (mapEditorFileAlreadyExistsQuestion)
		mapEditorFileAlreadyExistsQuestion->updatePositionAndSize();
}

//creating new map
void setMapEditorVariables(int mapEditorMapWidth, int mapEditorMapHeight)
{
	editingNewMap = true;
	mapEditorMap = new MapForEditing(mapEditorMapWidth, mapEditorMapHeight);
	mapEditorMap->setTextures(0.9);
	mapEditorMap->fitInRectangle(sf::Vector2f(0, 0), sf::Vector2f(1, 1));
	mapEditorMapDragging = false;

	windowSize = window.getSize();
	setMapEditorButtons();

	updateMapEditorVariables();
}

//loading and editing saved map
void setMapEditorVariables(std::string &fileName)
{
	editingNewMap = false;
	mapEditorMap = new MapForEditing(fileName.data());
	mapEditorMap->setTextures(0.9);
	mapEditorMap->fitInRectangle(sf::Vector2f(0, 0), sf::Vector2f(1, 1));
	mapEditorMapDragging = false;

	windowSize = window.getSize();
	setMapEditorButtons();

	updateMapEditorVariables();
}
