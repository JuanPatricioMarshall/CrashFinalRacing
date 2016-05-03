/*
 * CodificadorMensajes.cpp
 *
 *  Created on: Apr 2, 2016
 *      Author: gonzalo
 */

#include "AlanTuring.h"

AlanTuring::AlanTuring()
{

}
AlanTuring::~AlanTuring()
{

}
/********************************************Metodos del Juego*********************************************************************/
int AlanTuring::encodeDrawMessage(DrawMessage drawMsg, char* bufferSalida)
{
	//inicializa el buffer de salida
	bzero(bufferSalida,MESSAGE_BUFFER_SIZE);

	NetworkMessage codigoEnigma;
	bzero(codigoEnigma.msg_Data, MESSAGE_DATA_SIZE);
	codigoEnigma.msg_Code[0] = 'd';
	codigoEnigma.msg_Code[1] = 'm';
	codigoEnigma.msg_Code[2] = 's';


	//copia el draw message en el buffer de network message data
	bzero(codigoEnigma.msg_Data, DRAW_MESSAGE_SIZE + 1);
	memcpy(codigoEnigma.msg_Data, &drawMsg, DRAW_MESSAGE_SIZE);

	codigoEnigma.msg_Length = DRAW_MESSAGE_SIZE + MESSAGE_LENGTH_BYTES + MESSAGE_CODE_BYTES;

	//copia el mensaje de red al buffer ingresado
	memcpy(bufferSalida, &codigoEnigma, sizeof(NetworkMessage));

	return codigoEnigma.msg_Length;
}
int AlanTuring::encodeInputMessage(InputMessage inputMsg, char* bufferSalida)
{
	//inicializa el buffer de salida
	bzero(bufferSalida, MESSAGE_BUFFER_SIZE);

	NetworkMessage codigoEnigma;
	bzero(codigoEnigma.msg_Data, MESSAGE_DATA_SIZE);
	codigoEnigma.msg_Code[0] = 'i';
	codigoEnigma.msg_Code[1] = 'm';
	codigoEnigma.msg_Code[2] = 's';


	//copia el draw message en el buffer de network message data
	bzero(codigoEnigma.msg_Data, INPUT_MESSAGE_SIZE + 1);
	memcpy(codigoEnigma.msg_Data, &inputMsg, INPUT_MESSAGE_SIZE);

	codigoEnigma.msg_Length = INPUT_MESSAGE_SIZE + MESSAGE_LENGTH_BYTES + MESSAGE_CODE_BYTES;

	//copia el mensaje de red al buffer ingresado
	memcpy(bufferSalida, &codigoEnigma, sizeof(NetworkMessage));

	return codigoEnigma.msg_Length;
}

DrawMessage AlanTuring::decodeDrawMessage (NetworkMessage netMsg)
{
	DrawMessage drawMsg;
	memcpy(&drawMsg, netMsg.msg_Data, sizeof(DataMessage));
	return drawMsg;
}
InputMessage AlanTuring::decodeInputMessage (NetworkMessage netMsg)
{
	InputMessage inputMsg;
	memcpy(&inputMsg, netMsg.msg_Data, sizeof(DataMessage));
	return inputMsg;
}
/**********************************************************************************************************************************/

int AlanTuring::encodeXMLMessage(Mensaje mensaje, char* bufferSalida)
{
	//inicializa el buffer de salida
	bzero(bufferSalida,MESSAGE_BUFFER_SIZE);

	//codifica el mensaje en a un mensaje de Red
	NetworkMessage codigoEnigma;
	fillMsgData(&codigoEnigma, mensaje);
	int msgLength = codigoEnigma.msg_Length;
	//copia el mensaje de red al buffer de salida
	memcpy(bufferSalida, &codigoEnigma, sizeof(NetworkMessage));

	return msgLength;
}

int AlanTuring::encodeNetworkMessage(NetworkMessage netMsg, char* bufferSalida )
{
	bzero(bufferSalida,MESSAGE_BUFFER_SIZE);
	memcpy(bufferSalida, &netMsg, sizeof(NetworkMessage));
	int length = (int)netMsg.msg_Length;
	return length;
}

NetworkMessage AlanTuring::decode(char* codigoEnigma)
{
	NetworkMessage netMsg;
	memcpy(&netMsg, codigoEnigma, sizeof(NetworkMessage));
	return netMsg;
}

/*
 * METODOS DE DECODIFICACION
 */
unsigned short AlanTuring::decodeLength(char* codigoEnigma)
{
	unsigned short messageLength;
	memcpy(&messageLength, codigoEnigma, sizeof(messageLength));
	return messageLength;
}

