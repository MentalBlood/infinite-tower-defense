Text *currentSecondsToNextWaveText,
	 *currentWaveNumberText,
	 *baseHealthText;

void setGameInfoVariables()
{
	currentSecondsToNextWaveText = new Text("next wave in ",
											"fonts/currentSecondsToNextWaveTextFont.otf",
											sf::Color(255, 255, 255, 192),
											0.05, 0.9, 0.05);

	currentWaveNumberText =	new Text(		"wave ",
											"fonts/currentWaveNumberTextFont.otf",
											sf::Color(255, 128, 128, 192),
											0.8, 0.9, 0.05);

	baseHealthText = new Text(				"base health:",
											"fonts/baseHealthTextFont.otf",
											sf::Color(0, 255, 0, 192),
											0.7, 0, 0.05);
}

void updateGameInfoVariables()
{
	currentSecondsToNextWaveText->updatePositionAndSize();
	currentWaveNumberText->updatePositionAndSize();
	baseHealthText->updatePositionAndSize();
}

void updateCurrentSecondsToNextWaveText()
{
	currentSecondsToNextWaveText->setString("next wave in " + 
											sf::String(intToString(int(*currentSecondsToNextWave))));
}

void updateCurrentWaveNumberText()
{
	currentWaveNumberText->setString("wave " + sf::String(intToString(currentWaveNumber)));
}

void updateBaseHealthText()
{
	baseHealthText->setString("base health: " + sf::String(intToString(gameBaseHealth)));
	baseHealthText->setColor(sf::Color(	255 * (1 - 100.0 / gameBaseHealth),
										255 * 100.0 / gameBaseHealth, 0, 192));
}

void drawGameInfo()
{
	currentSecondsToNextWaveText->draw();
	currentWaveNumberText->draw();
	baseHealthText->draw();
}
