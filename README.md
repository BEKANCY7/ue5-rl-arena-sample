# UE5 RL Sample — ArenaSample

Representative **Unreal Engine 5 / C++** reinforcement-learning coding task for
agent evaluation. Original work prepared as a public sample for Adzzat-style
UE5 data sourcing.

| Artifact | Path |
|----------|------|
| Agent instructions | [`TASK.md`](TASK.md) |
| Metadata | [`metadata.json`](metadata.json) |
| UE5 project | [`ArenaSample.uproject`](ArenaSample.uproject) |
| Game module (starter, buggy) | [`Source/ArenaSample/`](Source/ArenaSample/) |
| Portable verifier (no Editor) | [`Harness/`](Harness/) + [`verify.sh`](verify.sh) |
| Reference solution | [`solution/`](solution/) |
| Docker | [`Dockerfile`](Dockerfile) |

## Project facts
- **Name / genre:** ArenaSample — action / RPG systems slice (inventory + damage)
- **Engine:** Unreal Engine **5.4** (`.uproject` association)
- **Languages:** C++ (no Blueprint assets required for the graded task)
- **Size:** small sample module (~hundreds of LOC gameplay code + harness)
- **Build status:** portable harness builds and tests on Linux with CMake/g++; full Editor build optional if UE 5.4+ is installed
- **Tasks / verification:** one medium bug-fix pack; `./verify.sh` is the programmatic signal

## Quick verify

```bash
./verify.sh          # starter should FAIL
cp solution/ArenaInventory.cpp Source/ArenaSample/Private/Inventory/ArenaInventory.cpp
cp solution/ArenaDamage.cpp Source/ArenaSample/Private/Combat/ArenaDamage.cpp
./verify.sh          # expect VERIFY_OK
```

## Docker

```bash
docker build -t ue5-arena-rl-sample .
docker run --rm ue5-arena-rl-sample
```

## Related
Mobile RL sample (same packaging style):
https://github.com/BEKANCY7/mobile-rl-shopcart-sample
