/**
 * Ad: Star Wars
 * Aciklama: Kotu karakterlerden kacarak çikisa ulasma oyunu
 * Tarih: 19 Mart 2019
 * Yapimci: Fatma Degirmenci & Berfin Kosemen
 * Numaralar: 170201008 & 170201058
 */


#include "Karakter.h"
#include "DarthVader.h"
#include "KyloRen.h"
#include "Lokasyon.h"
#include "LukeSkywalker.h"
#include "MasterYoda.h"
#include "StormTrooper.h"

#include <iostream>
#include <string>
#include <fstream> //Dosyalama islemleri icin gerekli olan kutuphane.
#include <sstream> //sstringstream icin
#include <iomanip> // formatli yazmak icin
#include<vector> //vektor kullanimi icin
#include <cmath> //shortestPath

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

vector<int> finish, roots, rootsD;
vector <vector<int> >ways, waysD;

int olcum;
int returnDegeri;
using namespace std;

int numberOfBadCharacters;
string *badCharactersName;
string *gates;

Karakter *character;
DarthVader* Dv = nullptr;
KyloRen* Kr = nullptr;
Stormtrooper* St = nullptr;

string nameOfUsersCharacter;
vector<Karakter*> badCharacters;

//For restart
vector <int> firstLocationBadCharactersX, firstLocationBadCharactersY;
int firstLocationUserX, firstLocationUserY;

const float FPS = 8.5;
const int SCREEN_W = 750, SCREEN_H = 645;

const float addMotion = 35.0, startX = (SCREEN_W-(14*35)) / 2.0, startY = (SCREEN_H - (11*35)) / 2.0; //x icin 130, y icin 130

ALLEGRO_BITMAP * ZERO = NULL, *ONE = NULL, *A = NULL, *B = NULL, *C = NULL, *D = NULL, *E = NULL, *START = NULL;
ALLEGRO_BITMAP * AWARD = NULL, *LEFT = NULL, *RIGHT = NULL, *UP = NULL, *DOWN = NULL, *FULL = NULL, *HALFLEFT = NULL, *HALFRIGHT = NULL;
ALLEGRO_BITMAP *DARTHVADER = NULL, *STORMTROOPER = NULL, *KYLOREN = NULL, *MASTERYODA = NULL, *LUKESKYWALKER = NULL;
ALLEGRO_BITMAP * RED = NULL;

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;

const int endpointX = startX+13*35, endpointY = startY+9*35;
bool gameStatus = true;

int map[11][14];

