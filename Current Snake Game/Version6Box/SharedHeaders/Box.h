	#ifndef BOX
	#define BOX

	#include <stdio.h>
	#include <stdlib.h>
	#include <SFML/Graphics.hpp>
	#include <iostream>

	// See Version 1 - 4 for info on using templates

	namespace GameBoxes
	{
		class Box
		{
		public:
			Box(); //Initializes black screen of size 600 by 400 with 20 x 20 block size.

			Box(int width, int height, int xSize, int ySize);
				//Initialized custom black screen size based on command line arguments.
				
			Box(const Box &square);

			void getSizeArray(int (&array)[4]) const;
				//Returns Screen Size Parameters
			
			void createBackGroundTexture(sf::Image & background, sf::Texture & texture);
				//Creates the black screen for drawing

		private:
			int windowWidth;
			int windowHeight;
			int blockXSize;
			int blockYSize;

		};
	} //GameBoxes



	#endif //BOX