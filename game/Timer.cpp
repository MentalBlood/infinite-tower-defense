class Timer
{
	private:
		void (*function)();
		float secondsToWait;

		Timer *previous, *next;

	public:
		static Timer *first;

		Timer(float secondsToWait, void (*function)()):
			function(function), secondsToWait(secondsToWait), previous(NULL), next(first)
		{
			if (first) first->previous = this;
			first = this;
		}

		bool tick()
		{
			if (secondsToWait > elapsed.asSeconds())
			{
				secondsToWait -= elapsed.asSeconds();
				return true;
			}
			return false;
		}

		void tickChain()
		{
			//if some time left
			if (tick())
			{
				if (next) next->tickChain();
				return;
			}

			//else remove self from list
			if (previous)
				previous->next = next;
			else
				first = next;
			if (next)
				next->previous = previous;

			//call function
			function();

			//process next timer
			if (next) next->tickChain();

			//delete self
			delete this;
		}
};

Timer *Timer::first = NULL;

void processTimers()
{
	if (!Timer::first) return;
	Timer::first->tickChain();
}
