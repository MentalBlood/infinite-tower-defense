sf::Color randomRedColor(unsigned int alpha)
{ return sf::Color(196 + rand() % 36, 32, 32, alpha); }

sf::Color randomBlueColor(unsigned int alpha)
{ return sf::Color(32, 32, 196 + rand() % 36, alpha); }

sf::Color randomColor(unsigned char alpha)
{ return sf::Color(rand() % 256, rand() % 256, rand() % 256, alpha); }

sf::Vector2f randomPointOnDistance(float radius)
{
	float angle = rand() % 360;
	return sf::Vector2f(cos(angle), sin(angle)) * radius;
}

sf::Vector2f randomPoint(float maxRadius)
{
	float angle = rand() % 360,
		  radius = (rand() % 32) * maxRadius / 31;
	return sf::Vector2f(cos(angle), sin(angle)) * radius;
}

sf::Vector2f randomPoint(sf::Vector2f & center, float maxRadius)
{ return center + randomPoint(maxRadius); }

class ModelD : public Monster
{
	private:
		static unsigned int numberOfTriangles;

	public:
		ModelD(const float speed, unsigned int health):
		Monster(4, speed, health)
		{
			graphicalElements = new std::vector<sf::VertexArray>;
			graphicalElements->resize(1);

			(*graphicalElements)[0].setPrimitiveType(sf::Triangles);
			unsigned int numberOfVertexes = numberOfTriangles * 3;
			(*graphicalElements)[0].resize(numberOfVertexes);

			sf::Transform rotation;
			rotation.rotate(360.0 / numberOfTriangles);
			(*graphicalElements)[0][0].position = sf::Vector2f(radius, 0);
			(*graphicalElements)[0][0].color = randomRedColor(255);
			(*graphicalElements)[0][1].position = rotation.transformPoint((*graphicalElements)[0][0].position);
			(*graphicalElements)[0][1].color = randomRedColor(255);
			(*graphicalElements)[0][2].position = randomPoint(radius / 2);
			(*graphicalElements)[0][2].color = randomBlueColor(196);
			for (unsigned int i = 3; i < numberOfVertexes; i += 3)
			{
				(*graphicalElements)[0][i] = (*graphicalElements)[0][i-2];
				(*graphicalElements)[0][i+1] = rotation.transformPoint((*graphicalElements)[0][i].position);
				(*graphicalElements)[0][i+1].color = randomRedColor(255);
				(*graphicalElements)[0][i+2].position = randomPoint(radius / 2);
				(*graphicalElements)[0][i+2].color = randomBlueColor(196);
			}
		}

		void animate()
		{
			sf::Transform rotation, inverseRotation;
			float rotationAngle = float(elapsed.asMilliseconds()) / 2;
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

unsigned int ModelD::numberOfTriangles = 16;
