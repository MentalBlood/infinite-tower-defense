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
			(*graphicalElements)[0].resize(3);
			(*graphicalElements)[0][0].position = sf::Vector2f(radius * (0.01 * (rand() % 101)), 0);
			(*graphicalElements)[0][1].position = sf::Vector2f(-radius,
																radius * (0.01 * (rand() % 101)));
			(*graphicalElements)[0][2].position = sf::Vector2f(-radius,
																-radius * (0.01 * (rand() % 101)));
			for (unsigned int i = 0; i < 3; i++)
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
