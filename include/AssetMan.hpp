//Asset Manager: holds all the required fonts and textures for our game
#pragma once

#include <map> //use std::map for texture and font
#include <memory>
#include <string>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

namespace Engine
{
    class AssetMan
    {
        private:
            std::map<int, std::unique_ptr<sf::Texture> > m_textures; //this std::map object called "m_textures" has 2 members? one int for the ID of the texture, and one unique pointer to Texture
            std::map<int, std::unique_ptr<sf::Font> > m_fonts; //this std::map object called "m_fonts" has 2 members? one int for the ID of the font, and one unique pointer to font

        public:
            AssetMan();
            ~AssetMan();

            void AddTexture(int id, const std::string &filePath, bool wantRepeated = false);
            //wantRepeated flag allows the texture to be repeated as many time as needed to fill the entire rectangle
            void AddFont(int id, const std::string &filePath);


            const sf::Texture &GetTexture(int id) const;
            const sf::Font &GetFont(int id) const;

    };
}