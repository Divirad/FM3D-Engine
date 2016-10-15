#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	struct BaseLight {
		Vector3f color;
		float ambientIntensity;
		float diffuseIntensity;
	};


	struct DirectionalLight : public BaseLight {
		Vector3f direction;
	};


	struct LightAttenuation {
		float constant;
		float linear;
		float exp;
	};


	struct PointLight : public BaseLight {
		Vector3f position;
		LightAttenuation attenuation;
	};


	struct SpotLight : public PointLight {
		Vector3f direction;
		float cutoff;
	};
}