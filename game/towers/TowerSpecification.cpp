class TowerSpecification
{
	private:
		char shotType;
		sf::Texture texture;
		unsigned int damage;
		float range;
		float shotsDelay;
		
	public:
		TowerSpecification(char *textureFileName, char *characteristicsFileName, char shotType):
		shotType(shotType)
		{
			if (!texture.loadFromFile(textureFileName)) Closed();

			FILE *characteristicsFile = fopen(characteristicsFileName, "rb");
			if (!characteristicsFile) Closed();
			fscanf(characteristicsFile, "%u", &damage);
			fscanf(characteristicsFile, "%f", &range);
			fscanf(characteristicsFile, "%f", &shotsDelay);
			fclose(characteristicsFile);
		}

		const sf::Texture & getTexture()
		{ return texture; }

		unsigned int getDamage()
		{ return damage; }

		float getRange()
		{ return range; }

		float getShotsDelay()
		{ return shotsDelay; }

		char getShotType()
		{ return shotType; }
};
