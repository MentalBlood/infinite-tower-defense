#define PATH_END 0
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

class Map
{
	private:
		int mapHeight, mapWidth,
			x1, y1;
		char *path;

	public:
		Map(int height, int width):
			mapHeight(height), mapWidth(width), x1(0), y1(0)
		{
			path = (char*)malloc(sizeof(char)*16);
			path[0] = RIGHT;
			path[1] = PATH_END;
		}

		Map(char *fileName)
		{
			loadFile(fileName);
		}

		void loadFile(char *fileName)
		{
			delete path;

			FILE *file = fopen(fileName, "rb");

			//read map size and initial dot coordinates
			fscanf(file, "%d%d%d%d", &mapWidth, &mapHeight, &x1, &y1);

			//read path
			path = (char*)malloc(sizeof(char)*16);
			int pathIndex = 0;
			while (true)
			{
				char c = char(fgetc(file));
				if (!c) break;
				path[pathIndex] = c;
				++pathIndex;
				if (pathIndex % 16)
					path = (char*)realloc(path, sizeof(char)*(pathIndex+16));
			}
			path[pathIndex] = 0;
			++pathIndex;
			if (!(pathIndex % 16))
				path = (char*)realloc(path, sizeof(char)*pathIndex);
		}

		const sf::Texture& textureFromLoaded(unsigned int mapTextureHeight)
		{
			unsigned int mapTextureWidth = (unsigned int)(float(mapTextureHeight) * (float(mapHeight)/float(mapWidth)));

			//1. drawing cell texture
			unsigned int cellTextureSize = (unsigned int)(float(mapTextureWidth) / float(mapWidth));
			sf::RenderTexture cellRenderTexture;
			if (!cellRenderTexture.create(cellTextureSize, cellTextureSize)) Closed();

			cellRenderTexture.clear();

			//1.1 drawing rounded corners by circles
			sf::CircleShape circle((unsigned int)(float(cellTextureSize)/4), (std::size_t)cellTextureSize);
			circle.setFillColor(sf::Color(255, 0, 0));
			//1.1.1 upper left
			circle.setPosition(sf::Vector2f(float(cellTextureSize)/4, float(cellTextureSize)/4));
			cellRenderTexture.draw(circle);
			//1.1.2 upper right
			circle.setPosition(sf::Vector2f(3*float(cellTextureSize)/4, float(cellTextureSize)/4));
			cellRenderTexture.draw(circle);
			//1.1.3 bottom left
			circle.setPosition(sf::Vector2f(float(cellTextureSize)/4, 3*float(cellTextureSize)/4));
			cellRenderTexture.draw(circle);
			//1.1.4 bottom right
			circle.setPosition(sf::Vector2f(3*float(cellTextureSize)/4, 3*float(cellTextureSize)/4));
			cellRenderTexture.draw(circle);

			//1.2 drawing borders/interior
			sf::RectangleShape rectangle(sf::Vector2f(cellTextureSize, float(cellTextureSize)/2));
			rectangle.setFillColor(sf::Color(0, 0, 255));
			//1.2.1 left and right
			rectangle.setPosition(sf::Vector2f(0, float(cellTextureSize)/4));
			cellRenderTexture.draw(rectangle);
			//1.2.2 bottom and upper
			rectangle.setSize(sf::Vector2f(float(cellTextureSize)/4, float(cellTextureSize)));
			rectangle.setPosition(sf::Vector2f(float(cellTextureSize), 0));
			cellRenderTexture.draw(rectangle);

			cellRenderTexture.display();

			sf::Sprite cellSprite(cellRenderTexture.getTexture());

			//2. drawing map texture
			sf::RenderTexture mapRenderTexture;
			if (!mapRenderTexture.create(mapTextureWidth, mapTextureHeight)) Closed();

			mapRenderTexture.clear();

			//2.1 drawing towers cells
			cellSprite.setPosition(0, 0);
			float cellSpriteX = 0,
				  cellSpriteY = 0;
			for (int i = 0; i < mapHeight; i++, cellSpriteY += cellTextureSize)
				for (int j = 0; j < mapWidth; j++, cellSpriteX += cellTextureSize)
				{
					cellSprite.setPosition(sf::Vector2f(cellSpriteX, cellSpriteY));
					mapRenderTexture.draw(cellSprite);
				}

			//2.2 drawing path cells
			cellSprite.setColor(sf::Color(0, 255, 0));
			cellSpriteX = float(x1)*cellTextureSize;
			cellSpriteY = float(y1)*cellTextureSize;
			cellSprite.setPosition(sf::Vector2f(cellSpriteX, cellSpriteY));
			for (char *pathDirection = path; *path; path++)
			{
				if (*pathDirection == UP) cellSpriteY -= cellTextureSize;
				else if (*pathDirection == DOWN) cellSpriteY += cellTextureSize;
				else if (*pathDirection == LEFT) cellSpriteX -= cellTextureSize;
				else if (*pathDirection == RIGHT) cellSpriteX += cellTextureSize;
				cellSprite.setPosition(sf::Vector2f(cellSpriteX, cellSpriteY));
				mapRenderTexture.draw(cellSprite);
			}

			//2.3 returning map texture
			mapRenderTexture.display();
			return mapRenderTexture.getTexture();
		}
};
