#ifndef TEXT_GAME_OBJECT_H
#define TEXT_GAME_OBJECT_H
#include "GameObject.h"

class TextGameObect : public GameObject
{
public:
	TextGameObect();
	~TextGameObect();
	virtual void init() = 0;
	virtual void update(float dt) = 0;
	virtual void handleEvent(sf::Event) = 0;

	void render();
	sf::FloatRect getRect();

	bool setFontFromPath(std::string _path);
	sf::Font* getFont() { return font; };

	void setText(std::string _string) { string = _string; };
	std::string getText() { return string; };
	void setCharSize(int _size) { char_size = _size; };
	int getCharSize() { return char_size; };

protected:
	std::string string;
	sf::Font* font = nullptr;
	sf::Text text;
	int char_size = 20;
	bool is_bold = false;
	bool is_Underlined = false;

private:
};

#endif // !TEXT_GAME_OBJECT_H
