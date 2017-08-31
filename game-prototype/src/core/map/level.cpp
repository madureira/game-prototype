#include "level.h"

namespace core { namespace tmx {

	Level::Level(TmxMap* tmxMap, unsigned int winWidth, unsigned int winHeight)
	{
		this->m_TileSetName = tmxMap->getTileset()->getName();
		this->m_TileSetWidth = tmxMap->getTileset()->getTileWidth();
		this->m_TileSetHeight = tmxMap->getTileset()->getTileHeight();
		this->m_TileSetCount = tmxMap->getTileset()->getTileCount();
		this->m_TileSetColumns = tmxMap->getTileset()->getColumns();
		this->m_TileSetImagePath = tmxMap->getTileset()->getImage()->getSource();
		this->m_TileSetImageWidth = tmxMap->getTileset()->getImage()->getWidth();
		this->m_TileSetImageHeight = tmxMap->getTileset()->getImage()->getHeight();
		this->m_LevelWidth = tmxMap->getWidth() * m_TileSetWidth;
		this->m_LevelHeight = tmxMap->getHeight() * m_TileSetHeight;

		for (auto const& layer : tmxMap->getLayers()) {
			int tileId = 0;
			int columnIdx = 0;
			int rowIdx = 0;

			for (auto const& tile : layer->getTiles()) {
				tileId = tile.getGid();

				int destX = 0;
				int destY = 0;

				if (columnIdx == tmxMap->getWidth() - 1)
				{
					destX = columnIdx * this->m_TileSetWidth;
					destY = rowIdx * this->m_TileSetHeight;
					columnIdx = 0;
					rowIdx++;
				}
				else {
					destX = columnIdx * this->m_TileSetWidth;
					destY = rowIdx * this->m_TileSetHeight;
					columnIdx++;
				}

				if (tileId == 0) {
					continue;
				}

				int tileSetX = ((tileId % this->m_TileSetColumns) - 1) * this->m_TileSetWidth;
				int tileSetY = ((int)tileId / this->m_TileSetColumns) * this->m_TileSetHeight;

				if (tileSetX < 0)
				{
					tileSetX = this->m_TileSetImageWidth - this->m_TileSetWidth;
					tileSetY -= this->m_TileSetHeight;
				}

				if (tileSetY < 0)
				{
					tileSetY = 0;
				}

				std::pair<SDL_Rect, SDL_Rect> tileRects;
				tileRects.first = { tileSetX, tileSetY, this->m_TileSetWidth, this->m_TileSetHeight };
				tileRects.second = { destX, destY, this->m_TileSetWidth, this->m_TileSetHeight };

				if (layer->getName() == "layer_0" || layer->getName() == "layer_1")
				{
					this->m_TilesLayer1.push_back(tileRects);
				}
				else if (layer->getName() == "layer_2")
				{
					this->m_TilesLayer2.push_back(tileRects);
				}
			}
		}

		for (auto const& objectGroup : tmxMap->getObjectGroups()) {
			if (objectGroup->getName() == "collisions")
			{
				for (auto const& collision : objectGroup->getObjects())
				{
					TmxPolyline polyline = collision.getPolyline();

					std::vector<TmxPoint> points = polyline.getPoints();

					if (points.size() > 0)
					{
						for (auto const& point : points)
						{
							this->m_Slopes.push_back(glm::vec2(point.x, point.y));
						}
					}
					else {
						this->m_Collisions.push_back({ collision.getX(), collision.getY(), collision.getWidth(), collision.getHeight() });
					}
				}
			}
			else if (objectGroup->getName() == "player")
			{
				TmxProperty playerProp = objectGroup->getObjects()[0].getProperties().getProperty("speed");

				if (playerProp.type == "int")
				{
					this->m_PlayerSpeed = std::stoi(playerProp.value);
				}

				this->m_PlayerPosition = glm::vec2(objectGroup->getObjects()[0].getX(), objectGroup->getObjects()[0].getY());
			}
			else if (objectGroup->getName() == "camera")
			{
				int cameraX = objectGroup->getObjects()[0].getX() - winWidth / 2;
				int cameraY = objectGroup->getObjects()[0].getY() - winHeight / 2;
				TmxProperty cameraProp = objectGroup->getObjects()[0].getProperties().getProperty("speed");

				if (cameraProp.type == "int")
				{
					this->m_CameraSpeed = std::stoi(cameraProp.value);
				}

				if (cameraX < 0) {
					cameraX = 0;
				}

				if (cameraY < 0) {
					cameraY = 0;
				}

				if (cameraX + winWidth >= this->getLevelWidth()) {
					cameraX = this->getLevelWidth() - winWidth;
				}

				if (cameraY + winHeight >= this->getLevelHeight()) {
					cameraY = this->getLevelHeight() - winHeight;
				}

				this->m_Camera = { cameraX, cameraY, (int) winWidth, (int) winHeight };
			}
			else if (objectGroup->getName() == "triggers")
			{
				for (auto const& trigger : objectGroup->getObjects())
				{
					this->m_Triggers.push_back(new Trigger(trigger.getName(), trigger.getX(), trigger.getY(), trigger.getWidth(), trigger.getHeight()));
				}
			}
		}
		
	}

	Level::~Level()
	{
		for (std::vector<Trigger*>::iterator it = this->m_Triggers.begin(); it != this->m_Triggers.end(); ++it)
		{
			delete (*it);
		}
		this->m_Triggers.clear();
	}

} }