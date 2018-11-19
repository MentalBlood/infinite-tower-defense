class ShotTypeB : public Shot
{
	private:

	public:
		ShotTypeB(	Tower *tower, Monster *monster, sf::Color color,
					unsigned int numberOfVertexes):
		Shot(tower, monster, 0.2)
		{
			graphicalElements = new std::vector<sf::VertexArray>;
			makeVertexArraysHalo(*graphicalElements, 0, 0, 0, radius, radius,
								numberOfVertexes, color);
		}

		void animate()
		{}
};
