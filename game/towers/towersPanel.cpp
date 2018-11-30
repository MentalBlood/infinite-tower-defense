float towersPanelRelativeX = 0.8,
	  towersPanelRelativeY = 0,
	  towersPanelRelativeWidth = 0.2,
	  towersPanelRelativeHeight = 1,
	  towersPanelRelativeIndent = 0.02;

std::vector<sf::VertexArray> towersPanelGraphicsElements;

#include "TowerSpecification.cpp"
#include "TowerUpgradeInfo.cpp"
#include "Tower.cpp"
Tower *addingTower;

#include "TowerInfo.cpp"
#include "TowersInfoStack.cpp"
TowersInfoStack *towersInfoStack;

void updateTowersPanelPositionAndSize()
{
	makeVertexArrayQuad(&towersPanelGraphicsElements[0],
						towersPanelRelativeX * windowSize.x, towersPanelRelativeY * windowSize.y,
						towersPanelRelativeWidth * windowSize.x,
						towersPanelRelativeHeight * windowSize.y, sf::Color(0, 33, 102));
	towersInfoStack->updatePositionAndSize();
}

void setTowersPanel()
{
	towersInfoStack = new TowersInfoStack(	"textures/towers", "towersSpecifications", 5,
											towersPanelRelativeX, towersPanelRelativeY,
											towersPanelRelativeWidth, towersPanelRelativeHeight,
											towersPanelRelativeIndent);

	towersPanelGraphicsElements.resize(1);
	updateTowersPanelPositionAndSize();
}

void drawTowersPanel()
{
	for (unsigned int i = 0; i < towersPanelGraphicsElements.size(); i++)
		window.draw(towersPanelGraphicsElements[i]);
	towersInfoStack->draw();
}
