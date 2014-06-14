#ifndef RESOURCES_H
#define RESOURCES_H

#include "headers.h"

class Resource : public TSingleton<Resource>
{
public:
	enum TEXTURES {
		NO_TEXTURE,
		TEX_PATH,
		TEX_COLLIDER,
		TEX_START,
		TEX_FINISH,
		TEX_VISITED,
	};
	enum SPRITES {
		NO_SPRITE,
		SPR_PATH,
		SPR_COLLIDER,
		SPR_START,
		SPR_FINISH,
		SPR_VISITED,
	};

	Resource();
	~Resource();
	sf::Texture &getTexture(TEXTURES t);
	sf::Sprite &getSprite(SPRITES s);
	sf::Font &getFont();
private:
	map<TEXTURES, sf::Texture*> m_textures;
	map<SPRITES, sf::Sprite *> m_sprites;
	sf::Font m_font;
};

#endif