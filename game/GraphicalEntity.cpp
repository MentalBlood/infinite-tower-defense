class GraphicalEntity
{
	private:
		sf::Vector2f position;
		float rotationAngle;
		sf::Transform	transform,
						rotationTransform;

	protected:
		float radius,
			  scale;
		std::vector<sf::VertexArray> graphicalElements;

		void rotate(float angle)
		{
			rotationTransform.rotate(angle);
			rotationAngle += angle;
		}

		void rotateInDirection(float angle)
		{
			rotationTransform.rotate(angle - rotationAngle);
			rotationAngle = angle;
		}

		void rotateToPoint(sf::Vector2f point)
		{
			sf::Vector2f distanceVector = point - position;
			float angle = 180.0 / M_PI * atan(distanceVector.y / distanceVector.x);
			if (distanceVector.x < 0) angle += 180;
			rotateInDirection(angle);
		}

		void drag(const sf::Vector2f & offset)
		{
			transform.translate(offset / scale);
			position += sf::Vector2f(offset);
		}

		void move(const sf::Vector2f &offset)
		{
			transform.translate(offset);
			position += offset * scale;
		}

		void changeScale(float delta)
		{
			transform.scale(sf::Vector2f(delta, delta));
			scale *= delta;
		}

		sf::Vector2f changeScale(float delta, const sf::Vector2f & center)
		{
			sf::Vector2f shift = (delta - 1) * (position - center);
			drag(shift);
			transform.scale(sf::Vector2f(delta, delta));
			scale *= delta;
			return shift;
		}

	public:
		GraphicalEntity(sf::Vector2f initialPosition, float radius, float initialScale,
						float initialRotationAngle):
		position(sf::Vector2f(0, 0)), rotationAngle(0), radius(radius), scale(1)
		{
			if (initialScale != 1) changeScale(initialScale);
			if (initialPosition != sf::Vector2f(0, 0)) drag(initialPosition);
			if (initialRotationAngle != 0) rotate(initialRotationAngle);
		}

		virtual ~GraphicalEntity()
		{}

		void draw()
		{
			sf::Transform totalTransform = transform * rotationTransform;
			for (unsigned int i = 0; i < graphicalElements.size(); i++)
				window.draw(graphicalElements[i], totalTransform);
		}

		sf::Vector2f getDistanceVector(sf::Vector2f & point)
		{
			return point - position;
		}

		sf::Vector2f & getPosition()
		{ return position; }

		float getRadius()
		{ return radius; }

		float getScale()
		{ return scale; }

		virtual void animate() =0;
};
