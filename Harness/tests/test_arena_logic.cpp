#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

#include "Combat/ArenaDamage.h"
#include "Inventory/ArenaInventory.h"

namespace
{
int GFailures = 0;

void ExpectTrue(bool Cond, const std::string& Msg)
{
	if (!Cond)
	{
		std::cerr << "FAIL: " << Msg << "\n";
		++GFailures;
	}
}

void ExpectEqInt(int32 Actual, int32 Expected, const std::string& Msg)
{
	if (Actual != Expected)
	{
		std::cerr << "FAIL: " << Msg << " expected=" << Expected << " actual=" << Actual << "\n";
		++GFailures;
	}
}

void ExpectNear(float Actual, float Expected, float Eps, const std::string& Msg)
{
	if (std::fabs(Actual - Expected) > Eps)
	{
		std::cerr << "FAIL: " << Msg << " expected=" << Expected << " actual=" << Actual << "\n";
		++GFailures;
	}
}
} // namespace

static void TestInventoryMergeAndOverflow()
{
	FArenaInventory Inv;
	ExpectTrue(Inv.AddItem("Potion", 40, 50), "add first stack");
	ExpectTrue(Inv.AddItem("Potion", 20, 50), "merge into existing");
	ExpectEqInt(Inv.CountItem("Potion"), 60, "merged quantity across stacks");
	ExpectEqInt(Inv.GetStacks().Num(), 2, "overflow creates second stack");
	ExpectEqInt(Inv.GetStacks()[0].Quantity, 50, "first stack filled to max");
	ExpectEqInt(Inv.GetStacks()[1].Quantity, 10, "remainder in second stack");
}

static void TestInventoryRemoveCompacts()
{
	FArenaInventory Inv;
	Inv.AddItem("Arrow", 10, 99);
	ExpectTrue(Inv.RemoveItem("Arrow", 10), "remove entire stack");
	ExpectEqInt(Inv.CountItem("Arrow"), 0, "no arrows remain");
	ExpectEqInt(Inv.GetStacks().Num(), 0, "empty stacks removed");
}

static void TestInventoryRemovePartial()
{
	FArenaInventory Inv;
	Inv.AddItem("Arrow", 10, 99);
	ExpectTrue(Inv.RemoveItem("Arrow", 3), "partial remove");
	ExpectEqInt(Inv.CountItem("Arrow"), 7, "remaining arrows");
	ExpectEqInt(Inv.GetStacks().Num(), 1, "stack retained");
}

static void TestPhysicalDamagePipeline()
{
	FArenaDamageRequest Req;
	Req.BaseDamage = 100.f;
	Req.Type = EArenaDamageType::Physical;
	Req.bIsCritical = true;
	Req.CritMultiplier = 2.f;
	Req.Penetration = 10.f;

	FArenaDefenseStats Def;
	Def.Armor = 30.f;
	Def.Resistance = 50.f; // must NOT affect physical

	// crit first: 200, mitigation max(0, 30-10)=20 => 180
	ExpectNear(FArenaDamageCalculator::ComputeFinalDamage(Req, Def), 180.f, 0.01f, "physical crit pipeline");
}

static void TestMagicalIgnoresArmor()
{
	FArenaDamageRequest Req;
	Req.BaseDamage = 80.f;
	Req.Type = EArenaDamageType::Magical;
	Req.bIsCritical = false;
	Req.Penetration = 5.f;

	FArenaDefenseStats Def;
	Def.Armor = 100.f;
	Def.Resistance = 20.f;

	// 80 - max(0, 20-5)=15 => 65
	ExpectNear(FArenaDamageCalculator::ComputeFinalDamage(Req, Def), 65.f, 0.01f, "magical uses resistance only");
}

int main()
{
	TestInventoryMergeAndOverflow();
	TestInventoryRemoveCompacts();
	TestInventoryRemovePartial();
	TestPhysicalDamagePipeline();
	TestMagicalIgnoresArmor();

	if (GFailures != 0)
	{
		std::cerr << GFailures << " assertion(s) failed\n";
		return 1;
	}
	std::cout << "All arena logic tests passed\n";
	return 0;
}
