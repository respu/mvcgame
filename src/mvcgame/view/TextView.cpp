#include <mvcgame/view/TextView.hpp>
#include <mvcgame/view/Sprite.hpp>

namespace mvcgame {

	TextView::TextView() :
	_changed(false),
	_horizAlign(HorizontalAlign::Left),
	_vertiAlign(VerticalAlign::Top)
	{
	}

	void TextView::setHorizontalAlign(HorizontalAlign align)
	{
		_horizAlign = align;
	}

	void TextView::setVerticalAlign(VerticalAlign align)
	{
		_vertiAlign = align;
	}

	void TextView::setText(const std::string& text, bool changeSize)
	{
		_text = text;
		_changed = true;
	}

	const TextView::Sheet& TextView::getSheet() const
	{
		return _sheet;
	}

    void TextView::setSheet(const Sheet& sheet)
    {
    	_sheet = sheet;
    	_changed = true;
    }

    std::vector<const FontLetter*> TextView::getLetters(const std::string& text) const
    {
    	std::vector<const FontLetter*> letters;
		for(unsigned i=0; i<text.size();)
		{
			unsigned j=1;
			std::string letterName;
			while(true)
			{
				letterName = text.substr(i, j);
				if(_sheet.hasLetter(letterName))
				{
					letters.push_back(&_sheet.getLetter(letterName));
					i += j;
					break;					
				}
				if(i+j>=text.size())
				{
					letters.push_back(nullptr);
					i += 1;
					break;
				}
				j++;
			}
		}
		return letters;
    }

    void TextView::update()
    {
    	if(_changed)
    	{
	    	removeChildren();
	    	std::vector<const FontLetter*> letters = getLetters(_text);
	    	Point p;
	    	const FontInfo& info = _sheet.getInfo();
	    	for(const FontLetter* letter : letters)
			{
				if(letter)
				{
					std::unique_ptr<Sprite> letterSprite(new Sprite());
					SpriteSheet letterSheet(_sheet.getSpriteFrame(*letter));
					letterSprite->setSheet(letterSheet);
					letterSprite->setAnchor(Anchor(0, 0));
					letterSprite->getFrame().origin = p;
					p.x += letter->getRegion().advanceX;
					addChild(std::move(letterSprite));
				}
				else
				{
					p.x += info.baseHeight;
				}
			}
			getFrame().size.width = p.x;
			getFrame().size.height = info.lineHeight;
		}
		View::update();
    }

}