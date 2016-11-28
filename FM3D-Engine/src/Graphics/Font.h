#pragma once
#include <Engine.h>

namespace FM3D {

#define CHARACTER_COUNT 256

	struct  Character {
		float advanceX, advanceY;
		float width, height;
		float left, top;
		float offsetX;
	};

	class Font {
	private:
		Vector2f m_scale;
		Texture* m_fontAtlas;
		Character* m_chars;
	public:
		Font(Character* chars, Vector2f scale, Texture* tex) : m_scale(scale), m_fontAtlas(tex), m_chars(chars) {};

		const Texture* getTexture() const { return m_fontAtlas; }
		const Vector2f* getScale() const { return &m_scale; };
		//float getKerning() const;
		const Character* getChar(char c) const { return &(m_chars[c]); };

		float getTextWidth(const std::string text) {
			float width = 0;
			for (int i = 0; i < (int)text.length(); i++) {
				width += m_chars[text[i]].advanceX * m_scale.x;
			}
			return width;
		}

		void setScale(float x, float y) { m_scale = Vector2f(x, y); }
		void setScale(Vector2f& vec) { m_scale = vec; }
	};

	struct Text {
		std::string txt;
		Font* font;
		uint color;
	};
}