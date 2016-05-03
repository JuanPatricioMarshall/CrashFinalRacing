#include "TextureManager.h"

TextureManager* TextureManager::s_pInstance = 0;

bool TextureManager::load(std::string fileName, int id, SDL_Renderer* renderer)
{


    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

    if(pTempSurface == 0)
    {
		std::cout << IMG_GetError();
        return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(renderer, pTempSurface);

    SDL_FreeSurface(pTempSurface);

    if(pTexture != 0)
    {
        m_textureMap[id] = pTexture;
        return true;
    }

    return false;
}
TextureInfo TextureManager::getTextureInfo(int textureId){
	return m_textureMapInfo[textureId];
}
void TextureManager::init(){

	TextureInfo hola;
	hola.height = 38;
	hola.numFrames = 1;
	hola.path =	"Assets/Sprites/BlackShip.png";
	hola.width =64 ;
	m_textureMapInfo[1]=hola;

	hola.height = 600;
	hola.numFrames = 1;
	hola.path =	"Assets/Sprites/island.jpg";
	hola.width = 800 ;
	m_textureMapInfo[3]=hola;

	hola.height = 150;
	hola.numFrames = 1;
	hola.path =	"Assets/Sprites/water.jpg";
	hola.width = 150 ;
	m_textureMapInfo[2]=hola;
}
void TextureManager::draw(int id, int x, int y, int width, int height, double angle, SDL_Renderer* renderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(renderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::drawFrame(int id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer, double angle, int alpha, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = width * currentFrame;
    srcRect.y = height * currentRow;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::clearTextureMap()
{
    m_textureMap.clear();
}

void TextureManager::clearFromTextureMap(int id)
{
    m_textureMap.erase(id);
}