enum MYKEYS	{
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

void activeAllegro();
void destroyAllegro();
void createDisplay();
void draw_map();
void drawRed();
void drawCharacter();
void createCharacter(string);
//void chooseCharacterType();
void readHaritaTxt();
void createBadCharacters();
void compareCoordinatesOfCharacters();
bool checkCharactersHealth();
bool checkGameStatus();
void drawBadCharacters();
void drawHealth();
void restartGame();
void assignStartingPoint();
void startOfCoordinatesBadCharacters();

int main(int argc, char **argv) {
	activeAllegro();
	//chooseCharacterType();
	readHaritaTxt();
	createBadCharacters();
	startOfCoordinatesBadCharacters();
	assignStartingPoint();
	createDisplay();
	draw_map();
	drawCharacter();

    return 0;
}

void activeAllegro() {
	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_install_keyboard();
}

void createDisplay() {
	display = al_create_display(SCREEN_W, SCREEN_H);
}

void destroyAllegro() {
	al_destroy_bitmap(character->character);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
}

/*void chooseCharacterType() {
	int choice;
	x : cout << "\t2 Karakterden birini secin: \n" <<endl;
	cout << "\t\tMaster Yoda icin 1'e \n"
			"\t\tLuke Skywalker icin 2'ye\n\n"
			"\tbasin : ";
	cin >> choice;

	if(choice == 1) {
		nameOfUsersCharacter = "MasterYoda";
		createCharacter("MasterYoda");
	}
	else if(choice == 2) {
		nameOfUsersCharacter = "LukeSkywalker";
		createCharacter("LukeSkywalker");
	}
	else {
		cout << "\n\tHatali giris! Lutfen tekrar deneyiniz.\n" <<endl;
		goto x;
	}
}*/

void readHaritaTxt() {
	ifstream file;
	string word;
	int wordCounter = 0;

	file.open("Harita.txt");
	while(file >> word) {
		wordCounter++;
	}
	file.close();

	string allWords[wordCounter];

	file.open("Harita.txt");
	int i = 0;
	while(file >> word) {
		allWords[i] = word;
		i++;
	}

	numberOfBadCharacters = wordCounter - 11*14-1;

	int k=0;
	for(int i=0; i<11; i++) {
		for(int j=0; j<14; j++) {
			istringstream iss(allWords[numberOfBadCharacters+1+k]);
			iss >> map[i][j];
			k++;
		}
	}

	badCharactersName = new string[numberOfBadCharacters];
	gates = new string[numberOfBadCharacters];
    int sayac = 0;

	for(int i=0; i<=numberOfBadCharacters; i++) {
		char *arr = new char [allWords[i].length()+1];
		strcpy(arr, allWords[i].c_str());

		for(int j=0; j<strlen(arr); j++) {
			if(arr[j] == ':') {
			    if(arr[j+1] == 'M' && sayac == 0) {
                    nameOfUsersCharacter = "MasterYoda";
                    createCharacter("MasterYoda");
                    sayac++;
                    j += 10;
			    }
			    if(arr[j+1] == 'L' && sayac == 0) {
                    nameOfUsersCharacter = "LukeSkywalker";
                    createCharacter("LukeSkywalker");
                    sayac++;
                    j += 13;
			    }
			    else {
                    for(int k = j+1; k<strlen(arr); k++) {
                        if(arr[k] == ',') {
                            badCharactersName[i-1] = string(&arr[j+1], &arr[k]);
                        }
                        if(arr[k] == ',' && arr[k+5] == ':') {
                            gates[i-1] = string(&arr[k+6]);
                        }
                    }
                }
            }
        }
    }
}

void createCharacter(string characterType) {
	if(characterType.compare("MasterYoda") == 0) {

		character = new MasterYoda;
		character->character = al_load_bitmap("images\\images_MasterYoda.png");
	}
	else if(characterType.compare("LukeSkywalker") == 0) {
		character = new LukeSkywalker;
		character->character = al_load_bitmap("images\\images_LukeSkywalker.png");
	}

	al_set_target_bitmap(character->character);
	character->setXCoordinate(startX + 6*35);
	character->setYCoordinate(startY + 5*35);
}

void compareCoordinatesOfCharacters() {
	int flag = 0;

	for(int i=0; i<numberOfBadCharacters; i++) {
		if(badCharacters[i]->getXCoordinate() == character->getXCoordinate() &&
			badCharacters[i]->getYCoordinate() == character->getYCoordinate()) {
				flag++;
		}
	}

	if(flag != 0) {
		if(nameOfUsersCharacter == "MasterYoda") {
			character->setHealth(character->getHealth()-1);
			restartGame();
		}
		if(nameOfUsersCharacter == "LukeSkywalker")
			character->setHealth(character->getHealth()-2);
			restartGame();
	}

	draw_map();
    int olcum = 0;
	Karakter *p;

        for(int i=0; i<numberOfBadCharacters; i++) {
            p=badCharacters[i];
            if (Kr = dynamic_cast<KyloRen*>(p))
            {
                Kr->shortestPath(&badCharacters, character, olcum, &finish, &ways, &roots, i);
            }
            else if (Dv = dynamic_cast<DarthVader*>(p))
            {
                returnDegeri = Dv->shortestPath(&badCharacters, character, olcum, &finish, &waysD, &rootsD, i);
            }
            else if (St = dynamic_cast<Stormtrooper*>(p))
            {
                St->shortestPath(&badCharacters, character, olcum, &finish, &ways, &roots, i);
            }
        }

    drawRed();

	drawHealth();
}

bool checkCharactersHealth() {
	if(character->getHealth() == 0) {
		gameStatus = false;
		return false;
	}
	return true;
}

bool checkGameStatus() {
	if(character->getXCoordinate() == endpointX &&
		character->getYCoordinate() == endpointY) {
        gameStatus = false;
        return false;
	}
	return true;
}

void createBadCharacters() {
	for(int i=0; i<numberOfBadCharacters; i++) {
		if(gates[i].compare("A") == 0) {
			if(badCharactersName[i].compare("DarthVader") == 0) {
				badCharacters.push_back(new DarthVader());
			}
			if(badCharactersName[i].compare("KyloRen") == 0) {
				badCharacters.push_back(new KyloRen());
			}
			if(badCharactersName[i].compare("Stormtrooper") == 0) {
				badCharacters.push_back(new Stormtrooper());
			}

			badCharacters[i]->setXCoordinate(startX+0*35);
			badCharacters[i]->setYCoordinate(startX+5*35);
		}
		if(gates[i].compare("B") == 0) {
			if(badCharactersName[i].compare("DarthVader") == 0) {
				badCharacters.push_back(new DarthVader());
			}
			if(badCharactersName[i].compare("KyloRen") == 0) {
				badCharacters.push_back(new KyloRen());
			}
			if(badCharactersName[i].compare("Stormtrooper") == 0) {
				badCharacters.push_back(new Stormtrooper());
			}

			badCharacters[i]->setXCoordinate(startX+4*35);
			badCharacters[i]->setYCoordinate(startY+0*35);
		}
		if(gates[i].compare("C") == 0) {
			if(badCharactersName[i].compare("DarthVader") == 0) {
				badCharacters.push_back(new DarthVader());
			}
			if(badCharactersName[i].compare("KyloRen") == 0) {
				badCharacters.push_back(new KyloRen());
			}
			if(badCharactersName[i].compare("Stormtrooper") == 0) {
				badCharacters.push_back(new Stormtrooper());
			}

			badCharacters[i]->setXCoordinate(startX+12*35);
			badCharacters[i]->setYCoordinate(startY+0*35);
		}
		if(gates[i].compare("D") == 0) {
			if(badCharactersName[i].compare("DarthVader") == 0) {
				badCharacters.push_back(new DarthVader());
			}
			if(badCharactersName[i].compare("KyloRen") == 0) {
				badCharacters.push_back(new KyloRen());
			}
			if(badCharactersName[i].compare("Stormtrooper") == 0) {
				badCharacters.push_back(new Stormtrooper());
			}

			badCharacters[i]->setXCoordinate(startX+13*35);
			badCharacters[i]->setYCoordinate(startY+5*35);
		}
		if(gates[i].compare("E") == 0) {
			if(badCharactersName[i].compare("DarthVader") == 0) {
				badCharacters.push_back(new DarthVader());
			}
			if(badCharactersName[i].compare("KyloRen") == 0) {
				badCharacters.push_back(new KyloRen());
			}
			if(badCharactersName[i].compare("Stormtrooper") == 0) {
				badCharacters.push_back(new Stormtrooper());
			}

			badCharacters[i]->setXCoordinate(startX+4*35);
			badCharacters[i]->setYCoordinate(startY+10*35);
		}
	}
}

void draw_map() {
	bool redraw = true;

	DARTHVADER = al_load_bitmap("images\\images_DarthVader.png");
	STORMTROOPER = al_load_bitmap("images\\images_Stormtrooper.png");
	KYLOREN = al_load_bitmap("images\\images_KyloRen.png");
	MASTERYODA = al_load_bitmap("images\\images_MasterYoda.png");
	LUKESKYWALKER = al_load_bitmap("images\\images_LukeSkywalker.png");

	ZERO = al_load_bitmap("images\\images_0.png");
	ONE = al_load_bitmap("images\\images_1.png");
	A = al_load_bitmap("images\\images_A.png");
	B = al_load_bitmap("images\\images_B.png");
	C = al_load_bitmap("images\\images_C.png");
	D = al_load_bitmap("images\\images_D.png");
	E = al_load_bitmap("images\\images_E.png");
	START = al_load_bitmap("images\\images_BASLANGIC.png");

	RED = al_load_bitmap("images\\images_RED.png");

	AWARD = al_load_bitmap("images\\images_award.png");
	LEFT = al_load_bitmap("images\\images_left.png");
	RIGHT = al_load_bitmap("images\\images_right.png");
	UP = al_load_bitmap("images\\images_up.png");
	DOWN = al_load_bitmap("images\\images_down.png");
	FULL = al_load_bitmap("images\\images_full.png");
	HALFLEFT = al_load_bitmap("images\\images_halfleft.png");
	HALFRIGHT = al_load_bitmap("images\\images_halfright.png");

    al_clear_to_color(al_map_rgb(110,110,110));
	drawHealth();
	al_draw_bitmap(AWARD, startX+14*35, startY+9*35-10, 0);

	int del = 5;
	for(int i=0; i<11; i++) {
		for(int j=0; j<14; j++) {
			if(i==5 && j==6) {
				al_draw_bitmap(START, startX+j*35, startY+i*35, 0);
			}
			else if(i==5 && j==0) {
				al_draw_bitmap(A, startX+j*35, startY+i*35, 0);
				al_draw_bitmap(RIGHT, startX+(j-1)*35-del, startY+i*35, 0);
			}
			else if(i==0 && j==4) {
				al_draw_bitmap(B, startX+j*35, startY+i*35, 0);
				al_draw_bitmap(DOWN, startX+j*35-del, startY * (i-1)*35, 0);
			}
			else if(i==0 && j==12) {
				al_draw_bitmap(C, startX+j*35, startY+i*35, 0);
				al_draw_bitmap(DOWN, startX+j*35-del, startY+(i-1)*35, 0);
			}
			else if(i==5 && j==13) {
				al_draw_bitmap(D, startX+j*35, startY+i*35, 0);
				al_draw_bitmap(LEFT, startX+(j+1)*35-del, startY+i*35, 0);
			}
			else if(i==10 && j==4) {
				al_draw_bitmap(E, startX+j*35, startY+i*35, 0);
				al_draw_bitmap(UP, startX+j*35-del, startY+(i+1)*35, 0);
			}
			else if(map[i][j] == 0) {
				al_draw_bitmap(ZERO, startX+j*35, startY+i*35, 0);
			}
			else if(map[i][j]== 1) {
				al_draw_bitmap(ONE, startX+j*35, startY+i*35, 0);
			}
		}
	}

	ALLEGRO_FONT *font = al_load_ttf_font("fonts\\fonts_pirulen.ttf", 24, 0);
	al_draw_text(font, al_map_rgb(0,0,0), startX+10*35+15, startY-3*35+5, ALLEGRO_ALIGN_CENTER, "Canlar: ");

	ALLEGRO_FONT *font3 = al_load_ttf_font("fonts\\fonts_AdventPro-Regular.ttf", 30, 0);
}

void drawRed() {
    ALLEGRO_FONT *font3 = al_load_ttf_font("fonts\\fonts_AdventPro-Regular.ttf", 20, 0);

    int intText, artis = 0;
    string strText,type, coordx, coordy, coordx2, coordy2, all;

    if(olcum==0) {
        for(int i=0;i<finish.size();i++) {
            Karakter *p;
            p=badCharacters[i];

            if (Dv = dynamic_cast<DarthVader*>(p)) {
                for(int j=1; j<waysD[returnDegeri].size(); j++) {
                    al_draw_bitmap(RED, rootsD[waysD[returnDegeri][j]*2]*35+130, rootsD[waysD[returnDegeri][j]*2+1]*35+130, 0);
                }
            }
            else {
                for(int j=1; j<ways[finish.at(i)].size(); j++)
                    al_draw_bitmap(RED, roots[ways[finish.at(i)][j]*2]*35+130, roots[ways[finish.at(i)][j]*2+1]*35+130, 0);
            }


            type = badCharactersName[i];
            coordx = to_string((badCharacters[i]->getXCoordinate()-130)/35);
            coordy = to_string((badCharacters[i]->getYCoordinate()-130)/35);
            coordx2 = to_string((character->getXCoordinate()-130)/35);
            coordy2 = to_string((character->getYCoordinate()-130)/35);
            all = type + " (" + coordx + ", " + coordy + ")'den (" + coordx2 + ", " + coordy2 + ")'ya";

            const char* chrAll = all.c_str();
            al_draw_text(font3, al_map_rgb(0,0,0), 120, 565+artis, ALLEGRO_ALIGN_LEFT, chrAll);

            if (Dv = dynamic_cast<DarthVader*>(p))
                intText = waysD[returnDegeri].size()-1;
            else if(Kr = dynamic_cast<KyloRen*>(p))
                intText = (ways[finish.at(i)].size())/2;
            else
                intText = ways[finish.at(i)].size()-1;

            strText = to_string(intText);
            char const *chrText = strText.c_str();
            al_draw_text(font3, al_map_rgb(0,0,0), 390, 565+artis, ALLEGRO_ALIGN_LEFT, chrText);
            al_draw_text(font3, al_map_rgb(0,0,0), 405, 565+artis, ALLEGRO_ALIGN_LEFT, "adimda ulasir");
            artis += 20;
        }
    }
    else {
       for(int i=0;i<finish.size();i++) {
            Karakter *p;
            p=badCharacters[i];
            if(i==0) {
                if (Dv = dynamic_cast<DarthVader*>(p)) {
                    for(int j=1; j<waysD[returnDegeri].size(); j++) {
                        al_draw_bitmap(RED, rootsD[waysD[returnDegeri][j]*2]*35+130, rootsD[waysD[returnDegeri][j]*2+1]*35+130, 0);
                    }
                }
                 else if (Kr = dynamic_cast<KyloRen*>(p)){
                    for(int j=1; j<ways[finish.at(i)].size(); j++)
                        al_draw_bitmap(RED, roots[ways[finish.at(i)][j]*2]*35+130, roots[ways[finish.at(i)][j]*2+1]*35+130, 0);
                }
                else {
                    for(int j=1; j<ways[finish.at(i)].size(); j++)
                        al_draw_bitmap(RED, roots[ways[finish.at(i)][j]*2]*35+130, roots[ways[finish.at(i)][j]*2+1]*35+130, 0);
                }
            }
            else {
                if (Dv = dynamic_cast<DarthVader*>(p)) {
                    for(int j=1; j<waysD[returnDegeri].size(); j++) {
                        al_draw_bitmap(RED, rootsD[waysD[returnDegeri][j]*2]*35+130, rootsD[waysD[returnDegeri][j]*2+1]*35+130, 0);
                    }
                }
                 else if (Kr = dynamic_cast<KyloRen*>(p)){
                    for(int j=1; j<ways[finish.at(i)].size(); j++)
                        al_draw_bitmap(RED, roots[ways[finish.at(i)][j]*2]*35+130, roots[ways[finish.at(i)][j]*2+1]*35+130, 0);
                }
                else {
                    for(int j=1; j<ways[finish.at(i)].size(); j++)
                        al_draw_bitmap(RED, roots[ways[finish.at(i)][j]*2]*35+130, roots[ways[finish.at(i)][j]*2+1]*35+130, 0);
                }
            }

            type = badCharactersName[i];
            coordx = to_string((badCharacters[i]->getXCoordinate()-130)/35);
            coordy = to_string((badCharacters[i]->getYCoordinate()-130)/35);
            coordx2 = to_string((character->getXCoordinate()-130)/35);
            coordy2 = to_string((character->getYCoordinate()-130)/35);
            all = type + " (" + coordx + ", " + coordy + ")'den (" + coordx2 + ", " + coordy2 + ")'ya";

            const char* chrAll = all.c_str();
            al_draw_text(font3, al_map_rgb(0,0,0), 120, 565+artis, ALLEGRO_ALIGN_LEFT, chrAll);

            if(i==0) {
                if (Dv = dynamic_cast<DarthVader*>(p))
                    intText = waysD[returnDegeri].size()-1;
                else if(Kr = dynamic_cast<KyloRen*>(p))
                    intText = (ways[finish.at(i)].size())/2;
                else
                    intText = ways[finish.at(i)].size()-1;
            }
            else {
                if (Dv = dynamic_cast<DarthVader*>(p))
                    intText = waysD[returnDegeri].size()-1;
                else if(Kr = dynamic_cast<KyloRen*>(p))
                    intText = (ways[finish.at(i)].size())/2;
                else
                    intText = ways[finish.at(i)].size()-1;
            }


            strText = to_string(intText);
            char const *chrText = strText.c_str();
            al_draw_text(font3, al_map_rgb(0,0,0), 390, 565+artis, ALLEGRO_ALIGN_LEFT, chrText);
            al_draw_text(font3, al_map_rgb(0,0,0), 405, 565+artis, ALLEGRO_ALIGN_LEFT, "adimda ulasir");
            artis += 20;
        }
    }
}

void drawCharacter() {
	int src = 43;
	int NUMBEROFNODES;

	NUMBEROFNODES = 43 + 1 + numberOfBadCharacters; //43 dugum 1 iyi karakter 1 kotu karakter

	bool key[4] = {false, false, false, false};
	bool redraw = true;
	bool doexit = false;

	timer = al_create_timer(1.0/FPS);

	al_set_target_bitmap(al_get_backbuffer(display));
	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);

