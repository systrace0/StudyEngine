#pragma once

namespace trace
{
	struct WindowConfig
	{
		const char* title{ "TRACE Engine" };
		int			width{ 1280 };
		int			height{ 720 };
	};

	struct AppConfig
	{
		WindowConfig window;
		const char* vertexShader{ "shaders/basic.vert" };
		const char* fragmentShader{ "shaders/basic.frag" };
		const char* texture{ "assets/textures/container.jpg" };
	};
}