#pragma once

#if defined _WIN32 || defined __CYGWIN__
#ifdef BUILDING_VECTOR
#define VECTOR_API __declspec(dllexport)
#else
#define VECTOR_API __declspec(dllimport)
#endif
#else // Linux / macOS etc.
#define VECTOR_API __attribute__((visibility("default")))
#endif
