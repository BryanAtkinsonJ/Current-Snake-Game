	#ifndef GRIDPIECE_H
	#define GRIDPIECE_H
		//The preprocessor lines above needed to be changed from Gridpiece to work

	// See Version 1 - 4 for info on using templates

	#include "../../SharedHeaders/Box.h"
	namespace GameBoxes
	{
	
		class GridPiece : public GameBoxes::Box, public sf::Drawable, public sf::Transformable
		{
		public:
			GridPiece(int xPositionNumb, int yPositionNumb, Box square);
				// Class Constructor. Sets Square Sizes Based Off Position and BlockSize
				
			GridPiece();
				// Dummy Constructor. If colorDesignation = -2, then setPosition gives that pointer
				// a null pointer
				
			void setPointers(GridPiece * leftSquare, GridPiece * rightSquare, GridPiece * topSquare,
						GridPiece * bottomSquare);
						
			void moveSnake();
			
			void setSquareType(int designation);
			
			void setNextSnakeBlock(GridPiece & snakeBody);
			
			int getColorDesignation();
		
		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			
			sf::Vector2f point1, point2, point3, point4;
				// Vertices determined by xPositionNumb and yPositionNumb during
				// construction
			sf::Texture m_texture;
				// TO DO: Put In Code That Creates The Largest Possible Rectangle in The Rendered Window
				
			GridPiece *gridConnect[4];
				// [0] is left grid, [1] is right grid, [2] is top grid, [3] is bottom grid
			GridPiece *nextToSnakeTail;
				// Pointer to the next Snake Square toward tail from current square
			int colorDesignation;
			sf::Color color;
				// >=1 is white, 0 is green, -1 is red
				// color.r changes red, color.g changes green, color.b changes blue
				
			int xIndexNumb;
			int yIndexNumb;
				// These two are going to be used to find boundaries of the grid.
		
		};
		
	} // GameBoxes





	#endif //GridPiece_H