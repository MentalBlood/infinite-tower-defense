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
		
		~Timer()
		{
			if (previous)
				previous->next = next;
			else
				first = next;
			if (next)
				next->previous = previous;
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

		Type getArgument()
		{ return argument; }

		bool haveNext()
		{
			if (next) return true;
			return false;
		}

		void deleteTimersWithSuchArgument(Type argumentToDelete)
		{
			printf("deleteTimersWithSuchArgument\n");
			if (next) next->deleteTimersWithSuchArgument(argumentToDelete);
			else return;
			printf("checking next\n");
			if (next->getArgument() == argumentToDelete)
			{
				printf("delete next\n");
				delete next;
			}
			printf("check ok\n");
		}

		void abandonChain()
		{
			secondsToWait = 0;
			if (next) next->abandonChain();
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

template<class Type>
void deleteTimersWithSuchArgument(Type argument)
{
	if (!Timer<Type>::first) return;
	Timer<Type>::first->deleteTimersWithSuchArgument(argument);
	if (Timer<Type>::first->getArgument() == argument)
	{
		if (!Timer<Type>::first->haveNext())
		{
			delete Timer<Type>::first;
			Timer<Type>::first = NULL;
		}
		else
			delete Timer<Type>::first;
	}
}

template<class Type>
void abandonTimers()
{
	if (!Timer<Type>::first) return;
	Timer<Type>::first->abandonChain();
}
