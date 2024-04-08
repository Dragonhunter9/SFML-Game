#include "TextureManager.hpp"

void TextureManager::loadTexture(const std::string& name, const std::string& filename)
{
	sf::Texture tex;
	tex.loadFromFile(filename);
	textures[name] = tex;
}

sf::Texture& TextureManager::getRef(const std::string& texture)
{
	return textures.at(texture);
}

TextureManager::TextureManager() {}