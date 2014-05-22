#include "headers.h"

Resource::Resource()
{
	//TO DO
}

Resource::~Resource()
{
	//TO DO
}

sf::Texture &Resource::getTexture(TEXTURES t)
{
	if (m_textures.find(t) == m_textures.end())
		return (*m_textures[NO_TEXTURE]);
	return (*m_textures[t]);
}

sf::Sprite &Resource::getSprite(SPRITES s)
{
	if (m_sprites.find(s) == m_sprites.end())
		return (*m_sprites[NO_SPRITE]);
	return (*m_sprites[s]);
}