	#include "../Headers/GridPiece.h"

	// See Version 1 - 4 for info on using templates

	namespace GameBoxes
	{
		GridPiece::GridPiece() : colorDesignation(-2), xIndexNumb(-1), yIndexNumb(-2),
			nextToSnakeTail(nullptr), gridConnect({nullptr,nullptr,nullptr,nullptr})
		{
		}
		
		GridPiece::GridPiece(int xPositionNumb, int yPositionNumb, Box square) : Box(square),
			colorDesignation(0), xIndexNumb(xPositionNumb), yIndexNumb(yPositionNumb),
			nextToSnakeTail(nullptr), gridConnect({nullptr,nullptr,nullptr,nullptr})
		{			
			color.g = 255;
			color.r = 0;
			color.b = 0;
			
			int gridDimensions[4];
			getSizeArray(gridDimensions);
			
			point1 = sf::Vector2f((gridDimensions[0] - (xIndexNumb + 1) * gridDimensions[2]),
				(gridDimensions[1] - (yIndexNumb + 1) * gridDimensions[3]));
			point2 = sf::Vector2f((gridDimensions[0] - xIndexNumb * gridDimensions[2]),
				(gridDimensions[1] - (yIndexNumb + 1) * gridDimensions[3]));
			point3 = sf::Vector2f((gridDimensions[0] - xIndexNumb * gridDimensions[2]),
				(gridDimensions[1] - yIndexNumb * gridDimensions[3]));
			point4 = sf::Vector2f((gridDimensions[0] - (xIndexNumb + 1) * gridDimensions[2]),
				(gridDimensions[1] - yIndexNumb * gridDimensions[3]));
				// Vertices start at the upper left hand corner and go clockwise
			
		}
		
		void GridPiece::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			states.transform *= getTransform(); // getTransform() is defined by sf::Transformable
				// apply the entity's transform -- combine it with the one that was passed by the caller

			states.texture = &m_texture;
				// apply the texture

				// you may also override states.shader or states.blendMode if you want

			/*
			target.draw(m_vertices, states);
				// draw the vertex array
			*/
			sf::Vertex quad[4];
			quad[0] = sf::Vertex(point1, color);
			quad[1] = sf::Vertex(point2, color);
			quad[2] = sf::Vertex(point3, color);
			quad[3] = sf::Vertex(point4, color);
			target.draw(quad, 4, sf::Quads, states);
		}
				
		void GridPiece::setPointers(GridPiece * leftSquare, GridPiece * rightSquare, GridPiece * topSquare,
									GridPiece * bottomSquare)
		{
			if ((*leftSquare).getColorDesignation() != -2)
			{
				gridConnect[0] = leftSquare;
			}
			
			if ((*rightSquare).getColorDesignation() != -2)
			{
				gridConnect[0] = rightSquare;
			}
			
			if ((*topSquare).getColorDesignation() != -2)
			{
				gridConnect[0] = topSquare;
			}
			
			if ((*bottomSquare).getColorDesignation() != -2)
			{
				gridConnect[0] = bottomSquare;
			}
		}
				 
		int GridPiece::getColorDesignation()
		{
			return colorDesignation;
		}
				 
		void GridPiece::setSquareType(int designation)
		{
			colorDesignation = designation;
			if (colorDesignation == 0)
			{
				color.g = 255;
				color.r = 0;
				color.b = 0;
			}
			else if (colorDesignation >= 1)
			{
				color.g = 255;
				color.r = 255;
				color.b = 255;
			}
			else if (colorDesignation == -1)
			{
				color.g = 0;
				color.r = 255;
				color.b = 0;
			}
			//remove these two
			else if (colorDesignation == -3)
			{
				color.g = 0;
				color.r = 0;
				color.b = 255;
			}
			else if (colorDesignation == -4)
			{
				color.g = 0;
				color.r = 255;
				color.b = 255;
			}
		}
		
		void GridPiece::moveSnake()
		{
			// Placeholder
		}
		
		void GridPiece::setNextSnakeBlock(GridPiece & snakeBody)
		{
			// Placeholder
		}

	} // GameBoxes


