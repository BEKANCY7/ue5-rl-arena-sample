#pragma once

#include "ArenaCompat.h"

/**
 * Stackable inventory used by ArenaSample characters.
 *
 * Intended rules:
 * 1. Adding an item that already exists merges into that stack (Qty += Amount).
 * 2. Removing Qty that empties a stack deletes the entry (no zero-qty ghosts).
 * 3. Max stack size is respected; overflow creates additional stacks of the same ItemId.
 */
struct ARENA_API FArenaItemStack
{
	FString ItemId;
	int32 Quantity = 0;
	int32 MaxStack = 99;
};

class ARENA_API FArenaInventory
{
public:
	const TArray<FArenaItemStack>& GetStacks() const { return Stacks; }

	/** Total quantity across all stacks for ItemId. */
	int32 CountItem(const FString& ItemId) const;

	/**
	 * Adds Amount of ItemId. Merges into existing stacks first (up to MaxStack),
	 * then appends new stacks as needed. Returns false if Amount <= 0.
	 */
	bool AddItem(const FString& ItemId, int32 Amount, int32 MaxStack = 99);

	/**
	 * Removes Amount of ItemId across stacks (oldest first).
	 * Returns false if the inventory does not contain enough quantity.
	 */
	bool RemoveItem(const FString& ItemId, int32 Amount);

private:
	TArray<FArenaItemStack> Stacks;
};
