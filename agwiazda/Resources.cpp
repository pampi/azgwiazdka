#include "headers.h"

Resource::Resource()
{
	sf::Sprite *sprite = nullptr;
	sf::Texture *texture = new sf::Texture();
	puts("Creating Resource instance!");

	if (texture->loadFromFile("blank.png"))
	{
		m_textures[NO_TEXTURE] = texture;
		sprite = new sf::Sprite();
		sprite->setTexture(*texture);
		m_sprites[NO_SPRITE] = sprite;
		texture = new sf::Texture();
	}
	else puts("Could not load texture blank.png!!!");

	if (texture->loadFromFile("path.png"))
	{
		m_textures[TEX_PATH] = texture;
		sprite = new sf::Sprite();
		sprite->setTexture(*texture);
		m_sprites[SPR_PATH] = sprite;
		texture = new sf::Texture();
	}
	else puts("Could not load texture path.png!!!");

	if (texture->loadFromFile("collider.png"))
	{
		m_textures[TEX_COLLIDER] = texture;
		sprite = new sf::Sprite();
		sprite->setTexture(*texture);
		m_sprites[SPR_COLLIDER] = sprite;
		texture = new sf::Texture();
	}
	else puts("Could not load texture collider.png!!!");

	if (texture->loadFromFile("finish.png"))
	{
		m_textures[TEX_FINISH] = texture;
		sprite = new sf::Sprite();
		sprite->setTexture(*texture);
		m_sprites[SPR_FINISH] = sprite;
		texture = new sf::Texture();
	}
	else puts("Could not load texture finish.png!!!");

	if (texture->loadFromFile("start.png"))
	{
		m_textures[TEX_START] = texture;
		sprite = new sf::Sprite();
		sprite->setTexture(*texture);
		m_sprites[SPR_START] = sprite;
		texture = new sf::Texture();
	}
	else puts("Could not load texture start.png!!!");

	if (texture->loadFromFile("visited.png"))
	{
		m_textures[TEX_VISITED] = texture;
		sprite = new sf::Sprite();
		sprite->setTexture(*texture);
		m_sprites[SPR_VISITED] = sprite;
		texture = new sf::Texture();
	}
	else puts("Could not load texture visited.png!!!");

	delete texture;


	if (!m_font.loadFromFile("NinePin.ttf"))
	{
		printf("Font not loaded\n");
	}
}

Resource::~Resource()
{
	for (map<SPRITES, sf::Sprite *>::iterator i = m_sprites.begin(); i != m_sprites.end(); ++i)
	{
		delete i->second;
	}

	for (map<TEXTURES, sf::Texture*>::iterator i = m_textures.begin(); i != m_textures.end(); ++i)
	{
		delete i->second;
	}

	m_sprites.clear();
	m_textures.clear();
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

sf::Font &Resource::getFont()
{
	return m_font;
}