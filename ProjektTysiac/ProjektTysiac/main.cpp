#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "naglowek.h"
#include "Menu.h"
#include "Zasady.h"
#include "Licytacja.h"
using namespace std;

class Gra{
private:
	/*
	*Okno, talie kart, tekstury
	*/
	Karta talia[24], gracz1[9], gracz2[9], gracz3[9], musik[3];
	sf::RenderWindow window;
	sf::RectangleShape wybierzKarte;
	sf::Texture texture;
	sf::Texture texturePlansza;
	sf::Texture uzytyMusik;
	sf::View view;
	
	sf::Sprite plansza;


	/*
	* Zmienne napisowe
	*/
	sf::Font czcionka;
	sf::Text punkty1, punkty2, punkty3, wygrana, przegrana, aByKontynuowac;
	sf::Text lic[5];
	int pkt1, pkt2, pkt3, pkt1tmp, pkt2tmp, pkt3tmp;
	float a, b;
	float yLicytacja;

	/*
	* Menu
	*/
	Menu menu;
	int przejscieDo;

	/*
	* Zmienne mechaniki gry
	*/
	int ktoraKarta;
	int ktoraKartaMusik;
	int przyznanyMusik;
	int kartyUzyte[8];
	int kartyUzyteMusik[3];
	int doResetuZostalo;
	int wygrywaG1, wygrywaG2, wygrywaG3;
	int prowadziGracz;
	bool czyReset;
	bool czyMusik;
	bool musikCzyNie;
	bool wystawienie;
	pair<bool,bool> czyJaProwadze;
	int punkty;

	/*
	* Zmienne licytacji
	*/
	Licytacja licytacja;
	int licytacjaJa, licytacjaBot2, licytacjaBot3;
	bool czyLicytacja;

	int doZdobycia;
	int ktoWygralLicytacje;
	int ktoLicytuje;
	int ktoWygralPartie;

	/*
	* zmienne meldunk�w
	*/
	pair<pair<bool, int>,string> meldunekKrole[4];
	pair<pair<bool, int>,string> meldunekKrolowe[4];
	bool jakiMeldunek1[4];
	bool jakiMeldunek2[4];
	bool jakiMeldunek3[4];
	int ileMeldunkow;
	int aktywnyMeldunek;
	sf::Text meldunek[4];
	Karta wybranaPrzezBota;

	Karta* poprzednia1;
	Karta* poprzednia2;
	Karta* poprzednia3;

	/*
	* zmienna zasad
	*/
	Zasady zasady;
	
	/*
	* Funkcje okna, ustawianie kart
	*/
	void przebieg();
	void okno();
	void pozycjaKart();
	
	/*
	* Funkcje poruszania si� po aplikacji
	*/
	void wLewo();
	void wPrawo();
	void wDol();
	void wGore();
	void wystawKarte(Karta&);

	/*
	* Funkcje g��wnej mechaniki gry
	*/
	int tmp, tmp2{};
	void pobieranieWartosci(Karta&, Karta&);
	Karta pobierzWartosciBot(Karta&, Karta[], float);
	Karta pobierzWartosciBot(Karta[], float);
	void pobierzAdresBot(Karta&);
	void wybierzMusik();
	void wybierzMusikBot(Karta[], Karta[], Karta[]);
	void ustawMusik(Karta[], bool&, sf::Vector2u, int, int, int);
	void reset();
	void usunKarty();
	/*
	* Funkcje meldunk�w
	*/
	void czyMeldunek(Karta[], bool[]);
	void podajMeldunek(bool[]);
	/*
	* Funkcje punkt�w i og�lnego sprawdzania wygranej
	*/
	void mechanika(Karta&, Karta&, Karta&);
	void podliczPunkty(string, string, string);
	/*
	* Funkcje licytacji
	*/
	void sprawdzLicytacje();

public:

	/*
	* Konstruktor wraz z funkcj� rozpoczynaj�c� gr�
	*/
	Gra();
	void rozpocznij();
};

/*
* Konstruktor domy�lny
*/
Gra::Gra()
	/*
	* Nadawanie zmiennym warto�ci
	*/
	:window(sf::VideoMode(1200, 800), "Gra w tysiaca", sf::Style::Close | sf::Style::Resize),
	menu(window.getSize().x, window.getSize().y),
	zasady(),
	pkt1(0),
	pkt2(0),
	pkt3(0),
	pkt1tmp(0),
	pkt2tmp(0),
	pkt3tmp(0),
	a(630.0f),
	b(710.0f),
	yLicytacja(250.0f),
	czyReset(false),
	czyMusik(true),
	musikCzyNie(true),
	wystawienie(true),
	czyLicytacja(true),
	czyJaProwadze(true, true),
	poprzednia1(nullptr),
	poprzednia2(nullptr),
	poprzednia3(nullptr),
	przejscieDo(0),
	ktoraKarta(0),
	ktoraKartaMusik(0),
	przyznanyMusik(0),
	doResetuZostalo(0),
	ileMeldunkow(0),
	aktywnyMeldunek(0),
	wygrywaG1(0),
	wygrywaG2(0),
	wygrywaG3(0),
	prowadziGracz(1),
	licytacjaJa(0),
	licytacjaBot2(0),
	licytacjaBot3(0),
	doZdobycia(0),
	ktoWygralLicytacje(0),
	ktoLicytuje(1),
	ktoWygralPartie(1),
	punkty(0),
	tmp(0)
{
	texture.loadFromFile("talia.png");
	texturePlansza.loadFromFile("plansza.png");
	uzytyMusik.loadFromFile("uzyta.png");
	
	plansza.setTexture(texturePlansza);

	view.setSize(sf::Vector2f(1200.0f, 800.0f));
	view.setCenter(sf::Vector2f(600.0f, 400.0f));

	czcionka.loadFromFile("sansation.ttf");
	punkty1.setFont(czcionka);
	punkty2.setFont(czcionka);
	punkty3.setFont(czcionka);
	punkty1.setFillColor(sf::Color::Red);
	punkty2.setFillColor(sf::Color::Red);
	punkty3.setFillColor(sf::Color::Red);
	punkty1.setString(to_string(pkt1));
	punkty2.setString(to_string(pkt2));
	punkty3.setString(to_string(pkt3));
	punkty1.setPosition(sf::Vector2f(100.0f, 160.0f));
	punkty2.setPosition(sf::Vector2f(100.0f, 600.0f));
	punkty3.setPosition(sf::Vector2f(900.0f, 400.0f));
	wygrana.setString("Wygrana!");
	wygrana.setFont(czcionka);
	wygrana.setFillColor(sf::Color::Red);
	wygrana.setPosition(sf::Vector2f(600.0f, 350.0f));
	przegrana.setString("Przegrana!");
	przegrana.setFont(czcionka);
	przegrana.setFillColor(sf::Color::Red);
	przegrana.setPosition(sf::Vector2f(600.0f, 350.0f));

	aByKontynuowac.setFont(czcionka);
	aByKontynuowac.setFillColor(sf::Color::Green);
	aByKontynuowac.setCharacterSize(36);
	aByKontynuowac.setString("Wcisnij A by kontynuowac!");
	aByKontynuowac.setPosition(sf::Vector2f(300.0f, 550.0f));
	
	wczytajKarty(talia);
	przypiszObraz(talia, &texture);

	wybierzKarte.setSize(sf::Vector2f(60.0f, 60.0f));
	wybierzKarte.setFillColor(sf::Color::Red);
	wybierzKarte.setOrigin(sf::Vector2f(wybierzKarte.getGlobalBounds().width / 2, wybierzKarte.getGlobalBounds().height / 2));
	wybierzKarte.setPosition(sf::Vector2f(450.0f, 450.0f));
	


	for (int i = 0; i < 8; i++)
		kartyUzyte[i] = -1;
	for (int i = 0; i < 3; i++)
		kartyUzyteMusik[i] = -1;

	for (int i = 0; i < 4; i++) {
		meldunekKrole[i].first.second = 0;
		meldunekKrole[i].first.first = false;
		meldunekKrolowe[i].first.second = 0;
		meldunekKrolowe[i].first.first = false;
		jakiMeldunek1[i] = false;
		jakiMeldunek2[i] = false;
		jakiMeldunek3[i] = false;
		meldunek[i].setFont(czcionka);
		meldunek[i].setString("");
		meldunek[i].setPosition(sf::Vector2f(-100.0f, -100.0f));
	}
	meldunekKrole[0].second = "karo";
	meldunekKrolowe[0].second = "karo";
	meldunekKrole[1].second = "kier";
	meldunekKrolowe[1].second = "kier";
	meldunekKrole[2].second = "pik";
	meldunekKrolowe[2].second = "pik";
	meldunekKrole[3].second = "trefl";
	meldunekKrolowe[3].second = "trefl";
	meldunek[0].setString("karo");
	meldunek[1].setString("kier");
	meldunek[2].setString("pik");
	meldunek[3].setString("trefl");
}

/*
*  Funkja ustawiaj�ca karty graczy i karty z musiku we w�a�ciwych pozycjach
*/
void Gra::pozycjaKart() {
	for (int i = 0; i < 8; i++) {
		gracz1[i].card.setPosition(sf::Vector2f(120.0f + (110.0f * i), 80.0f));
		gracz3[i].card.setPosition(sf::Vector2f(1100.0f, 100.0f + (100.0f * i)));
		gracz2[i].card.setPosition(sf::Vector2f(120.0f + (110.0f * i), 700.0f));
	}
	for (int i = 0; i < 3; i++) {
		musik[i].card.setPosition(sf::Vector2f(450.0f + (110.0f * i), 450.0f));
	}
}


