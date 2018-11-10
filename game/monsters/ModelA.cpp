class ModelA : public Monster
{
	private:
		float initialMouthAngle,
			  currentMouthAngle;
		unsigned int numberOfVertexes;
		bool closingMouth;

	public:
		ModelA(unsigned int numberOfVertexes, float initialMouthAngle, MapForPlaying *map):
			Monster(map, 5), initialMouthAngle(initialMouthAngle), currentMouthAngle(initialMouthAngle),
			numberOfVertexes(numberOfVertexes), closingMouth(true)
		{
			graphicalElements.resize(1);
			graphicalElements[0].setPrimitiveType(sf::TriangleFan);
			graphicalElements[0].resize(numberOfVertexes + 1);
			graphicalElements[0][0].position = sf::Vector2f(0, 0); //center

			sf::Transform rotation;
			rotation.rotate((360 - initialMouthAngle) / (numberOfVertexes-1), position); //for geting other points

			sf::Transform mouthRotation;
			mouthRotation.rotate(initialMouthAngle/2, position); //for geting point with index 1

			//positioning other points
			graphicalElements[0][1].position = mouthRotation.transformPoint(sf::Vector2f(radius, 0));
			for (unsigned int i = 2; i <= numberOfVertexes; i++)
				graphicalElements[0][i].position = rotation.transformPoint(graphicalElements[0][i-1].position);

			move(map->getSpawnPoint());
			changeScale(map->getScale());

			//coloring points
			graphicalElements[0][0].color = sf::Color(140, 40, 40);
			for (unsigned int i = 1; i <= numberOfVertexes; i++)
			{
				graphicalElements[0][i].color = graphicalElements[0][i-1].color;
				nextColor(graphicalElements[0][i].color, 255*6/(numberOfVertexes+1), sf::Color(40, 40, 40), sf::Color(140, 140, 140));
			}
		}

		void animate()
		{
			//change colors
			for (unsigned int i = 0; i <= numberOfVertexes; i++)
				nextColor(graphicalElements[0][i].color, elapsed.asMilliseconds()*(rand()%2), sf::Color(40, 40, 40), sf::Color(140, 140, 140));

			//closing/opening mouth
			float jawRotationAngle = initialMouthAngle/1024 * elapsed.asMilliseconds();
			sf::Transform	upperMouthPartRotation,
							lowerMouthPartRotation;

			if (closingMouth)
			{
				if ((currentMouthAngle - 2*jawRotationAngle) <= 0)
				{
					jawRotationAngle = (2*jawRotationAngle - currentMouthAngle);
					closingMouth = false;
				}
				currentMouthAngle -= 2*jawRotationAngle;
				upperMouthPartRotation.rotate(jawRotationAngle);
				lowerMouthPartRotation.rotate(-jawRotationAngle);
			}
			else
			{
				if ((currentMouthAngle + 2*jawRotationAngle) >= initialMouthAngle)
				{
					jawRotationAngle = (currentMouthAngle + 2*jawRotationAngle) - initialMouthAngle;
					closingMouth = true;
				}
				currentMouthAngle += 2*jawRotationAngle;
				upperMouthPartRotation.rotate(-jawRotationAngle);
				lowerMouthPartRotation.rotate(jawRotationAngle);
			}

			for (unsigned int i = 0; i < numberOfVertexes/2; i++)
			{
				graphicalElements[0][numberOfVertexes - i].position = 
					upperMouthPartRotation.transformPoint(graphicalElements[0][numberOfVertexes - i].position);
				graphicalElements[0][1 + i].position = 
					lowerMouthPartRotation.transformPoint(graphicalElements[0][1 + i].position);
			}
		}
};