    draw_map();
	olcum = 0;
	Karakter *p;

        for(int i=0; i<numberOfBadCharacters; i++) {
            p=badCharacters[i];
            if (Kr = dynamic_cast<KyloRen*>(p))
            {
                Kr->shortestPath(&badCharacters, character, olcum, &finish, &ways, &roots, i);
            }
            else if (Dv = dynamic_cast<DarthVader*>(p))
            {
                returnDegeri = Dv->shortestPath(&badCharacters, character, olcum, &finish, &waysD, &rootsD, i);
            }
            else if (St = dynamic_cast<Stormtrooper*>(p))
            {
                St->shortestPath(&badCharacters, character, olcum, &finish, &ways, &roots, i);
            }
        }
        drawRed();

	while(!doexit) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(!checkGameStatus()) {
			ALLEGRO_BITMAP * youWinBackground = NULL;
			youWinBackground = al_create_bitmap(750, 645);
			al_set_target_bitmap(youWinBackground);

			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_set_target_bitmap(al_get_backbuffer(display));

			al_draw_bitmap(youWinBackground, 0, 0, 0);

			ALLEGRO_FONT *youWinText = al_load_ttf_font("fonts_pirulen.ttf", 48, 0);

			al_rest(0.1);

			al_draw_text(youWinText, al_map_rgb(255, 255, 255), 750/2, 645/2, ALLEGRO_ALIGN_CENTER, "YOU WIN");

			al_flip_display();

			if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
					break;
				}

