#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	struct DirectionalLight {
		Vector3f color;
		float ambientIntensity;
		float diffuseIntensity;

		Vector3f direction;
	};


	struct LightAttenuation {
		float constant;
		float linear;
		float exp;
	};


	struct PointLight {
		Vector3f color;
		float ambientIntensity;
		float diffuseIntensity;

		Vector3f position;
		LightAttenuation attenuation;
	};


	struct SpotLight  {
		Vector3f color;
		float ambientIntensity;
		float diffuseIntensity;

		Vector3f position;
		LightAttenuation attenuation;

		Vector3f direction;
		float cutoff;
	};
}