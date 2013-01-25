/*

Chess

*/

#ifndef CHESS_GUI_H
#define CHESS_GUI_H

// SFGUI
#include <SFGUI/SFGUI.hpp>

// Forward 
class Game;
namespace sf
{
	class Event;
	class RenderTarget;
}

class GUI
{
public:
	// Constructor
	GUI( Game* game, sf::Vector2f size, sf::Vector2f pos );
	
	// Destructor
	~GUI() {};

	// Hand off events to the window
	void handleEvent( const sf::Event &event );

	// Hand off updates to the window
	void update( float seconds );

	// Hand off drawing to the window
	void draw( sf::RenderTarget &target );

	// Add a move in the log
	void addMove( const sf::String &text, bool currLine = false );

	// Reset the log
	void reset();

private:
	// GUI Handeler
	sfg::SFGUI m_sfgui;

	// Window
	sfg::Window::Ptr m_window;

	// Scrolled box for recording moves
	sfg::Box::Ptr m_scrolled_window_box;

	// Pointer to game owner
	Game* game;
};


#endif