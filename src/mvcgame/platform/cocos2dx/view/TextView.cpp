#include <mvcgame/platform/cocos2dx/view/TextView.hpp>
#include <cocos2dx/label_nodes/CCLabelTTF.h>

namespace mvcgame {

    TextView::TextView(cocos2d::CCLabelTTF* label) : View(label)
    {

    }

    TextView::TextView() : View(new cocos2d::CCLabelTTF())
    {

    }

	void TextView::setTextHorizontalAlign(ITextView::HorizontalAlign align)
	{
		BaseTextView::setTextHorizontalAlign(align);
	}

	void TextView::setTextVerticalAlign(ITextView::VerticalAlign align)
	{
		BaseTextView::setTextVerticalAlign(align);
	}

	void TextView::setTextFont(const std::string& font)
	{
		BaseTextView::setTextFont(font);
	}

	void TextView::setTextSize(unsigned short size)
	{
		BaseTextView::setTextSize(size);
	}

	void TextView::setText(const std::string& text)
	{
		BaseTextView::setText(text);
	}

	void TextView::setTextColor(const Color& color)
	{
		BaseTextView::setTextColor(color);
	}
}