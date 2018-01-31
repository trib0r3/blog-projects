/*

Name: Tic Tac Toe - Multiplayer

Author: Szymon Siarkiewicz (sheadovas)
Website: http://szymonsiarkiewicz.pl/

*/


#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <iostream>
#include <fstream>
#include <string>

using namespace sf;
using namespace std;

const int WIDTH = 600;
const int HEIGHT = 315;

IpAddress ip; //ip osoby z ktora sie laczymy

unsigned short s_port = 50001; //port na ktorym dane odbiera serwer 
unsigned short k_port = 50002; //port na ktorym dane odbiera klient

UdpSocket socket;

bool serwer; //flaga mowiaca o tym czy gracz jest klientem czy serwerem
Vector2f pozycja; // pozycja pola na planszy
bool odebrano_dane; // flaga okreslajaca czy juz odebrano dane

void odbierzDane()
{
	odebrano_dane = false;
	
	unsigned short port;
	if(serwer) port = s_port;
	else port = k_port;
	
	Packet p;
	socket.receive(p,ip,port);

	Vector2f poz;
	p >> poz.x >> poz.y;

	pozycja = poz;

	odebrano_dane = true;
}

void wyslijDane()
{
	unsigned short port;
	if(serwer) port = k_port;
	else port = s_port;

	Packet p;
	p << pozycja.x << pozycja.y;

	socket.send(p,ip,port);
}

int check(char pole[3][3])
{
	size_t zajete = 0;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(pole[i][j] != ' ')
				zajete++;
		}
	}
	if(zajete == 9)
		return 3;
	
	//sytuacja nr 1
	if(pole[0][0] != ' ' && pole[0][0] == pole[0][1] && pole[0][0] == pole[0][2])
	{
		if(pole[0][0] == 's') return 1;
		else return 2;
	}
	//sytuacja nr 2
	if(pole[1][0] != ' ' && pole[1][0] == pole[1][1] && pole[1][0] == pole[1][2])
	{
		if(pole[1][0] == 's') return 1;
		else return 2;
	}
	//sytuacja nr 3
	if(pole[2][0] != ' ' && pole[2][0] == pole[2][1] && pole[2][0] == pole[2][2])
	{
		if(pole[2][0] == 's') return 1;
		else return 2;
	}
	//sytuacja nr 4
	if(pole[0][0] != ' ' && pole[0][0] == pole[1][0] && pole[0][0] == pole[2][0])
	{
		if(pole[0][0] == 's') return 1;
		else return 2;
	}
	//sytuacja nr 5
	if(pole[0][1] != ' ' && pole[0][1] == pole[1][1] && pole[0][1] == pole[2][1])
	{
		if(pole[0][1] == 's') return 1;
		else return 2;
	}
	//sytuacja nr 6
	if(pole[0][2] != ' ' && pole[0][2] == pole[1][2] && pole[0][2] == pole[2][2])
	{
		if(pole[0][2] == 's') return 1;
		else return 2;
	}
	//sytuacja nr 7
	if(pole[0][0] != ' ' && pole[0][0] == pole[1][1] && pole[0][0] == pole[2][2])
	{
		if(pole[0][0] == 's') return 1;
		else return 2;
	}
	//sytuacja nr 8
	if(pole[2][0] != ' ' && pole[2][0] == pole[1][1] && pole[2][0] == pole[0][2])
	{
		if(pole[2][0] == 's') return 1;
		else return 2;
	}

	return 0;
}

