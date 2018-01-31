#include "Game.h"
#include <fstream>

RenderWindow window;

Game::Game(void)
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	
	window.create(VideoMode(1280,720),"Mechanized Techno Explorer",Style::Default,
		settings);
	
	state = END;
	window.setFramerateLimit(100);

	if(!font.loadFromFile("data/Mecha.ttf"))
	{
		MessageBox(NULL,"Font not found!","ERROR",NULL);
		return;
	}

	state = MENU;

	audio.loadMusic(true);
	audio.loadSounds();

	audio.playMusic();
}


Game::~Game(void)
{
	audio.stopMusic();

	fstream file("config.cfg",ios::out | ios::trunc);
	file << unmute;
	file.close();
}


void Game::runGame()
{
	while(state != END)
	{
		switch (state)
		{
		case GameState::MENU:
			menu();
			break;
		case GameState::GAME:
			single();
			break;
		}
	}
}


void Game::menu()
{
	Text title("Mechanized Techno Explorer",font,80);
	title.setStyle(Text::Bold);

	title.setPosition(1280/2-title.getGlobalBounds().width/2,20);

	const int ile = 2;

	Text tekst[ile];

	string str[] = {"Play","Exit"};

	for(int i=0;i<ile;i++)
	{
		tekst[i].setFont(font);
		tekst[i].setCharacterSize(65);

		tekst[i].setString(str[i]);
		tekst[i].setPosition(1280/2-tekst[i].getGlobalBounds().width/2,250+i*120);
	}

	bool b;
	//opcje
	fstream file("config.cfg");
	if(file.is_open())
		file >> b;
	else
		b=true;
	file.close();
	
	Text options;
	string s="Music & Sounds: ";
	if(b==true)
			options.setString(s+"ON");
	else
		options.setString(s+"OFF");

	options.setFont(font);
	options.setCharacterSize(20);
	options.setPosition(10,10);
	audio.setVolume(!b);

	while(state == MENU)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;

		while(window.pollEvent(event))
		{
			//Wciœniêcie ESC lub przycisk X
			if(event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				state = END;
			
			//klikniêcie MENU                              
			else if(tekst[0].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				audio.stopMusic();
				audio.playSound(Audio::T_CLICK);
				state = GAME;
			}
			
			//klikniêcie EXIT
			else if(tekst[1].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = END;
				audio.playSound(Audio::T_CLICK);
			}

			//wyciszenie/wlaczenie muzyki
			else if(options.getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				if(b)
				{
					b=false;
					options.setString(s+"OFF");
				}
				else
				{
					b=true;
					options.setString(s+"ON");
				}
				audio.setVolume(!b);
				audio.playSound(Audio::T_CLICK);
			}
		}
		for(int i=0;i<ile;i++)
			if(tekst[i].getGlobalBounds().contains(mouse))
			{
				if(tekst[i].getColor()==Color::White)
				{
					audio.playSound(Audio::T_MENU);
				}
				tekst[i].setColor(Color::Cyan);
			}
			else tekst[i].setColor(Color::White);

		if(options.getGlobalBounds().contains(mouse))
		{
			options.setColor(Color::Cyan);
		}
		else
			options.setColor(Color::White);
		
		window.clear();
		
		window.draw(title);
		for(int i=0;i<ile;i++)
			window.draw(tekst[i]);

		window.draw(options);

		window.display();
	}
	unmute = b;
}

void Game::single()
{
	Engine engine(window,unmute);

	engine.runEngine();

	state = MENU;
}