#ifndef SERVER_H
#define SERVER_H

#include "ListaInteligente.h"
#include "AlanTuring.h"
#include "multiqueue.h"
#include "../Utils/Timer.h"
#include "MessageFactory.h"
#include "../Utils/StringHelper.h"
#include "../Utils/Logger.h"


#include <stdio.h>
#include <queue>
#include <stdlib.h>
#include <pthread.h>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory>


#define TIMEOUT_SECONDS 10
#define TIMEOUT_MICROSECONDS 0
#include "../Game.h"
class server
{
    public:
        server(int port,int maxC);
        void escuchar();
        void aceptar();
        void escribir(int id);
        bool leer(int id);
        void closeAllsockets();
        const int getMaxClientes();
        const int getNumClientes();
        void sendToAll(DrawMessage msg);
        void sendDrawMsg(int socketReceptor, DrawMessage msg);
        void sendConnectedMsg(int socketReceptor, ConnectedMessage msg);
        bool isRunning();
        ~server();

        //METODOS LOCOS
         void *procesar(void);
         void *postProcesamiento(void);
         static void *mati_method(void *context);//ES LO UNICO QUE PUEDE TENER GUION BAJO POR LO PODEROSO QUE ES
         static void *mati_method2(void *context);//ESTE ES AUN MAS PODEROSO
         static void *mati_method3(void *context);


    private:

        const int MAX_CLIENTES;
        AlanTuring* m_alanTuring;
        multiqueue m_queue;
        std::vector<multiqueue> m_queuePost;
        bool m_svRunning;
        int m_clientNum;
        ListaInteligente<int> m_listaDeClientes;
        ListaInteligente<Timer> m_listaTimeOuts;

        std::vector<pthread_t> m_clientThreads;
        std::vector<pthread_t> m_clientResponseThreads;

        int m_lastID;
        pthread_mutex_t  m_mutex;
        pthread_cond_t   m_condv;

        int sockfd, newsockfd, portno;

        char buffer[256];
        struct sockaddr_in serv_addr, cli_addr;
        pthread_t threadDeProcesos;

        bool crearCliente (int clientSocket);
        void checkTimeOuts();
        bool lecturaExitosa(int bytesLeidos, int clientID);
        void closeSocket(int id);
        void reducirNumeroClientes();
        void aumentarNumeroClientes();
        void startThread();
        void *newDialog(void);
        bool procesarMensaje(ServerMessage* serverMsg);
        void error(const char *msg);
        void sendMsg(int socketReceptor, Mensaje msg);
       // void setTimeOut(int socketID);

        void agregarTimeOutTimer(int clientPosition);
        void removeTimeOutTimer(int clientPosition);
};

#endif // SERVER_H
