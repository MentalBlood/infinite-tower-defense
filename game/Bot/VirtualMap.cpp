#define UPGRADE 0

class GameAction
{
	private:
		unsigned int x, y;
		char type;

	public:
		GameAction(unsigned int x, unsigned int y, bool type):
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
};

class VirtualMapCell
{
	private:
		unsigned int x, y;
		VirtualTower *tower;
		float maxBuildProfitValue;
		unsigned int maxBuildProfitTowerSpecificationIndex;

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

	public:
		VirtualMapCell(unsigned int x, unsigned int y):
		x(x), y(y), tower(NULL)
		{ setMaxBuildProfitValue(); }

		float getMaxActionProfitValue()
		{ return (tower) ? tower->getNextLevelProfit() : maxBuildProfitValue; }

		GameAction makeAction()
		{
			if (tower)
			{
				tower->upgrade();
				return GameAction(x, y, UPGRADE);
			}
			else
			{
				buildTower((*baseTowersSpecifications)[maxBuildProfitTowerSpecificationIndex]);
				return GameAction(x, y, maxBuildProfitTowerSpecificationIndex + 1);
			}
		}
};

std::list<VirtualMapCell*> *towersCellsList;

void fillVirtualMap()
{
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
