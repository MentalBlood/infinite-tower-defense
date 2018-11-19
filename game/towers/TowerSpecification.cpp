class TowerSpecification
{
	private:
		char shotType;
		sf::Texture texture;
		float damage,
			  range,
			  shotsDelay,
			  shellsSpeed;
		unsigned int cost;
		
	public:
		TowerSpecification(char *textureFileName, char *characteristicsFileName, char shotType):
		shotType(shotType)
		{
			if (!texture.loadFromFile(textureFileName)) Closed();

			FILE *characteristicsFile = fopen(characteristicsFileName, "rb");
			if (!characteristicsFile) Closed();
			fscanf(characteristicsFile, "%f", &damage);
			fscanf(characteristicsFile, "%f", &range);
			fscanf(characteristicsFile, "%f", &shotsDelay);
			fscanf(characteristicsFile, "%f", &shellsSpeed);
			fscanf(characteristicsFile, "%u", &cost);
			fclose(characteristicsFile);
		}

		const sf::Texture & getTexture()
		{ return texture; }

		float getDamage()
		{ return damage; }

		float getRange()
		{ return range; }

		float getShotsDelay()
		{ return shotsDelay; }

		float getShellsSpeed()
		{ return shellsSpeed; }

		unsigned int getCost()
		{ return cost; }

		char getShotType()
		{ return shotType; }
};
