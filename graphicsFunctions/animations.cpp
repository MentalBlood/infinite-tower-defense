class Movement
{
	private:
		sf::Sprite *sprite;
		float speedX,
			  speedY;
		sf::Time timeLeft;

		Movement *previous, *next;
		static Movement *first;

	public:
		Movement(sf::Sprite *sprite, float movementX, float movementY, sf::Time time):
			sprite(sprite), speedX(movementX / time.asSeconds()), speedY(movementY / time.asSeconds()),
			previous(NULL)
		{
			next = first;
			first = this;
			next->previous = this;
		}

		void doForElapsed()
		{
			if (timeLeft < elapsed)
			{
				sprite->move(speedX * timeLeft, speedY * timeLeft);

				//remove self from list and delete
				if (previous)
					previous->next = next;
				else
					first = next;
				if (next)
					next->previous = previous;

				delete this;
			}
			else
				sprite->move(speedX * elapsed, speedY * elapsed);
		}
}

Movement *Movement::first = NULL;

void animateMovements()
{
	if (Movement::first) Movement::first->doForElapsed();
}
