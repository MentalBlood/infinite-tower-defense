class TowersInfoStack
{
	private:
		std::vector<TowerInfo*> towersInfo;

		float relativeX,
			  relativeY,
			  relativeWidth,
			  relativeHeight,
			  relativeIndent,
			  x, height;

	public:
		TowersInfoStack(const char *towersTexturesDir, const char *towersCharacteristicsDir,
						unsigned int count,
						float relativeX, float relativeY, float relativeWidth, float relativeHeight,
						float relativeIndent):
		relativeX(relativeX), relativeY(relativeY),
		relativeWidth(relativeWidth), relativeHeight(relativeHeight), relativeIndent(relativeIndent),
		x(windowSize.x * relativeX)
		{
			towersInfo.resize(count);
			char	textureFileName[32],
					characteristicsFileName[32];
			float currentTowerInfoRelativeX = relativeX,
				  currentTowerInfoRelativeY = relativeY,
				  currentTowerInfoRelativeWidth = relativeWidth,
				  currentTowerInfoRelativeHeight = (relativeHeight - relativeIndent*(count-1)) / count;
			for (unsigned int i = 0; i < towersInfo.size(); i++, 
				currentTowerInfoRelativeY += currentTowerInfoRelativeHeight + relativeIndent)
			{
				sprintf(textureFileName, "%s/%u.png", towersTexturesDir, i);
				sprintf(characteristicsFileName, "%s/%u.txt", towersCharacteristicsDir, i);
				towersInfo[i] =
					new TowerInfo(	new TowerSpecification(textureFileName, characteristicsFileName, i),
									currentTowerInfoRelativeX, currentTowerInfoRelativeY,
									currentTowerInfoRelativeWidth, currentTowerInfoRelativeHeight);
			}
		}

		~TowersInfoStack()
		{
			for (unsigned int i = 0; i < towersInfo.size(); i++)
				delete towersInfo[i];
		}

		void updatePositionAndSize()
		{
			x = windowSize.x * relativeX;
			height = windowSize.y * relativeHeight;
			float currentTowerInfoRelativeX = relativeX,
				  currentTowerInfoRelativeY = relativeY,
				  currentTowerInfoRelativeWidth = relativeWidth,
				  currentTowerInfoRelativeHeight =
					  (relativeHeight - relativeIndent * (towersInfo.size()-1)) / towersInfo.size();

			for (unsigned int i = 0; i < towersInfo.size(); i++, 
				currentTowerInfoRelativeY += currentTowerInfoRelativeHeight + relativeIndent)
				towersInfo[i]->
					changePositionAndSize(currentTowerInfoRelativeX, currentTowerInfoRelativeY,
										currentTowerInfoRelativeWidth, currentTowerInfoRelativeHeight);
		}

		void draw()
		{
			for (unsigned int i = 0; i < towersInfo.size(); i++)
				towersInfo[i]->draw();
		}

		bool click(float mouseX, float mouseY)
		{
			if (mouseX < x) return false;
			towersInfo[int(mouseY / height * towersInfo.size())]->click();
			return true;
		}
};
