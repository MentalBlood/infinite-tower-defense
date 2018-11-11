void updateGame()
{
	for (std::list<Monster*>::iterator i = monsters.begin(); i != monsters.end(); i++)
	{
		(*i)->animate();
		(*i)->moveInCorrectDirection();

		if ((*i)->isCame())
		{
			if (damageTheBase((*i)->damage)) return;
			delete *i;
			monsters.erase(i);
			i--;
		}
	}

	processTimers<Monster*>();
	processTimers<char*>();
	updateCurrentSecondsToNextWaveText();
}
