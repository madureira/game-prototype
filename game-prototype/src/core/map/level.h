#pragma once

#include <SDL2/SDL.h>
#include <glm/vec2.hpp>
#include <vector>
#include <string>
#include "tiled/tmx_map.h"
#include "../entities/trigger.h"

namespace core { namespace tmx {

	using namespace entities;

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
		std::vector<Trigger> m_Triggers;
		SDL_Rect m_Camera;
		glm::vec2 m_PlayerPosition;
		unsigned int m_CameraSpeed;
		unsigned int m_PlayerSpeed;

	public:
		Level(TmxMap* tmxMap, unsigned int winWidth, unsigned int winHeight);
		~Level();

		inline std::string getTileSetName() const { return m_TileSetName; }
		inline int getTileSetWidth() const { return m_TileSetWidth; }
		inline int getTileSetHeight() const { return m_TileSetHeight; }
		inline int getTileSetCount() const { return m_TileSetCount; }
		inline int getTileSetColumns() const { return m_TileSetColumns; }
		inline std::string getTileSetImagePath() const { return m_TileSetImagePath; }
		inline int getTileSetImageWidth() const { return m_TileSetImageWidth; }
		inline int getTileSetImageHeight() const { return m_TileSetImageHeight; }
		inline std::vector<std::pair<SDL_Rect, SDL_Rect>> getTilesLayer1() const { return m_TilesLayer1; }
		inline std::vector<std::pair<SDL_Rect, SDL_Rect>> getTilesLayer2() const { return m_TilesLayer2; }
		inline std::vector<SDL_Rect> getCollisions() const { return m_Collisions; }
		inline std::vector<glm::vec2> getSlopes() const { return m_Slopes; };
		inline glm::vec2 getPlayerPosition() const { return m_PlayerPosition; }
		inline int getLevelWidth() const { return m_LevelWidth; }
		inline int getLevelHeight() const { return m_LevelHeight; }
		inline SDL_Rect getCamera() const { return m_Camera; };
		inline unsigned int getCameraSpeed() const { return m_CameraSpeed; }
		inline unsigned int getPlayerSpeed() const { return m_PlayerSpeed; }
		inline std::vector<Trigger> getTriggers() { return m_Triggers; };
	};

} }