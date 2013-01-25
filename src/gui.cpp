/*

Chess

*/

// Class definition
#include "gui.h"

// Game
#include "game.h"

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

GUI::GUI( Game* game, sf::Vector2f size, sf::Vector2f pos ) : game ( game )
{
	// Initialize the objects
	m_window = sfg::Window::Create();
	m_window->SetTitle( "Moves" );
	m_window->SetRequisition( size );
	m_window->SetPosition( pos );
	m_window->SetState( sfg::Widget::INSENSITIVE );

	// Make a box for the objects in the window
	sfg::Box::Ptr windowBox( sfg::Box::Create( sfg::Box::VERTICAL, 5.0f ) );

	// Make the scroll window and a box to stay within it
	sfg::ScrolledWindow::Ptr scrolledWindow = sfg::ScrolledWindow::Create();
	scrolledWindow->SetRequisition( sf::Vector2f(0.0f, size.y - 100.0f) );
	m_scrolled_window_box = sfg::Box::Create( sfg::Box::VERTICAL );

	// Set our scroll properties
	scrolledWindow->SetScrollbarPolicy( sfg::ScrolledWindow::VERTICAL_ALWAYS | sfg::ScrolledWindow::HORIZONTAL_AUTOMATIC );

	// Add the window box to the window
	scrolledWindow->AddWithViewport( m_scrolled_window_box );

	// Create an alignment.
 	//sfg::Alignment::Ptr alignment = sfg::Alignment::Create();
	//sfg::Box::Ptr box = sfg::Box::Create( sfg::Box::VERTICAL );
	//alignment->Add( box );
 	//m_scrolled_window_box->Pack( alignment );

	// Add buttons
	sfg::Button::Ptr newGameButton( sfg::Button::Create( "New Game" ) );
	sfg::Button::Ptr exitGameButton( sfg::Button::Create( "Quit" ) );
	newGameButton->GetSignal( sfg::Widget::OnLeftClick ).Connect( &Game::newGame, game );
	exitGameButton->GetSignal( sfg::Widget::OnLeftClick ).Connect( &Game::exitGame, game );

	sfg::Box::Ptr buttonBox( sfg::Box::Create( sfg::Box::HORIZONTAL, 10.0f ) );
	buttonBox->Pack( newGameButton );
	buttonBox->Pack( exitGameButton );

	// Add the widgets to the main window box
	windowBox->Pack( scrolledWindow );
	windowBox->Pack( buttonBox );

	// Add the scroll window
	m_window->Add( windowBox );
}

void GUI::handleEvent( const sf::Event &event )
{
	m_window->HandleEvent( event );
}

void GUI::update( float seconds )
{
	m_window->Update( seconds );
}

void GUI::draw( sf::RenderTarget &target )
{
	m_sfgui.Display( target );
}

void GUI::addMove( const sf::String &text, bool currLine )
{
	// We need a previous line to be there is we want to use it
	if ( currLine && !m_scrolled_window_box->GetChildren().empty() )
	{
		// Set the current line's text
		sfg::Label::Ptr currLine = sfg::StaticPointerCast<sfg::Label>(m_scrolled_window_box->GetChildren().back());
		currLine->SetText( text );
	}
	else if ( !currLine )
	{
		// Make a new line with the text
		m_scrolled_window_box->Pack( sfg::Label::Create( text ), false );
	}
}

void GUI::reset()
{
	// Remove all text boxes
	m_scrolled_window_box->RemoveAll();
}