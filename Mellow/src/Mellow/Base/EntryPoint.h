#pragma once

#include "Base.h"

#ifndef MW_ENTRY_POINT
#define MW_ENTRY_POINT

#ifdef MW_PLATFORM_WINDOWS

extern Mellow::Application* Mellow::CreateApplication();

int main(int arc, char** argv) {
	
	auto app = Mellow::CreateApplication();
	app->Run();
	delete app;

	return 0;
}
#endif

#endif