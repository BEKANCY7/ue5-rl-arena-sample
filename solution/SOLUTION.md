# Reference solution

Copy the fixed implementations into the module:

```bash
cp solution/ArenaInventory.cpp Source/ArenaSample/Private/Inventory/ArenaInventory.cpp
cp solution/ArenaDamage.cpp Source/ArenaSample/Private/Combat/ArenaDamage.cpp
./verify.sh
```

## Fixes
- **Inventory AddItem:** merge into existing stacks up to `MaxStack`, then overflow.
- **Inventory RemoveItem:** drop stacks with `Quantity == 0`.
- **Damage:** crit before mitigation; type-correct pool; penetration reduces mitigation.
