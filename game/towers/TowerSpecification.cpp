class TowerSpecification
{
	private:
		sf::Texture texture;
		unsigned int damage;
		float range;
		
	public:
		TowerSpecification(char *textureFileName, char *characteristicsFileName)
		{
			if (!texture.loadFromFile(textureFileName)) Closed();

			FILE *characteristicsFile = fopen(characteristicsFileName, "rb");
			if (!characteristicsFile) Closed();
			fscanf(characteristicsFile, "%u", &damage);
			fscanf(characteristicsFile, "%f", &range);
			fclose(characteristicsFile);
		}

		const sf::Texture & getTexture()
		{ return texture; }

		unsigned int getDamage()
		{ return damage; }

		float getRange()
		{ return range; }
};
