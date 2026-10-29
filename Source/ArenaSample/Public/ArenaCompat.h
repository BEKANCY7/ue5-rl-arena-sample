#pragma once

/**
 * Tiny compatibility shims so the same .cpp can compile inside UE5
 * or under the portable Harness (ARENA_PORTABLE_BUILD).
 */
#ifdef ARENA_PORTABLE_BUILD
#include "ArenaPortable.h"
#else
#include "CoreMinimal.h"
#ifndef ARENA_API
#define ARENA_API
#endif
#ifndef FMathMin
#define FMathMin FMath::Min
#endif
#ifndef FMathMax
#define FMathMax FMath::Max
#endif
#endif