			al_rest(5.0);
			break;
		}
		if(!checkCharactersHealth()) {
			ALLEGRO_BITMAP * gameOverBackground = NULL;
			gameOverBackground = al_create_bitmap(750, 645);
			al_set_target_bitmap(gameOverBackground);

			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_set_target_bitmap(al_get_backbuffer(display));

			al_draw_bitmap(gameOverBackground, 0, 0, 0);
			ALLEGRO_FONT *gameOverText = al_load_ttf_font("fonts_pirulen.ttf", 48, 0);
			al_rest(0.1);

			al_draw_text(gameOverText, al_map_rgb(255, 255, 255), 750/2, 645/2-30, ALLEGRO_ALIGN_CENTER, "YOU LOSE");
			al_draw_text(gameOverText, al_map_rgb(255, 255, 255), 750/2, 645/2+30, ALLEGRO_ALIGN_CENTER, "GAME OVER");

			al_flip_display();

			if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                break;
            }

			al_rest(5.0);
			break;
		}

		if(ev.type == ALLEGRO_EVENT_TIMER) {
			if(key[KEY_UP] && character->getYCoordinate() > startY && (map[((int)character->getYCoordinate()-(int)addMotion-130)/35][((int)character->getXCoordinate()-130)/35] != 0)) {
                character->setYCoordinate(character->getYCoordinate()-addMotion);
                //compareCoordinatesOfCharacters();
                olcum++;
                for(int i=0; i<numberOfBadCharacters; i++) {
                    p=badCharacters[i];
                    if (Kr = dynamic_cast<KyloRen*>(p)) {
                        Kr->shortestPath(&badCharacters, character, olcum, &finish, &ways, &roots, i);
                    }
                    else if (Dv = dynamic_cast<DarthVader*>(p)) {
                        returnDegeri = Dv->shortestPath(&badCharacters, character, olcum, &finish, &waysD, &rootsD, i);
                    }
                    else if (St = dynamic_cast<Stormtrooper*>(p)) {
                        St->shortestPath(&badCharacters, character, olcum, &finish, &ways, &roots, i);
                    }
                }
                compareCoordinatesOfCharacters();
				drawBadCharacters();
			}
			if(key[KEY_DOWN] && character->getYCoordinate() < startY+10*35 && (map[((int)character->getYCoordinate()+(int)addMotion-130)/35][((int)character->getXCoordinate()-130)/35] != 0)) {
                character->setYCoordinate(character->getYCoordinate()+addMotion);
            //    compareCoordinatesOfCharacters();
                olcum++;
                for(int i=0; i<numberOfBadCharacters; i++) {
                    p=badCharacters[i];
                    if (Kr = dynamic_cast<KyloRen*>(p))
                    {
                        Kr->shortestPath(&badCharacters, character, olcum, &finish, &ways, &roots, i);
                    }
                    else if (Dv = dynamic_cast<DarthVader*>(p))
                    {
                        returnDegeri = Dv->shortestPath(&badCharacters, character, olcum, &finish, &waysD, &rootsD, i);
                    }
                    else if (St = dynamic_cast<Stormtrooper*>(p))
                    {
                        St->shortestPath(&badCharacters, character, olcum, &finish, &ways, &roots, i);
                    }
                }
                compareCoordinatesOfCharacters();
				drawBadCharacters();
			}
			if(key[KEY_LEFT] &&  character->getXCoordinate() > startX && (map[((int)character->getYCoordinate()-130)/35][((int)(character->getXCoordinate()-addMotion)-130)/35] != 0)) {
				character->setXCoordinate(character->getXCoordinate()-addMotion);
			//	compareCoordinatesOfCharacters();
				olcum++;
				for(int i=0; i<numberOfBadCharacters; i++) {
                    p=badCharacters[i];
                    if (Kr = dynamic_cast<KyloRen*>(p))
                    {
                        Kr->shortestPath(&badCharacters, character, olcum, &finish, &ways, &roots, i);
                    }
                    else if (Dv = dynamic_cast<DarthVader*>(p))
                    {
                        returnDegeri = Dv->shortestPath(&badCharacters, character, olcum, &finish, &waysD, &rootsD, i);
                    }
                    else if (St = dynamic_cast<Stormtrooper*>(p))
                    {
                        St->shortestPath(&badCharacters, character, olcum, &finish, &ways, &roots, i);
                    }
                }

                compareCoordinatesOfCharacters();
				drawBadCharacters();
			}
			if(key[KEY_RIGHT] && character->getXCoordinate() < startX + 13*35 && (map[((int)(character->getYCoordinate())-130)/35][((int)(character->getXCoordinate())+(int)addMotion-130)/35] != 0)) {
                character->setXCoordinate(character->getXCoordinate()+addMotion);
        //        compareCoordinatesOfCharacters();
                olcum++;
				for(int i=0; i<numberOfBadCharacters; i++) {
                    p=badCharacters[i];
                    if (Kr = dynamic_cast<KyloRen*>(p))
                    {
                        Kr->shortestPath(&badCharacters, character, olcum, &finish, &ways, &roots, i);
                    }
                    else if (Dv = dynamic_cast<DarthVader*>(p))
                    {
                        returnDegeri = Dv->shortestPath(&badCharacters, character, olcum, &finish, &waysD, &rootsD, i);
                    }
                    else if (St = dynamic_cast<Stormtrooper*>(p))
                    {
                        St->shortestPath(&badCharacters, character, olcum, &finish, &ways, &roots, i);
                    }
                }

                compareCoordinatesOfCharacters();
				drawBadCharacters();
			}
			redraw = true;
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) { // herhangi bi tusa basildiginda hareketi aktiflestiriyo
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = true;
					break;

				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = true;
					break;

				case ALLEGRO_KEY_LEFT:
					key[KEY_LEFT] = true;
					break;

				case ALLEGRO_KEY_RIGHT:
					key[KEY_RIGHT] = true;
					break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = false;
					draw_map();
					drawRed();

					break;

				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = false;
					draw_map();
					drawRed();
					break;

				case ALLEGRO_KEY_LEFT:
					key[KEY_LEFT] = false;
					draw_map();
					drawRed();
					break;

				case ALLEGRO_KEY_RIGHT:
					key[KEY_RIGHT] = false;
					draw_map();
					drawRed();
					break;

				case ALLEGRO_KEY_ESCAPE:
					doexit = true;
					draw_map();
					break;
			}
		}

		if(redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_draw_bitmap(character->character,character->getXCoordinate(), character->getYCoordinate(), 0);
			drawBadCharacters();

			al_flip_display();
		}
	}
}

