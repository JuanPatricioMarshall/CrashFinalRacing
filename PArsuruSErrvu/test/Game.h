#ifndef GAME_H_
#define GAME_H_


#include "Server/server.h"
#include "Utils/Parser/ParserServidor.h"
#include "Background/Island.h"
#include "Background/Background.h"
#include "Singletons/InputHandler.h"
#include "Singletons/TextureManager.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <sstream>
#include "Player.h";
#include "DrawObject.h"
#include <map>
using namespace std;
class Island;
class Background;
class server;
class Player;



class Game
{
public:

    static Game* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new Game();
            return s_pInstance;
        }
        return s_pInstance;
    }


    bool init(const char* title, int xpos, int ypos, int width, int height);

    //Funciones generales del ciclo de jueo
    void render();
    void update();
    void handleEvents();
    void clean();

    void createPlayer(int id);
    void removePlayer(int id);
    void setUpKorea();
    void conectToKorea();
    void sendToAllClients(DrawMessage mensaje);
   	void* koreaMethod(void);
   	void readFromKorea();
   	void interpretarDrawMsg(DrawMessage drwMsg);
   	void actualizarEstado(int id,InputMessage dataMsg);


    SDL_Renderer* getRenderer() const { return m_pRenderer; }
    SDL_Window* getWindow() const { return m_pWindow; }

    bool isRunning() { return m_running; }

    void quit() { m_running = false; }

    //Alto y Ancho de la ventana de juego
    int getGameWidth() const { return m_gameWidth; }
    int getGameHeight() const { return m_gameHeight; }
    pthread_t listenThread;
    float getScrollSpeed() { return m_scrollSpeed; }
    static void *thread_method(void *context);

private:

    std::map<int,Player> listOfPlayer;
    std::map<int,GameObject> listOfGameObject;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    //Provisorio
    Player* m_player;
    Background* m_background;
    Island* m_island;
    server* m_server;
    bool m_running;

    static Game* s_pInstance;

    int m_gameWidth;
    int m_gameHeight;
    float m_scrollSpeed;

    Game();
    ~Game();
    Game(const Game&);
	Game& operator=(const Game&);
};


#endif /* GAME_H_ */
