#pragma once

#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>

#include <map>

#include "Mellow/Base/Log.h"

#include "Mellow/Profiling/Instrumentor.h"

#ifdef MW_PLATFORM_WINDOWS
	#include <Windows.h>
#endif