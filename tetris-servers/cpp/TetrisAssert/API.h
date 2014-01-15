#pragma once

#ifdef TETRIS_ASSERT_EXPORTS
#define TETRIS_ASSERT_API __declspec(dllexport)
#else
#define TETRIS_ASSERT_API __declspec(dllimport)
#endif