float getVectorAngle(const sf::Vector2f & vector)
{
	float angle = 180.0 / M_PI * atan(vector.y / vector.x);
	if (vector.x < 0) angle += 180;
	return angle;
}

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
		std::vector<sf::VertexArray> *graphicalElements;

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
			rotateInDirection(getVectorAngle(point - position));
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
		position(sf::Vector2f(0, 0)), rotationAngle(0), radius(radius), scale(1),
		graphicalElements(NULL)
		{
			if (initialScale != 1) changeScale(initialScale);
			if (initialPosition != sf::Vector2f(0, 0)) drag(initialPosition);
			if (initialRotationAngle != 0) rotate(initialRotationAngle);
		}

		void setGraphicalElements(std::vector<sf::VertexArray> *newGraphicalElements)
		{
			if (graphicalElements) delete graphicalElements;
			graphicalElements = newGraphicalElements;
		}

		virtual ~GraphicalEntity()
		{}

		void draw()
		{
			sf::Transform totalTransform = transform * rotationTransform;
			for (unsigned int i = 0; i < graphicalElements->size(); i++)
				window.draw((*graphicalElements)[i], totalTransform);
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

		void completeSplinter(std::vector<sf::VertexArray> *);
		void collapse();

		virtual void animate() =0;
};
