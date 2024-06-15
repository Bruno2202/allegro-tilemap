#include<allegro5/allegro5.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include<iostream>

using namespace std;

#define BLOCKSIZE 32
#define WMAPA 50
#define HMAPA 25
#define SCREENWIDTH BLOCKSIZE*WMAPA
#define SCREENHEIGHT BLOCKSIZE*HMAPA

enum KEYS { UP, DOWN, LEFT, RIGHT };
enum KEYS2 { W, S, A, D };

struct Player {
    bool cheio, entrouPortal;
};

Player P1, P2;

int contItensEntregues = 0;

ALLEGRO_BITMAP* item1 = NULL;
ALLEGRO_BITMAP* item2 = NULL;
ALLEGRO_BITMAP* item3 = NULL;
ALLEGRO_BITMAP* item4 = NULL;
ALLEGRO_BITMAP* item5 = NULL;
ALLEGRO_BITMAP* item6 = NULL;
ALLEGRO_BITMAP* item7 = NULL;

ALLEGRO_BITMAP* pedra1 = NULL;

ALLEGRO_BITMAP* pedraTL = NULL;
ALLEGRO_BITMAP* pedraTR = NULL;
ALLEGRO_BITMAP* pedraBL = NULL;
ALLEGRO_BITMAP* pedraBR = NULL;

ALLEGRO_BITMAP* agua1 = NULL;

ALLEGRO_BITMAP* grama1 = NULL;
ALLEGRO_BITMAP* grama2 = NULL;
ALLEGRO_BITMAP* grama3 = NULL;

ALLEGRO_BITMAP* gramaTL = NULL;
ALLEGRO_BITMAP* gramaTR = NULL;
ALLEGRO_BITMAP* gramaBL = NULL;
ALLEGRO_BITMAP* gramaBR = NULL;

ALLEGRO_BITMAP* pc = NULL;

ALLEGRO_BITMAP* portalT = NULL;
ALLEGRO_BITMAP* portalB = NULL;


int mapa[HMAPA][WMAPA] = {
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 5, 0, 0, 0, 0, 4, 3, 3, 3, 3, 5, 2, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 4, 3,
    3, 0, 10, 0, 1, 0, 0, 3, 3, 3, 5, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 3, 5, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 9, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 9, 0, 0, 0, 0, 0, 2, 0, 3,
    3, 0, 0, 0, 1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 9, 0, 0, 0, 0, 3,
    3, 0, 1, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 3,
    3, 6, 0, 0, 0, 1, 7, 3, 0, 2, 0, 1, 0, 0, 0, 2, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 2, 19, 0, 0, 0, 2, 11, 12, 9, 0, 0, 0, 0, 0, 0, 3,
    3, 3, 3, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 9, 13, 14, 11, 12, 0, 0, 0, 0, 0, 3,
    3, 3, 3, 0, 0, 3, 3, 5, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 13, 14, 9, 0, 1, 0, 0, 3,
    3, 3, 3, 2, 0, 4, 3, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 1, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 15, 0, 0, 11, 12, 0, 0, 0, 3,
    3, 3, 5, 0, 0, 0, 3, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 1, 0, 2, 0, 0, 0, 16, 0, 0, 13, 14, 0, 0, 0, 3,
    3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 12, 9, 0, 0, 2, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 9, 0, 0, 2, 0, 0, 1, 1, 0, 0, 2, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 9, 11, 12, 13, 14, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 13, 14, 9, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 2, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 2, 17, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 2, 21, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 3,
    3, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 9, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 9, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 20, 0, 2, 0, 0, 2, 0, 0, 3,
    3, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 1, 2, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 3,
    3, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
    3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 7, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
};

