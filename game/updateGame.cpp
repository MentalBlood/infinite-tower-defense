void updateGame()
{
	for (unsigned int i = 0; i < monsters.size(); i++)
	{
		monsters[i].animate();
		monsters[i].moveInCorrectDirection();
	}

	processTimers();
}
