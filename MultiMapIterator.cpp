#include "MultiMapIterator.h"
#include "MultiMap.h"
#include<exception>


//Theta(1)
MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	currentKey = c.head;
	if (currentKey != nullptr)
		currentValue = c.head->val_head;
	else
		currentValue = nullptr;
}



//Theta(1)
TElem MultiMapIterator::getCurrent() const{
	if (currentValue != nullptr)
	{
		TElem nr;
		nr.first = currentKey->info;
		nr.second = currentValue->info;
		return nr;
	}
	throw exception();
}

//Theta(1)
bool MultiMapIterator::valid() const {
	if (currentKey == nullptr && currentValue == nullptr)
		return false;
	return true;
}

//Theta(1)
void MultiMapIterator::next() {
	if (currentKey == nullptr && currentValue == nullptr)
		throw exception();
	if (currentValue!=nullptr && currentValue->next == nullptr)
	{
		currentKey = currentKey->next;
		if (currentKey != nullptr)
			currentValue = currentKey->val_head;
		else
			currentValue = nullptr;
	}
	else
		currentValue = currentValue->next;

}

//Theta(1)
void MultiMapIterator::first() {
	currentKey = col.head;
	currentValue = col.head->val_head;
}
