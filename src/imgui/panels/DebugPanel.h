#pragma once

#include "Panel.h"

#include <imgui.h>

namespace engine
{
	class DebugPanel : public Panel
	{
	public:
		DebugPanel();
		void draw() override;

	private:
		const char* m_glVersion{ nullptr };
		const char* m_vendor{ nullptr };
		const char* m_renderer{ nullptr };
	};
}
