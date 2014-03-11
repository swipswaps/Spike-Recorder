#include "ErrorBox.h"
#include "BitmapFontGL.h"
#include "TextureGL.h"
#include "Application.h"
#include "Painter.h"

#include <sstream>

namespace BackyardBrains {

namespace Widgets {

ErrorBox::ErrorBox(const char *text) : text(text) {
	setSizeHint(Size(20, 20));
}

void ErrorBox::paintEvent() {
	Painter::setColor(Color(20,20,20,200));
	Painter::drawRect(rect());

	const BitmapFontGL &font = *Application::font();
	int linelen = std::max(1,(width()-20)/font.characterWidth());

	Painter::setColor(Colors::white);

	std::string::iterator lstart = text.begin();
	std::string::iterator lbreak = text.begin();
	int i = 0;
	int line = 0;
	for(std::string::iterator it = text.begin(); it != text.end(); it++) {
		if(*it == ' ' || *it == '\n') {
			lbreak = it;
		}


		if(i >= linelen || *it == '\n') {
			font.draw(std::string(lstart, lbreak).c_str(), 10, 10+line*(font.characterHeight()+2));
			lstart = lbreak+1;
			i = 0;
			line++;
		} else {
			i++;
		}
	}

	font.draw(std::string(lstart, text.end()).c_str(), 10, 10+line*(font.characterHeight()+2));

}

void ErrorBox::mousePressEvent(MouseEvent *event) {
	close();
}

}

}
