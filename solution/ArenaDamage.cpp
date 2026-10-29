#include "Combat/ArenaDamage.h"

float FArenaDamageCalculator::ComputeFinalDamage(
	const FArenaDamageRequest& Request,
	const FArenaDefenseStats& Defense)
{
	float Damage = Request.BaseDamage;

	if (Request.bIsCritical)
	{
		Damage *= Request.CritMultiplier;
	}

	float MitigationPool = (Request.Type == EArenaDamageType::Physical)
		? Defense.Armor
		: Defense.Resistance;

	const float EffectiveMitigation = FMathMax(0.f, MitigationPool - Request.Penetration);
	Damage = Damage - EffectiveMitigation;

	return FMathMax(0.f, Damage);
}
