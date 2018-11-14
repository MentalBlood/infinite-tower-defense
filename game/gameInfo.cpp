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
											0.65, 0.9, 0.05);

	baseHealthText = new Text(				"base health:",
											"fonts/baseHealthTextFont.otf",
											sf::Color(0, 255, 0, 192),
											0.55, 0, 0.05);
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
											sf::String(intToString(ceil(int(*currentSecondsToNextWave)))));
}

void updateCurrentWaveNumberText()
{
	currentWaveNumberText->setString("wave " + sf::String(intToString(currentWaveNumber)));
}

void updateBaseHealthText()
{
	baseHealthText->setString("base health: " + sf::String(intToString(gameBaseHealth)));
	baseHealthText->setColor(sf::Color(	255 * (1 - float(gameBaseHealth) / 100.0),
										255 * float(gameBaseHealth) / 100.0, 0, 192));
}

void drawGameInfo()
{
	currentSecondsToNextWaveText->draw();
	currentWaveNumberText->draw();
	baseHealthText->draw();
}
