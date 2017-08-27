#include "game.h"

namespace game {

	Game::Game()
	{
		static const int WINDOW_WIDTH = 1280;
		static const int WINDOW_HEIGHT = 720;
		static const bool FULLSCREEN = false;
		static const bool SHOW_FPS = false;
		static const bool SHOW_COLLISIONS = false;

		Window window("Game", WINDOW_WIDTH, WINDOW_HEIGHT, FULLSCREEN);
		Renderer* renderer = window.createRenderer();
		Input input(&window);

		MapLoader mapLoader;
		Level level = mapLoader.parse("assets/maps/map.tmx");

		AudioManager audioManager;
		audioManager.load("pokemon", "assets/sounds/Pokemon_Opening.wav", MUSIC);

		SDL_Rect viewport = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
		SDL_Rect mapPosition = { 0, 0, level.getLevelWidth(), level.getLevelHeight() };

		bool updateViewportX = false;
		bool updateViewportY = false;

		if (mapPosition.w > viewport.w)
		{
			updateViewportX = true;
		}
		
		if (mapPosition.h > viewport.h)
		{
			updateViewportY = true;
		}

		SDL_Texture* levelTileSetTexture = renderer->createTexture("assets/maps/" + level.getTileSetImagePath());
		SDL_Texture* levelLayer1 = renderer->createTextureLayer(level.getLevelWidth(), level.getLevelHeight());
		SDL_Texture* levelLayer2 = renderer->createTextureLayer(level.getLevelWidth(), level.getLevelHeight());
		
		StaticSprite levelSprite1(levelLayer1, 0, 0, level.getLevelWidth(), level.getLevelHeight());
		StaticSprite levelSprite2(levelLayer2, 0, 0, level.getLevelWidth(), level.getLevelHeight());
		
		AnimationsManager animationsManager("assets/sprites/ash_256x256.json");

		std::vector<SDL_Rect> collisions = level.getCollisions();
		std::vector<glm::vec2> slopes = level.getSlopes();

		Player player(renderer->createTexture("assets/sprites/" + animationsManager.getSpriteName()), level.getPlayerPosition().x, level.getPlayerPosition().y, animationsManager.getAnimations(), &collisions, &slopes, &mapPosition, &viewport);
		player.setViewport(updateViewportX, updateViewportY);

		std::vector<std::pair<SDL_Rect, SDL_Rect>> layer1 = level.getTilesLayer1();
		std::vector<std::pair<SDL_Rect, SDL_Rect>> layer2 = level.getTilesLayer2();

		StaticSprite layerSprite1(levelTileSetTexture, 0, 0, level.getTileSetImageWidth(), level.getTileSetImageHeight());
		renderer->setLayerTarget(levelLayer1);
		renderer->clear();
		for (auto const& tile : layer1) {
			layerSprite1.setSrcRect(tile.first);
			layerSprite1.setDestRect(tile.second);
			renderer->draw(&layerSprite1);
		}
		renderer->setLayerTarget(NULL);

		StaticSprite layerSprite2(levelTileSetTexture, 0, 0, level.getTileSetImageWidth(), level.getTileSetImageHeight());
		renderer->setLayerTarget(levelLayer2);
		renderer->clear();
		for (auto const& tile : layer2) {
			layerSprite2.setSrcRect(tile.first);
			layerSprite2.setDestRect(tile.second);
			renderer->draw(&layerSprite2);
		}
		renderer->setLayerTarget(NULL);

		audioManager.play("pokemon", MUSIC);

		FPS* fps = renderer->fpsCounter();
		while (!window.isClosed())
		{
			Command* command = input.handle();
			renderer->clear();
			command->execute(player);

			SDL_Rect levelRect1 = levelSprite1.getDestRect();
			SDL_Rect levelRect2 = levelSprite1.getDestRect();

			if (updateViewportX)
			{
				levelRect1.x = viewport.x;
				levelRect2.x = viewport.x;
			}

			if (updateViewportY)
			{
				levelRect1.y = viewport.y;
				levelRect2.y = viewport.y;
			}

			levelSprite1.setDestRect(levelRect1);
			levelSprite2.setDestRect(levelRect2);

			renderer->draw(&levelSprite1);
			renderer->draw(player.getSprite());
			renderer->draw(&levelSprite2);

			if (SHOW_COLLISIONS)
			{
				renderer->showCollisions(collisions, viewport);
			}

			if (SHOW_FPS)
			{
				fps->show();
			}

			renderer->render();
		}
	}

}