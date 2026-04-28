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
		for (int i = 0; i < (int)LogLevel::Count; ++i)
			ImGui::Checkbox(labels[i], &m_levelFilter[i]);

		ImGui::InputText("Logs", m_searchBuffer, sizeof(m_searchBuffer));

		// Creates a scrollable box, height = 0 fill remaining window space
		ImGui::BeginChild("LogEntries", ImVec2(0, 0), false);

		const ImVec4 levelColors[] = {
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			{ 1.0f, 1.0f, 0.0f, 1.0f },
			{ 1.0f, 0.3f, 0.3f, 1.0f },
			{ 1.0f, 0.0f, 1.0f, 1.0f },
			{ 0.0f, 1.0f, 0.0f, 1.0f },
		};

		const char* levelLabels[] = { "INFO", "WARN", "ERROR", "FATAL", "SUCCESS" };

		for (auto& entry : s_entries)
		{
			// Skip if levels is filtered out
			if (!m_levelFilter[(int)entry.level])
				continue;

			// Skip if search doesn't match (case sensitive for now)
			if (m_searchBuffer[0] != '\0' && entry.message.find(m_searchBuffer) == std::string::npos)
				continue;

			ImGui::PushStyleColor(ImGuiCol_Text, levelColors[(int)entry.level]);
			ImGui::Text("[%s] [%s]: %s",
				entry.timestamp.c_str(),
				levelLabels[(int)entry.level],
				entry.message.c_str());
			ImGui::PopStyleColor();
		}

		// Auto scroll to bottom
		if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
			ImGui::SetScrollHereY(1.0f);

		ImGui::EndChild();
		ImGui::End();
	}
}