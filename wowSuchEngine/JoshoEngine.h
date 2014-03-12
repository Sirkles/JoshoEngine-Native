#ifndef JOSHOENGINE_H_
#define JOSHOENGINE_H_

#if defined WIN32 || defined WIN64
#ifdef JOSHOENGINE_EXPORTS
#define JOSHO_API __declspec(dllexport)
#define JOSHO_C_API extern "C" __declspec(dllexport)
#else
#define JOSHO_API __declspec(dllimport)
#define JOSHO_C_API extern "C" __declspec(dllimport)
#endif
#else
// Since __declspec is only on Windows, we don't want it on other platforms.
#define JOSHO_API
#define JOSHO_C_API
#endif

#endif