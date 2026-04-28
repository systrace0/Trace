#include "LogPanel.h"

#include <imgui.h>

namespace engine
{
	std::vector<LogEntry> LogPanel::s_entries;

	void LogPanel::push(const LogEntry& entry)
	{
		s_entries.push_back(entry);
	}

	void LogPanel::draw()
	{
		ImGui::Begin("Log");

		const char* labels[] = { "Info", "Warn", "Error", "Fatal", "Success" };
		for (for i = 0; i < (int)LogLevel::Count; ++i)
			ImGui::Checkbox(labels[i], &m_levelFilter[i]);

		ImGui::InputText("Logs", m_searchBuffer, sizeof(m_searchBuffer));
		ImGui::End();
	}
}