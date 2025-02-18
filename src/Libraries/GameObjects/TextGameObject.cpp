#include "TextGameObject.h"
#include "../Singletons/GameInfo.h"

TextGameObect::TextGameObect()
{
}

TextGameObect::~TextGameObect()
{
    delete font;
}

void TextGameObect::render()
{
  if (is_drawn)
  {
    if (text.getFillColor() != colour)
    {
      text.setFillColor(colour);
    }
    if (text.getCharacterSize() != char_size)
    {
      text.setCharacterSize(char_size); 
    }

    text.setPosition(position->x, position->y);
    text.setString(string);
    //std::cout << "Textstring: " << text.getString().toAnsiString();
    //std::cout << "    TextcharSize: " << text.getCharacterSize();
    //std::cout << "    Textfont: " << text.getFont();
    //std::cout << "    TextPosition: (" << text.getPosition().x << ", "
    //          << text.getPosition().y << ")\n";

    GameInfo::getInstance()->window->draw(text);
  }
}

sf::FloatRect TextGameObect::getRect()
{
  text.setPosition(position->x, position->y);
  return text.getGlobalBounds();
}

bool TextGameObect::setFontFromPath(std::string _path)
{
  if (font != nullptr)
  {
    delete font;
  }
  font = new sf::Font();
  if (!font->loadFromFile(_path))
  {
    std::cout << "Failed to load Font from path " << _path << "\n";
    delete font;
    return false;
  }
  text.setFont(*font);
  return true;
}

