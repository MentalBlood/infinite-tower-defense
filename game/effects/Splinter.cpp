class Splinter : public GraphicalEntity
{
	private:
		sf::Vector2f velocity;
		float secondsBeforeDissapear;
		float colorDissapearDelta;
		float relativeRotatingVelocity;
		Splinter *previous, *next;

	public:
		static Splinter *first;

		Splinter(std::vector<sf::VertexArray> *graphicalElements, float initialRotationAngle,
				sf::Vector2f initialPosition, float initialScale, sf::Vector2f velocity,
				float relativeRotatingVelocity, float secondsBeforeDissapear):
		GraphicalEntity(initialPosition, initialRotationAngle, initialScale, getVectorAngle(velocity)),
		velocity(velocity), secondsBeforeDissapear(secondsBeforeDissapear),
		colorDissapearDelta(255.0 / secondsBeforeDissapear),
		relativeRotatingVelocity(relativeRotatingVelocity), previous(NULL), next(first)
		{
			setGraphicalElements(graphicalElements);
			if (first) first->previous = this;
			first = this;
		}

		void dissapear()
		{
			if (previous)
				previous->next = next;
			else
				first = next;
			if (next)
				next->previous = previous;
			delete this;
		}

		void moveSelf()
		{
			move(velocity * elapsed.asSeconds());
			secondsBeforeDissapear -= elapsed.asSeconds();
			/*for (unsigned int i = 0; i < graphicalElements->size(); i++)
			{
				for (unsigned int j = 0; j < (*graphicalElements)[i].getVertexCount(); j++)
					(*graphicalElements)[i][j].color.a -= colorDissapearDelta * elapsed.asSeconds();
			}*/
			rotate(colorDissapearDelta * (rand()%3 + 1) * elapsed.asSeconds() * relativeRotatingVelocity);
		}

		void animate()
		{}

		void moveChain()
		{
			if (next)
				next->moveChain();
			if (elapsed.asSeconds() > secondsBeforeDissapear)
				dissapear();
			else
				moveSelf();
		}

		void drawChain()
		{
			draw();
			if (next)
				next->drawChain();
		}

		void dragChain()
		{
			drag(gameDragOffset);
			if (next)
				next->dragChain();
		}

		void scaleChain()
		{
			changeScale(gameScaleDelta, gameScaleCenter);
			if (next)
				next->scaleChain();
		}

		void deleteChain()
		{
			if (next)
				next->deleteChain();
			delete this;
		}

		void countNext(unsigned int *count)
		{
			++*count;
			if (next) next->countNext(count);
		}
};

Splinter *Splinter::first = NULL;

void moveSplinters()
{
	if (!Splinter::first) return;
	Splinter::first->moveChain();
}

void drawSplinters()
{
	if (!Splinter::first) return;
	Splinter::first->drawChain();
}

void deleteSplinters()
{
	if (!Splinter::first) return;
	Splinter::first->deleteChain();
	Splinter::first = NULL;
}

void dragSplinters()
{
	if (!Splinter::first) return;
	Splinter::first->dragChain();
}

void scaleSplinters()
{
	if (!Splinter::first) return;
	Splinter::first->scaleChain();
}

unsigned int getSplintersCount()
{
	if (!Splinter::first) return 0;
	unsigned int count = 0;
	Splinter::first->countNext(&count);
	return count;
}