/*
* Funkcje, kt�re wybieraj� karty lewo-prawo 
*/
void Gra::wLewo() {
	cout << "Lewo" << endl;
	/*
	* ustawienie znacznika kart, na pierwsz� w r�ce, gdy partia dobiegnie ko�ca
	*/
	if (doResetuZostalo == 7)
		wybierzKarte.setPosition(sf::Vector2f(gracz1[0].card.getPosition().x, gracz1[0].card.getPosition().y));
	/*
	* Sprawdzenie czy aktualnie nie rozdajemy musiku
	* W zale�no�ci od tego albo poruszamy si� po kartach musiku rozdaj�c je graczom,
	* albo poruszamy si� po w�asnych kartach
	*/
	if (!musikCzyNie) {
		ktoraKartaMusik = 0;
		/*
		* Sprawdzenie, czy nast�pna karta nie zosta�a ju� u�yta
		* Je�eli karta s�siednia, na kt�r� chcemy prze��czy� znacznik jest u�yta, 
		* to nast�puje przeskok do nast�pnej, wolnej karty, kt�rej mo�emy u�y�
		* 
		* Je�eli karta, na kt�rej aktualnie jest znacznik znajduje si� skrajnie po lewej stronie,
		* to znacznik zostanie ustawiony na kart� skrajnie po prawej stronie
		*/
		if (ktoraKarta >= 0) {
			do {
				if (ktoraKarta == 0)
					ktoraKarta = 7;
				else
					ktoraKarta--;
			} while (ktoraKarta == kartyUzyte[ktoraKarta]);
			wybierzKarte.setPosition(sf::Vector2f(gracz1[ktoraKarta].card.getPosition().x, gracz1[ktoraKarta].card.getPosition().y));
		}
	}
	/*
	* Analogia dla musiku
	*/
	else {
		ktoraKarta = 0;
		if (ktoraKartaMusik >= 0) {
			do {
				if (ktoraKartaMusik == 0)
					ktoraKartaMusik = 2;
				else
					ktoraKartaMusik--;
			} while (ktoraKartaMusik == kartyUzyteMusik[ktoraKartaMusik]);
			wybierzKarte.setPosition(sf::Vector2f(musik[ktoraKartaMusik].card.getPosition().x, musik[ktoraKartaMusik].card.getPosition().y));
		}
	}
}
void Gra::wPrawo() {
	cout << "Prawo" << endl;
	/*
	* ustawienie znacznika kart, na pierwsz� w r�ce, gdy partia dobiegnie ko�ca
	*/
	if (doResetuZostalo == 7)
		wybierzKarte.setPosition(sf::Vector2f(gracz1[0].card.getPosition().x, gracz1[0].card.getPosition().y));
	if (!musikCzyNie) {
		ktoraKartaMusik = 0;
		/*
		* Sprawdzenie, czy nast�pna karta nie zosta�a ju� u�yta
		* Je�eli karta s�siednia, na kt�r� chcemy prze��czy� znacznik jest u�yta,
		* to nast�puje przeskok do nast�pnej, wolnej karty, kt�rej mo�emy u�y�
		* 
		* Je�eli karta, na kt�rej aktualnie jest znacznik znajduje si� skrajnie po prawej stronie,
		* to znacznik zostanie ustawiony na kart� skrajnie po lewej stronie
		*/
		if (ktoraKarta <= 7) {
			do {
				if (ktoraKarta == 7)
					ktoraKarta = 0;
				else
					ktoraKarta++;
			} while (ktoraKarta == kartyUzyte[ktoraKarta]);
			wybierzKarte.setPosition(sf::Vector2f(gracz1[ktoraKarta].card.getPosition().x, gracz1[ktoraKarta].card.getPosition().y));
		}
	}
	/*
	* Analogia dla musiku
	*/
	else {
		ktoraKarta = 0;
		if (ktoraKartaMusik <= 2) {
			do {
				if (ktoraKartaMusik == 2)
					ktoraKartaMusik = 0;
				else
					ktoraKartaMusik++;
			} while (ktoraKartaMusik == kartyUzyteMusik[ktoraKartaMusik]);
			wybierzKarte.setPosition(sf::Vector2f(musik[ktoraKartaMusik].card.getPosition().x, musik[ktoraKartaMusik].card.getPosition().y));
		}
	}
}
void Gra::wDol() {
	/*
	* Wybranie nast�pnej warto�ci licytacji, podczas licytacji.
	* 
	* Podobnie jak przy ruchu prawo-lewo, je�eli znacznik znajduje si� na skrajnie dolnym obiekcie,
	* to znacznik zostanie przeniesiony na skrajnie g�rny.
	*/
	cout <<"yLicytacja: " << yLicytacja << endl;
	if (yLicytacja < 450.0f) {
		yLicytacja += 50.0f;
		wybierzKarte.setPosition(sf::Vector2f(150.0f, yLicytacja));
	}
	else {
		yLicytacja = 250.0f;
		wybierzKarte.setPosition(sf::Vector2f(150.0f, yLicytacja));
	}
}
void Gra::wGore() {
	/*
	* Wybranie nast�pnej warto�ci licytacji, podczas licytacji.
	*
	* Podobnie jak przy ruchu prawo-lewo, je�eli znacznik znajduje si� na skrajnie gr�rnym obiekcie,
	* to znacznik zostanie przeniesiony na skrajnie dolny.
	*/
	cout << "yLicytacja: " << yLicytacja << endl;
	if (yLicytacja > 250.0f) {
		yLicytacja -= 50.0f;
		wybierzKarte.setPosition(sf::Vector2f(150.0f, yLicytacja));
	}
	else {
		yLicytacja = 450.0f;
		wybierzKarte.setPosition(sf::Vector2f(150.0f, yLicytacja));
	}
}
/*
* Metoda ustawia pozycj� karty, kt�r� wybrali�my na �rodek planszy
*/
void Gra::wystawKarte(Karta& karta) {
	cout << "Wystawiam Karte" << endl;
	karta.card.setPosition(sf::Vector2f(550.0f, 400.0f));
	wybierzKarte.setPosition(sf::Vector2f(karta.card.getPosition().x, karta.card.getPosition().y));
}

/*
* Metoda, wybierania musiku, czyli 3 kart, kt�re musz� by� rozdane graczom.
*/
void Gra::wybierzMusik() {
	cout << "Wybieram musik" << endl;
	sf::Vector2u textureSize = texture.getSize();
	textureSize.x /= 6;
	textureSize.y /= 4;
	int x = musik[ktoraKartaMusik].wartosc %6;
	int y = musik[ktoraKartaMusik].wartosc / 6;
	/*
	* Musik jest wybierany z 3 kart, 3 opcje w switch'u obrazuj� sytuacj�, 
	* najpierw kart� wybieramy dla siebie samych (gracz1), nast�pnie dla gracza 2, 
	* a na ko�cu dla gracza 3. Ustawiane s� wszystkie w�a�ciwo�ci kart z musiku �smej karcie na r�ce graczy
	*/
	switch (przyznanyMusik) {
	case 0:
		gracz1[7].figura = musik[ktoraKartaMusik].figura;
		gracz1[7].kolor = musik[ktoraKartaMusik].kolor;
		gracz1[7].wartosc = musik[ktoraKartaMusik].wartosc;
		gracz1[7].card.setTexture(texture);
		gracz1[7].card.setTextureRect(sf::IntRect(textureSize.x * x, textureSize.y * y, textureSize.x, textureSize.y));
		gracz1[7].card.setPosition(sf::Vector2f(890.0f, 80.0f));
		gracz1[7].card.setOrigin(sf::Vector2f(gracz1[7].card.getGlobalBounds().width / 2, gracz1[7].card.getGlobalBounds().height / 2));
		musik[ktoraKartaMusik].card.setTexture(uzytyMusik);
		czyMeldunek(gracz1, jakiMeldunek1);
		break;
	case 1:
		gracz2[7].figura = musik[ktoraKartaMusik].figura;
		gracz2[7].kolor = musik[ktoraKartaMusik].kolor;
		gracz2[7].wartosc = musik[ktoraKartaMusik].wartosc;
		gracz2[7].card.setTexture(texture);
		gracz2[7].card.setTextureRect(sf::IntRect(textureSize.x * x, textureSize.y * y, textureSize.x, textureSize.y));
		gracz2[7].card.setPosition(sf::Vector2f(890.0f, 700.0f));
		gracz2[7].card.setOrigin(sf::Vector2f(gracz2[7].card.getGlobalBounds().width / 2, gracz2[7].card.getGlobalBounds().height / 2));
		musik[ktoraKartaMusik].card.setTexture(uzytyMusik);
		czyMeldunek(gracz2, jakiMeldunek2);
		break;
	case 2:
		gracz3[7].figura = musik[ktoraKartaMusik].figura;
		gracz3[7].kolor = musik[ktoraKartaMusik].kolor;
		gracz3[7].wartosc = musik[ktoraKartaMusik].wartosc;
		gracz3[7].card.setTexture(texture);
		gracz3[7].card.setTextureRect(sf::IntRect(textureSize.x * x, textureSize.y * y, textureSize.x, textureSize.y));
		gracz3[7].card.setPosition(sf::Vector2f(1100.0f, 750.0f));
		gracz3[7].card.setOrigin(sf::Vector2f(gracz3[7].card.getGlobalBounds().width / 2, gracz3[7].card.getGlobalBounds().height / 2));
		musik[ktoraKartaMusik].card.setTexture(uzytyMusik);
		przyznanyMusik = 0;
		wybierzKarte.setPosition(sf::Vector2f(gracz1[0].card.getPosition().x, gracz1[0].card.getPosition().y));
		musikCzyNie = false;
		czyMusik = false;
		czyMeldunek(gracz3, jakiMeldunek3);
		break;
	}
	przyznanyMusik++;
}

/*
* Metoda, kt�ra za pomoc� kr�tkiego algorytmu, wybiera dla gracza, kt�ry nie jest sterowany przez nas
* Kart� o najwi�kszej warto�ci, a reszta jest przekazana dla gracza1 i ostatniego gracza, kt�ry nie otrzyma� karty
*/
void Gra::wybierzMusikBot(Karta wygrywajacy[], Karta gracz[], Karta botPrzegrywajacy[]) {
	cout << "Bot wybiera musik" << endl;
	sf::Vector2u textureSize = texture.getSize();
	textureSize.x /= 6;
	textureSize.y /= 4;
	int x, y;
	
	bool czyGracz3 = false;
	int max{}, id{};

	/*
	* Proste szukanie maksymalnej warto�ci spo�r�d 3 liczb
	* Znalezienie w�r�d talii kart odpowiednich wsp�rz�dnych grafiki karty
	*/
	for (int i = 0; i < 3; i++) {
		if (musik[i].wartosc >= max) {
			max = musik[i].wartosc;
			id = i;
			x = musik[i].wartosc % 6;
			y = musik[i].wartosc / 6;
		}
	}
	/*
	* Przekazanie karty do talii gracza
	*/
	ustawMusik(wygrywajacy, czyGracz3, textureSize, x, y, id);
	/*
	* Dopasowanie, kt�re karty z musika nie zosta�y wybrane i roznanie ich pozosta�ym graczom
	*/
	if (id == 1 || id == 2) {
		x = musik[0].wartosc % 6;
		y = musik[0].wartosc / 6;
		ustawMusik(gracz, czyGracz3, textureSize, x, y, 0);
		if (id != 1) {
			x = musik[1].wartosc % 6;
			y = musik[1].wartosc / 6;
			ustawMusik(botPrzegrywajacy, czyGracz3, textureSize, x, y, 1);
		}
		else {
			x = musik[2].wartosc % 6;
			y = musik[2].wartosc / 6;
			ustawMusik(botPrzegrywajacy, czyGracz3, textureSize, x, y, 2);
		}
	}
	else if (id == 0 || id == 2) {
		x = musik[1].wartosc % 6;
		y = musik[1].wartosc / 6;
		ustawMusik(gracz, czyGracz3, textureSize, x, y, 1);
		if (id == 0) {
			x = musik[2].wartosc % 6;
			y = musik[2].wartosc / 6;
			ustawMusik(botPrzegrywajacy, czyGracz3, textureSize, x, y, 2);
		}
		else {
			x = musik[0].wartosc % 6;
			y = musik[0].wartosc / 6;
			ustawMusik(botPrzegrywajacy, czyGracz3, textureSize, x, y, 0);
		}
	}
	else if (id == 0 || id == 1) {
		x = musik[2].wartosc % 6;
		y = musik[2].wartosc / 6;
		ustawMusik(gracz, czyGracz3, textureSize, x, y, 2);
		if (id == 0) {
			x = musik[1].wartosc % 6;
			y = musik[1].wartosc / 6;
			ustawMusik(botPrzegrywajacy, czyGracz3, textureSize, x, y, 1);
		}
		else {
			x = musik[0].wartosc % 6;
			y = musik[0].wartosc / 6;
			ustawMusik(botPrzegrywajacy, czyGracz3, textureSize, x, y, 0);
		}
	}
	/*
	* Wyzerowanie warto�ci odpowiadaj�cych za faz� musiku
	* Dzi�ki temu gra mo�e si� rozpocz��
	*/
	czyMusik = false;
	musikCzyNie = false;
	wybierzKarte.setPosition(sf::Vector2f(gracz1[0].card.getPosition().x, gracz1[0].card.getPosition().y));
}
/*
* Medota przypisuj�ca przes�an� karte z musiku, do przes�anej talii gracza
*/
void Gra::ustawMusik(Karta doUstawienia[], bool &czyGracz3, sf::Vector2u textureSize, int x, int y, int id) {
	doUstawienia[7].figura = musik[id].figura;
	doUstawienia[7].kolor = musik[id].kolor;
	doUstawienia[7].wartosc = musik[id].wartosc;
	doUstawienia[7].card.setTexture(texture);
	doUstawienia[7].card.setTextureRect(sf::IntRect(textureSize.x * x, textureSize.y * y, textureSize.x, textureSize.y));
	/*
	* W zale�no�ci od gracza uk�adane s� karty (gracz 3, ma karty u�o�one pionowo)
	*/
	if (doUstawienia[6].card.getPosition().x - doUstawienia[5].card.getPosition().x != 0)
		doUstawienia[7].card.setPosition(sf::Vector2f(doUstawienia[6].card.getPosition().x + 110.0f, doUstawienia[6].card.getPosition().y));
	else {
		doUstawienia[7].card.setPosition(sf::Vector2f(doUstawienia[6].card.getPosition().x, doUstawienia[6].card.getPosition().y + 100.0f));
		czyGracz3 = true;
	}
	doUstawienia[7].card.setOrigin(sf::Vector2f(doUstawienia[7].card.getGlobalBounds().width / 2, doUstawienia[7].card.getGlobalBounds().height / 2));
	musik[id].card.setTexture(uzytyMusik);
	czyMeldunek(doUstawienia, jakiMeldunek1);
}

