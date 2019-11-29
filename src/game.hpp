#pragma once
#include "view.hpp"

#include <memory>

using namespace std;

class Game {
	public:
		static shared_ptr<Game> getInstance();

		Game();
		virtual ~Game();

		void start();
	
	private:
		static shared_ptr<Game> instance;
		static shared_ptr<View> view;
};