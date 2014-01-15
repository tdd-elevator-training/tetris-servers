#pragma once

#ifdef TETRIS_EXPORTS
#define TETRIS_API __declspec(dllexport)
#else
#define TETRIS_API __declspec(dllimport)
#endif