void makeVertexArrayFrame(sf::VertexArray *vertexArrayPointer, float x, float y, float width, float height, float bordersThickness, sf::Color color)
{
	vertexArrayPointer->setPrimitiveType(sf::Quads);
	vertexArrayPointer->resize(16);
	for (int i = 0; i < 16; i++) (*vertexArrayPointer)[i].color = color;

	(*vertexArrayPointer)[0].position = sf::Vector2f(x, y);
	(*vertexArrayPointer)[1].position = sf::Vector2f(x + width, y);
	(*vertexArrayPointer)[2].position = sf::Vector2f(x + width, y + bordersThickness);
	(*vertexArrayPointer)[3].position = sf::Vector2f(x, y + bordersThickness);

	(*vertexArrayPointer)[4].position = sf::Vector2f(x + width, y + bordersThickness);
	(*vertexArrayPointer)[5].position = sf::Vector2f(x + width, y + height);
	(*vertexArrayPointer)[6].position = sf::Vector2f(x + width - bordersThickness, y + height);
	(*vertexArrayPointer)[7].position = sf::Vector2f(x + width - bordersThickness, y + bordersThickness);

	(*vertexArrayPointer)[8].position = sf::Vector2f(x, y + height - bordersThickness);
	(*vertexArrayPointer)[9].position = sf::Vector2f(x + width - bordersThickness, y + height - bordersThickness);
	(*vertexArrayPointer)[10].position = sf::Vector2f(x + width - bordersThickness, y + height);
	(*vertexArrayPointer)[11].position = sf::Vector2f(x, y + height);

	(*vertexArrayPointer)[12].position = sf::Vector2f(x, y + bordersThickness);
	(*vertexArrayPointer)[13].position = sf::Vector2f(x + bordersThickness, y + bordersThickness);
	(*vertexArrayPointer)[14].position = sf::Vector2f(x + bordersThickness, y + height - bordersThickness);
	(*vertexArrayPointer)[15].position = sf::Vector2f(x, y + height - bordersThickness);
}

void makeVertexArrayQuad(sf::VertexArray *vertexArrayPointer, float x, float y, float width, float height, sf::Color color)
{
	vertexArrayPointer->setPrimitiveType(sf::TriangleStrip);
	vertexArrayPointer->resize(4);
	for (int i = 0; i < 4; i++) (*vertexArrayPointer)[i].color = color;

	(*vertexArrayPointer)[0].position = sf::Vector2f(x, y);
	(*vertexArrayPointer)[1].position = sf::Vector2f(x + width, y);
	(*vertexArrayPointer)[2].position = sf::Vector2f(x, y + height);
	(*vertexArrayPointer)[3].position = sf::Vector2f(x + width, y + height);
}
