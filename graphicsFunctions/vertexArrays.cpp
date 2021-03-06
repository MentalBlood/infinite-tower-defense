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

void makeVertexArrayRing(sf::VertexArray *vertexArrayPointer, float x, float y,
						float internalRadius, float thickness,
						unsigned int numberOfVertexes, sf::Color internalColor, sf::Color externalColor)
{
	sf::Transform rotation;
	rotation.rotate(360.0 / numberOfVertexes, x, y);

	vertexArrayPointer->setPrimitiveType(sf::TriangleStrip);
	vertexArrayPointer->resize((numberOfVertexes + 1) * 2);

	(*vertexArrayPointer)[0].position = sf::Vector2f(x + internalRadius, y);
	(*vertexArrayPointer)[0].color = internalColor;
	(*vertexArrayPointer)[1].position = sf::Vector2f(x + internalRadius + thickness, y);
	(*vertexArrayPointer)[1].color = externalColor;

	for (unsigned int i = 2; i < (numberOfVertexes + 1) * 2; i += 2)
	{
		(*vertexArrayPointer)[i].position = rotation.transformPoint((*vertexArrayPointer)[i-2].position);
		(*vertexArrayPointer)[i].color = internalColor;
		(*vertexArrayPointer)[i+1].position = rotation.transformPoint((*vertexArrayPointer)[i-1].position);
		(*vertexArrayPointer)[i+1].color = externalColor;
	}
}

void makeVertexArraysHalo(std::vector<sf::VertexArray> & graphicalElements, float x, float y,
						float internalRadius, float internalThickness, float externalThickness,
						unsigned int numberOfVertexes, sf::Color color)
{
	graphicalElements.resize(2);

	makeVertexArrayRing(&graphicalElements[0], x, y, internalRadius, internalThickness,
						numberOfVertexes, sf::Color::Transparent, color);
	makeVertexArrayRing(&graphicalElements[1], x, y, internalRadius + internalThickness,
						externalThickness, numberOfVertexes, color, sf::Color::Transparent);
}

void makeVertexArrayCircle(sf::VertexArray *vertexArrayPointer, float x, float y,
						float radius, unsigned int numberOfVertexes,
						sf::Color innerColor, sf::Color outerColor)
{
	vertexArrayPointer->setPrimitiveType(sf::TriangleFan);
	vertexArrayPointer->resize(numberOfVertexes + 2);

	(*vertexArrayPointer)[0].position = sf::Vector2f(x, y);
	(*vertexArrayPointer)[0].color = innerColor;
	(*vertexArrayPointer)[1].position = sf::Vector2f(x + radius, y);
	(*vertexArrayPointer)[1].color = outerColor;

	sf::Transform rotation;
	rotation.rotate(360.0 / numberOfVertexes);

	for (unsigned int i = 2; i < (numberOfVertexes + 2); i++)
	{
		(*vertexArrayPointer)[i].position = rotation.transformPoint((*vertexArrayPointer)[i-1].position);
		(*vertexArrayPointer)[i].color = outerColor;
	}
}
