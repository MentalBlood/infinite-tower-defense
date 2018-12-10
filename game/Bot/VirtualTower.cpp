float getJobOnTheWave(float distanceCovered, float monstersNumber, float secondsBetweenSpawns,
					  float monstersSpeed, float towerDamage, float shotsDelay)
{
	return (distanceCovered + (monstersNumber - 1) * secondsBetweenSpawns * monstersSpeed) *
			towerDamage / (monstersSpeed * shotsDelay);
}

float getJobOnTheWave(float distanceCovered, float damage, float shotsDelay)
{
	return getJobOnTheWave(distanceCovered, monstersParameters[NUMBER]->getValue(),
						   monstersParameters[SECONDS_BETWEEN_SPAWNS]->getValue(),
						   monstersParameters[SPEED]->getValue(),
						   damage,
						   shotsDelay);
}

float getProfit(float jobOnTheWave, float nextLevelJobOnTheWave, float cost)
{ return ((nextLevelJobOnTheWave - jobOnTheWave) / cost) * 0.01; }

class VirtualTower
{
	private:
		std::vector<Parameter*> parameters;
		float distanceCovered,
			  nextLevelDistanceCovered,
			  jobOnTheWave,
			  nextLevelJobOnTheWave,
			  nextLevelProfit;

		void recalculateJobOnTheWave()
		{
			jobOnTheWave = getJobOnTheWave(distanceCovered,
										   parameters[DAMAGE]->getValue(),
										   parameters[SHOTS_DELAY]->getValue());
		}

		void recalculateNextLevelJobOnTheWave()
		{
			nextLevelJobOnTheWave =
							getJobOnTheWave(distanceCovered,
											parameters[DAMAGE]->getNextValue(),
											parameters[SHOTS_DELAY]->getNextValue());
		}

		void recalculateFirstNextLevelProfit()
		{
			recalculateJobOnTheWave();
			recalculateNextLevelJobOnTheWave();
			nextLevelProfit = getProfit(jobOnTheWave, nextLevelJobOnTheWave, parameters[UPGRADE_COST]->getValue());
		}

		void recalculateNextLevelProfit()
		{
			jobOnTheWave = nextLevelJobOnTheWave;
			recalculateNextLevelJobOnTheWave();
			nextLevelProfit = getProfit(jobOnTheWave, nextLevelJobOnTheWave, parameters[UPGRADE_COST]->getValue());
		}

	public:
		VirtualTower(TowerSpecification *specification,
					 float distanceCovered, float nextLevelDistanceCovered):
		distanceCovered(distanceCovered), nextLevelDistanceCovered(nextLevelDistanceCovered)
		{
			std::vector<Parameter*>* specificationParametersPointer =
				specification->getParametersPointer();
			parameters.resize(specificationParametersPointer->size());
			for (unsigned int i = 0; i < parameters.size(); i++)
				parameters[i] = new Parameter(*(*specificationParametersPointer)[i]);
			recalculateFirstNextLevelProfit();
		}

		float getNextLevelProfit()
		{ return nextLevelProfit; }

		void upgrade()
		{
			setNextParametersValues(parameters);
			recalculateNextLevelProfit();
		}

		unsigned int getUpgradeCost()
		{ return parameters[UPGRADE_COST]->getValue(); }
};
