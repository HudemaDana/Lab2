#pragma once
#include "MultiMap.h"

class MultiMap;

class MultiMapIterator
{
	friend class MultiMap;

private:
	const MultiMap& col;
	MultiMap::PNode currentKey;
	MultiMap::PVNode currentValue;

	//DO NOT CHANGE THIS PART
	MultiMapIterator(const MultiMap& c);

public:
	
	TElem getCurrent()const;
	bool valid() const;
	void next();
	void first();
};

