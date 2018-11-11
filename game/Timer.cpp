template<class Type>
class Timer
{
	private:
		void (*function)(Type);
		Type argument;
		float secondsToWait;

		Timer *previous, *next;

	public:
		static Timer<Type> *first;

		Timer(float secondsToWaitArg, void (*function)(Type), Type argument):
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

		void deleteArgument()
		{
			delete argument;
		}

		void deleteChain()
		{
			if (!next) return;
			if (next->next)
				next->deleteChain();
			delete next;
			delete argument;
		}

		float* getTimeLeftPointer()
		{ return &secondsToWait; }
};

template<class Type>
Timer<Type> *Timer<Type>::first = NULL;

template<class Type>
void processTimers()
{
	if (!Timer<Type>::first) return;
	Timer<Type>::first->tickChain();
}

template<class Type>
void deleteTimers()
{
	if (!Timer<Type>::first) return;
	Timer<Type>::first->deleteChain();
	delete Timer<Type>::first;
	Timer<Type>::first = NULL;
}
