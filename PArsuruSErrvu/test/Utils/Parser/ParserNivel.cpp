#include "ParserNivel.h"

ParserNivel::ParserNivel()
{


}

ParserNivel::~ParserNivel()
{
	m_listaDeSprites.clear();
	m_escenario.listaDeElementos.clear();


}

bool ParserNivel::parsearDocumento(const std::string& nombreArchivoXML){

	bool exito = true;
	if (!parsearDoc(nombreArchivoXML, false))
	{
		std::stringstream ss;
		ss << "No se pudo parsear con éxito el archivo XML: " << nombreArchivoXML.c_str() << ".";
		Logger::Instance()->LOG(ss.str(), ERROR);
		ss.clear();
		ss << "Se cargará el archivo default: " << XML_NIVEL_DEFAULT_PATH << ".";
		Logger::Instance()->LOG(ss.str(), WARN);

		exito = parsearDoc(XML_NIVEL_DEFAULT_PATH, true);
		if (!exito)
		{
			//El archivo XML default también tiene errores. No se pudo parsear.
			Logger::Instance()->LOG("No se pudieron parsear ninguno de los archivos XML cliente.", ERROR);
			//cout << "No se pudieron parsear ninguno delos archivos XML nivel";
		}
	}
	cout << "Si se cargo \n";
	return exito;

}


bool ParserNivel::parsearDoc(const std::string& nombreArchivoXML, bool isDefault)
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


	extraerSprites(&doc);
	extraerVentana(&doc,0);
	extraerEscenario(&doc,0);
	return parseadoExitoso;
}

bool ParserNivel::extraerSprites(const pugi::xml_document* doc)
{
	bool exito = true;
	pugi::xml_node spritesNode = doc->child("sprites");

	for (pugi::xml_node spr = spritesNode.first_child(); spr; spr = spr.next_sibling())
	{
	   Sprite sprite;
	   std::string id = spr.child("id").first_child().value();
	   std::string path = spr.child("path").first_child().value();
	   std::string cantidad = spr.child("cantidad").first_child().value();
	   std::string ancho = spr.child("ancho").first_child().value();
	   std::string alto = spr.child("alto").first_child().value();
	   if (!validarNumero(cantidad))
			{
		   	   Logger::Instance()->LOG("Se cargo el valor cantidad del sprite por default", WARN);
				cantidad = "2";
			}
	   if (!validarNumero(ancho))
	   			{
		   	   	   Logger::Instance()->LOG("Se cargo el valor ancho del sprite por default", WARN);
	   				ancho = "11";
	   			}
	   if (!validarNumero(alto))
	  	   			{
		   	   	   	   Logger::Instance()->LOG("Se cargo el valor alto del por default", WARN);
	  	   				alto = "11";
	  	   			}
		if (!validarPath(path))
			{
				Logger::Instance()->LOG("Se cargo el path del sprite por default", WARN);
				path = "Utils/Default/sprite.jpg";
			}

	   sprite.id = id;
	   sprite.path = path;
	   sprite.cantidad = stoi(cantidad);
	   sprite.ancho = stoi(ancho) ;
	   sprite.alto = stoi(alto);
	   m_listaDeSprites.push_back(sprite);
	}
	return exito;
}

bool ParserNivel::extraerVentana(const pugi::xml_document* doc, bool isLoadingDefault)
{
	bool exito = true;
	pugi::xml_node ventanaNode = doc->child("ventana");
	std::string anchoString = ventanaNode.child("ancho").first_child().value();
	std::string altoString = ventanaNode.child("alto").first_child().value();

	if (!validarNumero(anchoString))
		{
			Logger::Instance()->LOG("Se cargo el ancho de la ventana por default", WARN);
			anchoString = "810";
		}
	if (!validarNumero(altoString))
		{
			Logger::Instance()->LOG("Se cargo el alto de la ventana por default", WARN);
			altoString = "610";
		}

	m_ventana.alto = stoi(altoString);
	m_ventana.ancho = stoi(anchoString);
	return true;


}


