/*
 * tiposDefinidos.h
 *
 *  Created on: Mar 23, 2016
 *      Author: gonzalo
 */

#ifndef UTILS_TIPOSDEFINIDOS_H_
#define UTILS_TIPOSDEFINIDOS_H_

#define MESSAGE_BUFFER_SIZE 256
#define MESSAGE_ID_BYTES_LIMIT 25
#define MESSAGE_LENGTH_BYTES 4
#define MESSAGE_CODE_BYTES 3
#define MESSAGE_DATA_SIZE (MESSAGE_BUFFER_SIZE - MESSAGE_LENGTH_BYTES - MESSAGE_CODE_BYTES)
#define MESSAGE_VALUE_SIZE (MESSAGE_DATA_SIZE - MESSAGE_ID_BYTES_LIMIT - 1)

#define DRAW_MESSAGE_SIZE 24
#define INPUT_MESSAGE_SIZE 24
#define CONNECTED_MESSAGE_SIZE 8

#define BACKGROUND 1
#define MIDDLEGROUND 10
#define FOREGROUND 20

#include <string>

// TIPOS RELACIONADOS A ARCHIVOS XML

struct LoggerInfo
{
	bool debugAvailable;
	bool warningAvailable;
	bool errorAvailable;
};

struct Servidor{
	int cantMaximaClientes;
	int puerto;
};

struct Conexion{
	std::string ip;
	int puerto;
};

struct Mensaje{
	std::string id;
	std::string tipo;
	std::string valor;
};

//TIPOS DE DATOS RELACIONADOS CON MENSAJES DE RED

struct NetworkMessage
{
	int msg_Length;
	char msg_Code[MESSAGE_CODE_BYTES];
	char msg_Data[MESSAGE_DATA_SIZE];
};

struct ConnectedMessage
{
	int objectID;
	int textureID;
};

struct DrawMessage
{
	bool connectionStatus;
	bool alive;
	bool hasSound;
	bool otroBool;
	int objectID;
	int textureID;
	short soundID;
	short layer;
	short posX;
	short posY;
	short row;
	short column;
};

struct InputMessage
{
	int objectID;
	short buttonUp;
	short buttonDown;
	short buttonRight;
	short buttonLeft;
	short buttonShoot;
	short buttonReserved;//2 bytes reserved for future
	short buttonShootPower;
	short buttonXpecialCombo;
	short buttonCompressionSistem;
	short actionID;
};


struct DataMessage
{
	char msg_status;
	char msg_ID[MESSAGE_ID_BYTES_LIMIT];
	char msg_value[MESSAGE_VALUE_SIZE];
};

struct TextureInfo
{
	std::string path;
	int width;
	int height;
	int numFrames;

};

/*struct intMessage
{
	char msg_ID[MESSAGE_ID_BYTES_LIMIT];
	int msg_value;
};
struct charMessage
{
	char msg_ID[MESSAGE_ID_BYTES_LIMIT];
	char msg_value;
};
struct doubleMessage
{
	char msg_ID[MESSAGE_ID_BYTES_LIMIT];
	double msg_value;
};
struct stringMessage
{
	char msg_ID[MESSAGE_ID_BYTES_LIMIT];
	std::string msg_value;
};*/

#endif /* UTILS_TIPOSDEFINIDOS_H_ */

