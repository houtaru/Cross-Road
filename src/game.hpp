#pragma once

#include "view.hpp"
#include "sound.hpp"
#include "screen.hpp"

#include <memory>
#include <vector>

class Game {
	public:
		static std::shared_ptr<Game> getInstance();

		Game();
		virtual ~Game();

		void start();

		const Uint8 *getKeystate();
	
	private:
		static std::shared_ptr<Game> instance;
		static std::shared_ptr<View> view;
		static std::shared_ptr<Sound> sound;

		static const int FRAME_PER_SECOND;
		static const int SDL_DELAY_PER_FRAME;

		bool running;
		SDL_Event event;
		const Uint8 *keystate;
		std::vector<std::shared_ptr<Screen>> screens;

		// Initialize game
		void init();

		// Main loop
		void loop();
		
		// return to previous screen
		void backToPreScr();

		// switch to next screen
		void switchToNextScr(ScreenType nextScreenType);
};
