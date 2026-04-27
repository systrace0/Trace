#include "DebugPanel.h"

namespace engine
{
	DebugPanel::DebugPanel()
		: m_glVersion((const char*)glGetString(GL_VERSION))
		, m_vendor((const char*)glGetString(GL_VENDOR))
		, m_renderer((const char*)glGetString(GL_RENDERER))
	{
	}

	void DebugPanel::draw()
	{
		ImGui::Begin("Debug");
		ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
		ImGui::Text("GL Version: %s", glGetString(GL_VERSION));
		ImGui::Text("Vendor: %s", glGetString(GL_VENDOR));
		ImGui::Text("GPU: %s", glGetString(GL_RENDERER));
		ImGui::End();
	}
}