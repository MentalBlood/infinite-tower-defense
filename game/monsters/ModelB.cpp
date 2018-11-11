class ModelB : public Monster
{
	private:
		unsigned int numberOfVertexes;

		sf::Color	backgroundMinColor, backgroundMaxColor,
					linesMinColor, linesMaxColor;

	public:
		ModelB(	unsigned int numberOfVertexes,
				sf::Color backgroundMinColor, sf::Color backgroundMaxColor,
				sf::Color linesMinColor, sf::Color linesMaxColor,
				const float speed, unsigned int health):
			Monster(10, speed, health), numberOfVertexes(numberOfVertexes),
			backgroundMinColor(backgroundMinColor), backgroundMaxColor(backgroundMaxColor),
			linesMinColor(linesMinColor), linesMaxColor(linesMaxColor)
		{
			graphicalElements.resize(2);
			graphicalElements[1].setPrimitiveType(sf::LineStrip);
			graphicalElements[1].resize(numberOfVertexes+1);

			sf::Transform rotation;
			rotation.rotate(360 / numberOfVertexes, sf::Vector2f(0, 0)); //for geting other points

			//positioning points
			graphicalElements[1][0].position = sf::Vector2f(radius, 0);
			for (unsigned int i = 1; i < numberOfVertexes; i++)
				graphicalElements[1][i].position = rotation.transformPoint(graphicalElements[1][i-1].position);
			graphicalElements[1][numberOfVertexes].position = graphicalElements[1][0].position;

			//coloring points
			graphicalElements[1][0].color = sf::Color(linesMaxColor.r, linesMinColor.g, linesMinColor.b);
			for (unsigned int i = 1; i < (numberOfVertexes+1); i++)
			{
				graphicalElements[1][i].color = graphicalElements[1][i-1].color;
				nextColor(graphicalElements[1][i].color, 255*6/numberOfVertexes, linesMinColor, linesMaxColor);
			}

			//making background
			graphicalElements[0].setPrimitiveType(sf::TriangleFan);
			graphicalElements[0].resize(numberOfVertexes+2);

			graphicalElements[0][0].position = sf::Vector2f(0, 0);
			graphicalElements[0][1].position = sf::Vector2f(radius, 0);
			for (unsigned int i = 2; i < (numberOfVertexes+1); i++)
				graphicalElements[0][i].position = rotation.transformPoint(graphicalElements[0][i-1].position);
			graphicalElements[0][numberOfVertexes+1].position = graphicalElements[0][1].position;

			graphicalElements[0][0].color = sf::Color(backgroundMinColor.r, backgroundMinColor.g, backgroundMaxColor.b, 128);
			for (unsigned int i = 1; i < (numberOfVertexes+2); i++)
			{
				graphicalElements[0][i].color = graphicalElements[0][i-1].color;
				nextColor(graphicalElements[0][i].color, 255*6/numberOfVertexes, backgroundMinColor, backgroundMaxColor);
			}
		}

		void animate()
		{
			//change colors
			for (unsigned int i = 0; i < numberOfVertexes; i++)
				nextColor(graphicalElements[1][i].color, elapsed.asMilliseconds()*(rand()%2), linesMinColor, linesMaxColor);
			graphicalElements[1][numberOfVertexes].color = graphicalElements[1][0].color;

			for (unsigned int i = 0; i < (numberOfVertexes+1); i++)
				nextColor(graphicalElements[0][i].color, elapsed.asMilliseconds()*(rand()%2), backgroundMinColor, backgroundMaxColor);
			graphicalElements[0][numberOfVertexes+1].color = graphicalElements[0][1].color;

			//move vertexes
			sf::Transform	rotation,
							inverseRotation,
							*currentTransformation;
			float rotationAngle = 360.0/2048.0 * elapsed.asMilliseconds() * (rand() % 2 + 1);
			rotation.rotate(rotationAngle);
			inverseRotation.rotate(-rotationAngle);

			if (rand() % 2) currentTransformation = &rotation;
			else currentTransformation = &inverseRotation;

			graphicalElements[1][0].position = currentTransformation->transformPoint(graphicalElements[1][0].position);
			graphicalElements[1][numberOfVertexes].position = graphicalElements[1][0].position;

			for (unsigned int i = 1; i < numberOfVertexes; i++)
			{
				if (((rand() % 2) && (i % 2)) || (i % 3)) currentTransformation = &rotation;
				else currentTransformation = &inverseRotation;

				graphicalElements[1][i].position = currentTransformation->transformPoint(graphicalElements[1][i].position);
			}
		}
};
