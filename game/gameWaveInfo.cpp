Text *currentSecondsToNextWaveText,
	 *currentWaveNumberText;

void setGameWaveInfoVariables()
{
	currentSecondsToNextWaveText = new Text("next wave in ",
											"fonts/currentSecondsToNextWaveTextFont.otf",
											sf::Color(255, 255, 255, 192),
											0.05, 0.9, 0.05);

	currentWaveNumberText = new Text(		"wave ",
											"fonts/currentWaveNumberTextFont.otf",
											sf::Color(255, 128, 128, 192),
											0.8, 0.9, 0.05);
}

void updateGameWaveInfoVariables()
{
	currentSecondsToNextWaveText->updatePositionAndSize();
	currentWaveNumberText->updatePositionAndSize();
}

void updateCurrentSecondsToNextWaveText()
{
	currentSecondsToNextWaveText->setString("next wave in " + 
											sf::String(intToString(int(*currentSecondsToNextWave))));
}

void updateCurrentWaveNumberText()
{
	printf("updateCurrentWaveNumberText\n");
	currentWaveNumberText->setString("wave " + sf::String(intToString(currentWaveNumber)));
}

void drawGameWaveInfo()
{
	currentSecondsToNextWaveText->draw();
	currentWaveNumberText->draw();
}
