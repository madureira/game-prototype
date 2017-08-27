#include "level.h"

namespace core { namespace tmx {

	Level::Level(TmxMap* tmxMap)
	{
		m_TileSetName = tmxMap->getTileset()->getName();
		m_TileSetWidth = tmxMap->getTileset()->getTileWidth();
		m_TileSetHeight = tmxMap->getTileset()->getTileHeight();
		m_TileSetCount = tmxMap->getTileset()->getTileCount();
		m_TileSetColumns = tmxMap->getTileset()->getColumns();
		m_TileSetImagePath = tmxMap->getTileset()->getImage()->getSource();
		m_TileSetImageWidth = tmxMap->getTileset()->getImage()->getWidth();
		m_TileSetImageHeight = tmxMap->getTileset()->getImage()->getHeight();
		m_LevelWidth = tmxMap->getWidth() * m_TileSetWidth;
		m_LevelHeight = tmxMap->getHeight() * m_TileSetHeight;

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
					destX = columnIdx*m_TileSetWidth;
					destY = rowIdx*m_TileSetHeight;
					columnIdx = 0;
					rowIdx++;
				}
				else {
					destX = columnIdx*m_TileSetWidth;
					destY = rowIdx*m_TileSetHeight;
					columnIdx++;
				}

				if (tileId == 0) {
					continue;
				}

				int tileSetX = ((tileId % m_TileSetColumns) - 1) * m_TileSetWidth;
				int tileSetY = ((int)tileId / m_TileSetColumns) * m_TileSetHeight;

				if (tileSetX < 0)
				{
					tileSetX = m_TileSetImageWidth - m_TileSetWidth;
					tileSetY -= m_TileSetHeight;
				}

				if (tileSetY < 0)
				{
					tileSetY = 0;
				}

				std::pair<SDL_Rect, SDL_Rect> tileRects;
				tileRects.first = { tileSetX, tileSetY, m_TileSetWidth, m_TileSetHeight };
				tileRects.second = { destX, destY, m_TileSetWidth, m_TileSetHeight };

				if (layer->getName() == "layer_0" || layer->getName() == "layer_1")
				{
					m_TilesLayer1.push_back(tileRects);
				}
				else if (layer->getName() == "layer_2")
				{
					m_TilesLayer2.push_back(tileRects);
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
							m_Slopes.push_back(glm::vec2(point.x, point.y));
						}
					}
					else {
						m_Collisions.push_back({ collision.getX(), collision.getY(), collision.getWidth(), collision.getHeight() });
					}
				}
			}
			else if (objectGroup->getName() == "player")
			{
				m_PlayerPosition = { objectGroup->getObjects()[0].getX(), objectGroup->getObjects()[0].getY(), 0, 0 };
			}
		}
		
	}

	Level::~Level()
	{

	}

} }