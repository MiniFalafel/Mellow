#pragma once

#ifdef MW_PLATFORM_WINDOWS

extern Mellow::Application* Mellow::CreateApplication();

int main(int arc, char** argv) {
	
	// Initialize the log
	Mellow::Log::Init();

	// Create the app
	MW_PROFILE_BEGIN_SESSION("Startup", "Mellow-Startup.json");
	auto app = Mellow::CreateApplication();
	MW_PROFILE_END_SESSION();
	// Run the app
	MW_PROFILE_BEGIN_SESSION("Runtime", "Mellow-Runtime.json");
	app->Run();
	MW_PROFILE_END_SESSION();
	// Delete the app
	MW_PROFILE_BEGIN_SESSION("Shutdown", "Mellow-Shutdown.json");
	delete app;
	MW_PROFILE_END_SESSION();

	return 0;
}
#endif