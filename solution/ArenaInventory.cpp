#include "Inventory/ArenaInventory.h"

int32 FArenaInventory::CountItem(const FString& ItemId) const
{
	int32 Total = 0;
	for (const FArenaItemStack& Stack : Stacks)
	{
		if (Stack.ItemId == ItemId)
		{
			Total += Stack.Quantity;
		}
	}
	return Total;
}

bool FArenaInventory::AddItem(const FString& ItemId, int32 Amount, int32 MaxStack)
{
	if (Amount <= 0 || MaxStack <= 0)
	{
		return false;
	}

	int32 Remaining = Amount;

	for (FArenaItemStack& Stack : Stacks)
	{
		if (Stack.ItemId != ItemId)
		{
			continue;
		}
		const int32 Space = Stack.MaxStack - Stack.Quantity;
		if (Space <= 0)
		{
			continue;
		}
		const int32 Put = FMathMin(Space, Remaining);
		Stack.Quantity += Put;
		Remaining -= Put;
		if (Remaining == 0)
		{
			return true;
		}
	}

	while (Remaining > 0)
	{
		FArenaItemStack NewStack;
		NewStack.ItemId = ItemId;
		NewStack.MaxStack = MaxStack;
		NewStack.Quantity = FMathMin(MaxStack, Remaining);
		Remaining -= NewStack.Quantity;
		Stacks.Add(NewStack);
	}

	return true;
}

bool FArenaInventory::RemoveItem(const FString& ItemId, int32 Amount)
{
	if (Amount <= 0)
	{
		return false;
	}
	if (CountItem(ItemId) < Amount)
	{
		return false;
	}

	int32 Remaining = Amount;
	for (FArenaItemStack& Stack : Stacks)
	{
		if (Stack.ItemId != ItemId)
		{
			continue;
		}
		const int32 Take = FMathMin(Stack.Quantity, Remaining);
		Stack.Quantity -= Take;
		Remaining -= Take;
		if (Remaining == 0)
		{
			break;
		}
	}

	TArray<FArenaItemStack> Compacted;
	for (const FArenaItemStack& Stack : Stacks)
	{
		if (Stack.Quantity > 0)
		{
			Compacted.Add(Stack);
		}
	}
	Stacks = Compacted;
	return true;
}
