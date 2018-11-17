class ShotTypeA : public Shot
{
	private:
		sf::Color	minColor,
					maxColor;

	public:
		ShotTypeA(Tower *tower, Monster *monster, sf::Color minColor, sf::Color maxColor):
		Shot(tower, monster), minColor(minColor), maxColor(maxColor)
		{
			graphicalElements.resize(1);
			graphicalElements[0].setPrimitiveType(sf::Triangles);

			graphicalElements[0].resize(3);

			graphicalElements[0][0].position = sf::Vector2f(radius, 0);
			graphicalElements[0][1].position = sf::Vector2f(-radius, radius/2);
			graphicalElements[0][2].position = sf::Vector2f(-radius, -radius/2);

			graphicalElements[0][0].color = sf::Color(maxColor.r, minColor.g, minColor.b);
			graphicalElements[0][1].color = sf::Color(minColor.r, maxColor.g, minColor.b, 155);
			graphicalElements[0][2].color = sf::Color(minColor.r, minColor.g, maxColor.b, 155);
		}

		void animate()
		{
			for (unsigned int i = 0; i < 3; i++)
				nextColor(graphicalElements[0][i].color, elapsed.asMilliseconds()*(rand()%5 + 5), minColor, maxColor);
		}
};
