#pragma once

namespace ENGINE_NAME {

	class SetPoolManager {
	protected:
		SetPoolManager() = default;

	public:
		virtual ~SetPoolManager() = default;

		//virtual void SetPool(Pool* pool) = 0;
	};

	class InitializeManager {
	protected:
		InitializeManager() = default;

	public:
		virtual ~InitializeManager() = default;

		virtual void Initialize() = 0;
	};

	class ExecuteManager {
	protected:
		ExecuteManager() = default;

	public:
		virtual ~ExecuteManager() = default;

		virtual void Execute() = 0;
	};
}