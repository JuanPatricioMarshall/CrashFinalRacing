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


bool Game::init(const char* title, int xpos, int ypos, int width, int height)
{
    // Tamaño de la ventana
    m_gameWidth = width;
    m_gameHeight = height;

    //Provisorio rompen porq blackship water island son string... pone ints (hacer mapas primero)
    m_player = new Player();
   //m_player->load(m_gameWidth/2, m_gameHeight/2, 38, 64, "blackship", 1);
   m_player->load(m_gameWidth/2, m_gameHeight/2, 38, 64, 1, 1);
   int objectID = ObjectIdGenerator::Instance()->generateId();
   m_player->setObjectID(objectID);
   listOfPlayer[objectID]= *m_player;
   printf("Player inicializado con objectID %d\n", objectID);

   m_background = new Background();
   //m_background->load(0, 0, m_gameWidth, m_gameHeight, "water")
   objectID = ObjectIdGenerator::Instance()->generateId();
   m_background->setObjectID(objectID);
   m_background->load(0, 0, m_gameWidth, m_gameHeight, 2);
   listOfGameObject[m_background->getObjectId()] = *m_background;


   m_island = new Island();
   //m_island->load(0, m_gameHeight/2, 150, 150, "island", 1);
   m_island->load(0, m_gameHeight/2, 150, 150, 3, 1);
   // en ms
   m_island->setReappearanceTime(0);
   //listOfGameObject[m_island->getObjectId()] = *m_island;
    setUpKorea();
    //tudo ben
    m_running = true;
    return true;
}

void Game::createPlayer(int textureID)
{
	Player newPlayer;
	newPlayer.load(m_gameWidth/2, m_gameHeight/2, 38, 64, textureID, 1);
	int objectID = ObjectIdGenerator::Instance()->generateId();
	newPlayer.setObjectID(objectID);
	listOfPlayer[objectID]= newPlayer;
}

void Game::render()
{
    //SDL_RenderClear(m_pRenderer);


    //Dibujar lo que haya que dibujar
 /*   m_background->draw(); //Provisorio
    m_island->draw(); //Provisorio
    m_player->draw();//Provisorio
*/
    //SDL_RenderPresent(m_pRenderer);
}
void Game::interpretarDrawMsg(DrawMessage drwMsg){

	}

void Game::update()
{
	for (std::map<int,Player>::iterator it=listOfPlayer.begin(); it != listOfPlayer.end(); ++it)
	{
		printf("objectID = %d \n", it->second.getObjectId());
	     it->second.update();
	}
	for (std::map<int,GameObject>::iterator it=listOfGameObject.begin(); it != listOfGameObject.end(); ++it)
	{
		printf("objectID = %d \n", it->second.getObjectId());
	     //it->second.update();
	}

}

void Game::handleEvents()
{
}
void Game::setUpKorea()
{

	std::string fileName = "Utils/Default/servidor.xml";


	ParserServidor* servidorParser = new ParserServidor();
	servidorParser->parsearDocumento(fileName);

	LoggerInfo loggerInfo = servidorParser->getLoggerInfo();
	Logger::Instance()->setLoglevel(loggerInfo.debugAvailable, loggerInfo.warningAvailable, loggerInfo.errorAvailable);

	int porto = servidorParser->getServidorInfo().puerto ;
	printf("Cargo puerto: %d \n",porto);
	int maxClientes = servidorParser->getServidorInfo().cantMaximaClientes;
	printf("Cargo maxClientes: %d \n",maxClientes);
	printf("Creando enlazamiento\n");
	m_server = new server(13333, 1);
	printf("Se pone a escuchar\n");
	m_server->escuchar();
	printf("Escucho 1");
	int auxi = 0;
	while(m_server->getNumClientes() < m_server->getMaxClientes())
	{
		auxi++;
		m_server->aceptar();
		printf("Acepto %d \n",auxi);
	}
	//servidor->closeAllsockets();
	//delete servidor;
	//Logger::Instance()->Close();
}


void Game::sendToAllClients(DrawMessage mensaje)
{
	m_server->sendToAll(mensaje);
}
void* Game::koreaMethod(void)
{

	std::cout << "Empece a ciclar bitches!\n";
	while (Game::Instance()->isRunning()) {

		//	m_server->leer();
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

void Game::actualizarEstado(int id, InputMessage inputMsg){
	printf("Actualizar player %d\n",inputMsg.objectID);
	listOfPlayer[inputMsg.objectID].handleInput(inputMsg);
}

void Game::clean()
{
    cout << "cleaning game\n";

    delete m_background; //Provisorio
    delete m_island; //Provisorio
    delete m_player; //Provisorio

    InputHandler::Instance()->clean();
    TextureManager::Instance()->clearTextureMap();
    listOfPlayer.clear();
    listOfGameObject.clear();

    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}
