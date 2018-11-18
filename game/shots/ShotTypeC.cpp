class ShotTypeC : public Shot
{
	private:
		sf::Color	minColor,
					maxColor;

	public:
		ShotTypeC(Tower *tower, Monster *monster, sf::Color minColor, sf::Color maxColor):
		Shot(tower, monster, 0.25), minColor(minColor), maxColor(maxColor)
		{
			graphicalElements.resize(1);
			graphicalElements[0].setPrimitiveType(sf::TriangleStrip);

			graphicalElements[0].resize(5);

			graphicalElements[0][0].position = sf::Vector2f(radius, 0);
			graphicalElements[0][1].position = sf::Vector2f(0, radius);
			graphicalElements[0][2].position = sf::Vector2f(0, -radius);
			graphicalElements[0][3].position = sf::Vector2f(-radius/2, radius/2);
			graphicalElements[0][4].position = sf::Vector2f(-radius/2, -radius/2);

			graphicalElements[0][0].color = sf::Color(maxColor.r, minColor.g, minColor.b);
			graphicalElements[0][1].color = sf::Color(minColor.r, maxColor.g, minColor.b, 16);
			graphicalElements[0][2].color = sf::Color(minColor.r, maxColor.g, minColor.b, 16);
			graphicalElements[0][3].color = sf::Color(minColor.r, minColor.g, maxColor.b, 32);
			graphicalElements[0][4].color = sf::Color(minColor.r, minColor.g, maxColor.b, 32);
		}

		void animate()
		{
			for (unsigned int i = 0; i < 5; i++)
				nextColor(graphicalElements[0][i].color, elapsed.asMilliseconds()*(rand()%5 + 5), minColor, maxColor);
		}
};
