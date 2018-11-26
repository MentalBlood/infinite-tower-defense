class TowerUpgradeInfo;

enum towerParameterType
{
	DAMAGE,
	RANGE,
	SHOTS_DELAY,
	SHELLS_SPEED,
	COST,
	towerParametersCount
};

const char *towerParameterTypeName[fontsCount]
{
	"damage",
	"range",
	"shots delay",
	"shells speed",
	"COST"
};

class TowerSpecification
{
	private:
		char shotType;
		sf::Texture texture;
		std::vector<Parameter*> parameters;
		bool homingShots;

		unsigned int upgradeCost;

		void refreshUpgradeCost()
		{ upgradeCost = 2 * (parameters[COST]->getNextValue() - parameters[COST]->getValue()); }
		
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
		upgradeCost(specificationToCopy->getUpgradeCost())
		{
			for (unsigned int i = 0; i < parameters.size(); i++)
				parameters[i] = new Parameter(*parameters[i]);
			refreshUpgradeCost();
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

			fclose(characteristicsFile);
		}

		const sf::Texture & getTexture()
		{ return texture; }

		unsigned int getUpgradeCost()
		{ return upgradeCost; }

		std::vector<Parameter*> & getParameters()
		{ return parameters; }

		float getParameterValue(enum towerParameterType parameterType)
		{ return parameters[parameterType]->getValue(); }

		float getNextParameterValue(enum towerParameterType parameterType)
		{ return parameters[parameterType]->getNextValue(); }

		void setNextValues()
		{
			for (unsigned int i = 0; i < parameters.size(); i++)
				parameters[i]->setNextValue();
			refreshUpgradeCost();
		}

		bool areShotsHoming()
		{ return homingShots; }

		char getShotType()
		{ return shotType; }
};
