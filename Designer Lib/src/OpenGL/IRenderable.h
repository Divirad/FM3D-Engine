#pragma once
#include "../pch.h"

namespace DesignerLib {

	public interface class IRenderable {
	public:
		virtual FM3D::Model* GetModel() = 0;
	};
}