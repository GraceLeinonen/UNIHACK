#include "AssetMan.hpp"

Engine::AssetMan::AssetMan()
{
}

Engine::AssetMan::~AssetMan()
{
}

void Engine::AssetMan::AddTexture(int id, const std::string &filePath, bool wantRepeated)
{
    auto texture = std::make_unique<sf::Texture>(); //create a new texture of class sf::Texture

    if (texture->loadFromFile(filePath)) //load image to texture. loadFromFile function of sf returns a bool to see if the load was successful or not
    {
        texture->setRepeated(wantRepeated);//check if the texture wants to repeat itself
        m_textures[id] = std::move(texture);//if the texture is loaded successfully, store the texture to the position of m_textures[id] in the map
    }
}

void Engine::AssetMan::AddFont(int id, const std::string &filePath)
{
    auto font = std::make_unique<sf::Font>();

    if (font->loadFromFile(filePath))
    {
        m_fonts[id] = std::move(font);
    }
}

const sf::Texture &Engine::AssetMan::GetTexture(int id) const
{
    return *(m_textures.at(id).get()); //return the reference to the underlying texture object ie. the required asset from the internal map. Need if of the asset as the parameter.
}

const sf::Font &Engine::AssetMan::GetFont(int id) const
{
    return *(m_fonts.at(id).get()); 
}