//*************Mechanika gry****************//

/*
* Metoda, kt�ra przesuwa karty z pola widzenia, tak aby nie myli�y gracza po zako�czeniu partii
* na podstawie adresu, kart uzytych w poprzedniej partii
*/
void Gra::usunKarty() {
	cout << "Usuwam karty" << endl;
	poprzednia1->card.setPosition(sf::Vector2f(-100.0f, -100.0f));
	poprzednia2->card.setPosition(sf::Vector2f(-100.0f, -100.0f));
	poprzednia3->card.setPosition(sf::Vector2f(-100.0f, -100.0f));
}
/*
* Metoda, kt�ra sprawdza czy gracz, kt�rego talia zosta�a wys�ana posiada meldunek
*/
void Gra::czyMeldunek(Karta kartyGracza[], bool jakiMeldunek[]){
	cout << "Sprawdzam czy meldunek" << endl;
	for (int i = 0; i < 8; i++) {
		/*
		* Sprawdzenie po kr�lach oraz damach, je�eli wyst�puj� to odpowiednie warto�ci s� zmieniane.
		* meldunekKrole[] jest to tablica kr�li, kt�rej pierwsze warto�ci oznaczaj� czy s� na r�ce,
		* a druga m�wi o indeksie, gdzie znajduje si� w talii gracza. 
		* 
		* Analogia dla meldunekKrolowe[]
		*/
		if (kartyGracza[i].figura == "K") {
			if (kartyGracza[i].kolor == "karo") {
				meldunekKrole[0].first.first = true;
				meldunekKrole[0].first.second = i;
			}
			else if (kartyGracza[i].kolor == "kier") {
				meldunekKrole[1].first.first = true;
				meldunekKrole[1].first.second = i;
			}
			else if (kartyGracza[i].kolor == "pik") {
				meldunekKrole[2].first.first = true;
				meldunekKrole[2].first.second = i;
			}
			else if (kartyGracza[i].kolor == "trefl") {
				meldunekKrole[3].first.first = true;
				meldunekKrole[3].first.second = i;
			}
		}
		else if (kartyGracza[i].figura == "Q") {
			if (kartyGracza[i].kolor == "karo") {
				meldunekKrolowe[0].first.first = true;
				meldunekKrolowe[0].first.second = i;
			}
			else if (kartyGracza[i].kolor == "kier") {
				meldunekKrolowe[1].first.first = true;
				meldunekKrolowe[1].first.second = i;
			}
			else if (kartyGracza[i].kolor == "pik") {
				meldunekKrolowe[2].first.first = true;
				meldunekKrolowe[2].first.second = i;
			}
			else if (kartyGracza[i].kolor == "trefl") {
				meldunekKrolowe[3].first.first = true;
				meldunekKrolowe[3].first.second = i;
			}
		}
	}
	/*
	* Sprawdzenie tablicy, czy obie warto�ci o jednym indeksie maj� warto�� true, je�eli tak to taki gracz posiada meldunek
	*/
	for (int i = 0; i < 4; i++) {
		if (meldunekKrole[i].first.first == true && meldunekKrolowe[i].first.first == true) {
			kartyGracza[meldunekKrole[i].first.second].meldunek = true;
			kartyGracza[meldunekKrolowe[i].first.second].meldunek = true;
			jakiMeldunek[i] = true;
			ileMeldunkow++;
		}
	}
	podajMeldunek(jakiMeldunek);
	/*
	* Reset warto�ci, by mog�y zosta� sprawdzone inne talie graczy
	*/
	for (int i = 0; i < 4; i++) {
		meldunekKrole[i].first.first = false;
		meldunekKrolowe[i].first.first = false;
		meldunekKrole[i].first.second = 0;
		meldunekKrolowe[i].first.second = 0;
	}
}
/*
* Metoda, kt�ra pokazuje, jaki meldunek posiada gracz, metoda ta nie ma wp�ywu na mechanik�
*/
void Gra::podajMeldunek(bool jakiMeldunek[]) {
	if (ileMeldunkow != 0) {
		for (int i = 0; i < 4; i++) {
			if (jakiMeldunek[i] == true) {
				cout << "Mamy meldunek gracza: " << meldunekKrole[i].second << endl ;
			}
		}
	}
}
/*
* Metoda pobieraj�ca warto�ci, wybranych kart
*/
void Gra::pobieranieWartosci(Karta& kartaGracza, Karta& kartaBota) {
	cout << "Pobieranie Wartosci" << endl;
	Karta kartaGracza2, kartaGracza3;
	/*
	* W zale�no�ci od tego kto aktualnie prowadzi rozgrywk� w danej chwili
	* czyJaProwadze.first == true && czyJaProwadze.second == true - oznacza, �e prowadzi gracz 1 (true, true)
	* nast�pnie (false && true) oznacza gracz2, a (true&&false) - gracz3
	* 
	* Odpowiednio do prowadz�cego, dobierane s� warto�ci kart, kt�re zosta�y wybrane.
	*/
	if (czyJaProwadze.first == true && czyJaProwadze.second == true) {
		kartaGracza2 = pobierzWartosciBot(kartaGracza, gracz2, a);
		kartaGracza3 = pobierzWartosciBot(kartaGracza, gracz3, b);
		/*
		* G��wna mechanika gry, sprawdzaj�ca karty
		*/
		mechanika(kartaGracza, kartaGracza2, kartaGracza3);
	}
	else if (czyJaProwadze.first == false && czyJaProwadze.second == true) {
		kartaGracza3 = pobierzWartosciBot(kartaBota, gracz3, b);
		mechanika(kartaGracza, kartaBota, kartaGracza3);
	}
	else if (czyJaProwadze.first == true && czyJaProwadze.second == false) {
		kartaGracza2 = pobierzWartosciBot(kartaBota, gracz2, a);
		mechanika(kartaGracza, kartaGracza2, kartaBota);
	}
	poprzednia1 = &kartaGracza;
	tmp++;
	/*
	* Ustawienie zaktualizowanych punkt�w
	*/
	punkty1.setString(to_string(pkt1));
	punkty2.setString(to_string(pkt2));
	punkty3.setString(to_string(pkt3));
}
/*
* Pobieranie warto�ci gracza, kt�ry nie jest sterowany przez osob� graj�c�,
* w przypadku, gdy ten wygra� poprzedni� rund� i jest prowadz�cym
*/
Karta Gra::pobierzWartosciBot(Karta kartaBota[], float x) {
	cout << "Pobieranie wartosci Bota" << endl;
	int indexKartyBota{};
	int wartosc{};
	/*
	* Nieskomplikowany algorytm, kt�ry wbiera pierwsz� kart�, kt�r� gracz jest w stanie u�y�
	*/
	if (wartosc == 0 && indexKartyBota == 0) {
		for (int i = 0; i < 8; i++) {
			if (kartaBota[i].uzyta == false) {
				indexKartyBota = i;
				break;
			}
		}
	}
	cout << "Bot wygywa i wybiera: " << kartaBota[indexKartyBota].figura << "   " << kartaBota[indexKartyBota].kolor << endl;
	/*
	* Zaznaczenie, �e karta zosta�a ju� u�yta i nie mo�e by� uzyta raz jeszcze
	* Przesuni�cie na �rodek planszy
	*/
	kartaBota[indexKartyBota].uzyta = true;
	kartaBota[indexKartyBota].card.setPosition(sf::Vector2f(x, 400.0f));
	/*
	* Pobranie adresu karty, by po partyii mog�a zosta� przesuni�ta poza ekran
	*/
	pobierzAdresBot(kartaBota[indexKartyBota]);
	return kartaBota[indexKartyBota];
}
/*
* Metoda wybieraj�ca karty dla graczy, kt�re nie s� sterowane przez osob�
* w przypadku, gdy prowadz�cym jest osoba graj�ca
*/
Karta Gra::pobierzWartosciBot(Karta& kartaGracza, Karta kartaBota[], float x){
	cout << "Pobieranie wartosci Bota 2" << endl;
	int indexKartyBota{};
	int wartosc{};
	/*
	* Wybieranie spo�r�d talii gracza nieprowadz�cego takich kart, kt�re odpowiadaj� kolorem na wystawion� kart�
	* przez prowadz�cego oraz wybranie karty, kt�ra jest najmocniejsza obecnie z danego koloru
	*/
	for (int i = 0; i < 8; i++) {
		if (kartaGracza.kolor == kartaBota[i].kolor && kartaBota[i].uzyta == false) {
			if (kartaBota[i].wartosc > wartosc) {
				wartosc = kartaBota[i].wartosc;
				indexKartyBota = i;
			}
		}
	}
	/*
	* W przypadku braku takiej karty, brana jest pierwsza karta, kt�ra nie zosta�a jeszcze u�yta
	*/
	if (wartosc == 0 && indexKartyBota == 0) {
		for (int i = 0; i < 8; i++) {
			if (kartaBota[i].uzyta == false) {
				indexKartyBota = i;
				break;
			}
		}
	}
	cout << "Bot przegrywa i wybiera: " << kartaBota[indexKartyBota].figura << "   " << kartaBota[indexKartyBota].kolor << endl;
	/*
	* Zaznaczenie, �e karta zosta�a ju� u�yta i nie mo�e by� uzyta raz jeszcze
	* Przesuni�cie karty na �rodek planszy
	*/
	kartaBota[indexKartyBota].uzyta = true;
	kartaBota[indexKartyBota].card.setPosition(sf::Vector2f(x, 400.0f));
	/*
	* Pobranie adresu karty
	*/
	pobierzAdresBot(kartaBota[indexKartyBota]);
	return kartaBota[indexKartyBota];
}

