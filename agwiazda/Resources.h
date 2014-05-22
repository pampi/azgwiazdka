#ifndef RESOURCES_H
#define RESOURCES_H

#include "headers.h"

class Resource : public TSingleton<Resource>
{
public:
	enum TEXTURES {
		NO_TEXTURE,
	};
	enum SPRITES {
		NO_SPRITE,
	};

	Resource();
	~Resource();
	sf::Texture &getTexture(TEXTURES t);
	sf::Sprite &getSprite(SPRITES s);
private:
	map<TEXTURES, sf::Texture*> m_textures;
	map<SPRITES, sf::Sprite *> m_sprites;
};

#endif