	#include <string>
	#include <vector>
	#include <memory>
	#include "../Headers/GridPiece.h"

	// See Version 1 - 4 for info on using templates
  // TestCommit


	int main(int argc, char **argv)
	{
			//The following code initializes an array of box children and draws a box at each background
			//position
				//To_Implement: Children Class
		std::unique_ptr<GameBoxes::Box> squareBackground(new GameBoxes::Box(std::stoi(argv[1]), std::stoi(argv[2]),
								   std::stoi(argv[3]), std::stoi(argv[4])));

		int cArgs[4];
		(*squareBackground).getSizeArray(cArgs);

		sf::RenderWindow window( sf::VideoMode(cArgs[0], cArgs[1]), "SFML window");
		sf::Image background;
		sf::Texture texture;
		(*squareBackground).createBackGroundTexture(background, texture);
			//create a background and a texture, then initialize them in the class that handles it.
		sf::Sprite sprite(texture);
			//create the sprite for drawing

		// Create GridPieces : needs squareArray to inherit from it
		typedef std::shared_ptr<GameBoxes::GridPiece> GridSharedPointer;
		typedef std::vector< GridSharedPointer > GridPieceVector;
		std::vector < GridPieceVector > twoDGridVector;
			// Uses a typedef to create a shared_pointer
			// Uses a typedef to create a shared_pointer container of class objects
			// Declares a 2D vector

		for (int x_index = 0; x_index < cArgs[0] / cArgs[2]; x_index++) // Number of blocks in row
		{
			GridPieceVector rowOfGridPiece;
				// I CAN NOT PREALLOCATE SIZE. SEG FAULT
			twoDGridVector.emplace_back(rowOfGridPiece);
				// Emplace back prevents issues with SharedPointers
			for (int y_index = 0; y_index < cArgs[1] / cArgs[3]; y_index++) // number of blocks in column
			{
				twoDGridVector[x_index].emplace_back(GridSharedPointer(new GameBoxes::GridPiece(x_index,
				y_index, *squareBackground)));
					// Again emplace_back is safer
			}
		}
				// See version 4 for debugging

			// Declaring time variables
			// https://stackoverflow.com/questions/20957630/my-sfml-c-program-is-working-as-expected-but-how
			// -to-make-movement-slow/20958283#20958283
		sf::Time timePerFrame = sf::seconds(1.0f / 60.0f); // 60 frames per second
		sf::Clock deltaClock; // This tracks how much time has passed since last frame
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		int x_index = 0, y_index = 0; // indexes for twoDGridVector
		bool dead = true;

		while (window.isOpen())
        {
			sf::Event event;
			window.setVerticalSyncEnabled(true);

			window.display();

			if (dead == true)
			{
				window.clear();
				window.draw(sprite);
				dead = false;
					// create snake here
			}

			sf::Time deltaTime = deltaClock.restart(); // Restart resets time
			timeSinceLastUpdate += deltaTime;

			while (timeSinceLastUpdate >= timePerFrame || (x_index == 0 && y_index == 0))
				// Eventually use this to move the snake
			{

				window.draw(*(twoDGridVector[x_index][y_index])); // Draw a GridPiece
					// Move snake here instead and (x_index == 0 && y_index == 0) dissapears.
					// Move in random direction at the start, then in last moved direction otherwise
				timeSinceLastUpdate = sf::Time::Zero;


				y_index = (y_index + 1) % (cArgs[1] / cArgs[3]);
				if (y_index == 0)
				{
					x_index = (x_index +1) % (cArgs[0] / cArgs[2]);
				}
					// The above code increments the double for loop every time deltaTime reaches a
					// threshhold.

				break; // Stops while loop from immediately drawing Grid (0,0) when it resets)
			}

            // handle all events
            while (window.pollEvent(event))
            {



				// Make double threaded program where the main thread (drawing all squares) is constantly redrawing the
				// entire board (eventually just the snake) at a rate of one square every 2.5 seconds. Then there is a
				// second thread which 1) asks for user input (choose a square and change its color) and 2) redraws the
				// specified square (eventually the snake). When user input is given via 1) the threads join and 2) happens
				// BEFORE the main thread begins redrawing all the squares as a single square every 2.5 seconds.

				/*
				sf::Clock clock;
				for (int x_index = 0; x_index < cArgs[0] / cArgs[2]; x_index++)
				{
					for (int y_index = 0; y_index < cArgs[1] / cArgs[3]; y_index++)
					{
						if (clock.getElapsedTime().asSeconds() >= 1)
						{
							sf::Time elapsed = clock.restart();
							window.draw(*(twoDGridVector[x_index][y_index]));
						}

					}
				}	// See Version4 for debugging
				*/

				// Remember to declare each GridPiece as "GridPiece * squareName = new GridPiece(Init)"
					//Then when you are done, set all the pointers to nullptr and delete everything.

				// TODO: Start from bottom right and build out the squares right -> left and bottom -> top
				// such that the maximum possible space is filled. Create a 2D array of GridPiece's for
				// drawing. Then, once they are all drawn go through and hook the pointers up to every
				// GridPiece to the top, left, bottom and right. If a side is an end, make it a NULLPOINTER
					//calculate the size of the array by using getSizeArray from Box.h/Box.cpp

				// Have a fifth pointer, a int variable, and a Move function in GridPiece.
				// A Gridpiece variable in main will be the head of the snake, and the fifth pointer will
				// point to the next block of snake behind it. The int variable will say what position in
				// the snake it is, 0 if no snake, and -1 if apple. The move function, when used on the head
				// of the snake, will move the head in one of 3 possible directions by updating the int
				// variable in the block it moves to. Every time the int variable is changed in a GridPiece,
				// the color updates. 0 = green, -1 = red, >0 = white. The Snake head has the highest number
				// Signifying the length of the snake. Then the int variable of every block behind
				// the head is reduced by 1. The block that becomes 1 sets its fifth pointer to NULLPOINTER.
				// If the Snake eats an apple, the new head is given +1 value of the current head or greater,
				// rather than == to it and none of the blocks behind are changed. If the value given is >+1,
				// then randomly grow the snake from the tail until a GridPiece has int value 1.

				// When creating the snake, choose a random spot on the grid as the head and grow it randomly
				// in the available directions. If the snake dies, reset the board and randomize snake again.

                //Close window: exit
                if (event.type == sf::Event::Closed)
                            window.close();
            }
            // update

			if (x_index == 0 && y_index == 0)
			{
				dead = true;
				// The x_index == 0 && y_index == 0 condition is replaced with the snake
				// hitting its own body or a wall
			}

			// Have an if statement where if the snake eats an apple, it random grows. Then spawn another apple.

        }

		return 0;
	}

	//  See makefileV5 to compile
	// ./SnakeGame 800 800 20 20