int main()
{
	RenderWindow window(VideoMode(WIDTH,HEIGHT),"Tic Tac Toe: Multiplayer",Style::Close);
	
	cout<<"Moje IP: "<<IpAddress::getLocalAddress().toString()<<endl; //daj je osobie z ktora bedziesz gral
	
	//jezeli nie chcemy caly czas wpisywac ip znajomego mozemy je wczytywac z pliku
	fstream plik("ip.txt",ios::in);
	if(plik.is_open())
	{
		string str;
		plik >> str;
		ip = str;
	}
	plik.close();

	//czcionka i pierwszy wyœwietlony napis
	Font font;
	font.loadFromFile("robotastic.ttf");

	Text napis("Serwer ([S])/Klient ([K])",font,20);
	napis.setPosition(WIDTH/2-napis.getGlobalBounds().width/2,(HEIGHT/2-napis.getGlobalBounds().height/2));

	//wybor czym jestesmy (dziwnie to brzmi (: )
	while(true)
	{
		Event event;
		while(window.pollEvent(event));
		{
			if(event.type == Event::Closed)
				return 0;
			if(event.type == Event::KeyReleased && event.key.code == Keyboard::S)
			{
				serwer = true;
				break;
			}
			if(event.type == Event::KeyReleased && event.key.code == Keyboard::K)
			{
				serwer = false;
				break;
			}
		}
		window.clear();
		window.draw(napis);
		window.display();
	}

	//podajemy ip o ile wczesniej nie zostalo wczytane z pliku
	if(ip.toString() == "0.0.0.0")
	{
		napis.setString("Podaj ip klienta/serwera");
		napis.setPosition(WIDTH/2-napis.getGlobalBounds().width/2,(HEIGHT/2-napis.getGlobalBounds().height/2)-30);

		Text text_ip("",font,15);
		string str_ip;
		
		bool b = false;
		while(!b)
		{
			Event event;
			while(window.pollEvent(event))
			{
				if(event.type == Event::Closed)
					return 0;
				if(event.type == Event::KeyReleased && event.key.code == Keyboard::Return)
				{
					ip = str_ip;
					b = true;
				}
				
				else if(event.type == Event::TextEntered)
				{
					if (event.text.unicode == 8) //backspace
					{
						if(str_ip.size()>0)
							str_ip.erase(str_ip.size() - 1, 1);
					}
					else if (event.text.unicode < 128 && event.text.unicode != 13)
						str_ip+= (char)event.text.unicode;
					
					text_ip.setString(str_ip);
					text_ip.setPosition(WIDTH/2-text_ip.getGlobalBounds().width/2,HEIGHT/2-text_ip.getGlobalBounds().height/2);
				}
			}
			
			window.clear();
			window.draw(napis);
			window.draw(text_ip);
			window.display();
		}

	}
	//Probne polaczenie i odebranie pliku
	if(serwer) socket.bind(s_port);
	else socket.bind(k_port);

	if(serwer)
	{
		string tmp;
		Packet pakiet;
		socket.receive(pakiet,ip,s_port);

		pakiet >> tmp;
		cout<<tmp<<endl;

		pakiet.clear();

		tmp = "Polaczono z serwerem!\n";
		pakiet << tmp;
		socket.send(pakiet,ip,k_port);
	}
	else
	{
		string tmp = "Polaczono z klientem\n";
		Packet pakiet;
		pakiet << tmp;
		socket.send(pakiet,ip,s_port);

		pakiet.clear();
		socket.receive(pakiet,ip,k_port);
		pakiet >> tmp;
		cout<<tmp;
	}

	char logic[3][3]; // 's' pole zatjete przez serwer, 'k': przez klienta
	RectangleShape plansza[3][3]; // dla uproszczenia zamiast rysowania kolek bedziemy zmieniali kolor pol
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			logic[i][j] = ' ';
			
			plansza[i][j].setSize(Vector2f(60,60)); //wielkosc pola to 60x60
			plansza[i][j].setPosition(60+i*65,60+j*65); // plansza zaczyna sie od 60 piksela, pola rozstawione co 5 pikseli
		
			plansza[i][j].setFillColor(Color(255,153,0)); //pomaranczowy
			plansza[i][j].setOutlineColor(Color(255, 102, 0)); //pomaranczowy ciemniejszy
			plansza[i][j].setOutlineThickness(2.5f);
		}
	}

	
	// flagi koncowe, opcje
	Thread odbieranie(odbierzDane);
	Thread wysylanie(wyslijDane);
	bool receiving = false;
	bool moja_tura = (serwer == false ? true : false); //czy obecny ruch to tura gracza grajacego na tym kliencie

	if(moja_tura) 
	{
		napis.setString("Twoja tura");
		napis.setColor(Color::Blue);
	}
	else
	{
		napis.setString("Tura przeciwnika");
		napis.setColor(Color::Red);
	}
	napis.setCharacterSize(15);
	napis.setPosition(WIDTH - 20 - napis.getGlobalBounds().width,10);

	bool exit = false;

	//petla gry
	while(window.isOpen())
	{
		Event event;
		//odbieranie informacji o ruchu przeciwnika
		if(!moja_tura)
		{
			if(!receiving)
			{
				receiving = true; //czekamy na odebranie danych
				odbieranie.launch();
			}
			else if(odebrano_dane)
			{
				receiving = false; // odebrano dane
				
				//ustawienie pol
				Vector2i p;
				p = Vector2i(pozycja);
				logic[p.x][p.y] = (serwer ? 'k' : 's');
				plansza[p.x][p.y].setFillColor(Color::Red);

				moja_tura = true;
				napis.setString("Twoja tura");
				napis.setColor(Color::Blue);
				napis.setPosition(WIDTH - 20 - napis.getGlobalBounds().width,10);
			}
		}
		
		while(window.pollEvent(event))
		{
			if(event.type == Event::Closed || exit)
			{
				if(exit)
					sleep(seconds(2));

				window.close();
				odbieranie.terminate();
				wysylanie.terminate();
			}

			else if(moja_tura && event.type == Event::MouseButtonReleased)
			{
				for(int i=0;i<3;i++)
				{
					for(int j=0;j<3;j++)
					{
						if(plansza[i][j].getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))) && logic[i][j] == ' ')
						{
							pozycja = Vector2f(i,j);
							logic[i][j] = (serwer ? 's' : 'k');
							plansza[i][j].setFillColor(Color::Blue);

							moja_tura = false;
							napis.setString("Tura przeciwnika");
							napis.setColor(Color::Red);
							napis.setPosition(WIDTH - 20 - napis.getGlobalBounds().width,10);
							wysylanie.launch();
						}
					}
				}
			}
		}
		int test = check(logic);
		if(test != 0) // 0-nikt nie wygral, 1-serwer, 2-klient, 3-remis
		{
			if(test == 1) napis.setString("Wygral serwer");
			else if(test == 2) napis.setString("Wygral klient");
			else napis.setString("Remis");

			napis.setColor(Color::White);
			napis.setPosition(WIDTH - 20 - napis.getGlobalBounds().width,10);

			exit = true;
		}

		window.clear(Color(128,128,128));
		
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				window.draw(plansza[i][j]);
		window.draw(napis);
		
		window.display();
	}
	return 0;
}