/*
* Metoda pobieraj�ca adres karty gracza, niesterowanego przez osob�
*/
void Gra::pobierzAdresBot(Karta& kartaBot){
	cout <<"Co sie kryje w adresie: " << kartaBot.figura << "  " << kartaBot.kolor << endl;
	if (tmp2 == 0) {
		poprzednia2 = &kartaBot;
		tmp2 = 1;
	}
	else {
		poprzednia3 = &kartaBot;
		tmp2 = 0;
	}
}	

/*
* Metoda g��wnej mechaniki gry, pobiera ona wszystkie 3 karty, kt�re zosta�y wybrane przez graczy
*/
void Gra::mechanika(Karta& kartaGracza, Karta& kartaGracza2, Karta& kartaGracza3) {
	bool wylozonyKolor = false;
	/*
	* Warunek sprawdzaj�cy, jaki jest aktywny meldunek
	*/
	if (aktywnyMeldunek == 1) {
		cout << "Meldunek to pik" << endl;
	}
	else if (aktywnyMeldunek == 2) {
		cout << "Meldunek to trefl" << endl;
	}
	else if (aktywnyMeldunek == 3) {
		cout << "Meldunek to karo" << endl;
	}
	else if (aktywnyMeldunek == 4) {
		cout << "Meldunek to kier" << endl;
	}
	else {
		cout << "Brak meldunku" << endl;
	}
	cout << "Gracz1: " << kartaGracza.figura << "___" << kartaGracza.kolor << "___" << kartaGracza.wartosc << endl;
	cout << "Gracz2: " << kartaGracza2.figura << "___" << kartaGracza2.kolor << "___" << kartaGracza2.wartosc << endl;
	cout << "Gracz3: " << kartaGracza3.figura << "___" << kartaGracza3.kolor << "___" << kartaGracza3.wartosc << endl;
	/*
	* Podstawowy warunek, czy jest aktywny jaki� meldunek
	* aktywnyMeldunek == 0 oznacza jego brak
	*/
	if (aktywnyMeldunek != 0) {
		/*
		* Sprawdzenie kt�ry meldunek jest aktualnie aktywny podczas gry
		* 1 - pik
		* 2 - trefl
		* 3 - karo
		* 4 - kier
		* 
		* Po sprzwdzeniu sprawdzane s� czy karty, graczy posiadaj� ten kolor, jaki jest aktywny meldunek
		* Wybranie kart z tego w�a�nie koloru o najwi�kszej warto�ci
		* Gracz posiadaj�cy tak� kart�, wygrywa 1 parti�, staje si� prowadz�cym w nast�pnej i od niego nast�puje licytacja
		*/
		if (aktywnyMeldunek == 1) {
			if (kartaGracza.kolor == "pik" && kartaGracza2.kolor == "pik" && kartaGracza3.kolor == "pik") {
				wylozonyKolor = true;
				if (kartaGracza.wartosc > kartaGracza2.wartosc && kartaGracza.wartosc > kartaGracza3.wartosc) {
					cout << "  Wygrywa gracz 1 z meldunkiem (gracz 1 i 2 i 3 te same kolory)  " << endl;
					wygrywaG1 = 1;
					prowadziGracz = 1;
					czyJaProwadze.first = true;
					czyJaProwadze.second = true;
				}
				else if (kartaGracza2.wartosc > kartaGracza.wartosc && kartaGracza2.wartosc > kartaGracza3.wartosc) {
					cout << "  Wygrywa gracz 2 z meldunkiem (gracz 1 i 2 i 3 te same kolory)  " << endl;
					wygrywaG2 = 1;
					prowadziGracz = 2;
					czyJaProwadze.first = false;
					czyJaProwadze.second = true;
				}
				else if (kartaGracza3.wartosc > kartaGracza.wartosc && kartaGracza3.wartosc > kartaGracza3.wartosc) {
					cout << "  Wygrywa gracz 3 z meldunkiem (gracz 1 i 2 i 3 te same kolory)  " << endl;
					wygrywaG3 = 1;
					prowadziGracz = 3;
					czyJaProwadze.first = true;
					czyJaProwadze.second = false;
				}
			}
			else if (kartaGracza.kolor == "pik" && kartaGracza2.kolor == "pik" && kartaGracza3.kolor != "pik") {
				wylozonyKolor = true;
				if (kartaGracza.wartosc > kartaGracza2.wartosc) {
					cout << "  Wygrywa gracz 1 z meldunkiem (gracz 1 i 2 te same kolory)  " << endl;
					wygrywaG1 = 1;
					prowadziGracz = 1;
					czyJaProwadze.first = true;
					czyJaProwadze.second = true;
				}
				else if (kartaGracza2.wartosc > kartaGracza.wartosc) {
					cout << "  Wygrywa gracz 2 z meldunkiem (gracz 1 i 2 te same kolory)  " << endl;
					wygrywaG2 = 1;
					prowadziGracz = 2;
					czyJaProwadze.first = false;
					czyJaProwadze.second = true;
				}
			}
			else if (kartaGracza.kolor == "pik" && kartaGracza3.kolor == "pik" && kartaGracza2.kolor != "pik") {
				wylozonyKolor = true;
				if (kartaGracza.wartosc > kartaGracza3.wartosc) {
					cout << "  Wygrywa gracz 1 z meldunkiem (gracz 1 i 3 te same kolory)  " << endl;
					wygrywaG1 = 1;
					prowadziGracz = 1;
					czyJaProwadze.first = true;
					czyJaProwadze.second = true;
				}
				else if (kartaGracza3.wartosc > kartaGracza.wartosc) {
					cout << "  Wygrywa gracz 3 z meldunkiem (gracz 1 i 3 te same kolory)  " << endl;
					wygrywaG3 = 1;
					prowadziGracz = 3;
					czyJaProwadze.first = true;
					czyJaProwadze.second = false;
				}
			}
			else if (kartaGracza3.kolor == "pik" && kartaGracza2.kolor == "pik" && kartaGracza.kolor != "pik") {
				wylozonyKolor = true;
				if (kartaGracza3.wartosc > kartaGracza2.wartosc) {
					cout << "  Wygrywa gracz 3 z meldunkiem (gracz 2 i 3 te same kolory)  " << endl;
					wygrywaG3 = 1;
					prowadziGracz = 3;
					czyJaProwadze.first = true;
					czyJaProwadze.second = false;
				}
				else if (kartaGracza2.wartosc > kartaGracza3.wartosc) {
					cout << "  Wygrywa gracz 2 z meldunkiem (gracz 2 i 3 te same kolory)  " << endl;
					wygrywaG2 = 1;
					prowadziGracz = 2;
					czyJaProwadze.first = false;
					czyJaProwadze.second = true;
				}
			}
			else if (kartaGracza.kolor == "pik" && kartaGracza2.kolor != "pik" && kartaGracza3.kolor != "pik") {
				cout << "  Wygrywa gracz 1 z meldunkiem (brak kolorow)  " << endl;
				wylozonyKolor = true;
				wygrywaG1 = 1;
				prowadziGracz = 1;
				czyJaProwadze.first = true;
				czyJaProwadze.second = true;
			}
			else if (kartaGracza.kolor != "pik" && kartaGracza2.kolor == "pik" && kartaGracza3.kolor != "pik") {
				cout << "  Wygrywa gracz 2 z meldunkiem (brak kolorow)  " << endl;
				wylozonyKolor = true;
				wygrywaG2 = 1;
				prowadziGracz = 2;
				czyJaProwadze.first = false;
				czyJaProwadze.second = true;
			}
			else if (kartaGracza.kolor != "pik" && kartaGracza2.kolor != "pik" && kartaGracza3.kolor == "pik") {
				cout << "  Wygrywa gracz 3 z meldunkiem (brak kolorow)  " << endl;
				wylozonyKolor = true;
				wygrywaG3 = 1;
				prowadziGracz = 3;
				czyJaProwadze.first = true;
				czyJaProwadze.second = false;
			}
		}
		else if (aktywnyMeldunek == 2) {
			if (kartaGracza.kolor == "trefl" && kartaGracza2.kolor == "trefl" && kartaGracza3.kolor == "trefl") {
				wylozonyKolor = true;
				if (kartaGracza.wartosc > kartaGracza2.wartosc && kartaGracza.wartosc > kartaGracza3.wartosc) {
					cout << "  Wygrywa gracz 1 z meldunkiem (gracz 1 i 2 i 3 te same kolory)  " << endl;
					wygrywaG1 = 1;
					prowadziGracz = 1;
					czyJaProwadze.first = true;
					czyJaProwadze.second = true;
				}
				else if (kartaGracza2.wartosc > kartaGracza.wartosc && kartaGracza2.wartosc > kartaGracza3.wartosc) {
					cout << "  Wygrywa gracz 2 z meldunkiem (gracz 1 i 2 i 3 te same kolory)  " << endl;
					wygrywaG2 = 1;
					prowadziGracz = 2;
					czyJaProwadze.first = false;
					czyJaProwadze.second = true;
				}
				else if (kartaGracza3.wartosc > kartaGracza.wartosc && kartaGracza3.wartosc > kartaGracza3.wartosc) {
					cout << "  Wygrywa gracz 3 z meldunkiem (gracz 1 i 2 i 3 te same kolory)  " << endl;
					wygrywaG3 = 1;
					prowadziGracz = 3;
					czyJaProwadze.first = true;
					czyJaProwadze.second = false;
				}
			}
			else if (kartaGracza.kolor == "trefl" && kartaGracza2.kolor == "trefl" && kartaGracza3.kolor != "trefl") {
				wylozonyKolor = true;
				if (kartaGracza.wartosc > kartaGracza2.wartosc) {
					cout << "  Wygrywa gracz 1 z meldunkiem (gracz 1 i 2 te same kolory)  " << endl;
					wygrywaG1 = 1;
					prowadziGracz = 1;
					czyJaProwadze.first = true;
					czyJaProwadze.second = true;
				}
				else if (kartaGracza2.wartosc > kartaGracza.wartosc) {
					cout << "  Wygrywa gracz 2 z meldunkiem (gracz 1 i 2 te same kolory)  " << endl;
					wygrywaG2 = 1;
					prowadziGracz = 2;
					czyJaProwadze.first = false;
					czyJaProwadze.second = true;
				}
			}
			else if (kartaGracza.kolor == "trefl" && kartaGracza3.kolor == "trefl" && kartaGracza2.kolor != "trefl") {
				wylozonyKolor = true;
				if (kartaGracza.wartosc > kartaGracza3.wartosc) {
					cout << "  Wygrywa gracz 1 z meldunkiem (gracz 1 i 3 te same kolory)  " << endl;
					wygrywaG1 = 1;
					prowadziGracz = 1;
					czyJaProwadze.first = true;
					czyJaProwadze.second = true;
				}
				else if (kartaGracza3.wartosc > kartaGracza.wartosc) {
					cout << "  Wygrywa gracz 3 z meldunkiem (gracz 1 i 3 te same kolory)  " << endl;
					wygrywaG3 = 1;
					prowadziGracz = 3;
					czyJaProwadze.first = true;
					czyJaProwadze.second = false;
				}
			}
			else if (kartaGracza3.kolor == "trefl" && kartaGracza2.kolor == "trefl" && kartaGracza.kolor != "trefl") {
				wylozonyKolor = true;
				if (kartaGracza3.wartosc > kartaGracza2.wartosc) {
					cout << "  Wygrywa gracz 3 z meldunkiem (gracz 2 i 3 te same kolory)  " << endl;
					wygrywaG3 = 1;
					prowadziGracz = 3;
					czyJaProwadze.first = true;
					czyJaProwadze.second = false;
				}
				else if (kartaGracza2.wartosc > kartaGracza3.wartosc) {
					cout << "  Wygrywa gracz 2 z meldunkiem (gracz 2 i 3 te same kolory)  " << endl;
					wygrywaG2 = 1;
					prowadziGracz = 2;
					czyJaProwadze.first = false;
					czyJaProwadze.second = true;
				}
			}
			else if (kartaGracza.kolor == "trefl" && kartaGracza2.kolor != "trefl" && kartaGracza3.kolor != "trefl") {
				cout << "  Wygrywa gracz 1 z meldunkiem (brak kolorow)  " << endl;
				wylozonyKolor = true;
				wygrywaG1 = 1;
				prowadziGracz = 1;
				czyJaProwadze.first = true;
				czyJaProwadze.second = true;
			}
			else if (kartaGracza.kolor != "trefl" && kartaGracza2.kolor == "trefl" && kartaGracza3.kolor != "trefl") {
				cout << "  Wygrywa gracz 2 z meldunkiem (brak kolorow)  " << endl;
				wylozonyKolor = true;
				wygrywaG2 = 1;
				prowadziGracz = 2;
				czyJaProwadze.first = false;
				czyJaProwadze.second = true;
			}
			else if (kartaGracza.kolor != "trefl" && kartaGracza2.kolor != "trefl" && kartaGracza3.kolor == "trefl") {
				cout << "  Wygrywa gracz 3 z meldunkiem (brak kolorow)  " << endl;
				wylozonyKolor = true;
				wygrywaG3 = 1;
				prowadziGracz = 3;
				czyJaProwadze.first = true;
				czyJaProwadze.second = false;
			}
		}
		else if (aktywnyMeldunek == 3) {
			if (kartaGracza.kolor == "karo" && kartaGracza2.kolor == "karo" && kartaGracza3.kolor == "karo") {
				wylozonyKolor = true;
				if (kartaGracza.wartosc > kartaGracza2.wartosc && kartaGracza.wartosc > kartaGracza3.wartosc) {
					cout << "  Wygrywa gracz 1 z meldunkiem (gracz 1 i 2 i 3 te same kolory)  " << endl;
					wygrywaG1 = 1;
					prowadziGracz = 1;
					czyJaProwadze.first = true;
					czyJaProwadze.second = true;
				}
				else if (kartaGracza2.wartosc > kartaGracza.wartosc && kartaGracza2.wartosc > kartaGracza3.wartosc) {
					cout << "  Wygrywa gracz 2 z meldunkiem (gracz 1 i 2 i 3 te same kolory)  " << endl;
					wygrywaG2 = 1;
					prowadziGracz = 2;
					czyJaProwadze.first = false;
					czyJaProwadze.second = true;
				}
				else if (kartaGracza3.wartosc > kartaGracza.wartosc && kartaGracza3.wartosc > kartaGracza3.wartosc) {
					cout << "  Wygrywa gracz 3 z meldunkiem (gracz 1 i 2 i 3 te same kolory)  " << endl;
					wygrywaG3 = 1;
					prowadziGracz = 3;
					czyJaProwadze.first = true;
					czyJaProwadze.second = false;
				}
			}
			else if (kartaGracza.kolor == "karo" && kartaGracza2.kolor == "karo" && kartaGracza3.kolor != "karo") {
				wylozonyKolor = true;
				if (kartaGracza.wartosc > kartaGracza2.wartosc) {
					cout << "  Wygrywa gracz 1 z meldunkiem (gracz 1 i 2 te same kolory)  " << endl;
					wygrywaG1 = 1;
					prowadziGracz = 1;
					czyJaProwadze.first = true;
					czyJaProwadze.second = true;
				}
				else if (kartaGracza2.wartosc > kartaGracza.wartosc) {
					cout << "  Wygrywa gracz 2 z meldunkiem (gracz 1 i 2 te same kolory)  " << endl;
					wygrywaG2 = 1;
					prowadziGracz = 2;
					czyJaProwadze.first = false;
					czyJaProwadze.second = true;
				}
			}
			else if (kartaGracza.kolor == "karo" && kartaGracza3.kolor == "karo" && kartaGracza2.kolor != "karo") {
				wylozonyKolor = true;
				if (kartaGracza.wartosc > kartaGracza3.wartosc) {
					cout << "  Wygrywa gracz 1 z meldunkiem (gracz 1 i 3 te same kolory)  " << endl;
					wygrywaG1 = 1;
					prowadziGracz = 1;
					czyJaProwadze.first = true;
					czyJaProwadze.second = true;
				}
				else if (kartaGracza3.wartosc > kartaGracza.wartosc) {
					cout << "  Wygrywa gracz 3 z meldunkiem (gracz 1 i 3 te same kolory)  " << endl;
					wygrywaG3 = 1;
					prowadziGracz = 3;
					czyJaProwadze.first = true;
					czyJaProwadze.second = false;
				}
			}
			else if (kartaGracza3.kolor == "karo" && kartaGracza2.kolor == "karo" && kartaGracza.kolor != "karo") {
				wylozonyKolor = true;
				if (kartaGracza3.wartosc > kartaGracza2.wartosc) {
					cout << "  Wygrywa gracz 3 z meldunkiem (gracz 2 i 3 te same kolory)  " << endl;
					wygrywaG3 = 1;
					prowadziGracz = 3;
					czyJaProwadze.first = true;
					czyJaProwadze.second = false;
				}
				else if (kartaGracza2.wartosc > kartaGracza3.wartosc) {
					cout << "  Wygrywa gracz 2 z meldunkiem (gracz 2 i 3 te same kolory)  " << endl;
					wygrywaG2 = 1;
					prowadziGracz = 2;
					czyJaProwadze.first = false;
					czyJaProwadze.second = true;
				}
			}
			else if (kartaGracza.kolor == "karo" && kartaGracza2.kolor != "karo" && kartaGracza3.kolor != "karo") {
				cout << "  Wygrywa gracz 1 z meldunkiem (brak kolorow)  " << endl;
				wylozonyKolor = true;
				wygrywaG1 = 1;
				prowadziGracz = 1;
				czyJaProwadze.first = true;
				czyJaProwadze.second = true;
			}
			else if (kartaGracza.kolor != "karo" && kartaGracza2.kolor == "karo" && kartaGracza3.kolor != "karo") {
				cout << "  Wygrywa gracz 2 z meldunkiem (brak kolorow)  " << endl;
				wylozonyKolor = true;
				wygrywaG2 = 1;
				prowadziGracz = 2;
				czyJaProwadze.first = false;
				czyJaProwadze.second = true;
			}
			else if (kartaGracza.kolor != "karo" && kartaGracza2.kolor != "karo" && kartaGracza3.kolor == "karo") {
				cout << "  Wygrywa gracz 3 z meldunkiem (brak kolorow)  " << endl;
				wylozonyKolor = true;
				wygrywaG3 = 1;
				prowadziGracz = 3;
				czyJaProwadze.first = true;
				czyJaProwadze.second = false;
			}
		}
		else if (aktywnyMeldunek == 4) {
			if (kartaGracza.kolor == "kier" && kartaGracza2.kolor == "kier" && kartaGracza3.kolor == "kier") {
				wylozonyKolor = true;
				if (kartaGracza.wartosc > kartaGracza2.wartosc && kartaGracza.wartosc > kartaGracza3.wartosc) {
					cout << "  Wygrywa gracz 1 z meldunkiem (gracz 1 i 2 i 3 te same kolory)  " << endl;
					wygrywaG1 = 1;
					prowadziGracz = 1;
					czyJaProwadze.first = true;
					czyJaProwadze.second = true;
				}
				else if (kartaGracza2.wartosc > kartaGracza.wartosc && kartaGracza2.wartosc > kartaGracza3.wartosc) {
					cout << "  Wygrywa gracz 2 z meldunkiem (gracz 1 i 2 i 3 te same kolory)  " << endl;
					wygrywaG2 = 1;
					prowadziGracz = 2;
					czyJaProwadze.first = false;
					czyJaProwadze.second = true;
				}
				else if (kartaGracza3.wartosc > kartaGracza.wartosc && kartaGracza3.wartosc > kartaGracza3.wartosc) {
					cout << "  Wygrywa gracz 3 z meldunkiem (gracz 1 i 2 i 3 te same kolory)  " << endl;
					wygrywaG3 = 1;
					prowadziGracz = 3;
					czyJaProwadze.first = true;
					czyJaProwadze.second = false;
				}
			}
			else if (kartaGracza.kolor == "kier" && kartaGracza2.kolor == "kier" && kartaGracza3.kolor != "kier") {
				wylozonyKolor = true;
				if (kartaGracza.wartosc > kartaGracza2.wartosc) {
					cout << "  Wygrywa gracz 1 z meldunkiem (gracz 1 i 2 te same kolory)  " << endl;
					wygrywaG1 = 1;
					prowadziGracz = 1;
					czyJaProwadze.first = true;
					czyJaProwadze.second = true;
				}
				else if (kartaGracza2.wartosc > kartaGracza.wartosc) {
					cout << "  Wygrywa gracz 2 z meldunkiem (gracz 1 i 2 te same kolory)  " << endl;
					wygrywaG2 = 1;
					prowadziGracz = 2;
					czyJaProwadze.first = false;
					czyJaProwadze.second = true;
				}
			}
			else if (kartaGracza.kolor == "kier" && kartaGracza3.kolor == "kier" && kartaGracza2.kolor != "kier") {
				wylozonyKolor = true;
				if (kartaGracza.wartosc > kartaGracza3.wartosc) {
					cout << "  Wygrywa gracz 1 z meldunkiem (gracz 1 i 3 te same kolory)  " << endl;
					wygrywaG1 = 1;
					prowadziGracz = 1;
					czyJaProwadze.first = true;
					czyJaProwadze.second = true;
				}
				else if (kartaGracza3.wartosc > kartaGracza.wartosc) {
					cout << "  Wygrywa gracz 3 z meldunkiem (gracz 1 i 3 te same kolory)  " << endl;
					wygrywaG3 = 1;
					prowadziGracz = 3;
					czyJaProwadze.first = true;
					czyJaProwadze.second = false;
				}
			}
			else if (kartaGracza3.kolor == "kier" && kartaGracza2.kolor == "kier" && kartaGracza.kolor != "kier") {
				wylozonyKolor = true;
				if (kartaGracza3.wartosc > kartaGracza2.wartosc) {
					cout << "  Wygrywa gracz 3 z meldunkiem (gracz 2 i 3 te same kolory)  " << endl;
					wygrywaG3 = 1;
					prowadziGracz = 3;
					czyJaProwadze.first = true;
					czyJaProwadze.second = false;
				}
				else if (kartaGracza2.wartosc > kartaGracza3.wartosc) {
					cout << "  Wygrywa gracz 2 z meldunkiem (gracz 2 i 3 te same kolory)  " << endl;
					wygrywaG2 = 1;
					prowadziGracz = 2;
					czyJaProwadze.first = false;
					czyJaProwadze.second = true;
				}
			}
			else if (kartaGracza.kolor == "kier" && kartaGracza2.kolor != "kier" && kartaGracza3.kolor != "kier") {
				cout << "  Wygrywa gracz 1 z meldunkiem (brak kolorow)  " << endl;
				wylozonyKolor = true;
				wygrywaG1 = 1;
				prowadziGracz = 1;
				czyJaProwadze.first = true;
				czyJaProwadze.second = true;
			}
			else if (kartaGracza.kolor != "kier" && kartaGracza2.kolor == "kier" && kartaGracza3.kolor != "kier") {
				cout << "  Wygrywa gracz 2 z meldunkiem (brak kolorow)  " << endl;
				wylozonyKolor = true;
				wygrywaG2 = 1;
				prowadziGracz = 2;
				czyJaProwadze.first = false;
				czyJaProwadze.second = true;
			}
			else if (kartaGracza.kolor != "kier" && kartaGracza2.kolor != "kier" && kartaGracza3.kolor == "kier") {
				cout << "  Wygrywa gracz 3 z meldunkiem (brak kolorow)  " << endl;
				wylozonyKolor = true;
				wygrywaG3 = 1;
				prowadziGracz = 3;
				czyJaProwadze.first = true;
				czyJaProwadze.second = false;
			}
		}
	}
	/*
	* Mechanika, gdy nie ma aktywnego meldunku
	* Sprawdzenie czy osoba prowadz�ca aktywowa�a meldunek, przypisuje si� jej od razu punkty,
	* Karty sprawdzane s� czy karty wy�o�one przez nieprowadz�cego, maj� taki sam kolor, jak prowadz�cego
	* je�eli tak, to sprawdzana jest warto�� tych kart
	* 
	* Gracz, kt�rego karta ma najwi�ksz� warto��, otwrzymuje punkty oraz on jest ustawiany na gracza prowadz�cego
	* w nast�pnej partii
	*/
	if (!wylozonyKolor) {
		if (czyJaProwadze.first == true && czyJaProwadze.second == true) {
			if (kartaGracza.meldunek == true) {
				if (kartaGracza.kolor == "pik") {
					pkt1tmp += 40;
					aktywnyMeldunek = 1;
				}
				else if (kartaGracza.kolor == "trefl") {
					pkt1tmp += 60;
					aktywnyMeldunek = 2;
				}
				else if (kartaGracza.kolor == "karo") {
					pkt1tmp += 80;
					aktywnyMeldunek = 3;
				}
				else if (kartaGracza.kolor == "kier") {
					pkt1tmp += 100;
					aktywnyMeldunek = 4;
				}
			}
			if (kartaGracza.kolor == kartaGracza2.kolor && kartaGracza.kolor == kartaGracza3.kolor) {
				if (kartaGracza.wartosc > kartaGracza2.wartosc && kartaGracza.wartosc > kartaGracza3.wartosc) {
					cout << "  Wygrywa gracz 1 (te same kolory)  " << endl;
					wygrywaG1 = 1;
					prowadziGracz = 1;
					czyJaProwadze.first = true;
					czyJaProwadze.second = true;
				}
				else if (kartaGracza2.wartosc > kartaGracza.wartosc && kartaGracza2.wartosc > kartaGracza3.wartosc) {
					cout << "  Wygrywa gracz 2 (te same kolory)  " << endl;
					wygrywaG2 = 1;
					prowadziGracz = 2;
					czyJaProwadze.first = false;
					czyJaProwadze.second = true;
				}
				else if (kartaGracza3.wartosc > kartaGracza.wartosc && kartaGracza3.wartosc > kartaGracza2.wartosc) {
					cout << "  Wygrywa gracz 3 (te same kolory)  " << endl;
					wygrywaG3 = 1;
					prowadziGracz = 3;
					czyJaProwadze.first = true;
					czyJaProwadze.second = false;
				}
			}
			else if (kartaGracza.kolor == kartaGracza2.kolor) {
				if (kartaGracza.wartosc > kartaGracza2.wartosc) {
					cout << "  Wygrywa gracz 1 (gracz 2 i 1 te same kolory)  " << endl;
					wygrywaG1 = 1;
					prowadziGracz = 1;
					czyJaProwadze.first = true;
					czyJaProwadze.second = true;
				}
				else {
					cout << "  Wygrywa gracz 2 (gracz 2 i 1 te same kolory)  " << endl;
					wygrywaG2 = 1;
					prowadziGracz = 2;
					czyJaProwadze.first = false;
					czyJaProwadze.second = true;
				}
			}
			else if (kartaGracza.kolor == kartaGracza3.kolor) {
				if (kartaGracza.wartosc > kartaGracza3.wartosc) {
					cout << "  Wygrywa gracz 1 (gracz 2 i 1 te same kolory)  " << endl;
					wygrywaG1 = 1;
					prowadziGracz = 1;
					czyJaProwadze.first = true;
					czyJaProwadze.second = true;
				}
				else {
					cout << "  Wygrywa gracz 3 (gracz 2 i 1 te same kolory)  " << endl;
					wygrywaG3 = 1;
					prowadziGracz = 3;
					czyJaProwadze.first = true;
					czyJaProwadze.second = false;
				}
			}
			else {
				cout << "  Wygrywa gracz 1 (brak kolorow)     " << endl;
				wygrywaG1 = 1;
				prowadziGracz = 1;
				czyJaProwadze.first = true;
				czyJaProwadze.second = true;
			}
		}
		else if (czyJaProwadze.first == false && czyJaProwadze.second == true) {
			if (kartaGracza2.meldunek == true) {
				if (kartaGracza2.kolor == "pik") {
					pkt2tmp += 40;
					aktywnyMeldunek = 1;
				}
				else if (kartaGracza2.kolor == "trefl") {
					pkt2tmp += 60;
					aktywnyMeldunek = 2;
				}
				else if (kartaGracza2.kolor == "karo") {
					pkt2tmp += 80;
					aktywnyMeldunek = 3;
				}
				else if (kartaGracza2.kolor == "kier") {
					pkt2tmp += 100;
					aktywnyMeldunek = 4;
				}
			}
			if (kartaGracza2.kolor == kartaGracza.kolor && kartaGracza2.kolor == kartaGracza3.kolor) {
				if (kartaGracza2.wartosc > kartaGracza.wartosc && kartaGracza2.wartosc > kartaGracza3.wartosc) {
					cout << "  Wygrywa gracz 2 (te same kolory)  " << endl;
					wygrywaG2 = 1;
					prowadziGracz = 2;
					czyJaProwadze.first = false;
					czyJaProwadze.second = true;
				}
				else if (kartaGracza.wartosc > kartaGracza2.wartosc && kartaGracza.wartosc > kartaGracza3.wartosc) {
					cout << "  Wygrywa gracz 1 (te same kolory)  " << endl;
					wygrywaG1 = 1;
					prowadziGracz = 1;
					czyJaProwadze.first = true;
					czyJaProwadze.second = true;
				}
				else if (kartaGracza3.wartosc > kartaGracza2.wartosc && kartaGracza3.wartosc > kartaGracza.wartosc) {
					cout << "  Wygrywa gracz 3 (te same kolory)  " << endl;
					wygrywaG3 = 1;
					prowadziGracz = 3;
					czyJaProwadze.first = true;
					czyJaProwadze.second = false;
				}
			}
			else if (kartaGracza2.kolor == kartaGracza.kolor) {
				if (kartaGracza2.wartosc > kartaGracza.wartosc) {
					cout << "  Wygrywa gracz 2 (gracz 2 i 1 te same kolory)  " << endl;
					wygrywaG2 = 1;
					prowadziGracz = 2;
					czyJaProwadze.first = false;
					czyJaProwadze.second = true;
				}
				else {
					cout << "  Wygrywa gracz 1 (gracz 2 i 1 te same kolory)  " << endl;
					wygrywaG1 = 1;
					prowadziGracz = 1;
					czyJaProwadze.first = true;
					czyJaProwadze.second = true;
				}
			}
			else if (kartaGracza2.kolor == kartaGracza3.kolor) {
				if (kartaGracza2.wartosc > kartaGracza3.wartosc) {
					cout << "  Wygrywa gracz 2 (gracz 2 i 3 te same kolory)  " << endl;
					wygrywaG2 = 1;
					prowadziGracz = 2;
					czyJaProwadze.first = false;
					czyJaProwadze.second = true;
				}
				else {
					cout << "  Wygrywa gracz 3 (gracz 2 i 1 te same kolory)  " << endl;
					wygrywaG3 = 1;
					prowadziGracz = 3;
					czyJaProwadze.first = true;
					czyJaProwadze.second = false;
				}
			}
			else {
				cout << "  Wygrywa gracz 2 (brak kolorow)     " << endl;
				wygrywaG2 = 1;
				prowadziGracz = 2;
				czyJaProwadze.first = false;
				czyJaProwadze.second = true;
			}
		}
		else if (czyJaProwadze.first == true && czyJaProwadze.second == false) {
			if (kartaGracza3.meldunek == true) {
				if (kartaGracza3.kolor == "pik") {
					pkt3tmp += 40;
					aktywnyMeldunek = 1;
				}
				else if (kartaGracza3.kolor == "trefl") {
					pkt3tmp += 60;
					aktywnyMeldunek = 2;
				}
				else if (kartaGracza3.kolor == "karo") {
					pkt3tmp += 80;
					aktywnyMeldunek = 3;
				}
				else if (kartaGracza3.kolor == "kier") {
					pkt3tmp += 100;
					aktywnyMeldunek = 4;
				}
			}
			if (kartaGracza3.kolor == kartaGracza2.kolor && kartaGracza3.kolor == kartaGracza.kolor) {
				if (kartaGracza3.wartosc > kartaGracza2.wartosc && kartaGracza3.wartosc > kartaGracza.wartosc) {
					cout << "  Wygrywa gracz 3 (te same kolory)  " << endl;
					wygrywaG3 = 1;
					prowadziGracz = 3;
					czyJaProwadze.first = true;
					czyJaProwadze.second = false;
				}
				else if (kartaGracza2.wartosc > kartaGracza3.wartosc && kartaGracza2.wartosc > kartaGracza.wartosc) {
					cout << "  Wygrywa gracz 2 (te same kolory)  " << endl;
					wygrywaG2 = 1;
					prowadziGracz = 2;
					czyJaProwadze.first = false;
					czyJaProwadze.second = true;
				}
				else if (kartaGracza.wartosc > kartaGracza3.wartosc && kartaGracza.wartosc > kartaGracza2.wartosc) {
					cout << "  Wygrywa gracz 1 (te same kolory)  " << endl;
					wygrywaG1 = 1;
					prowadziGracz = 1;
					czyJaProwadze.first = true;
					czyJaProwadze.second = true;
				}
			}
			else if (kartaGracza3.kolor == kartaGracza2.kolor) {
				if (kartaGracza3.wartosc > kartaGracza2.wartosc) {
					cout << "  Wygrywa gracz 3 (gracz 2 i 3 te same kolory)  " << endl;
					wygrywaG3 = 1;
					prowadziGracz = 3;
					czyJaProwadze.first = true;
					czyJaProwadze.second = false;
				}
				else {
					cout << "  Wygrywa gracz 2 (gracz 2 i 3 te same kolory)  " << endl;
					wygrywaG2 = 1;
					prowadziGracz = 2;
					czyJaProwadze.first = false;
					czyJaProwadze.second = true;
				}
			}
			else if (kartaGracza3.kolor == kartaGracza.kolor) {
				if (kartaGracza3.wartosc > kartaGracza.wartosc) {
					cout << "  Wygrywa gracz 3 (gracz 3 i 1 te same kolory)  " << endl;
					wygrywaG3 = 1;
					prowadziGracz = 3;
					czyJaProwadze.first = true;
					czyJaProwadze.second = false;
				}
				else {
					cout << "  Wygrywa gracz 1 (gracz 3 i 1 te same kolory)  " << endl;
					wygrywaG1 = 1;
					prowadziGracz = 1;
					czyJaProwadze.first = true;
					czyJaProwadze.second = true;
				}
			}
			else {
				cout << "  Wygrywa gracz 3 (brak kolorow)     " << endl;
				wygrywaG3 = 1;
				prowadziGracz = 3;
				czyJaProwadze.first = true;
				czyJaProwadze.second = false;
			}
		}
	}
	/*
	* Podliczenie punkt�w po ka�dym wy�o�eniu kart
	*/
	podliczPunkty(kartaGracza.figura, kartaGracza2.figura, kartaGracza3.figura);
}
/*
* Metoda, odpowiadaj�ca podliczaniu punkt�w po ka�dej partii
*/
void Gra::podliczPunkty(string pierwszy, string drugi, string trzeci) {
	/*
	* Dodawanie odpowiednich punkt�w za karty, kt�re wygrali�my.
	*/
	if (pierwszy == "A")
		punkty += 11;
	else if (pierwszy == "K")
		punkty += 4;
	else if (pierwszy == "Q")
		punkty += 3;
	else if (pierwszy == "J")
		punkty += 2;
	else if (pierwszy == "10")
		punkty += 10;

	if (drugi == "A")
		punkty += 11;
	else if (drugi == "K")
		punkty += 4;
	else if (drugi == "Q")
		punkty += 3;
	else if (drugi == "J")
		punkty += 2;
	else if (drugi == "10")
		punkty += 10;

	if(trzeci == "A")
		punkty += 11;
	else if (trzeci == "K")
		punkty += 4;
	else if (trzeci == "Q")
		punkty += 3;
	else if (trzeci == "J")
		punkty += 2;
	else if (trzeci == "10")
		punkty += 10;
	
	if (wygrywaG1 == 1) {
		pkt1tmp += punkty;
	}
	else if (wygrywaG2 == 1) {
		pkt2tmp += punkty;
	}
	else if (wygrywaG3 == 1) {
		pkt3tmp += punkty;
	}
	cout << pkt1tmp << "  |   " << pkt2tmp << "   |   " << pkt3tmp << endl;
	punkty = 0;
	/*
	* Je�eli gra runda si� ko�czy, podliczane s� punkty zdobyte podczas tej rundy
	*/
	if (doResetuZostalo == 7) {
		cout << "Prowadzi gracz:  " << prowadziGracz << endl;
		/*
		* Gracz, kt�ry prowadzi� licytacj�, je�eli nie osi�gn�� tylu punkt�w ile zalicytowa�,
		* to tyle punkt�w zostaje odj�tych, w przypadku reszty graczy punkty sumuj� si� z ju� zdobytymi
		*/
		if (ktoWygralLicytacje == 1) {
			if (doZdobycia < pkt1tmp) {
				pkt1 += pkt1tmp;
			}
			else {
				pkt1 -= doZdobycia;
			}
			pkt2 += pkt2tmp;
			pkt3 += pkt3tmp;
			ktoWygralPartie = 1;
		}
		if (ktoWygralLicytacje == 2) {
			if (doZdobycia < pkt2tmp) {
				pkt2 += pkt2tmp;
			}
			else {
				pkt2 -= doZdobycia;
			}
			pkt1 += pkt1tmp;
			pkt3 += pkt3tmp;
			ktoWygralPartie = 2;
		}
		if (ktoWygralLicytacje == 3) {
			if (doZdobycia < pkt3tmp) {
				pkt3 += pkt3tmp;
			}
			else {
				pkt3 -= doZdobycia;
			}
			pkt1 += pkt1tmp;
			pkt2 += pkt2tmp;
			ktoWygralPartie = 3;
		}
		/*
		* Zerowanie zmiennych odpowiadaj�cych za podlicznie punkt�w podczas rundy
		*/
		pkt1tmp = 0;
		pkt2tmp = 0;
		pkt3tmp = 0;
	}
}
/*
* Metoda sprawdzaj�ca, kt�ry z graczy wygrywa licytacj�
*/
void Gra::sprawdzLicytacje() {
	/*
	* W zale�no�ci od tego, kt�ry z graczy jest prowadz�cym,
	* w odpowieni spos�b, do sytuacji pobierane s� wysoko�ci licytowanych punkt�w od poszczeg�lnych graczy
	*/
	if (czyJaProwadze.first == true && czyJaProwadze.second == true) {
		licytacjaJa = licytacja.getLicytujeZa();
		if (licytacjaBot2 != -1) {
			licytacjaBot2 = licytacja.licytujBot(gracz2);
		}
		if (licytacjaBot3 != -1) {
			licytacjaBot3 = licytacja.licytujBot(gracz3);
		}
	}
	else if (czyJaProwadze.first == false && czyJaProwadze.second == true) {
		licytacjaJa = licytacja.getLicytujeZa();
		if (licytacjaBot3 != -1) {
			licytacjaBot3 = licytacja.licytujBot(gracz3);
		}
	}
	else if (czyJaProwadze.first == true && czyJaProwadze.second == false) {
		licytacjaJa = licytacja.getLicytujeZa();
		if (licytacjaBot2 != -1) {
			licytacjaBot2 = licytacja.licytujBot(gracz2);
		}
	}
	cout << "Ja: " << licytacjaJa << endl << "Bot2: " << licytacjaBot2 << endl << "Bot3: "<< licytacjaBot3 << endl;
	/*
	* Sprawdzenie czy 2 z 3 graczy zrezygnowa�o z licytacji
	* Je�eli nie ma 2 graczy, kt�rzy zrezygnowali to licytacja odbywa si� wzi��,
	* dop�ki, 2 z graczy nie zrezygnuje
	*/
	if (licytacjaBot2 == -1 && licytacjaBot3 == -1) {
		cout << "Wygrales licytacje" << endl;
		czyJaProwadze.first = true;
		czyJaProwadze.second = true;
		czyLicytacja = false;
		prowadziGracz = 1;
		ktoWygralLicytacje = 1;
		doZdobycia = licytacjaJa;
		licytacja.resetKolei();
	}
	else if (licytacjaJa == -1 && licytacjaBot3 == -1) {
		cout << "Przegrales licytacje, wygrywa 2" << endl;
		czyJaProwadze.first = false;
		czyJaProwadze.second = true;
		czyLicytacja = false;
		prowadziGracz = 2;
		ktoWygralLicytacje = 2;
		doZdobycia = licytacjaBot2;
		licytacja.resetKolei();
		wybierzMusikBot(gracz2, gracz1, gracz3);
	}
	else if (licytacjaJa == -1 && licytacjaBot2 == -1) {
		cout << "Przegrales licytacje, wygrywa 3" << endl;
		czyJaProwadze.first = true;
		czyJaProwadze.second = false;
		czyLicytacja = false;
		prowadziGracz = 3;
		ktoWygralLicytacje = 3;
		doZdobycia = licytacjaBot3;
		licytacja.resetKolei();
		wybierzMusikBot(gracz3, gracz1, gracz2);
	}
	else {
		cout << "Kolejna tura" << endl;
	}

}

