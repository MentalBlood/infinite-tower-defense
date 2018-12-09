sf::Vector2f getCenter(const sf::VertexArray & vertexArray)
{
	sf::Vector2f center = sf::Vector2f(0, 0);
	unsigned int numberOfVertexes = vertexArray.getVertexCount();
	for (unsigned int i = 0; i < numberOfVertexes; i++)
		center += vertexArray[i].position;
	return center / float(numberOfVertexes);
}

void GraphicalEntity::completeSplinter(std::vector<sf::VertexArray> *splinterGraphicalElements)
{
	sf::Vector2f splinterCenter = getCenter((*splinterGraphicalElements)[0]) + position;
	printf("(%f, %f)\n", splinterCenter.x, splinterCenter.y);
	sf::Vector2f splinterVelocity = (splinterCenter - position) * float(16);
	splinterVelocity.x *= 0.7 + 0.1 * (rand() % 4);
	splinterVelocity.y *= 0.7 + 0.1 * (rand() % 4);
	float splinterRelativeRotatingVelocity = (0.1 * (rand() % 11) - 1) / 4;
	new Splinter(splinterGraphicalElements, rotationAngle, splinterCenter, scale,
				splinterVelocity, splinterRelativeRotatingVelocity, 2.5);
}

void GraphicalEntity::collapse()
{
	std::vector<sf::VertexArray> *splinterGraphicalElements;
	for (unsigned int i = 0; i < graphicalElements->size(); i++)
	{
		if ((*graphicalElements)[i].getPrimitiveType() == sf::TriangleFan)
		{
			for (unsigned int j = 2; j < (*graphicalElements)[i].getVertexCount(); j++)
			{
				splinterGraphicalElements = new std::vector<sf::VertexArray>;
				splinterGraphicalElements->resize(1);
				(*splinterGraphicalElements)[0].setPrimitiveType(sf::Triangles);
				(*splinterGraphicalElements)[0].resize(3);
				(*splinterGraphicalElements)[0][0] = (*graphicalElements)[i][0];
				(*splinterGraphicalElements)[0][1] = (*graphicalElements)[i][j-1];
				(*splinterGraphicalElements)[0][2] = (*graphicalElements)[i][j];
				completeSplinter(splinterGraphicalElements);
			}
		}
		else
		if ((*graphicalElements)[i].getPrimitiveType() == sf::LineStrip)
		{
			for (unsigned int j = 1; j < (*graphicalElements)[i].getVertexCount(); j++)
			{
				splinterGraphicalElements = new std::vector<sf::VertexArray>;
				splinterGraphicalElements->resize(1);
				(*splinterGraphicalElements)[0].setPrimitiveType(sf::Lines);
				(*splinterGraphicalElements)[0].resize(2);
				(*splinterGraphicalElements)[0][0] = (*graphicalElements)[i][j];
				(*splinterGraphicalElements)[0][1] = (*graphicalElements)[i][j-1];
				completeSplinter(splinterGraphicalElements);
			}
		}
		else
		if ((*graphicalElements)[i].getPrimitiveType() == sf::Triangles)
		{
			for (unsigned int j = 2; j < (*graphicalElements)[i].getVertexCount(); j += 3)
			{
				splinterGraphicalElements = new std::vector<sf::VertexArray>;
				splinterGraphicalElements->resize(1);
				(*splinterGraphicalElements)[0].setPrimitiveType(sf::Triangles);
				(*splinterGraphicalElements)[0].resize(3);
				(*splinterGraphicalElements)[0][0] = (*graphicalElements)[i][j-2];
				(*splinterGraphicalElements)[0][1] = (*graphicalElements)[i][j-1];
				(*splinterGraphicalElements)[0][2] = (*graphicalElements)[i][j];
				completeSplinter(splinterGraphicalElements);
			}
		}
		else
		if ((*graphicalElements)[i].getPrimitiveType() == sf::Lines)
		{
			for (unsigned int j = 1; j < (*graphicalElements)[i].getVertexCount(); j += 2)
			{
				splinterGraphicalElements = new std::vector<sf::VertexArray>;
				splinterGraphicalElements->resize(1);
				(*splinterGraphicalElements)[0].setPrimitiveType(sf::Lines);
				(*splinterGraphicalElements)[0].resize(2);
				(*splinterGraphicalElements)[0][0] = (*graphicalElements)[i][j-1];
				(*splinterGraphicalElements)[0][1] = (*graphicalElements)[i][j];
				completeSplinter(splinterGraphicalElements);
			}
		}
		else
		if ((*graphicalElements)[i].getPrimitiveType() == sf::TriangleStrip)
		{
			for (unsigned int j = 2; j < (*graphicalElements)[i].getVertexCount(); j++)
			{
				splinterGraphicalElements = new std::vector<sf::VertexArray>;
				splinterGraphicalElements->resize(1);
				(*splinterGraphicalElements)[0].setPrimitiveType(sf::Triangles);
				(*splinterGraphicalElements)[0].resize(3);
				(*splinterGraphicalElements)[0][0] = (*graphicalElements)[i][j-2];
				(*splinterGraphicalElements)[0][1] = (*graphicalElements)[i][j-1];
				(*splinterGraphicalElements)[0][1] = (*graphicalElements)[i][j];
				completeSplinter(splinterGraphicalElements);
			}
		}
		else
		if ((*graphicalElements)[i].getPrimitiveType() == sf::Points)
		{
			for (unsigned int j = 0; j < (*graphicalElements)[i].getVertexCount(); j++)
			{
				splinterGraphicalElements = new std::vector<sf::VertexArray>;
				splinterGraphicalElements->resize(1);
				(*splinterGraphicalElements)[0].setPrimitiveType(sf::Points);
				(*splinterGraphicalElements)[0].resize(1);
				(*splinterGraphicalElements)[0][0] = (*graphicalElements)[i][j];
				completeSplinter(splinterGraphicalElements);
			}
		}
	}
}
