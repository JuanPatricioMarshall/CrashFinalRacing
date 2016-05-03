/* ParserTextureManager.cpp
 *
 *  Created on: May 3, 2016
 *      Author: Juampa
 */

#include "ParserTextureManager.h"


ParserTextureManager::ParserTextureManager()
{
}

ParserTextureManager::~ParserTextureManager()
{
}

bool ParserTextureManager::parsearDocumento(const std::string& nombreArchivoXML)
{
	bool exito = true;
	if (!parsearDoc(nombreArchivoXML))
	{
		std::stringstream ss;
		ss << "No se pudo parsear el archivo XML: " << nombreArchivoXML.c_str() << ". ";
		Logger::Instance()->LOG(ss.str(), ERROR);
		ss.clear();
		ss << "Se cargará el archivo default: " << XML_SERVIDOR_DEFAULT_PATH << ".";
		Logger::Instance()->LOG(ss.str(), WARN);

		exito = parsearDoc(XML_SERVIDOR_DEFAULT_PATH);
		if (!exito)
		{
			//El archivo XML default también tiene errores. No se pudo parsear.
			Logger::Instance()->LOG("No se pudieron parsear ninguno de los archivos XML servidor.", ERROR);
		}
	}
	return exito;
}

bool ParserTextureManager::parsearDoc(const std::string& nombreArchivoXML)
{
	bool parseadoExitoso = true;;
	std::stringstream ss;

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(nombreArchivoXML.c_str());

	if (!result)
	{
		parseadoExitoso = false;
		//No se pudo abrir el archivo XML
		//LOGUEO DE ERRORES EN CASO DE QUE NO SE PUEDA CARGAR EL ARCHIVO XML
		ss << "Archivo " << nombreArchivoXML.c_str() <<  " dañado. Error Description: " << result.description() << ".";
		Logger::Instance()->LOG(ss.str(), ERROR);

		return parseadoExitoso;
	}

	if (!extraerInfo(&doc))
	{
		parseadoExitoso = false;
	}

	return parseadoExitoso;
}



bool ParserTextureManager::extraerInfo(const pugi::xml_document* doc)
{
	bool exito = true;
	pugi::xml_node textureManagerNode = doc->child("TextureInfo");
	std::string Id = textureManagerNode.child("Id").first_child().value();
	
	std::string height = textureManagerNode.child("height").first_child().value();
	std::string numFrames = textureManagerNode.child("numFrames").first_child().value();
	std::string path = textureManagerNode.child("path").first_child().value();
	std::string width = textureManagerNode.child("width").first_child().value();
	if (exito)
	{
		int ID = std::stoi(Id);
		int numFramesInt = std::stoi(numFrames);
		int widthInt = std::stoi(width); 
		int heightInt = std::stoi(height);

		m_textureInfo.id = ID;
		m_textureInfo.numFrames = numFramesInt;
		m_textureInfo.width = widthInt;

		m_textureInfo.height = heightInt;
		m_textureInfo.path = path;
	}

	return exito;
}
