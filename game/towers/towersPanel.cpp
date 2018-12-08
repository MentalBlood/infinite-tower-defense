float towersPanelRelativeX = 0.8,
	  towersPanelRelativeY = 0,
	  towersPanelRelativeWidth = 0.2,
	  towersPanelRelativeHeight = 1,
	  towersPanelRelativeIndent = 0.02;

std::vector<sf::VertexArray> towersPanelGraphicsElements;

TwoConditionButton *towersPanelOpenCloseButton;

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
	towersPanelOpenCloseButton->updatePositionAndSize();
}

bool towersPanelOpened;

void openCloseTowersPanel()
{
	if (towersPanelOpened)
	{
		towersPanelOpened = false;
		towersPanelOpenCloseButton->move(1 - towersPanelRelativeX, 0);
		towersPanelOpenCloseButton->setString("<");
	}
	else
	{
		towersPanelOpened = true;
		towersPanelOpenCloseButton->move(towersPanelRelativeX - 1, 0);
		towersPanelOpenCloseButton->setString(">");
	}
}

void setTowersPanel()
{
	towersInfoStack = new TowersInfoStack(	"textures/towers", "towersSpecifications", 5,
											towersPanelRelativeX, towersPanelRelativeY,
											towersPanelRelativeWidth, towersPanelRelativeHeight,
											towersPanelRelativeIndent);
	towersPanelOpenCloseButton = new TwoConditionButton(nothing, openCloseTowersPanel, ">", towersPanelOpenCloseButtonFont,
					sf::Color(255, 255, 255), sf::Color(32, 64, 128), sf::Color(0, 33, 102),
					towersPanelRelativeX - towersPanelRelativeWidth/8,
					towersPanelRelativeY + towersPanelRelativeHeight/2 - towersPanelRelativeHeight/16,
					towersPanelRelativeWidth/8,
					towersPanelRelativeHeight/8, 1, 4);

	towersPanelGraphicsElements.resize(1);
	towersPanelOpened = true;
	updateTowersPanelPositionAndSize();
}

void deleteTowersPanel()
{
	delete towersInfoStack;
	delete towersPanelOpenCloseButton;
}

void drawTowersPanel()
{
	for (unsigned int i = 0; i < towersPanelGraphicsElements.size(); i++)
		window.draw(towersPanelGraphicsElements[i]);
	towersInfoStack->draw();
}