/*
* Metoda resetuj�ca wszystkie ustawienia niezb�dne do funkcjonowania poprawnie gry od pocz�tku
*/
void Gra::reset() {
	cout <<"====  Do resetu zostalo: "<< doResetuZostalo << endl;
	if (doResetuZostalo == 8 || czyReset == true) {
		cout << "RESET!" << endl;
		tmp = 0;
		przyznanyMusik = 0;
		licytacjaJa = 0;
		licytacjaBot2 = 0;
		licytacjaBot3 = 0;
		czyReset = false;
		czyMusik = true;
		czyLicytacja = true;
		musikCzyNie = true;
		wystawienie = true;
		poprzednia1 = nullptr;
		poprzednia2 = nullptr;
		poprzednia3 = nullptr;
		czyJaProwadze.first = true;
		czyJaProwadze.second = true;
		gracz1[7].card.setPosition(sf::Vector2f(-100.0f, -100.0f));
		gracz2[7].card.setPosition(sf::Vector2f(-100.0f, -100.0f));
		gracz3[7].card.setPosition(sf::Vector2f(-100.0f, -100.0f));
		wybierzKarte.setPosition(sf::Vector2f(450.0f, 450.0f));
		doResetuZostalo = 0;
		prowadziGracz = 1;
		if (czyReset == true) {
			pkt1 = 0;
			pkt2 = 0;
			pkt3 = 0;
			pkt1tmp = 0;
			pkt2tmp = 0;
			pkt3tmp = 0;
			punkty1.setString(to_string(pkt1));
			punkty2.setString(to_string(pkt2));
			punkty3.setString(to_string(pkt3));
		}
		for (int i = 0; i < 8; i++) {
			kartyUzyte[i] = -1;
			gracz1[i].uzyta = false;
			gracz2[i].uzyta = false;
			gracz3[i].uzyta = false;
		}
		for (int i = 0; i < 3; i++)
			kartyUzyteMusik[i] = -1;
		for (int i = 0; i < 4; i++) {
			meldunekKrole[i].first.first = false;
			meldunekKrole[i].first.second = 0;
			meldunekKrolowe[i].first.first = false;
			meldunekKrolowe[i].first.second = 0;
			jakiMeldunek1[i] = false;
			jakiMeldunek2[i] = false;
			jakiMeldunek3[i] = false;
		}
		licytacja.reset();
		przetasujKarty(talia);
		rozdanie(gracz1, gracz2, gracz3, talia, musik);
		pozycjaKart();
	}
}