DataMessage AlanTuring::decodeMessage (NetworkMessage netMsg)
{
	DataMessage dataMsg;
	memcpy(&dataMsg, netMsg.msg_Data, sizeof(DataMessage));

	std::string msgID(dataMsg.msg_ID);

	int pos = msgID.find("$");
	string id(msgID.substr(0, pos));

	msgID.erase(0, pos + 1);

	string valor(msgID);

	memcpy(dataMsg.msg_ID, id.c_str(), MESSAGE_ID_BYTES_LIMIT);
	memcpy(dataMsg.msg_value, valor.c_str(), MESSAGE_VALUE_SIZE);

	return dataMsg;
}


/*
 * 	METODOS DE CODIFICACION
 */
void AlanTuring::fillMsgData(NetworkMessage* netMsg, const Mensaje mensaje)
{
	bzero(netMsg->msg_Data,MESSAGE_DATA_SIZE);

	if ((strcmp(mensaje.tipo.c_str(), "int")) == 0)
	{
		netMsg->msg_Code[0] = 'i';
		netMsg->msg_Code[1] = 'n';
		netMsg->msg_Code[2] = 't';
		encodeMessage(netMsg, mensaje);
	}
	if ((strcmp(mensaje.tipo.c_str(), "char")) == 0)
	{
		netMsg->msg_Code[0] = 'c';
		netMsg->msg_Code[1] = 'h';
		netMsg->msg_Code[2] = 'r';
		encodeMessage(netMsg, mensaje);
	}
	if ((strcmp(mensaje.tipo.c_str(), "double")) == 0)
	{
		netMsg->msg_Code[0] = 'd';
		netMsg->msg_Code[1] = 'b';
		netMsg->msg_Code[2] = 'l';
		encodeMessage(netMsg, mensaje);
	}
	if ((strcmp(mensaje.tipo.c_str(), "string")) == 0)
	{
		netMsg->msg_Code[0] = 's';
		netMsg->msg_Code[1] = 't';
		netMsg->msg_Code[2] = 'r';
		encodeMessage(netMsg, mensaje);
	}
	if ((strcmp(mensaje.tipo.c_str(), "exit")) == 0)
	{
		netMsg->msg_Code[0] = 'e';
		netMsg->msg_Code[1] = 'x';
		netMsg->msg_Code[2] = 't';
		encodeMessage(netMsg, mensaje);
	}
	if ((strcmp(mensaje.tipo.c_str(), "connected")) == 0)
	{
		netMsg->msg_Code[0] = 'c';
		netMsg->msg_Code[1] = 'n';
		netMsg->msg_Code[2] = 't';
		encodeMessage(netMsg, mensaje);
	}
	if ((strcmp(mensaje.tipo.c_str(), "serverfull")) == 0)
	{
		netMsg->msg_Code[0] = 'f';
		netMsg->msg_Code[1] = 'u';
		netMsg->msg_Code[2] = 'l';
		encodeMessage(netMsg, mensaje);
	}
	if ((strcmp(mensaje.tipo.c_str(), "timeoutACK")) == 0)
	{
		netMsg->msg_Code[0] = 't';
		netMsg->msg_Code[1] = 'm';
		netMsg->msg_Code[2] = 'o';
		encodeMessage(netMsg, mensaje);
	}
}

void AlanTuring::encodeMessage(NetworkMessage* netMsg, const Mensaje mensaje)
{
	DataMessage dataMsg;

	dataMsg.msg_status = '-';
	string id(mensaje.id.c_str());
	id.append("$");

	//copia el ID extraido del xml en el struct DataMessage
	bzero(dataMsg.msg_ID,MESSAGE_ID_BYTES_LIMIT);
	memcpy(dataMsg.msg_ID, id.c_str(), MESSAGE_ID_BYTES_LIMIT);

	//copia el valor string al buffer de DataMeessage
	bzero(dataMsg.msg_value, MESSAGE_VALUE_SIZE);
	if (mensaje.id.length() < MESSAGE_ID_BYTES_LIMIT)
	{
		memcpy(dataMsg.msg_ID + id.length(), mensaje.valor.c_str(), MESSAGE_ID_BYTES_LIMIT - id.length());
		memcpy(dataMsg.msg_value, mensaje.valor.c_str() + MESSAGE_ID_BYTES_LIMIT - id.length(), MESSAGE_VALUE_SIZE);
	}
	else
		memcpy(dataMsg.msg_value, mensaje.valor.c_str(), MESSAGE_VALUE_SIZE);

	//network message length
	netMsg->msg_Length = MESSAGE_LENGTH_BYTES + MESSAGE_CODE_BYTES + 1 +id.length() + mensaje.valor.length();

	//network message data
	bzero(netMsg->msg_Data, MESSAGE_DATA_SIZE);
	memcpy(netMsg->msg_Data, &dataMsg, MESSAGE_DATA_SIZE);

}

