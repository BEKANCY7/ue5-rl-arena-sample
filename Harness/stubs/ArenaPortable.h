#pragma once
/**
 * Minimal stand-ins so Arena gameplay logic can be unit-tested without
 * linking the full Unreal Engine runtime.
 */
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

using FString = std::string;
using int32 = int32_t;
using uint8 = uint8_t;

template <typename T>
class TArray
{
public:
	void Add(const T& Value) { Data.push_back(Value); }
	void Empty() { Data.clear(); }
	int32 Num() const { return static_cast<int32>(Data.size()); }
	T& operator[](int32 Index) { return Data[static_cast<size_t>(Index)]; }
	const T& operator[](int32 Index) const { return Data[static_cast<size_t>(Index)]; }

	typename std::vector<T>::iterator begin() { return Data.begin(); }
	typename std::vector<T>::iterator end() { return Data.end(); }
	typename std::vector<T>::const_iterator begin() const { return Data.begin(); }
	typename std::vector<T>::const_iterator end() const { return Data.end(); }

	void Reset() { Data.clear(); }
	void Append(const TArray<T>& Other)
	{
		Data.insert(Data.end(), Other.Data.begin(), Other.Data.end());
	}
	void operator=(const TArray<T>& Other) { Data = Other.Data; }

private:
	std::vector<T> Data;
};

inline float FMathMax(float A, float B) { return std::max(A, B); }
inline float FMathMin(float A, float B) { return std::min(A, B); }
inline int32 FMathMax(int32 A, int32 B) { return std::max(A, B); }
inline int32 FMathMin(int32 A, int32 B) { return std::min(A, B); }

#ifndef ARENA_API
#define ARENA_API
#endif
