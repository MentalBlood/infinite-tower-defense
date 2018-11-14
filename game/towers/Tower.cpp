class Tower
{
	private:
		TowerSpecification *specification;
		sf::Sprite sprite;

	public:
		Tower(TowerSpecification *specification, sf::Vector2f position):
		specification(specification)
		{
			sprite.setTextureRect(sf::IntRect(0, 0, gameMap->getCellSize(), gameMap->getCellSize()));
			sprite.setTexture(specification->getTexture());
			sprite.setPosition(position);
		}

		void drag(sf::Vector2f offset)
		{ sprite.move(offset / sprite.getScale().x); }

		void draw()
		{ window.draw(sprite); }
};
