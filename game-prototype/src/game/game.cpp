#include "./game.h"

namespace game {

	Game::Game()
	{
		static const bool DEBUG_MODE = false;
		static const bool FULL_SCREEN = false;

		static const int WINDOW_WIDTH = 1280;
		static const int WINDOW_HEIGHT = 720;

		Window window("Game", WINDOW_WIDTH, WINDOW_HEIGHT, FULL_SCREEN, DEBUG_MODE);
		Renderer renderer = window.createRenderer();
		Input input(&window);

		MapManager mapManager(WINDOW_WIDTH, WINDOW_HEIGHT);
		mapManager.load("level_01", "assets/maps/level_01/map.tmx");

		Level* level = mapManager.getLevel("level_01");
		Camera camera(level->getCamera(), level->getCameraSpeed(), level->getLevelWidth(), level->getLevelHeight());

		renderer.setSize(level->getLevelWidth(), level->getLevelHeight());
		renderer.setCamera(&camera);
		renderer.setCollisions(level->getCollisions());
		renderer.setTriggers(level->getTriggers());

		EventManager eventManager;

		AnimationsManager animationsManager;
		animationsManager.load("player", "assets/sprites/player/ash.json");

		Player player(renderer.createTexture(animationsManager.getSprite("player")), level->getPlayerPosition(), level->getPlayerSpeed(), animationsManager.getAnimationsTo("player"), &eventManager);

		CollisionsManager collisionsManager(level->getCollisions(), &eventManager);
		TriggerManager triggerManager(level->getTriggers(), &eventManager);

		AudioManager audioManager(&eventManager);
		audioManager.load("pokemon", "assets/sounds/musics/pokemon.wav", MUSIC);
		audioManager.load("steps", "assets/sounds/effects/steps.wav", EFFECT);
		audioManager.load("enter_door", "assets/sounds/effects/enter_door.wav", EFFECT);
		audioManager.play("pokemon", MUSIC, 10, -1);

		StaticSprite levelSprite(renderer.createTexture(level->getTileSetImagePath()), 0, 0, level->getTileSetImageWidth(), level->getTileSetImageHeight());

		while (!window.isClosed())
		{
			renderer.clear();

			Command* command = input.handle();
			command->execute(player);

			for (auto const& tile : level->getTilesLayer1())
			{
				levelSprite.setSrcRect(tile.first);
				levelSprite.setDestRect(tile.second);
				renderer.draw(&levelSprite);
			}

			renderer.draw(player.getSprite());

			for (auto const& tile : level->getTilesLayer2())
			{
				levelSprite.setSrcRect(tile.first);
				levelSprite.setDestRect(tile.second);
				renderer.draw(&levelSprite);
			}

			camera.lookAt(player.getPosition(), player.getDirection());

			renderer.render();
		}

		delete level;
	}

	Game::~Game()
	{

	}

}
