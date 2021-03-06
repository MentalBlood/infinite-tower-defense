class TowerUpgradeInfo;

enum towerParameterType
{
	DAMAGE,
	RANGE,
	SHOTS_DELAY,
	SHELLS_SPEED,
	UPGRADE_COST,
	towerParametersCount
};

const char *towerParameterTypeName[fontsCount]
{
	"damage",
	"range",
	"shots delay",
	"shells speed"
};

class TowerSpecification
{
	private:
		char shotType;
		sf::Texture texture;
		std::vector<Parameter*> parameters;
		bool homingShots;

		long long unsigned int cost,
							   costWithUpgrades;

	public:
		TowerSpecification(char *textureFileName, char *characteristicsFileName, char shotTypeArg)
		{
			shotType = shotTypeArg;
			if (!texture.loadFromFile(textureFileName)) Closed();
			refreshParameters(characteristicsFileName);
		}

		TowerSpecification(TowerSpecification *specificationToCopy):
		shotType(specificationToCopy->getShotType()), texture(specificationToCopy->getTexture()),
		parameters(specificationToCopy->getParameters()), homingShots(specificationToCopy->areShotsHoming()),
		cost(specificationToCopy->getCost()), costWithUpgrades(specificationToCopy->getCostWithUpgrades())
		{
			for (unsigned int i = 0; i < parameters.size(); i++)
				parameters[i] = new Parameter(*parameters[i]);
		}

		~TowerSpecification()
		{
			for (unsigned int i = 0; i < parameters.size(); i++)
				delete parameters[i];
		}

		void refreshParameters(char *characteristicsFileName)
		{
			FILE *characteristicsFile = fopen(characteristicsFileName, "rb");
			if (!characteristicsFile) Closed();

			parameters.resize(towerParametersCount);
			for (unsigned int i = 0; i < parameters.size(); i++)
				parameters[i] = new Parameter(characteristicsFile);

			int temp;
			fscanf(characteristicsFile, "%d", &temp);
			if (temp)
				homingShots = true;
			else
				homingShots = false;

			fscanf(characteristicsFile, "%llu", &cost);
			costWithUpgrades = cost;

			fclose(characteristicsFile);
		}

		const sf::Texture & getTexture()
		{ return texture; }

		long long unsigned int getCost()
		{ return cost; }

		long long unsigned int getCostWithUpgrades()
		{ return costWithUpgrades; }

		std::vector<Parameter*> & getParameters()
		{ return parameters; }

		std::vector<Parameter*>* getParametersPointer()
		{ return &parameters; }

		double getParameterValue(enum towerParameterType parameterType)
		{ return parameters[parameterType]->getValue(); }

		double getNextParameterValue(enum towerParameterType parameterType)
		{ return parameters[parameterType]->getNextValue(); }

		void setNextValues()
		{
			costWithUpgrades += parameters[UPGRADE_COST]->getValue();
			setNextParametersValues(parameters);
		}

		bool areShotsHoming()
		{ return homingShots; }

		char getShotType()
		{ return shotType; }
};
