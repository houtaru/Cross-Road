# Cross Road

This is, as the name, a game that you will move the player character cross the roads so that it does not collide with obstacles. There are traffic lights (the obstacles move fast with green, slow with yellow and stop for a few seconds with red) to make the game easier.

### Requirement
You need the following libraries and tools to build and run this game:
```
cmake
SDL2
SDL2_image
SDL2_mixer
SDL2_ttf
```


### Build
First create a foler named build, which will be used to build and run everything. Typing the following lines in the command line to build. <br />
*Tips: If you want more obstacle skins, paste them into **assets/images/obstacle/** before build the game. Or remove **build** folder and do this step again to update skin.*
```
mkdir build
cd build
cmake ..
make
```


### Run
Finally, run and enjoy our game
```
./src/cross_road
```


### Further improvements
* The GUI can be optimized. 
* Movement of player character is still somehow not smooth as we expected. 
* Arcade mode can be created to make the game more interesting.
* **There is a big problem that when you click on back button, it will be a series of click so that you will quick the game. Therefore, click on the most bottom left corner to avoid that.**
