#pragma once

#ifdef MYSOLVER_EXPORTS
#define MYSOLVER_API __declspec(dllexport)
#else
#define MYSOLVER_API __declspec(dllimport)
#endif