void AlanTuring::changeDataValue(NetworkMessage* networkMessage, std::string& newValue)
{
	DataMessage dataMessage =  decodeMessage(*networkMessage);
	//memcpy(&dataMessage, networkMessage->msg_Data, sizeof(DataMessage));

	string id(dataMessage.msg_ID);
	id.append("$");

	bzero(dataMessage.msg_ID,MESSAGE_ID_BYTES_LIMIT);
	memcpy(dataMessage.msg_ID, id.c_str(), MESSAGE_ID_BYTES_LIMIT);

	bzero(dataMessage.msg_value, MESSAGE_VALUE_SIZE);
	if (id.length() < MESSAGE_ID_BYTES_LIMIT)
	{
		memcpy(dataMessage.msg_ID + id.length(), newValue.c_str(), MESSAGE_ID_BYTES_LIMIT - id.length());
		memcpy(dataMessage.msg_value, newValue.c_str() + MESSAGE_ID_BYTES_LIMIT - id.length(), MESSAGE_VALUE_SIZE);
	}
	else
		memcpy(dataMessage.msg_value, newValue.c_str(), MESSAGE_VALUE_SIZE);

	networkMessage->msg_Length = MESSAGE_LENGTH_BYTES + MESSAGE_CODE_BYTES + 1 +id.length() + newValue.length();

	//network message data
	bzero(networkMessage->msg_Data, MESSAGE_DATA_SIZE);
	memcpy(networkMessage->msg_Data, &dataMessage, MESSAGE_DATA_SIZE);
}


void AlanTuring::setNetworkMessageStatus(NetworkMessage* networkMessage, char statusCode)
{
	DataMessage dataMessage;
	memcpy(&dataMessage, networkMessage->msg_Data, sizeof(DataMessage));
	dataMessage.msg_status = statusCode;
	bzero(networkMessage->msg_Data, MESSAGE_DATA_SIZE);
	memcpy(networkMessage->msg_Data, &dataMessage, sizeof(dataMessage));

}

/*char* AlanTuring::setNetworkMessageStatus(NetworkMessage* networkMessage, char statusCode)
{
	char bufferSalida[MESSAGE_BUFFER_SIZE];
	bzero(bufferSalida, MESSAGE_BUFFER_SIZE);

	DataMessage dataMessage = decodeMessage(networkMessage->msg_Data);
	dataMessage.msg_status = statusCode;

	bzero(networkMessage->msg_Data, MESSAGE_DATA_SIZE);
	memcpy(networkMessage->msg_Data, &dataMessage, sizeof(dataMessage));

	//copia el mensaje de red al buffer de salida
	memcpy(bufferSalida, networkMessage, sizeof(NetworkMessage));

	return bufferSalida;
}*/

/*intMessage AlanTuring::decodeIntMessage(char* datosCodigoEnigma)
{
	intMessage intMsg;
	memcpy(&intMsg, datosCodigoEnigma, sizeof(intMessage));
	return intMsg;
}

charMessage AlanTuring::decodeCharMessage(char* datosCodigoEnigma)
{
	charMessage charMsg;
	memcpy(&charMsg, datosCodigoEnigma, sizeof(charMessage));
	return charMsg;
}

doubleMessage AlanTuring::decodeDoubleMessage(char* datosCodigoEnigma)
{
	doubleMessage doubleMsg;
	memcpy(&doubleMsg, datosCodigoEnigma, sizeof(doubleMessage));
	return doubleMsg;
}

stringMessage AlanTuring::decodeStringMessage(char* datosCodigoEnigma)
{
	stringMessage stringMsg;
	memcpy(&stringMsg, datosCodigoEnigma, sizeof(stringMessage));
	return stringMsg;
}*/

