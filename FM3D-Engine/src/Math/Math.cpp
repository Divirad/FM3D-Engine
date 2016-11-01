#include <Engine.h>

namespace ENGINE_NAME {

	Color3f Math::ConvertColor(const Color3b& color) {
		return ((float)color[0]) / 255.0f, ((float)color[1]) / 255.0f, ((float)color[2]) / 255.0f;
	}

	Color3b Math::ConvertColor(const Color3f& color) {
		return (byte)(color[0] * 255.0f), (byte)(color[1] * 255.0f), (byte)(color[2] * 255.0f);
	}

	Color4f Math::ConvertColor(const Color4b& color) {
		return ((float)color[0]) / 255.0f, ((float)color[1]) / 255.0f, ((float)color[2]) / 255.0f, ((float)color[3]) / 255.0f;
	}

	Color4b Math::ConvertColor(const Color4f& color) {
		return (byte)(color[0] * 255.0f), (byte)(color[1] * 255.0f), (byte)(color[2] * 255.0f), (byte)(color[3] * 255.0f);
	}

}