/*
* Metoda w kt�rej obs�ugiwane s� zdarzenia okna
*/
void Gra::przebieg() {
	sf::Event zdarzenie;
	while (window.pollEvent(zdarzenie)) {
		switch (zdarzenie.type) {
		case sf::Event::Closed:
			cout << "Zamykam";
			window.close();
			break;
		case sf::Event::KeyReleased:
			/*
			* Okno menu
			*/
			if (przejscieDo == 0) {
				switch (zdarzenie.key.code) {
				case sf::Keyboard::Down:
					menu.wDol();
					break;
				case sf::Keyboard::Up:
					menu.wGore();
					break;
				case sf::Keyboard::Return:
					switch (menu.getOpcja()) {
					/*
					* Przej�cie do gry w�a�ciwej, rozdanie kart i zmiena t�a.
					*/
					case 0:
						przejscieDo = 1;
						przetasujKarty(talia);
						rozdanie(gracz1, gracz2, gracz3, talia, musik);
						pozycjaKart();
						break;
					/*
					* Przejscie do zasad gry
					*/
					case 1:
						przejscieDo = 2;
						break;
					/*
					* Wyjscie z gry
					*/
					case 2:
						window.close();
						break;
					}
				}
			}
			/*
			* Okno gry
			*/
			if (przejscieDo == 1) {
				switch (zdarzenie.key.code) {
				/*
				* Powr�t do menu
				*/
				case sf::Keyboard::Escape:
					reset();
					przejscieDo = 0;
					break;
				case sf::Keyboard::Left:
					if (doResetuZostalo != 7)
						wLewo();
					break;
				case sf::Keyboard::Right:
					if (doResetuZostalo != 7)
						wPrawo();
					break;
				/*
				* Wyb�r karty
				*/
				case sf::Keyboard::A:
					/*
					* Niedost�pne, gdy jest licytacja
					*/
					if (!czyLicytacja) {
						/*
						* Je�eli jest musik, to wybierane s� karty musiku,
						* je�eli nie to karty z talii gracza
						*/
						if (czyMusik) {
							wybierzMusik();
							kartyUzyteMusik[ktoraKartaMusik] = ktoraKartaMusik;
							if (ktoraKartaMusik != 2)
								wPrawo();
							else
								wLewo();
						}
						else {
							/*
							* Je�eli karty s� wystawiane to wystawienie == true
							* je�eli karty zosta�y sprawdzone, to ponowne wci�ni�cie kalwisza A,
							* spowoduje usuni�cie ich z pola widzenia
							*/
							if (wystawienie) {
								if (prowadziGracz == 1) {
									wystawKarte(gracz1[ktoraKarta]);
									pobieranieWartosci(gracz1[ktoraKarta], wybranaPrzezBota);
									kartyUzyte[ktoraKarta] = ktoraKarta;
									if (doResetuZostalo != 7)
										wPrawo();
									wystawienie = false;
								}
								else if (prowadziGracz == 2) {
									wybranaPrzezBota = pobierzWartosciBot(gracz2, a);
									prowadziGracz = 1;
								}
								else if (prowadziGracz == 3) {
									wybranaPrzezBota = pobierzWartosciBot(gracz3, b);
									prowadziGracz = 1;
								}
							}
							else {
								usunKarty();
								wygrywaG1 = 0;
								wygrywaG2 = 0;
								wygrywaG3 = 0;
								wystawienie = true;
								doResetuZostalo++;
								reset();
							}
						}
					}
					break;
				/*
				* Reset gry
				*/
				case sf::Keyboard::R:
					czyReset = true;
					reset();
					break;
				/*
				* Licytacja okre�lonej o wcze�niej wysoko�ci
				*/
				case sf::Keyboard::L:
					/*
					* Niekatywna, je�eli licytacja si� ju� odby�a
					*/
					if (czyLicytacja) {
						/*
						* W zale�no�ci od gracza prowadz�cego jest wybierana kolejno�� licytacji
						*/
						if (ktoWygralPartie == 1) {
							if (licytacjaJa != -1) {
								cout << "Licytacja uzyte: " << licytacja.getLicytacjaUzyte() << endl;
								licytacja.licytuj();
								sprawdzLicytacje();
							}
							else {
								if (licytacjaBot2 > licytacjaBot3) {
									czyJaProwadze.first = false;
									czyJaProwadze.second = true;
									sprawdzLicytacje();
								}
								else {
									czyJaProwadze.first = true;
									czyJaProwadze.second = false;
									sprawdzLicytacje();
								}
							}
						}
						else if (ktoWygralPartie == 2) {
							licytacjaBot2 = licytacja.licytujBot(gracz2);
							cout << "Bot 2 zalicytowal: " <<licytacjaBot2 << endl;
							czyJaProwadze.first = false;
							czyJaProwadze.second = true;
							ktoWygralPartie = 1;
						}
						else if (ktoWygralPartie == 3) {
							licytacjaBot3 = licytacja.licytujBot(gracz3);
							cout << "Bot 3 zalicytowal: " << licytacjaBot3 << endl;
							czyJaProwadze.first = true;
							czyJaProwadze.second = false;
							ktoWygralPartie = 1;
						}
					}
					break;
				case sf::Keyboard::Down:
					if (czyLicytacja && licytacjaJa != -1) {
						licytacja.wDol();
					}
					break;
				case sf::Keyboard::Up:
					if (czyLicytacja && licytacjaJa != -1){
						licytacja.wGore();
					}
					break;
				}			
			}
			/*
			* Ekran zasad
			*/
			if (przejscieDo == 2) {
				switch (zdarzenie.key.code){
				case sf::Keyboard::Escape:
					przejscieDo = 0;
					zasady.ScrollReset();
					break;
				default:
					break;
				}
			}
			break;
			/*
			* W celu przesuni�cia ekranu nale�y u�y� Scrolla na myszy
			*/
		case sf::Event::MouseWheelScrolled:
			if (przejscieDo == 2) {
				if (zdarzenie.mouseWheelScroll.delta > 0) {
					zasady.ScrollWGore();
				}
				else if (zdarzenie.mouseWheelScroll.delta < 0) {
					zasady.ScrollWDol();
				}
			}
		default:
			break;
		}
	}
}

