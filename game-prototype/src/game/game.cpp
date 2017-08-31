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

		MapManager mapManager(WINDOW_WIDTH, WINDOW_HEIGHT);
		mapManager.load("level_01", "assets/maps/level_01/map.tmx");

		Level* level = mapManager.getLevel("level_01");
		renderer.setRendererSize(level->getLevelWidth(), level->getLevelHeight());

		AnimationsManager animationsManager;
		animationsManager.load("player", "assets/sprites/player/ash.json");

		EventManager eventManager;

		Player player(renderer.createTexture("assets/sprites/player/ash.png"), level->getPlayerPosition(), level->getPlayerSpeed(), animationsManager.getAnimationsTo("player"), &eventManager);

		Camera camera(level->getCamera(), level->getCameraSpeed(), level->getLevelWidth(), level->getLevelHeight());

		CollisionsManager collisionsManager(level->getCollisions(), &eventManager);

		TriggerManager triggerManager(level->getTriggers(), &eventManager);

		AudioManager audioManager(&eventManager);
		audioManager.load("pokemon", "assets/sounds/musics/pokemon.wav", MUSIC);
		audioManager.load("steps", "assets/sounds/effects/steps.wav", EFFECT);
		audioManager.load("enter_door", "assets/sounds/effects/enter_door.wav", EFFECT);
		audioManager.play("pokemon", MUSIC, 10, -1);

		StaticSprite levelSprite(renderer.createTexture("assets/maps/level_01/atlas.png"), 0, 0, level->getTileSetImageWidth(), level->getTileSetImageHeight());

		Command* command = NULL;
		while (!window.isClosed())
		{
			renderer.clear();

			command = input.handle();
			command->execute(player);

			for (auto const& tile : level->getTilesLayer1()) {
				if (camera.isVisible(tile.second)) { // draws only visible tiles on layer1
					levelSprite.setSrcRect(tile.first);
					levelSprite.setDestRect(tile.second);
					renderer.draw(&levelSprite);
				}
			}

			renderer.draw(player.getSprite());

			for (auto const& tile : level->getTilesLayer2()) {
				if (camera.isVisible(tile.second)) { // draws only visible tiles on layer2
					levelSprite.setSrcRect(tile.first);
					levelSprite.setDestRect(tile.second);
					renderer.draw(&levelSprite);
				}
			}

			// display collisions and triggers (only on debug mode)
			renderer.showCollisions(level->getCollisions());
			renderer.showTriggers(level->getTriggers());

			// updates camera position
			renderer.setRendererPosition(camera.getPosition(player.getSprite()->getDestRect(), player.getDirection()));

			renderer.render();
		}

		delete command;
		delete level;
	}

}