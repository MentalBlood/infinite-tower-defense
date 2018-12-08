class ModelE : public Monster
{
	private:
		static unsigned int numberOfTriangles;

	public:
		ModelE(const float speed, unsigned int health):
		Monster(4, speed, health)
		{
			graphicalElements = new std::vector<sf::VertexArray>;
			graphicalElements->resize(2);

			(*graphicalElements)[0].setPrimitiveType(sf::Triangles);
			unsigned int numberOfVertexes = numberOfTriangles * 6;
			(*graphicalElements)[0].resize(numberOfVertexes);

			sf::Transform rotation;
			rotation.rotate(360.0 / numberOfTriangles);
			(*graphicalElements)[0][0].position = sf::Vector2f(radius / 4, 0);
			(*graphicalElements)[0][0].color = randomColor(128);
			(*graphicalElements)[0][1].position = rotation.transformPoint((*graphicalElements)[0][0].position);
			(*graphicalElements)[0][1].color = randomColor(128);
			(*graphicalElements)[0][2].position = randomPointOnDistance(radius);
			(*graphicalElements)[0][2].color = randomColor(255);
			for (unsigned int i = 3; i < numberOfVertexes; i += 3)
			{
				(*graphicalElements)[0][i] = (*graphicalElements)[0][i-2];
				(*graphicalElements)[0][i+1] = rotation.transformPoint((*graphicalElements)[0][i].position);
				(*graphicalElements)[0][i+1].color = randomColor(128);
				(*graphicalElements)[0][i+2].position = randomPointOnDistance(radius);
				(*graphicalElements)[0][i+2].color = randomColor(255);
			}

			makeVertexArrayCircle(&(*graphicalElements)[1], 0, 0, radius, 16, sf::Color(0, 0, 0, 128), sf::Color::Transparent);
		}

		void animate()
		{
			sf::Transform rotation, inverseRotation;
			float rotationAngle = elapsed.asMilliseconds() / 4;
			rotation.rotate(rotationAngle, sf::Vector2f(0, 0));
			inverseRotation.rotate(-rotationAngle, sf::Vector2f(0, 0));
			for (unsigned int i = 2; i < (*graphicalElements)[0].getVertexCount(); i += 3)
				if (i % 2)
					(*graphicalElements)[0][i].position =
						rotation.transformPoint((*graphicalElements)[0][i].position);
				else
					(*graphicalElements)[0][i].position =
						inverseRotation.transformPoint((*graphicalElements)[0][i].position);
		}
};

unsigned int ModelE::numberOfTriangles = 4;
