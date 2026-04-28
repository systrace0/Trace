#include "LogPanel.h"

#include <imgui.h>

// -- Sanity checks --------------------------------------------------------------------------------
static_assert((int)engine::LogLevel::Count == 6, "Update LogPanel filter array");

namespace engine
{

	std::vector<LogEntry> LogPanel::s_entries;

	void LogPanel::push(const LogEntry& entry)
	{
		s_entries.push_back(entry);

		if (s_entries.size() > 2000)
			s_entries.erase(s_entries.begin(), s_entries.begin() + 500);
	}

	void LogPanel::draw()
	{
		ImGui::Begin("Log", nullptr, ImGuiWindowFlags_NoCollapse);

		const ImVec4 levelColors[] = {
			{ 0.5f, 0.5f, 0.5f, 1.0f },  // Debug   — grey
			{ 0.4f, 0.6f, 1.0f, 1.0f },  // Info    — baby blue
			{ 0.8f, 0.6f, 0.0f, 1.0f },  // Warn    — darker yellow
			{ 0.9f, 0.2f, 0.2f, 1.0f },  // Error   — red
			{ 0.7f, 0.3f, 0.9f, 1.0f },  // Fatal   — purple
			{ 0.0f, 0.7f, 0.3f, 1.0f },  // Success — darker green
		};

		const char* levelLabels[] = { "DBG", "INF", "WRN", "ERR", "FTL", "SUC" };

		// Filter Buttons
		for (int i = 0; i < (int)LogLevel::Count; ++i)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.0f);
			ImVec4 color = m_levelFilter[i]
				? levelColors[i]
				: ImVec4(0.4f, 0.4f, 0.4f, 1.0f);

			ImGui::PushStyleColor(ImGuiCol_Button, color);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, color);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, color);

			if (ImGui::Button(levelLabels[i]))
				m_levelFilter[i] = !m_levelFilter[i];

			ImGui::PopStyleColor(3);

			if (i < (int)LogLevel::Count - 1)
				ImGui::SameLine();
			ImGui::PopStyleVar();
		}

		float availableWidth = ImGui::GetContentRegionAvail().x
			- ImGui::CalcTextSize("Auto-Scroll").x
			- ImGui::CalcTextSize("Clear").x
			- 80.0f;
		ImGui::SetNextItemWidth(availableWidth);
		ImGui::InputText("##search", m_searchBuffer, sizeof(m_searchBuffer));

		ImGui::SameLine();
		ImGui::InputText("Filter", m_searchBuffer, sizeof(m_searchBuffer));
		ImGui::SameLine();

		ImGui::Checkbox("Auto-Scroll", &m_autoScroll);
		ImGui::SameLine();

		if (ImGui::Button("Clear")) s_entries.clear();

		ImGui::Separator();

		// Creates a scrollable box, height = 0 fill remaining window space
		ImGui::BeginChild("LogEntries", ImVec2(0, 0), false);

		for (auto& entry : s_entries)
		{
			// Skip if levels is filtered out
			if (!m_levelFilter[(int)entry.level])
				continue;

			// Skip if search doesn't match (case sensitive for now)
			if (m_searchBuffer[0] != '\0' && entry.message.find(m_searchBuffer) == std::string::npos)
				continue;

			ImGui::TextDisabled("[%s]", entry.timestamp.c_str());
			ImGui::SameLine();
			ImGui::PushStyleColor(ImGuiCol_Text, levelColors[(int)entry.level]);
			ImGui::Text("[%s]", levelLabels[(int)entry.level]);
			ImGui::SameLine();
			ImGui::TextWrapped("%s", entry.message.c_str());
			ImGui::PopStyleColor();
		}

		// Auto scroll to bottom
		if (m_autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY() - 4.0f)
			ImGui::SetScrollHereY(1.0f);

		ImGui::EndChild();
		ImGui::End();
	}
}