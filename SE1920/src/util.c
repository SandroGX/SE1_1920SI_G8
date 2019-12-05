int setMasked(int currValue, int nextValue, int mask)
{
	return (nextValue & mask) | (currValue & ~mask);
}
