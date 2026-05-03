#include "Core/App.h"
#include "Core/AppConfig.h"

int main()
{
	trace::AppConfig config;
	config.window.title = "TRACE Engine";
	config.window.width = 1280;
	config.window.height = 720;

	trace::App app(config);
	app.run();

	return 0;
}