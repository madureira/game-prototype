#pragma once

#include <SDL2/SDL.h>
#include <glm/vec2.hpp>
#include <vector>
#include <string>
#include "tmx_map.h"

namespace core { namespace tmx {

	class Level {
	private:
		int m_LevelWidth;
		int m_LevelHeight;
		std::string m_TileSetName;
		int m_TileSetWidth;
		int m_TileSetHeight;
		int m_TileSetCount;
		int m_TileSetColumns;
		std::string m_TileSetImagePath;
		int m_TileSetImageWidth;
		int m_TileSetImageHeight;
		std::vector<std::pair<SDL_Rect, SDL_Rect>> m_TilesLayer1;
		std::vector<std::pair<SDL_Rect, SDL_Rect>> m_TilesLayer2;
		std::vector<SDL_Rect> m_Collisions;
		std::vector<glm::vec2> m_Slopes;
		SDL_Rect m_Camera;
		glm::vec2 m_PlayerPosition;
		unsigned int m_CameraSpeed;
		unsigned int m_PlayerSpeed;

	public:
		Level(TmxMap* tmxMap, unsigned int winWidth, unsigned int winHeight);
		~Level();

		std::string getTileSetName() const { return m_TileSetName; }
		int getTileSetWidth() const { return m_TileSetWidth; }
		int getTileSetHeight() const { return m_TileSetHeight; }
		int getTileSetCount() const { return m_TileSetCount; }
		int getTileSetColumns() const { return m_TileSetColumns; }
		std::string getTileSetImagePath() const { return m_TileSetImagePath; }
		int getTileSetImageWidth() const { return m_TileSetImageWidth; }
		int getTileSetImageHeight() const { return m_TileSetImageHeight; }
		std::vector<std::pair<SDL_Rect, SDL_Rect>> getTilesLayer1() const { return m_TilesLayer1; }
		std::vector<std::pair<SDL_Rect, SDL_Rect>> getTilesLayer2() const { return m_TilesLayer2; }
		std::vector<SDL_Rect> getCollisions() const { return m_Collisions; }
		std::vector<glm::vec2> getSlopes() const { return m_Slopes; };
		glm::vec2 getPlayerPosition() const { return m_PlayerPosition; }
		int getLevelWidth() const { return m_LevelWidth; }
		int getLevelHeight() const { return m_LevelHeight; }
		SDL_Rect getCamera() const { return m_Camera; };
		unsigned int getCameraSpeed() const { return m_CameraSpeed; }
		unsigned int getPlayerSpeed() const { return m_PlayerSpeed; }
	};

} }