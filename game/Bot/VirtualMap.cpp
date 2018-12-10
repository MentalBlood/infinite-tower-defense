#define UPGRADE 0

class GameAction
{
	private:
		unsigned int x, y;
		char type;

	public:
		GameAction(unsigned int x, unsigned int y, char type):
		x(x), y(y), type(type)
		{}

		void printToFile(FILE *file)
		{
			fprintf(file, "(%u, %u) ", x, y);
			if (type == UPGRADE)
				fprintf(file, "upgrade\n");
			else
				fprintf(file, "build type %d\n", type);
		}

		char getType()
		{ return type; }
};

class VirtualMapCell
{
	private:
		unsigned int x, y;
		VirtualTower *tower;
		float maxBuildProfitValue;
		long long unsigned int maxBuildProfitTowerSpecificationIndex;
		GameAction *maxProfitAction;

		float getDistanceCoveredByTowerOnThisCell(float towerDamageRadius)
		{ return getDistanceCoveredByTower(x, y, towerDamageRadius); }

		float getBuildProfitValue(TowerSpecification *specification)
		{
			float distanceCovered =
				getDistanceCoveredByTowerOnThisCell(specification->getParameterValue(RANGE));
			return getProfit(getJobOnTheWave(distanceCovered, specification->getParameterValue(DAMAGE),
											 specification->getParameterValue(SHOTS_DELAY)),
							 getJobOnTheWave(distanceCovered, specification->getNextParameterValue(DAMAGE),
											 specification->getNextParameterValue(SHOTS_DELAY)),
							 specification->getCost());
		}

		void setMaxBuildProfitValue()
		{
			maxBuildProfitValue = 0;
			for (unsigned int i = 0; i < baseTowersSpecifications->size(); i++)
			{
				float currentSpecificationBuildProfitValue =
					  getBuildProfitValue((*baseTowersSpecifications)[i]);
				if (maxBuildProfitValue < currentSpecificationBuildProfitValue)
				{
					maxBuildProfitValue = currentSpecificationBuildProfitValue;
					maxBuildProfitTowerSpecificationIndex = i;
				}
			}
		}

		void buildTower(TowerSpecification *specification)
		{
			tower = new VirtualTower(specification,
						getDistanceCoveredByTowerOnThisCell(specification->getParameterValue(RANGE)),
						getDistanceCoveredByTowerOnThisCell(specification->getNextParameterValue(RANGE)));
		}

		void recalculateMaxProfitAction()
		{
			if (maxProfitAction)
				delete maxProfitAction;
			if (tower)
				maxProfitAction = new GameAction(x, y, UPGRADE);
			else
				maxProfitAction = new GameAction(x, y, maxBuildProfitTowerSpecificationIndex + 1);
		}

	public:
		VirtualMapCell(unsigned int x, unsigned int y):
		x(x), y(y), tower(NULL), maxProfitAction(NULL)
		{
			setMaxBuildProfitValue();
			recalculateMaxProfitAction();
		}

		~VirtualMapCell()
		{
			delete tower;
			delete maxProfitAction;
		}

		float getMaxActionProfitValue()
		{ return (tower) ? tower->getNextLevelProfit() : maxBuildProfitValue; }

		float getMaxActionJobIncrease()
		{
			if (tower)
				return tower->getUpgradeCost() * tower->getNextLevelProfit();
			else
				return (*baseTowersSpecifications)[maxBuildProfitTowerSpecificationIndex]->getCost() *
					   maxBuildProfitValue;
		}

		void makeAction()
		{
			if (tower)
				tower->upgrade();
			else
				buildTower((*baseTowersSpecifications)[maxBuildProfitTowerSpecificationIndex]);
			recalculateMaxProfitAction();
		}

		GameAction getMaxProfitAction()
		{ return *maxProfitAction; }

		long long unsigned int getMaxProfitActionCost()
		{
			if (tower)
				return tower->getUpgradeCost();
			else
				return (*baseTowersSpecifications)[maxBuildProfitTowerSpecificationIndex]->getCost();
		}

		sf::Vector2u getPosition()
		{ return sf::Vector2u(x, y); }
};

std::list<VirtualMapCell*> *towersCellsList;

double currentProfitValue;

void fillVirtualMap()
{
	currentProfitValue = 0;
	towersCellsList = new std::list<VirtualMapCell*>;
	std::vector<std::vector<char> >* pathMapPointer = gameMap->getPathMapPointer();
	for (unsigned int i = 0; i < pathMapPointer->size(); i++)
		for (unsigned int j = 0; j < (*pathMapPointer)[i].size(); j++)
			if ((*pathMapPointer)[i][j] == EMPTY)
				towersCellsList->push_back(new VirtualMapCell(i, j));
}

void deleteVirtualMap()
{
	for (std::list<VirtualMapCell*>::iterator i = towersCellsList->begin(); i != towersCellsList->end(); i++)
		delete (*i);
	delete towersCellsList;
	towersCellsList = NULL;
}
