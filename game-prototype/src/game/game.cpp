#include "game.h"

namespace game {

	Game::Game()
	{
#ifdef DEBUG
		static const bool DEBUG_MODE = true;
		static const bool FULL_SCREEN = false;
#else
		static const bool DEBUG_MODE = false;
		static const bool FULL_SCREEN = true;
#endif
		static const int WINDOW_WIDTH = 1280;
		static const int WINDOW_HEIGHT = 720;

		Window window("Game", WINDOW_WIDTH, WINDOW_HEIGHT, FULL_SCREEN, DEBUG_MODE);
		Renderer renderer = window.createRenderer();
		Input input(&window);

		AudioManager audioManager;
		audioManager.load("pokemon", "assets/sounds/Pokemon_Opening.wav", MUSIC);
		audioManager.load("level_finish", "assets/sounds/finish_effect.wav", EFFECT);
		audioManager.load("step", "assets/sounds/step.wav", EFFECT);

		AnimationsManager animationsManager;
		animationsManager.load("player", "assets/sprites/ash_256x256.json");

		MapManager mapManager(WINDOW_WIDTH, WINDOW_HEIGHT);
		mapManager.load("level_1", "assets/maps/map.tmx");

		Level* level = mapManager.getLevel("level_1");
		renderer.setRendererSize(level->getLevelWidth(), level->getLevelHeight());

		Camera camera(level->getCamera(), level->getCameraSpeed(), level->getLevelWidth(), level->getLevelHeight());

		std::vector<SDL_Rect> collisions = level->getCollisions();
		std::vector<glm::vec2> slopes = level->getSlopes();

		std::string playerSpritePath = "assets/sprites/" + animationsManager.getSpriteNameTo("player");
		Player player(renderer.createTexture(playerSpritePath), level->getPlayerPosition(), level->getPlayerSpeed(), animationsManager.getAnimationsTo("player"), &collisions, &slopes);

		std::vector<std::pair<SDL_Rect, SDL_Rect>> layer1 = level->getTilesLayer1();
		std::vector<std::pair<SDL_Rect, SDL_Rect>> layer2 = level->getTilesLayer2();
		StaticSprite levelSprite(renderer.createTexture("assets/maps/" + level->getTileSetImagePath()), 0, 0, level->getTileSetImageWidth(), level->getTileSetImageHeight());

		audioManager.play("pokemon", MUSIC, 10, -1);
		
		int playingStep = false;

		Command* command = NULL;
		while (!window.isClosed())
		{
			renderer.clear();

			command = input.handle();
			command->execute(player);

			for (auto const& tile : layer1) {
				if (camera.isVisible(tile.second)) { // draws only visible tiles on layer1
					levelSprite.setSrcRect(tile.first);
					levelSprite.setDestRect(tile.second);
					renderer.draw(&levelSprite);
				}
			}

			renderer.draw(player.getSprite());

			for (auto const& tile : layer2) {
				if (camera.isVisible(tile.second)) { // draws only visible tiles on layer2
					levelSprite.setSrcRect(tile.first);
					levelSprite.setDestRect(tile.second);
					renderer.draw(&levelSprite);
				}
			}

			glm::vec2 playerDirection = player.getDirection();

			if (playingStep && (playerDirection.x == 0 && playerDirection.y == 0))
			{
				playingStep = false;
				audioManager.stop("step", EFFECT);
			}
			else if (!playingStep && (playerDirection.x != 0 || playerDirection.y != 0)) {
				playingStep = true;
				audioManager.play("step", EFFECT, 100, -1);
			}

			// display collisions *only on debug mode
			renderer.showCollisions(collisions);

			// updates camera position
			renderer.setRendererPosition(camera.getPosition(player.getSprite()->getDestRect(), playerDirection));

			renderer.render();
		}

		delete command;
		delete level;
	}

}