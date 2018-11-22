class ShotTypeD : public Shot
{
	private:

	public:
		ShotTypeD(Tower *tower, Monster *monster):
		Shot(tower, monster, 0.2)
		{
			graphicalElements = new std::vector<sf::VertexArray>;
			graphicalElements->resize(1);
			makeVertexArrayRing(&(*graphicalElements)[0], 0, 0, 0, radius, 16, sf::Color(196, 32, 196, 32),
								sf::Color(196, 32, 196, 196));
		}

		void animate()
		{}
};
