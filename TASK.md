# Task: Fix ArenaSample inventory stacking and damage pipeline

## Platform
- Unreal Engine 5.4 game module — C++

## Difficulty
Medium

## Summary
`ArenaSample` is a small UE5 C++ game module. Inventory stacking and the shared
damage calculator in `Source/ArenaSample/Private/` do not match the documented
rules in the public headers. Restore the intended behavior so the portable
harness tests pass.

## Files to fix
- `Source/ArenaSample/Private/Inventory/ArenaInventory.cpp`
- `Source/ArenaSample/Private/Combat/ArenaDamage.cpp`

Do **not** modify:
- `Harness/tests/`
- Public header rule comments (treat them as the spec)

## Inventory rules (`FArenaInventory`)
1. `AddItem` must **merge** into existing stacks of the same `ItemId`, filling
   each stack up to `MaxStack`, then create additional stacks for overflow.
2. `RemoveItem` must delete stacks whose quantity reaches 0 (no ghost stacks).

## Damage rules (`FArenaDamageCalculator::ComputeFinalDamage`)
Order of operations:
1. Start from `BaseDamage`.
2. If critical, multiply by `CritMultiplier`.
3. Choose mitigation pool: `Armor` for Physical, `Resistance` for Magical.
4. Apply `Penetration` by reducing that mitigation pool (floor at 0).
5. Final damage = `max(0, DamageAfterCrit - EffectiveMitigation)`.

Physical damage must **not** be reduced by Resistance. Magical damage must
**not** be reduced by Armor.

## Verification (no Unreal Editor required)
From the repository root:

```bash
./verify.sh
```

This configures the portable CMake harness under `Harness/`, builds
`arena_logic_tests`, and runs them. Exit code 0 and `VERIFY_OK` required.

## Optional (full engine)
With Unreal Engine 5.4+ installed, you may also open `ArenaSample.uproject`
and build the `ArenaSample` editor target. The graded signal for this task
pack is the portable harness above.
