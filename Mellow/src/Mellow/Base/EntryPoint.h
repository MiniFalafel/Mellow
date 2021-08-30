#pragma once

#include "Mellow/Base/Base.h"
#include "Mellow/Base/Log.h"

#ifndef MW_ENTRY_POINT
#define MW_ENTRY_POINT

#ifdef MW_PLATFORM_WINDOWS

extern Mellow::Application* Mellow::CreateApplication();

int main(int arc, char** argv) {
	
	// Initialize the log
	Mellow::Log::Init();

	// Create the app
	auto app = Mellow::CreateApplication();
	// Run the app
	app->Run();
	// Delete the app
	delete app;

	return 0;
}
#endif

#endif