/*
* Metoda odpowiadaj�ca za wy�wietlanie element�w na ekranie
*/
void Gra::okno() {
	window.clear();
	/*
	* Wy�wietlanie poszczeg�lnych obiekt�w
	* przejscieDo == 0 - menu
	* przejscieDo == 1 - gra w�a�ciwa
	* przejscieDo == 2 - zasady gry
	*/
	if (przejscieDo==0) {
		window.setView(view);
		menu.draw(window);
	}
	else if (przejscieDo == 1) {
		window.setView(view);
		window.draw(plansza);
		if(!czyLicytacja)
			window.draw(wybierzKarte);
		for (int i = 0; i < 8; i++) {
			window.draw(gracz1[i].card);
			window.draw(gracz2[i].card);
			window.draw(gracz3[i].card);
		}
		if (czyMusik && !czyLicytacja) {
			for (int i = 0; i < 3; i++) {
				window.draw(musik[i].card);
			}
		}
		if (!wystawienie) {
			window.draw(aByKontynuowac);
			if (wygrywaG1 == 1) {
				window.draw(wygrana);
			}
			else {
				window.draw(przegrana);
			}
		}
		if (czyLicytacja) {
			licytacja.draw(window);
		}
		window.draw(punkty1);
		window.draw(punkty2);
		window.draw(punkty3);
	}
	else if (przejscieDo == 2) {
		zasady.draw(window);
	}
	window.display();
}

