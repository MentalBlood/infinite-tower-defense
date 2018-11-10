class Timer
{
	private:
		void (*function)(char);
		char argument;
		float secondsToWait;

		Timer *previous, *next;

	public:
		static Timer *first;

		Timer(float secondsToWaitArg, void (*function)(char), char argument):
			function(function), argument(argument), secondsToWait(secondsToWaitArg),
			previous(NULL), next(first)
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
			function(argument);

			//process next timer
			if (next) next->tickChain();

			//delete self
			delete this;
		}

		void deleteChain()
		{
			if (!next) return;
			if (next->next)
				next->deleteChain();
			delete next;
		}

		float* getTimeLeftPointer()
		{ return &secondsToWait; }
};

Timer *Timer::first = NULL;

void processTimers()
{
	if (!Timer::first) return;
	Timer::first->tickChain();
}

void deleteTimers()
{
	Timer::first->deleteChain();
	delete Timer::first;
	Timer::first = NULL;
}
