float vectorLengthSquare(const sf::Vector2f & vector)
{ return vector.x * vector.x + vector.y * vector.y; }

float vectorLength(const sf::Vector2f & vector)
{ return sqrt(vector.x * vector.x + vector.y * vector.y); }

sf::Vector2f unitVector(sf::Vector2f distanceVector)
{ return distanceVector / vectorLength(distanceVector); }

sf::Vector2f unitVector(sf::Vector2f & A, sf::Vector2f & B)
{
	sf::Vector2f distanceVector = B - A;
	return distanceVector / vectorLength(distanceVector);
}

class ModelC : public Monster
{
	private:
		static unsigned int numberOfVertexes;
		static float maxRelativeDistanceFromTeethToCenter;
		bool closingMouth;
		float maxDistanceFromTeethToCenter;
		float distanceFromTeethToCenter;

	public:
		ModelC(const float speed, unsigned int health):
		Monster(4, speed, health), closingMouth(true),
		maxDistanceFromTeethToCenter(maxRelativeDistanceFromTeethToCenter * radius)
		{
			distanceFromTeethToCenter = maxDistanceFromTeethToCenter;
			graphicalElements = new std::vector<sf::VertexArray>;
			graphicalElements->resize(2);
			makeVertexArrayCircle(&(*graphicalElements)[0], 0, 0, radius, numberOfVertexes,
								  sf::Color(255, 0, 0), sf::Color(0, 196, 0, 128));

			(*graphicalElements)[1].setPrimitiveType(sf::Triangles);
			unsigned int numberOfVertexesInArray1 = numberOfVertexes * 3;
			(*graphicalElements)[1].resize(numberOfVertexesInArray1);
			sf::Transform rotation, doubleRotation;
			rotation.rotate(180.0 / numberOfVertexes, sf::Vector2f(0, 0));
			(*graphicalElements)[1][0].position = sf::Vector2f(radius, 0);
			(*graphicalElements)[1][0].color = sf::Color::White;
			(*graphicalElements)[1][1].position = rotation.transformPoint(sf::Vector2f(distanceFromTeethToCenter, 0));
			(*graphicalElements)[1][1].color = sf::Color::White;
			doubleRotation.rotate(360.0 / numberOfVertexes, sf::Vector2f(0, 0));
			(*graphicalElements)[1][2].position = doubleRotation.transformPoint((*graphicalElements)[1][0].position);
			for (unsigned int i = 3; i < numberOfVertexesInArray1; i += 3)
			{
				(*graphicalElements)[1][i].position = (*graphicalElements)[1][i-1].position;
				(*graphicalElements)[1][i].color = sf::Color::White;
				(*graphicalElements)[1][i+1].position = doubleRotation.transformPoint((*graphicalElements)[1][i-2].position);
				(*graphicalElements)[1][i+1].color = sf::Color::White;
				(*graphicalElements)[1][i+2].position = doubleRotation.transformPoint((*graphicalElements)[1][i].position);
				(*graphicalElements)[1][i+2].color = sf::Color::White;
			}
		}

		void animate()
		{
			float distanceToMove = float(elapsed.asMilliseconds()) / 64;
			if (closingMouth)
			{
				if (distanceToMove > distanceFromTeethToCenter)
					closingMouth = false;
			}
			else
				if ((distanceToMove + distanceFromTeethToCenter) > maxDistanceFromTeethToCenter)
					closingMouth = true;

			if (closingMouth)
			{
				for (unsigned int i = 0; i < (*graphicalElements)[1].getVertexCount(); i++)
					(*graphicalElements)[1][i].position -=
						distanceToMove * unitVector((*graphicalElements)[1][i].position);
				distanceFromTeethToCenter -= distanceToMove;
			}
			else
			{
				for (unsigned int i = 0; i < (*graphicalElements)[1].getVertexCount(); i++)
					(*graphicalElements)[1][i].position +=
						distanceToMove * unitVector((*graphicalElements)[1][i].position);
				distanceFromTeethToCenter += distanceToMove;
			}

			sf::Transform rotation;
			rotation.rotate(float(elapsed.asMilliseconds()) / 4, sf::Vector2f(0, 0));
			for (unsigned int i = 0; i < (*graphicalElements)[1].getVertexCount(); i++)
				(*graphicalElements)[1][i].position = rotation.transformPoint((*graphicalElements)[1][i].position);
		}
};

unsigned int ModelC::numberOfVertexes = 8;
float ModelC::maxRelativeDistanceFromTeethToCenter = 0.5;
