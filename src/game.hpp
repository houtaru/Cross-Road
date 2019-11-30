#pragma once
#include "view.hpp"

#include <memory>

class Game {
	public:
		static std::shared_ptr<Game> getInstance();

		Game();
		virtual ~Game();

		void start();
	
	private:
		static std::shared_ptr<Game> instance;
		static std::shared_ptr<View> view;
};