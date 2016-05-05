#include "Game.h"

Game* Game::s_pInstance = 0;

Game::Game():
m_pWindow(0),
m_pRenderer(0),
m_running(false),
m_scrollSpeed(0.8)
{

}

Game::~Game()
{
    // we must clean up after ourselves to prevent memory leaks
    m_pRenderer= 0;
    m_pWindow = 0;
}


bool Game::init(const char* title, int xpos, int ypos, int width, int height, int SDL_WINDOW_flag)
{
    // Tamaño de la ventana
    m_gameWidth = width;
    m_gameHeight = height;

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        cout << "SDL init success\n";

        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_flag);

        if(m_pWindow != 0)
        {
            cout << "window creation success\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_SOFTWARE);

            if(m_pRenderer != 0)
            {
                cout << "renderer creation success\n";
                SDL_SetRenderDrawColor(m_pRenderer, 0,0,0,255);
            }
            else
            {
                cout << "renderer init fail\n";
                return false;
            }
        }
        else
        {
            cout << "window init fail\n";
            return false;
        }
    }
    else
    {
        cout << "SDL init fail\n";
        return false;
    }


    //Provisorio rompen porq blackship water island son string... pone ints (hacer mapas primero)
    TextureManager::Instance()-> init();
    TextureManager::Instance()->load("Assets/Sprites/BlackShip.png", 1, Game::Instance()->getRenderer());
   // m_player->load(m_gameWidth/2, m_gameHeight/2, 38, 64, "blackship", 1);

    /*  m_background = new Background();
    m_background->load(0, 0, m_gameWidth, m_gameHeight, "water");

    m_island = new Island();
    m_island->load(0, m_gameHeight/2, 150, 150, "island", 1);
    // en ms
    m_island->setReappearanceTime(0);
*/
    m_player = new Player(true);

    if (!setUpKorea())
    	return false;

    //tudo ben
    m_running = true;
    return true;
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);

    for (std::map<int,DrawObject*>::iterator it=listObjects.begin(); it!=listObjects.end(); ++it)
    {
         it->second->draw();
    }

    //Dibujar lo que haya que dibujar
 /*   m_background->draw(); //Provisorio
    m_island->draw(); //Provisorio
    m_player->draw();//Provisorio
*/
    SDL_RenderPresent(m_pRenderer);
}
void Game::interpretarDrawMsg(DrawMessage drwMsg){
	/*printf("interpretando draw message del objeto %d\n",drwMsg.objectID);
	printf("texture ID: %d \n",drwMsg.textureID);
	printf("Pos X: %d \n",drwMsg.posX);
	printf("Pos Y: %d \n",drwMsg.posY);*/

	if ( listObjects.find(drwMsg.objectID) == listObjects.end() )
	{
		printf("Creando nuevo objeto con objectID: %d\n", drwMsg.objectID);
		DrawObject* newObject = new DrawObject();

		newObject->setObjectID(drwMsg.objectID);
		newObject->load(static_cast<int>(drwMsg.posX),static_cast<int>(drwMsg.posY),drwMsg.textureID);
		newObject->setCurrentRow(static_cast<int>(drwMsg.row));
		newObject->setCurrentFrame(static_cast<int>(drwMsg.column));

		listObjects[drwMsg.objectID] = newObject;
		//PARA BORRAR listObjects.erase(id);
	}else
	{
		listObjects[drwMsg.objectID]->setCurrentRow(static_cast<int>(drwMsg.row));
		listObjects[drwMsg.objectID]->setCurrentFrame(static_cast<int>(drwMsg.column));
		listObjects[drwMsg.objectID]->setPosition(Vector2D(drwMsg.posX,drwMsg.posY));
	}

}

void Game::update()
{
	/*m_background->update(); //Provisorio
	m_island->update(); //Provisorio
	m_player->update(); // Provisorio*/
}

void Game::handleEvents()
{
	InputHandler::Instance()->update();
	//Pseudo controler
	m_player->handleInput();
}
bool Game::setUpKorea()
{
		std::string	fileName = "Utils/Default/cliente.xml";

		ParserCliente* parsersito = new ParserCliente();
	    parsersito->parsearDocumento(fileName);

		LoggerInfo loggerInfo = parsersito->getLoggerInfo();
		Logger::Instance()->setLoglevel(loggerInfo.debugAvailable, loggerInfo.warningAvailable, loggerInfo.errorAvailable);

	    string ip = parsersito->getConexionInfo().ip;
	    int porto = parsersito->getConexionInfo().puerto;
	    std::vector<Mensaje> listaDeMensajes = parsersito->getListaMensajes() ;

	    m_client = new cliente(3,ip,porto, listaDeMensajes);

	    if (!conectToKorea())
	    	return false;

	    return true;

}

void Game::createPlayer(int objectID, int textureID)
{
	//m_player = new Player();
	m_player->setObjectID(objectID);
}

bool Game::conectToKorea()
{
	if (!m_client->conectar())
	{
		printf("No se pudo establecer conexión con el servidor.\n");
		return false;

	}
	else
	{
		readFromKorea();
	}
	return true;
}


void Game::sendToKorea(InputMessage mensaje)
{
	m_client->sendInputMsg(mensaje);
}
void* Game::koreaMethod(void)
{
	std::cout << "Empece a ciclar bitches!\n";
	while (Game::Instance()->isRunning()) {
			m_client->leer();
	}
	 pthread_exit(NULL);
}
void *Game::thread_method(void *context)
{
	return ((Game *)context)->koreaMethod();
}
void Game::readFromKorea()
{
	pthread_create(&listenThread, NULL, &Game::thread_method, (void*)this);

}
void Game::clean()
{
    cout << "cleaning game\n";

    for (std::map<int,DrawObject*>::iterator it=listObjects.begin(); it!=listObjects.end(); ++it)
    {
    	it->second->clean();
		delete it->second;
    }
   /* delete m_background; //Provisorio
    delete m_island; //Provisorio
    delete m_player; //Provisorio*/


    InputHandler::Instance()->clean();
    TextureManager::Instance()->clearTextureMap();
    listObjects.clear();

    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}
