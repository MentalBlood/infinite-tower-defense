Parameter *nextWaveNumberOfMonsters,
		  *nextWaveSecondsBetweenSpawns,
		  *nextWaveMonstersSpeed,
		  *nextWaveMonstersHealth;

void loadMonstersParameters()
{
	FILE *file = fopen("monstersParametres.txt", "wb");
	if (!file) Closed();

	Parameter::write(file, 64, 1, 1, true);
	Parameter::write(file, 0.4, 0.5, 0.5);
	Parameter::write(file, 0.09, 0, 1.05);
	Parameter::write(file, 5, 0, 1);

	fclose(file);

	file = fopen("monstersParametres.txt", "rb");
	if (!file) Closed();

	nextWaveNumberOfMonsters = new Parameter(file);
	nextWaveSecondsBetweenSpawns = new Parameter(file);
	nextWaveMonstersSpeed = new Parameter(file);
	nextWaveMonstersHealth = new Parameter(file);

	fclose(file);
}

void clearMonsterParameters()
{
	delete nextWaveNumberOfMonsters;
	delete nextWaveSecondsBetweenSpawns;
	delete nextWaveMonstersSpeed;
	delete nextWaveMonstersHealth;
}

void calculateNextWaveMonstersParametres()
{
	nextWaveNumberOfMonsters->setNextValue();
	nextWaveSecondsBetweenSpawns->setNextValue();
	nextWaveMonstersSpeed->setNextValue();
	nextWaveMonstersHealth->setNextValue();
}
