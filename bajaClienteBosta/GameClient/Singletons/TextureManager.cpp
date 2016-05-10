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

	hola.width =38;
	hola.height = 64;
	hola.numFrames = 1;
	hola.path =	"Assets/Sprites/BlackShip.png";
	m_textureMapInfo[1]=hola;


	hola.width =61;
	hola.height = 68;
	hola.numFrames = 1;
	hola.path =	"Assets/Sprites/redfighter.png";
	m_textureMapInfo[0]=hola;

	hola.height = 150;
	hola.numFrames = 1;
	hola.path =	"Assets/Sprites/island.jpg";
	hola.width = 150;
	m_textureMapInfo[3]=hola;

	hola.width = 800;
	hola.height = 600;
	hola.numFrames = 1;
	hola.path =	"Assets/Sprites/water.jpg";
	m_textureMapInfo[2]=hola;

	hola.width = 9;
	hola.height = 54;
	hola.numFrames = 1;
	hola.path =	"Assets/Sprites/laserBlue01.png";
	m_textureMapInfo[11]=hola;



	hola.width = 32;
	hola.height = 32;
	hola.numFrames = 1;
	hola.path =	"Assets/Sprites/bullet.png";
	m_textureMapInfo[10]=hola;
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

void TextureManager::changeTextureColor(int textureID, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(m_textureMap[textureID], r, g, b);
}

void TextureManager::clearTextureMap()
{
    m_textureMap.clear();
}

void TextureManager::clearFromTextureMap(int id)
{
    m_textureMap.erase(id);
}