/*void AlanTuring::encodeIntMessage(NetworkMessage* netMsg, const Mensaje mensaje)
{
	intMessage intMsg;
	//network message code
	netMsg->msg_Code[0] = 'i';
	netMsg->msg_Code[1] = 'n';
	netMsg->msg_Code[2] = 't';

	//copia el ID extraido del xml en un buffer y luego al struct intMessage
	char buffer[MESSAGE_ID_BYTES_LIMIT];
	bzero(buffer,MESSAGE_ID_BYTES_LIMIT);
	strncpy(buffer, mensaje.id.c_str(), sizeof(buffer));
	//copia id al msg_ID
	strncpy(intMsg.msg_ID, buffer, sizeof(buffer));

	intMsg.msg_value = std::stoi (mensaje.valor);

	//network message length
	netMsg->msg_Length = MESSAGE_LENGTH_BYTES + MESSAGE_CODE_BYTES + (unsigned short)sizeof(intMessage);

	//network message data
	char dataBuffer[MESSAGE_DATA_SIZE];
	bzero(dataBuffer,MESSAGE_DATA_SIZE);
	memcpy(netMsg->msg_Data, &intMsg, sizeof(intMessage));
}

void AlanTuring::encodeCharMessage(NetworkMessage* netMsg, const Mensaje mensaje)
{
	charMessage charMsg;
	//network message code
	netMsg->msg_Code[0] = 'c';
	netMsg->msg_Code[1] = 'h';
	netMsg->msg_Code[2] = 'r';

	//copia el ID extraido del xml en un buffer y luego al struct intMessage
	char buffer[MESSAGE_ID_BYTES_LIMIT];
	bzero(buffer,MESSAGE_ID_BYTES_LIMIT);
	strncpy(buffer, mensaje.id.c_str(), sizeof(buffer));
	//copia id al msg_ID
	strncpy(charMsg.msg_ID, buffer, sizeof(buffer));

	if (mensaje.valor.length() > 1)
		Logger::Instance()->LOG("Mensaje: Mensaje del tipo char contiene multiplos caracteres. Se enviará solo el primero.", WARN);
	charMsg.msg_value = mensaje.valor.at(0);;

	//network message length
	netMsg->msg_Length = MESSAGE_LENGTH_BYTES + MESSAGE_CODE_BYTES + (unsigned short)sizeof(charMessage);

	//network message data
	char dataBuffer[MESSAGE_DATA_SIZE];
	bzero(dataBuffer,MESSAGE_DATA_SIZE);
	memcpy(netMsg->msg_Data, &charMsg, sizeof(charMessage));
}

void AlanTuring::encodeDoubleMessage(NetworkMessage* netMsg, const Mensaje mensaje)
{
	doubleMessage doubleMsg;
	//network message code
	netMsg->msg_Code[0] = 'd';
	netMsg->msg_Code[1] = 'b';
	netMsg->msg_Code[2] = 'l';

	//copia el ID extraido del xml en un buffer y luego al struct intMessage
	char buffer[MESSAGE_ID_BYTES_LIMIT];
	bzero(buffer,MESSAGE_ID_BYTES_LIMIT);
	strncpy(buffer, mensaje.id.c_str(), sizeof(buffer));
	//copia id al msg_ID
	strncpy(doubleMsg.msg_ID, buffer, sizeof(buffer));

	doubleMsg.msg_value = std::stod (mensaje.valor);

	//network message length
	netMsg->msg_Length = MESSAGE_LENGTH_BYTES + MESSAGE_CODE_BYTES + (unsigned short)sizeof(doubleMessage);

	//network message data
	char dataBuffer[MESSAGE_DATA_SIZE];
	bzero(dataBuffer,MESSAGE_DATA_SIZE);
	memcpy(netMsg->msg_Data, &doubleMsg, sizeof(doubleMessage));
}

void AlanTuring::encodeStringMessage(NetworkMessage* netMsg, const Mensaje mensaje)
{
	stringMessage stringMsg;
	//network message code
	netMsg->msg_Code[0] = 's';
	netMsg->msg_Code[1] = 't';
	netMsg->msg_Code[2] = 'r';

	//copia el ID extraido del xml en un buffer y luego al struct intMessage
	char buffer[MESSAGE_ID_BYTES_LIMIT];
	bzero(buffer,MESSAGE_ID_BYTES_LIMIT);
	strncpy(buffer, mensaje.id.c_str(), sizeof(buffer));
	//copia id al msg_ID
	strncpy(stringMsg.msg_ID, buffer, sizeof(buffer));

	stringMsg.msg_value = mensaje.valor.c_str();

	//network message length
	netMsg->msg_Length = MESSAGE_LENGTH_BYTES + MESSAGE_CODE_BYTES + (unsigned short)sizeof(stringMessage);

	//network message data
	char dataBuffer[MESSAGE_DATA_SIZE];
	bzero(dataBuffer,MESSAGE_DATA_SIZE);
	memcpy(netMsg->msg_Data, &stringMsg, sizeof(stringMessage));
}*/
