Parameter<unsigned int> *nextWaveNumberOfMonsters;
Parameter<float>		*nextWaveSecondsBetweenSpawns,
						*nextWaveMonstersSpeed,
						*nextWaveMonstersHealth;

void loadMonstersParameters()
{
	FILE *file = fopen("monstersParametres.txt", "wb");
	if (!file) Closed();

	Parameter<unsigned int>::write(file, 64, 1, 1, false, true);
	Parameter<float>::write(file, 0.4, 0.5, 0.5, true);
	Parameter<float>::write(file, 0.09, 0, 1.05, true);
	Parameter<float>::write(file, 5, 0, 1, true);

	fclose(file);

	file = fopen("monstersParametres.txt", "rb");
	if (!file) Closed();

	nextWaveNumberOfMonsters = new Parameter<unsigned int>(file, false);
	nextWaveSecondsBetweenSpawns = new Parameter<float>(file, true);
	nextWaveMonstersSpeed = new Parameter<float>(file, true);
	nextWaveMonstersHealth = new Parameter<float>(file, true);

	fclose(file);
}

void calculateNextWaveMonstersParametres()
{
	nextWaveNumberOfMonsters->calculateNextValue();
	nextWaveSecondsBetweenSpawns->calculateNextValue();
	nextWaveMonstersSpeed->calculateNextValue();
	nextWaveMonstersHealth->calculateNextValue();
}
