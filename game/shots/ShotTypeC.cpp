class ShotTypeC : public Shot
{
	private:
		sf::Color color;

	public:
		ShotTypeC(Tower *tower, Monster *monster, sf::Color color):
		Shot(tower, monster, 0.25), color(color)
		{
			graphicalElements = new std::vector<sf::VertexArray>;
			graphicalElements->resize(1);
			(*graphicalElements)[0].setPrimitiveType(sf::TriangleStrip);

			(*graphicalElements)[0].resize(5);

			(*graphicalElements)[0][0].position = sf::Vector2f(radius, 0);
			(*graphicalElements)[0][1].position = sf::Vector2f(0, radius);
			(*graphicalElements)[0][2].position = sf::Vector2f(0, -radius);
			(*graphicalElements)[0][3].position = sf::Vector2f(-radius/2, radius/2);
			(*graphicalElements)[0][4].position = sf::Vector2f(-radius/2, -radius/2);

			(*graphicalElements)[0][0].color = color;
			(*graphicalElements)[0][1].color = color - sf::Color(0, 0, 0, 64);
			(*graphicalElements)[0][2].color = color - sf::Color(0, 0, 0, 64);
			(*graphicalElements)[0][3].color = color - sf::Color(0, 0, 0, 128);
			(*graphicalElements)[0][4].color = color - sf::Color(0, 0, 0, 128);
		}

		void animate()
		{
			//for (unsigned int i = 0; i < 5; i++)
			//	nextColor((*graphicalElements)[0][i].color, elapsed.asMilliseconds()*(rand()%5 + 5), minColor, maxColor);
		}
};
