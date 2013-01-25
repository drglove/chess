/*

Chess

*/

// Class definition
#include "spriteSheet.h"

void SpriteSheet::loadSpriteSheet( std::string filename, int spriteWidth, int spriteHeight )
{
   // Load the tileset
   if ( !m_tileSheet.loadFromFile( filename ) )
   {
      return;
   }

   loadSpriteSheet( m_tileSheet, spriteWidth, spriteHeight );
}

void SpriteSheet::loadSpriteSheet( sf::Texture& texture, int spriteWidth, int spriteHeight )
{

   // Setup the initial rect
   m_subRect.width = spriteWidth;
   m_subRect.height = spriteHeight;

   // Load the tile vector
   for ( unsigned int verIter = 0; verIter < m_tileSheet.getSize().y ; verIter += m_subRect.height )
   {
      m_subRect.top = verIter;

      for ( unsigned int horIter = 0; horIter < m_tileSheet.getSize().x ; horIter += m_subRect.width )
      {
         m_subRect.left = horIter;

         sf::Sprite tile( m_tileSheet, m_subRect );
         m_tiles.push_back( tile );
      }
   }

   // Reset the subRect
   m_subRect.left = 0;
   m_subRect.top = 0;
}

sf::Sprite& SpriteSheet::at( int i )
{
   return m_tiles[i];
}

int SpriteSheet::size()
{
   return m_tiles.size();
}
