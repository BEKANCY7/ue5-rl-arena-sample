#pragma once

#include "ArenaCompat.h"

enum class EArenaDamageType : uint8
{
	Physical = 0,
	Magical = 1
};

struct ARENA_API FArenaDamageRequest
{
	float BaseDamage = 0.f;
	EArenaDamageType Type = EArenaDamageType::Physical;
	bool bIsCritical = false;
	float CritMultiplier = 1.5f;
	/** Flat armor/resistance penetration applied before mitigation. */
	float Penetration = 0.f;
};

struct ARENA_API FArenaDefenseStats
{
	float Armor = 0.f;      // mitigates Physical
	float Resistance = 0.f; // mitigates Magical
};

/**
 * Shared damage pipeline for ArenaSample.
 *
 * Intended order:
 * 1. Start from BaseDamage.
 * 2. If critical, multiply by CritMultiplier.
 * 3. Select mitigation pool by damage type (Armor for Physical, Resistance for Magical).
 * 4. Apply Penetration by reducing the mitigation pool (not below 0).
 * 5. Final = max(0, DamageAfterCrit - EffectiveMitigation).
 */
class ARENA_API FArenaDamageCalculator
{
public:
	static float ComputeFinalDamage(const FArenaDamageRequest& Request, const FArenaDefenseStats& Defense);
};