bool ParserNivel::extraerEscenario(const pugi::xml_document* doc, bool isLoadingDefault)
{

	bool exito = true;
	pugi::xml_node escenarioNode = doc->child("escenario");
	std::string anchoString = escenarioNode.child("ancho").first_child().value();

	if (!validarNumero(anchoString))
		{
			Logger::Instance()->LOG("Se cargo el ancho del escenario por default", WARN);
			anchoString = "110";
		}
	std::string altoString = escenarioNode.child("alto").first_child().value();
	if (!validarNumero(altoString))
		{
			Logger::Instance()->LOG("Se cargo el alto del escenario por default", WARN);
			altoString = "1100";
		}

			extraerFondo(doc,1);
			extraerElementos(doc,1);
			m_escenario.ancho = std::stoi(anchoString);
			m_escenario.alto = std::stoi(altoString);
			m_escenario.fondo = m_fondo;
		return true;


}
bool ParserNivel::extraerElementos(const pugi::xml_document* doc, bool isLoadingDefault)
{
	bool exito = true;
	pugi::xml_node elemNode = doc->child("elementos");

	for (pugi::xml_node eleme = elemNode.first_child(); eleme; eleme = eleme.next_sibling())
	{
	   Elemento elem;
	   std::string id = eleme.child("id").first_child().value();

	   elem.spriteId = id;
	   bool found;
	   std::vector<Sprite> lista =  getListaSprites();
	   for(int i=0; i < lista.size(); i++){
	      if (id == lista[i].id)
	      {
	    	  found = true;
	      }
	   }
	   if (found)
	   {
		   std::string posx = eleme.child("posicion").child("x").first_child().value();
		   std::string posy = eleme.child("posicion").child("y").first_child().value();
		   Posicion pos;
		   if (!validarNumero(posx))
		   {
			   Logger::Instance()->LOG("Se cargo la posx del elemento por default", WARN);
			   posx = "1";
		   }
		   if (!validarNumero(posy))
		   {
			   Logger::Instance()->LOG("Se cargo la posy del elemento por default", WARN);
			   posy = "1";
		   }
		   pos.x = stoi(posx);
		   pos.y = stoi(posy);
		   elem.posicion = pos;

		   m_escenario.listaDeElementos.push_back(elem);
		   return exito;
	   }
	   Logger::Instance()->LOG("No se cargo el elemento por no tener un id existente entre los sprites", ERROR);
	   return exito;
	}
}

bool ParserNivel::extraerFondo(const pugi::xml_document* doc, bool isLoadingDefault)
{
	bool exito = true;
	pugi::xml_node escenarioNode = doc->child("escenario");
	std::string anchoString = escenarioNode.child("fondo").child("ancho").first_child().value();
	std::string altoString = escenarioNode.child("fondo").child("alto").first_child().value();
	std::string spriteIdString = escenarioNode.child("fondo").child("spriteId").first_child().value();

	if(! validarNumero(anchoString))
	{
		Logger::Instance()->LOG("Se cargo el ancho del fondo por default", WARN);
		anchoString = "12";
	}
	if(! validarNumero(altoString))
	{
		Logger::Instance()->LOG("Se cargo el alto del fondo por default", WARN);
		altoString = "12";
	}

	m_fondo.ancho = std::stoi(anchoString);
	m_fondo.alto = std::stoi(altoString);
	m_fondo.spriteId = spriteIdString;

	return true;

}

bool ParserNivel::is_file_exist(std::string& fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}
bool ParserNivel::validarPath(std::string& path)
{
	return is_file_exist(path);
}

bool validarRoot(const pugi::xml_document* doc)
{


}

bool validarSprite(Sprite* sprite)
{


}

bool validarVentana(Ventana* ventana)
{


}
bool validarEscenario(Escenario *escenario)
{


}
bool ParserNivel::validarNumero(std::string& intString)
{
	if (intString.empty())
			return false;
		quitarEspacios(intString);
		for (uint i = 0 ; i < intString.length(); i++)
		{
			if (!std::isdigit(intString[i]))
				return false;
		}
	return true;
}


bool validarTipoDeDato(std::string& tipoDatoString)
{


}