void DrawMap() {
    for (int i = 0; i < HMAPA; i++) {
        for (int j = 0; j < WMAPA; j++) {

            if (mapa[i][j] == 0) {
                al_draw_bitmap(grama1, j * BLOCKSIZE, i * BLOCKSIZE, 0);
            }
            else if (mapa[i][j] == 1) {
                al_draw_bitmap(grama2, j * BLOCKSIZE, i * BLOCKSIZE, 0);
            }
            else if (mapa[i][j] == 2) {
                al_draw_bitmap(grama3, j * BLOCKSIZE, i * BLOCKSIZE, 0);
            }

            // Colisores
            else if (mapa[i][j] == 3) {
                al_draw_bitmap(agua1, j * BLOCKSIZE, i * BLOCKSIZE, 0);
            }

            //Cantos
            else if (mapa[i][j] == 4) {
                al_draw_bitmap(gramaTL, j * BLOCKSIZE, i * BLOCKSIZE, 0);
            }
            else if (mapa[i][j] == 5) {
                al_draw_bitmap(gramaTR, j * BLOCKSIZE, i * BLOCKSIZE, 0);
            }
            else if (mapa[i][j] == 6) {
                al_draw_bitmap(gramaBL, j * BLOCKSIZE, i * BLOCKSIZE, 0);
            }
            else if (mapa[i][j] == 7) {
                al_draw_bitmap(gramaBR, j * BLOCKSIZE, i * BLOCKSIZE, 0);
            }

            // Itens
            else if (mapa[i][j] == 8) {
                al_draw_bitmap(item1, j * BLOCKSIZE, i * BLOCKSIZE, 0);
            }
            else if (mapa[i][j] == 17) {
                al_draw_bitmap(item2, j * BLOCKSIZE, i * BLOCKSIZE, 0);
            }
            else if (mapa[i][j] == 18) {
                al_draw_bitmap(item3, j * BLOCKSIZE, i * BLOCKSIZE, 0);
            }            
            else if (mapa[i][j] == 19) {
                al_draw_bitmap(item4, j * BLOCKSIZE, i * BLOCKSIZE, 0);
            }            
            else if (mapa[i][j] == 20) {
                al_draw_bitmap(item5, j * BLOCKSIZE, i * BLOCKSIZE, 0);
            }            
            else if (mapa[i][j] == 21) {
                al_draw_bitmap(item6, j * BLOCKSIZE, i * BLOCKSIZE, 0);
            }

            // Pedra pequena
            else if (mapa[i][j] == 9) {
                al_draw_bitmap(pedra1, j * BLOCKSIZE, i * BLOCKSIZE, 0);
            }

            // PC
            else if (mapa[i][j] == 10) {
                al_draw_bitmap(pc, j * BLOCKSIZE, i * BLOCKSIZE, 0);
            }

            // Pedra grande
            else if (mapa[i][j] == 11) {
                al_draw_bitmap(pedraTL, j * BLOCKSIZE, i * BLOCKSIZE, 0);
            }
            else if (mapa[i][j] == 12) {
                al_draw_bitmap(pedraTR, j * BLOCKSIZE, i * BLOCKSIZE, 0);
            }
            else if (mapa[i][j] == 13) {
                al_draw_bitmap(pedraBL, j * BLOCKSIZE, i * BLOCKSIZE, 0);
            }
            else if (mapa[i][j] == 14) {
                al_draw_bitmap(pedraBR, j * BLOCKSIZE, i * BLOCKSIZE, 0);
            }

            if (mapa[i][j] == 15) {
                al_draw_bitmap(grama2, j * BLOCKSIZE, i * BLOCKSIZE, 0);
            }
            else if (mapa[i][j] == 16) {
                al_draw_bitmap(grama1, j * BLOCKSIZE, i * BLOCKSIZE, 0);
            }

            // Portal
            if (contItensEntregues == 6) {
                if (mapa[i][j] == 15 ) {
                    al_draw_bitmap(portalT, j * BLOCKSIZE, i * BLOCKSIZE, 0);
                }
                else if (mapa[i][j] == 16) {
                    al_draw_bitmap(portalB, j * BLOCKSIZE, i * BLOCKSIZE, 0);
                }
            }
        }
    }
}

