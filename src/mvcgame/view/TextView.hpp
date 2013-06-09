

#ifndef mvcgame_TextView_hpp
#define mvcgame_TextView_hpp

#include <mvcgame/view/View.hpp>
#include <mvcgame/base/Color.hpp>
#include <mvcgame/font/FontSheet.hpp>

#include <string>
#include <vector>

namespace mvcgame {

	class TextView : public View
	{
	public:
        typedef FontSheet Sheet;

		enum class HorizontalAlign
		{
			Left,
			Right,
			Center
		};
		enum class VerticalAlign
		{
			Top,
			Bottom,
			Center
		};

	protected:
		bool _changed;
		HorizontalAlign _horizAlign;
		VerticalAlign _vertiAlign;
		std::string _text;
		Sheet _sheet;

		std::vector<const FontLetter*> getLetters(const std::string& text) const;
	public:
		TextView();

		void setHorizontalAlign(HorizontalAlign align);
		void setVerticalAlign(VerticalAlign align);
		void setText(const std::string& text, bool changeSize=true);

		const Sheet& getSheet() const;
        void setSheet(const Sheet& sheet);
        void update();
	};

}

#endif