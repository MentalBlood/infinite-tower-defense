class TowerSpecification
{
	private:
		char shotType;
		sf::Texture texture;
		Parameter *damage,
				  *range,
				  *shotsDelay,
				  *shellsSpeed,
				  *cost;
		bool homingShots;
		
	public:
		TowerSpecification(char *textureFileName, char *characteristicsFileName, char shotTypeArg)
		{
			shotType = shotTypeArg;
			if (!texture.loadFromFile(textureFileName)) Closed();

			FILE *characteristicsFile = fopen(characteristicsFileName, "rb");
			if (!characteristicsFile) Closed();

			damage = new Parameter(characteristicsFile);
			range = new Parameter(characteristicsFile);
			shotsDelay = new Parameter(characteristicsFile);
			shellsSpeed = new Parameter(characteristicsFile);
			int temp;
			fscanf(characteristicsFile, "%d", &temp);
			if (temp)
				homingShots = true;
			else
				homingShots = false;
			cost = new Parameter(characteristicsFile);

			fclose(characteristicsFile);

			printf("damage = %f\nrange = %f\nshotsDelay = %f\nshellsSpeed = %f\ncost = %f\n",
					damage->getValue(),
					range->getValue(),
					shotsDelay->getValue(),
					shellsSpeed->getValue(),
					cost->getValue());
		}

		~TowerSpecification()
		{
			delete damage;
			delete range;
			delete shotsDelay;
			delete shellsSpeed;
			delete cost;
		}

		const sf::Texture & getTexture()
		{ return texture; }

		float getDamage()
		{ return damage->getValue(); }

		float getRange()
		{ return range->getValue(); }

		float getShotsDelay()
		{ return shotsDelay->getValue(); }

		float getShellsSpeed()
		{ return shellsSpeed->getValue(); }

		float getCost()
		{ return cost->getValue(); }

		bool areShotsHoming()
		{ return homingShots; }

		char getShotType()
		{ return shotType; }
};