bool colisao(int px, int py) {
    int x1 = py / BLOCKSIZE;
    int y1 = px / BLOCKSIZE;
    int x2 = (py + 30) / BLOCKSIZE;
    int y2 = (px + 30) / BLOCKSIZE;
    if (mapa[x1][y1] == 3 || mapa[x1][y2] == 3 || mapa[x1][y1] == 9 || mapa[x1][y2] == 9 ||
        mapa[x2][y1] == 3 || mapa[x2][y2] == 3 || mapa[x2][y1] == 9 || mapa[x2][y2] == 9 ||
        mapa[x1][y1] == 11 || mapa[x1][y2] == 11 || mapa[x1][y1] == 12 || mapa[x1][y2] == 12 ||
        mapa[x2][y1] == 11 || mapa[x2][y2] == 11 || mapa[x2][y1] == 12 || mapa[x2][y2] == 12 ||
        mapa[x1][y1] == 13 || mapa[x1][y2] == 13 || mapa[x1][y1] == 14 || mapa[x1][y2] == 14 ||
        mapa[x2][y1] == 13 || mapa[x2][y2] == 13 || mapa[x2][y1] == 14 || mapa[x2][y2] == 14)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool pegarItem(int px, int py, bool cheio) {
    int x1 = py / BLOCKSIZE;
    int y1 = px / BLOCKSIZE;
    int x2 = (py + 30) / BLOCKSIZE;
    int y2 = (px + 30) / BLOCKSIZE;

    if (!cheio)
    {
        if (mapa[x1][y1] == 8 || mapa[x1][y1] == 17 || mapa[x1][y1] == 18 || mapa[x1][y1] == 19 || mapa[x1][y1] == 20 || mapa[x1][y1] == 21)
        {
            mapa[x1][y1] = 0;
            return true;
        }
        else if (mapa[x1][y2] == 8 || mapa[x1][y2] == 17 || mapa[x1][y2] == 18 || mapa[x1][y2] == 19 || mapa[x1][y1] == 20 || mapa[x1][y2] == 21)
        {
            mapa[x1][y2] = 0;
            return true;
        }
        else if (mapa[x2][y1] == 8 || mapa[x2][y1] == 17 || mapa[x2][y1] == 18 || mapa[x2][y1] == 19 || mapa[x2][y1] == 20 || mapa[x2][y1] == 21)
        {
            mapa[x2][y1] = 0;
            return true;
        }
        else if (mapa[x2][y2] == 8 || mapa[x2][y2] == 17 || mapa[x2][y2] == 18 || mapa[x2][y2] == 19 || mapa[x2][y2] == 20 || mapa[x2][y2] == 21)
        {
            mapa[x2][y2] = 0;
            return true;
        }
        else
        {
            return false;
        }
    } 
    else
    {
        return false;
    }
}

bool entregarItem(int px, int py) {
    int x1 = py / BLOCKSIZE;
    int y1 = px / BLOCKSIZE;
    int x2 = (py + 30) / BLOCKSIZE;
    int y2 = (px + 30) / BLOCKSIZE;

    if (mapa[x1][y1] == 10 || mapa[x1][y2] == 10 ||
        mapa[x2][y1] == 10 || mapa[x2][y2] == 10)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

bool entrarPortal(int px, int py) {
    int x1 = py / BLOCKSIZE;
    int y1 = px / BLOCKSIZE;
    int x2 = (py + 30) / BLOCKSIZE;
    int y2 = (px + 30) / BLOCKSIZE;

    if (mapa[x1][y1] == 15 || mapa[x1][y2] == 15 || mapa[x1][y1] == 16 || mapa[x1][y2] == 16 ||
        mapa[x2][y1] == 15 || mapa[x2][y2] == 15 || mapa[x1][y1] == 16 || mapa[x1][y2] == 16 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main() {

    ALLEGRO_DISPLAY* display;

    const float FPS = 60.0;
    bool done = false;
    bool redesenha = true;
    int posX = 260;
    int posY = 260;
    int posX2 = 265;
    int posY2 = 265;

    bool keys[4] = { false, false, false, false };
    bool keys2[4] = { false, false, false, false };

    al_init();
    display = al_create_display(SCREENWIDTH, SCREENHEIGHT);
    al_set_window_position(display, 200, 200);

    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    ALLEGRO_BITMAP* player = al_load_bitmap("assets/p1.png");
    ALLEGRO_BITMAP* player2 = al_load_bitmap("assets/p2.png");

    grama1 = al_load_bitmap("assets/tiles/grama/grama1.png");
    grama2 = al_load_bitmap("assets/tiles/grama/grama2.png");
    grama3 = al_load_bitmap("assets/tiles/grama/grama3.png");

    gramaTL = al_load_bitmap("assets/tiles/grama/gramaTL.png");
    gramaTR = al_load_bitmap("assets/tiles/grama/gramaTR.png");
    gramaBL = al_load_bitmap("assets/tiles/grama/gramaBL.png");
    gramaBR = al_load_bitmap("assets/tiles/grama/gramaBR.png");

    pedra1 = al_load_bitmap("assets/tiles/pedra/pedra.png");
    pedraTL = al_load_bitmap("assets/tiles/pedra/pedraTL.png");
    pedraTR = al_load_bitmap("assets/tiles/pedra/pedraTR.png");
    pedraBL = al_load_bitmap("assets/tiles/pedra/pedraBL.png");
    pedraBR = al_load_bitmap("assets/tiles/pedra/pedraBR.png");

    agua1 = al_load_bitmap("assets/tiles/agua/agua.png");

    item1 = al_load_bitmap("assets/tiles/item/item1.png");
    item2 = al_load_bitmap("assets/tiles/item/item2.png");
    item3 = al_load_bitmap("assets/tiles/item/item3.png");
    item4 = al_load_bitmap("assets/tiles/item/item4.png");
    item5 = al_load_bitmap("assets/tiles/item/item5.png");
    item6 = al_load_bitmap("assets/tiles/item/item6.png");

    pc = al_load_bitmap("assets/pc.png");

    portalT = al_load_bitmap("assets/tiles/portal/portalT.png");
    portalB = al_load_bitmap("assets/tiles/portal/portalB.png");

    al_start_timer(timer);

    while (!done) {

        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);
        ALLEGRO_EVENT_TYPE tipoEvento = events.type;

        switch (tipoEvento) {

            case ALLEGRO_EVENT_TIMER: { redesenha = true; break; }
            case ALLEGRO_EVENT_DISPLAY_CLOSE: { done = true; break; }
                
            // Movimento ↑↓←→
            case ALLEGRO_EVENT_KEY_DOWN: {
                int tecla = events.keyboard.keycode;
                switch (tecla) {
                    case ALLEGRO_KEY_UP: { keys[UP] = true; break; }
                    case ALLEGRO_KEY_DOWN: { keys[DOWN] = true; break; }
                    case ALLEGRO_KEY_LEFT: { keys[LEFT] = true; break; }
                    case ALLEGRO_KEY_RIGHT: { keys[RIGHT] = true; break; }
                }
                break;
            }
            case ALLEGRO_EVENT_KEY_UP: {
                int tecla = events.keyboard.keycode;
                switch (tecla) {
                    case ALLEGRO_KEY_UP: { keys[UP] = false; break; }
                    case ALLEGRO_KEY_DOWN: { keys[DOWN] = false; break; }
                    case ALLEGRO_KEY_LEFT: { keys[LEFT] = false; break; }
                    case ALLEGRO_KEY_RIGHT: { keys[RIGHT] = false; break; }
                    case ALLEGRO_KEY_ESCAPE: { done = true; break; }
                }
                break;
            }
        }

        // Movimento WASD
        if (events.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (events.keyboard.keycode) {
                case ALLEGRO_KEY_W: { keys2[W] = true; break; }
                case ALLEGRO_KEY_S: { keys2[S] = true; break; }
                case ALLEGRO_KEY_A: { keys2[A] = true; break; }
                case ALLEGRO_KEY_D: { keys2[D] = true; break; }
            }
        }
        else if (events.type == ALLEGRO_EVENT_KEY_UP) {
            switch (events.keyboard.keycode) { 
                case ALLEGRO_KEY_W: { keys2[W] = false; break; }
                case ALLEGRO_KEY_S: { keys2[S] = false; break; }
                case ALLEGRO_KEY_A: { keys2[A] = false; break; }
                case ALLEGRO_KEY_D: { keys2[D] = false; break; }
                case ALLEGRO_KEY_ESCAPE: { done = true; break; }
            }
        }

        // Colisão Player 1
        if (!colisao(posX, posY - 2)) {
            posY -= keys[UP] * 2;
        }
        if (!colisao(posX, posY + 2)) {
            posY += keys[DOWN] * 2;
        }
        if (!colisao(posX - 2, posY)) {
            posX -= keys[LEFT] * 2;
        }
        if (!colisao(posX + 2, posY)) {
            posX += keys[RIGHT] * 2;
        }

        // Colisão Player 2
        if (!colisao(posX2, posY2 - 2)) {
            posY2 -= keys2[UP] * 2;
        }
        if (!colisao(posX2, posY2 + 2)) {
            posY2 += keys2[DOWN] * 2;
        }
        if (!colisao(posX2 - 2, posY2)) {
            posX2 -= keys2[LEFT] * 2;
        }
        if (!colisao(posX2 + 2, posY2)) {
            posX2 += keys2[RIGHT] * 2;
        }

        // Pegar Item Player 1
        if (pegarItem(posX + 2, posY, P1.cheio)) {
            cout << "P1 Pegou o item1!" << endl;
            P1.cheio = true;
        }        

        // Pegar Item Player 2
        if (pegarItem(posX2 + 2, posY2, P2.cheio)) {
            cout << "P2 Pegou o item1!" << endl;
            P2.cheio = true;
        }        

        // Entregar Item Player 1
        if (entregarItem(posX + 2, posY) && P1.cheio == true) {
            cout << "Entregou o item!" << endl;
            contItensEntregues++;
            P1.cheio = false;
        }        
        
        // Entregar Item Player 2
        if (entregarItem(posX2 + 2, posY2) && P2.cheio == true) {
            cout << "Entregou o item!" << endl;
            contItensEntregues++;
            P2.cheio = false;
        }

        // Entral no Portal Player1
        if (entrarPortal(posX + 2, posY) && contItensEntregues == 6) {
            cout << "P1 Entrou no portal!" << endl;
            P1.entrouPortal = true;
            posX = 0;
            posY = 0;
        }        
        
        // Entral no Portal Player2
        if (entrarPortal(posX2 + 2, posY2) && contItensEntregues == 6) {
            cout << "P2 Entrou no portal!" << endl;
            P2.entrouPortal = true;
            posX2 = 0;
            posY2 = 0;
        }

        if (P1.entrouPortal && P2.entrouPortal) {
            done = true;
        }

        if (redesenha) {
            DrawMap();

            al_draw_bitmap(player, posX, posY, 0);

            colisao(posX, posY);

            al_draw_bitmap(player2, posX2, posY2, 0);

            colisao(posX2, posY2);

            al_draw_bitmap(agua1, 0, 0, 0);

            al_flip_display();
            redesenha = false;
        }
    }

    // Tela de GAME OVER
    al_clear_to_color(al_map_rgb(0, 0, 0)); // Preenche a tela com preto
    ALLEGRO_FONT* font = al_create_builtin_font();
    al_draw_textf(font, al_map_rgb(255, 255, 255), SCREENWIDTH / 2, SCREENHEIGHT / 2, ALLEGRO_ALIGN_CENTER, "FIM DE JOGO");
    al_draw_textf(font, al_map_rgb(255, 255, 255), SCREENWIDTH / 2, SCREENHEIGHT / 2 + 50, ALLEGRO_ALIGN_CENTER, "Todos os itens foram entregues!");
    al_flip_display();
    al_rest(5); // Aguarda por 5 segundos antes de sair do jogo

    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);

    return 0;
}

