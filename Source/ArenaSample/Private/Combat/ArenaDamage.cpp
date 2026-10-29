#include "Combat/ArenaDamage.h"

float FArenaDamageCalculator::ComputeFinalDamage(
	const FArenaDamageRequest& Request,
	const FArenaDefenseStats& Defense)
{
	float Damage = Request.BaseDamage;

	float Mitigation = (Request.Type == EArenaDamageType::Physical)
		? Defense.Armor
		: Defense.Resistance;

	if (Request.Type == EArenaDamageType::Physical)
	{
		Mitigation += Defense.Resistance;
	}

	Damage = Damage + Request.Penetration - Mitigation;

	if (Request.bIsCritical)
	{
		Damage *= Request.CritMultiplier;
	}

	return FMathMax(0.f, Damage);
}
