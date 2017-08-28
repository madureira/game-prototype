#include "game.h"

namespace game {

	Game::Game()
	{
#ifdef DEBUG
		static const bool FULLSCREEN = false;
		static const bool SHOW_FPS = true;
		static const bool SHOW_COLLISIONS = true;
		static const bool PLAY_AUDIO = false;
#else
		static const bool FULLSCREEN = true;
		static const bool SHOW_FPS = false;
		static const bool SHOW_COLLISIONS = false;
		static const bool PLAY_AUDIO = true;
#endif

		static const int WINDOW_WIDTH = 1280;
		static const int WINDOW_HEIGHT = 720;

		Window window("Game", WINDOW_WIDTH, WINDOW_HEIGHT, FULLSCREEN);
		Renderer* renderer = window.createRenderer();
		Input input(&window);

		MapLoader mapLoader;
		Level level = mapLoader.parse("assets/maps/map.tmx");

		AudioManager audioManager;
		audioManager.load("pokemon", "assets/sounds/Pokemon_Opening.wav", MUSIC);
		SDL_Rect playerPos = level.getPlayerPosition();

		int cameraX = playerPos.x - WINDOW_WIDTH / 2;
		int cameraY = playerPos.y - WINDOW_HEIGHT / 2;

		if (cameraX < 0) {
			cameraX = 0;
		}

		if (cameraY < 0) {
			cameraY = 0;
		}

		if (cameraX + WINDOW_WIDTH >= level.getLevelWidth()) {
			cameraX = level.getLevelWidth() - WINDOW_WIDTH;
		}

		if (cameraY + WINDOW_HEIGHT >= level.getLevelHeight()) {
			cameraY = level.getLevelHeight() - WINDOW_HEIGHT;
		}

		SDL_Rect viewport = { cameraX, cameraY, WINDOW_WIDTH, WINDOW_HEIGHT };
		SDL_Rect mapPosition = { 0, 0, level.getLevelWidth(), level.getLevelHeight() };

		renderer->setRendererSize(level.getLevelWidth(), level.getLevelHeight());

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
		
		AnimationsManager animationsManager("assets/sprites/ash_256x256.json");

		std::vector<SDL_Rect> collisions = level.getCollisions();
		std::vector<glm::vec2> slopes = level.getSlopes();

		Player player(renderer->createTexture("assets/sprites/" + animationsManager.getSpriteName()), level.getPlayerPosition().x, level.getPlayerPosition().y, animationsManager.getAnimations(), &collisions, &slopes, &mapPosition, &viewport);
		player.setViewport(updateViewportX, updateViewportY);

		std::vector<std::pair<SDL_Rect, SDL_Rect>> layer1 = level.getTilesLayer1();
		std::vector<std::pair<SDL_Rect, SDL_Rect>> layer2 = level.getTilesLayer2();

		StaticSprite layerSprite1(levelTileSetTexture, 0, 0, level.getTileSetImageWidth(), level.getTileSetImageHeight());
		StaticSprite layerSprite2(levelTileSetTexture, 0, 0, level.getTileSetImageWidth(), level.getTileSetImageHeight());

		if (PLAY_AUDIO)
		{
			audioManager.play("pokemon", MUSIC);
		}

		FPS* fps = renderer->fpsCounter();
		while (!window.isClosed())
		{
			Command* command = input.handle();
			renderer->clear();
			command->execute(player);

			for (auto const& tile : layer1) {
				if (tile.second.x + tile.second.w * 2 >= viewport.x + tile.second.w &&
					tile.second.y + tile.second.h * 2 >= viewport.y + tile.second.h &&
					tile.second.x <= viewport.x + viewport.w &&
					tile.second.y <= viewport.y + viewport.h) {
					layerSprite1.setSrcRect(tile.first);
					layerSprite1.setDestRect(tile.second);
					renderer->draw(&layerSprite1);
				}
			}

			renderer->draw(player.getSprite());

			for (auto const& tile : layer2) {
				if (tile.second.x + tile.second.w * 2 >= viewport.x + tile.second.w &&
					tile.second.y + tile.second.h * 2 >= viewport.y + tile.second.h &&
					tile.second.x <= viewport.x + viewport.w &&
					tile.second.y <= viewport.y + viewport.h) {
					layerSprite2.setSrcRect(tile.first);
					layerSprite2.setDestRect(tile.second);
					renderer->draw(&layerSprite2);
				}
			}

			renderer->setRendererPosition(viewport.x, viewport.y);

			if (SHOW_COLLISIONS)
			{
				renderer->showCollisions(collisions);
			}

			if (SHOW_FPS)
			{
				fps->show();
			}

			renderer->render();
		}
	}

}