void drawBadCharacters() {
	for(int i=0; i<numberOfBadCharacters; i++) {
		if(badCharactersName[i].compare("DarthVader") == 0) {
			al_draw_bitmap(DARTHVADER, badCharacters[i]->getXCoordinate(), badCharacters[i]->getYCoordinate(), 0);
		}
		if(badCharactersName[i].compare("Stormtrooper") == 0) {
			al_draw_bitmap(STORMTROOPER, badCharacters[i]->getXCoordinate(), badCharacters[i]->getYCoordinate(), 0);
		}
		if(badCharactersName[i].compare("KyloRen") == 0) {
			al_draw_bitmap(KYLOREN, badCharacters[i]->getXCoordinate(), badCharacters[i]->getYCoordinate(), 0);
		}
	}
	al_flip_display();
}

void startOfCoordinatesBadCharacters() {
	for(int i=0; i<numberOfBadCharacters; i++) {
		if(gates[i].compare("A") == 0) {
			badCharacters[i]->setXCoordinate(startX+0*35);
			badCharacters[i]->setYCoordinate(startY+5*35);
		}
		if(gates[i].compare("B") == 0) {
			badCharacters[i]->setXCoordinate(startX+4*35);
			badCharacters[i]->setYCoordinate(startY+0*35);
		}
		if(gates[i].compare("C") == 0) {
			badCharacters[i]->setXCoordinate(startX+12*35);
			badCharacters[i]->setYCoordinate(startY+0*35);
		}
		if(gates[i].compare("D") == 0) {

			badCharacters[i]->setXCoordinate(startX+13*35);
			badCharacters[i]->setYCoordinate(startY+5*35);
		}
		if(gates[i].compare("E") == 0) {

			badCharacters[i]->setXCoordinate(startX+4*35);
			badCharacters[i]->setYCoordinate(startY+10*35);
		}
	}
}

