class ShotTypeE : public Shot
{
	private:

	public:
		ShotTypeE(Tower *tower, Monster *monster):
		Shot(tower, monster, 0.2)
		{
			graphicalElements = new std::vector<sf::VertexArray>;
			graphicalElements->resize(2);
			(*graphicalElements)[0].setPrimitiveType(sf::Triangles);
			(*graphicalElements)[0].resize(6);
			(*graphicalElements)[0][0].position = sf::Vector2f(radius, radius / 3 + radius / 8);
			(*graphicalElements)[0][1].position = sf::Vector2f(-radius, radius / 1.5 + radius / 8);
			(*graphicalElements)[0][2].position = sf::Vector2f(-radius, radius / 8);
			(*graphicalElements)[0][3].position = sf::Vector2f(radius, -radius / 3 - radius / 8);
			(*graphicalElements)[0][4].position = sf::Vector2f(-radius, -radius / 1.5 - radius / 8);
			(*graphicalElements)[0][5].position = sf::Vector2f(-radius, -radius / 8);
			for (unsigned int i = 0; i < 6; i++)
				(*graphicalElements)[0][i].color = sf::Color(128 + (rand() % 128), 128 + (rand() % 128), 0);

			makeVertexArrayCircle(	&(*graphicalElements)[1], 0, 0, radius, 16,
									sf::Color::Transparent,
									sf::Color(128 + (rand() % 128), 128 + (rand() % 128), 0, 128));
		}

		void animate()
		{
			//rotateImage(elapsed.asMilliseconds() * (rand() % 2 + 1));
		}
};
