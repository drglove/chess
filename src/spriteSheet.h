/*

Chess

*/

#ifndef CHESS_SPRITE_SHEET_H
#define CHESS_SPRITE_SHEET_H

// SFML
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>

// STL
#include <string>
#include <vector>
using namespace std;

class SpriteSheet
{
public:
   sf::Sprite& at( int i );

   void loadSpriteSheet( std::string filename, int spriteWidth, int spriteHeight );
   void loadSpriteSheet( sf::Texture& texture, int spriteWidth, int spriteHeight );

   int size();

private:
   sf::Texture m_tileSheet;
   std::vector< sf::Sprite > m_tiles;

   sf::IntRect m_subRect;
};

#endif
