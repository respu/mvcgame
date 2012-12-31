#include <mvcgame/platform/cocos2dx/view/TextView.hpp>
#include <cocos2dx/label_nodes/CCLabelTTF.h>
#include <cocos2dx/include/ccTypes.h>

namespace mvcgame {

    TextView::TextView(cocos2d::CCLabelTTF* label) : View(label), _label(label)
    {
    	//updateLabel(_label);
    }

    TextView::TextView() : TextView(new cocos2d::CCLabelTTF())
    {
    	assert(_label->init());
    }

    void TextView::updateLabel(cocos2d::CCLabelTTF* label)
    {
    	updateLabelHorizontalAlign(label);
    	updateLabelVerticalAlign(label);
    	updateLabelFont(label);
    	updateLabelSize(label);
    	updateLabelColor(label);
    	updateLabelText(label);
    }

    void TextView::updateNodeFrame(cocos2d::CCNode* node)
    {
    	View::updateNodeFrame(node);
    	_label->setDimensions(cocos2d::CCSizeMake(_frame.size.width, _frame.size.height));
    }

    void TextView::updateLabelHorizontalAlign(cocos2d::CCLabelTTF* label)
    {
    	const ITextView::HorizontalAlign a = _textHorizAlign;
		if(a == ITextView::HorizontalAlign::Left)
		{
			label->setHorizontalAlignment(cocos2d::kCCTextAlignmentLeft);
		}
		else if(a == ITextView::HorizontalAlign::Right)
		{
			label->setHorizontalAlignment(cocos2d::kCCTextAlignmentRight);
		}
		else if(a == ITextView::HorizontalAlign::Center)
		{
			label->setHorizontalAlignment(cocos2d::kCCTextAlignmentCenter);
		}
    }

    void TextView::updateLabelVerticalAlign(cocos2d::CCLabelTTF* label)
    {
    	const ITextView::VerticalAlign a = _textVertiAlign;
		if(a == ITextView::VerticalAlign::Top)
		{
			label->setVerticalAlignment(cocos2d::kCCVerticalTextAlignmentTop);
		}
		else if(a == ITextView::VerticalAlign::Bottom)
		{
			label->setVerticalAlignment(cocos2d::kCCVerticalTextAlignmentBottom);
		}
		else if(a == ITextView::VerticalAlign::Center)
		{
			label->setVerticalAlignment(cocos2d::kCCVerticalTextAlignmentCenter);
		}
    }

    void TextView::updateLabelFont(cocos2d::CCLabelTTF* label)
    {
		label->setFontName(_textFont.c_str());
    }

    void TextView::updateLabelSize(cocos2d::CCLabelTTF* label)
    {
		label->setFontSize(_textSize);
    }

    void TextView::updateLabelText(cocos2d::CCLabelTTF* label)
    {
		label->setString(_text.c_str());
    }

    void TextView::updateLabelColor(cocos2d::CCLabelTTF* label)
    {
    	const Color& c = _textColor;
		label->setColor(cocos2d::ccc3(c.r,c.g,c.b));
		label->setOpacity(c.a);
    }

	void TextView::setTextHorizontalAlign(ITextView::HorizontalAlign align)
	{
		BaseTextView::setTextHorizontalAlign(align);
		updateLabelHorizontalAlign(_label);
	}

	void TextView::setTextVerticalAlign(ITextView::VerticalAlign align)
	{
		BaseTextView::setTextVerticalAlign(align);
		updateLabelVerticalAlign(_label);
	}

	void TextView::setTextFont(const std::string& font)
	{
		BaseTextView::setTextFont(font);
		updateLabelFont(_label);
	}

	void TextView::setTextSize(unsigned short size)
	{
		BaseTextView::setTextSize(size);
		updateLabelSize(_label);
	}

	void TextView::setText(const std::string& text)
	{
		BaseTextView::setText(text);
		updateLabelText(_label);
	}

	void TextView::setTextColor(const Color& color)
	{
		BaseTextView::setTextColor(color);
		updateLabelColor(_label);
	}
}