/*
* Metoda odpowiadaj�ca rozpocz�ciu gry
*/
void Gra::rozpocznij() {
	while (window.isOpen()) {
		przebieg();
		okno();
	}
}


int main() {
	/*
	* Tworzenie obiektu typu Gra, gdzie znajduj� si� funkcjonalno�ci gry
	*/
	Gra gra;
	gra.rozpocznij();
	return 0;
}

//****************TO-DO LIST*********************
/*   __________________________________________________________________________________________________
	|* przycisk R jako reset/ od poczatku - (resetuje punkty, ustawienie kart, przetasowuje karty)     |
	|	~reset musi nastepowac po kazdej wygranej rundzie, bez resetu punktow (jakis bool)			   |  <- Zrobione
	|__________________________________________________________________________________________________|
	*normalne liczenie punktow, po osiagnieciu w ktorejs turze 1000 pkt, sprawdzane jest, kto ma najwiecej, ten wygrywa (�adny napis)
	
	*zamiast zasady napisac instrukja |-> sterowanie (ruszajace sie strzalki, a[accept] do zatwierdzania, r[reset] do resetu od podstaw)
									  |-> zasady gry (rozdanie, licytacja, meldunki (moze jakies ilustracje), musik, przebieg, zakonczenie.
		
	*meldunek, tworzenie tablicy kroli i dam, jezeli sa w kartach, jezeli maja ten sam kolor to meldunek ++.
		Po wyrzuceniu damy badz kr�la, je�eli owy meldunek mamy to ten kolor jest kolorem dominuj�cym.
	
	 _____________________________________________________
	|*wypisywanie musiku i wybieranie go				  |
	|													  | <--- Zrobione
	|=====================================================|
	|	if wybrana z musiku								  |
	|		to dodaj do gracza							  |
	|	if not											  |
	|		wybrana dodaj do gracza tego innego niz ja    |
	|		zamien moja wybrana z musiskiem miejscami	  |
	|_____________________________________________________|

	 ___________________________________________________________________________________________________________
	|*po wyjsciu z gry (escape) gra musi si� resetowa�, p�ki co tylko wychodzi a nie resetuj� si� punkty.		| <--- Zrobione
	|*																											|
	|																											|
	|* Naprawi� licytacje!!!																					|
	|___________________________________________________________________________________________________________|

*/ 
