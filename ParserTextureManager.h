/*
 * TextureManager.h
 *
 *  Created on: May 3, 2016
 *      Author: juampa_94
 */

#ifndef PARSERTEXTUREMANAGER_H_
#define PARSERTEXTUREMANAGER_H_

#define XML_SERVIDOR_DEFAULT_PATH "Utils/Default/TextureManager.xml"

#include "Parser.h"
#include "../Logger.h"
#include "../TiposDefinidos.h"
#include "../pugixml/pugixml.hpp"
#include <string>
#include <sstream>

using namespace pugi;

class ParserTextureManager: public Parser
{
	//Parsea el xml del TextureInfo
	//En caso de que el archivo esté dañado, utiliza un archivo xml default para cargar los datos.

public:

	//Obtiene los datos del documento pasado por parámetro
	bool parsearDocumento(const std::string& nombreArchivoXML);

	ParserTextureManager();
	~ParserTextureManager();

	//GETTERS
	const Texture getTextureInfo() const {
		return m_textureInfo;
	}

private:

	Texture m_textureInfo;

	bool parsearDoc(const std::string& nombreArchivoXML);
	bool extraerInfo(const pugi::xml_document* doc);


};



#endif /* TEXTUREMANAGER_H_ */
