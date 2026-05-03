#pragma once

namespace trace
{
	class Panel
	{
	public:
		virtual ~Panel() = default;
		virtual void draw() = 0;	// Every panel MUST implement this
	};
}