void drawHealth() {
	if(character->getHealth() == 6) {
		al_draw_bitmap(FULL, startX+13*35, startY-3*35, 0);
		al_draw_bitmap(FULL, startX+14*35, startY-3*35, 0);
		al_draw_bitmap(FULL, startX+15*35, startY-3*35, 0);
	}
	else if(character->getHealth() == 5) {
		al_draw_bitmap(FULL, startX+13*35, startY-3*35, 0);
		al_draw_bitmap(FULL, startX+14*35, startY-3*35, 0);
		al_draw_bitmap(HALFLEFT, startX+15*35, startY-3*35, 0);
	}
	else if(character->getHealth() == 4) {
		al_draw_bitmap(FULL, startX+13*35, startY-3*35, 0);
		al_draw_bitmap(FULL, startX+14*35, startY-3*35, 0);
	}
	else if(character->getHealth() == 3) {
		al_draw_bitmap(FULL, startX+13*35, startY-3*35, 0);
		al_draw_bitmap(HALFLEFT, startX+14*35, startY-3*35, 0);
	}
	else if(character->getHealth() == 2) {
		al_draw_bitmap(FULL, startX+13*35, startY-3*35, 0);
	}
	else if(character->getHealth() == 1) {
		al_draw_bitmap(HALFLEFT, startX+13*35, startY-3*35, 0);
	}
	else if(character->getHealth() == 5) {
		/**/
	}
	al_flip_display();
}

void assignStartingPoint() {
	firstLocationUserX = character->getXCoordinate();
	firstLocationUserY = character->getYCoordinate();

	for(int i=0; i<numberOfBadCharacters; i++) {
		firstLocationBadCharactersX.push_back(badCharacters[i]->getXCoordinate());
		firstLocationBadCharactersY.push_back(badCharacters[i]->getYCoordinate());
	}
}

void restartGame() {
	character->setXCoordinate(firstLocationUserX);
	character->setYCoordinate(firstLocationUserY);

	for(int i=0; i<numberOfBadCharacters; i++) {
		badCharacters[i]->setXCoordinate(firstLocationBadCharactersX.at(i));
		badCharacters[i]->setYCoordinate(firstLocationBadCharactersY.at(i));
	}


}
