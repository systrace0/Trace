#pragma once

namespace engine
{
	class Panel
	{
	public:
		virtual ~Panel() = default;
		virtual void draw() = 0;	// Every panel MUST implement this
	};
}