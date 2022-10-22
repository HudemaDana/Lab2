#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


//Theta(1)
MultiMap::SLLNode::SLLNode(TKey e, PNode n, PVNode t)
{
	info = e;
	next = n;
	val_head = t;
}

//Theta(1)
MultiMap::SLLofValues::SLLofValues(TValue e, PVNode n) 
{
	info = e;
	next = n;
}

//Theta(1)
MultiMap::MultiMap() 
{

	head = nullptr;
}

//Complexity:O(n), where n is the number of keys and m is the number of values
void MultiMap::add(TKey c, TValue v)
{
	PVNode node_val = new SLLofValues(v, nullptr);
	PNode first = head;
	while (first!= nullptr and first->next != nullptr)
	{
		if (first->info == c)
		{
			
			node_val->next = first->val_head;
			first->val_head = node_val;
			first->size++;
			return;
		}
		first = first->next;
	}

	if (first!= nullptr && first->info == c)
	{

		node_val->next = first->val_head;
		first->val_head = node_val;
		first->size++;
		return;
	}

	PNode new_node = new SLLNode(c, nullptr, node_val);
	new_node->next = head;
	head = new_node;
	head->val_head = node_val;

}

//Complexity: BC: Omega(1), WC: O(n), Total:O(n), where n is the number of the total numbers of keys and values
bool MultiMap::remove(TKey c, TValue v) 
{
	PNode current_node = head;
	PNode prev_node = nullptr;
	while (current_node != nullptr && current_node->info != c)
	{
		prev_node = current_node;
		current_node = current_node->next;

	}
	if (current_node != nullptr)
	{
		if (current_node->size == 1 && current_node->val_head->info == v)
		{
			if (prev_node == nullptr)
				head = head->next;
			else
				prev_node->next = current_node->next;

			while (current_node->val_head != nullptr)
			{
				PVNode node = current_node->val_head;
				current_node->val_head = current_node->val_head->next;
				delete node;
			}
			delete current_node;
			return true;
		}
		else
		{
			PVNode cv_node = current_node->val_head;
			PVNode pv_node =nullptr;
			while (cv_node != nullptr && cv_node->info != v)
			{
				pv_node = cv_node;
				cv_node = cv_node->next;
			}
			if (cv_node != nullptr)
			{
				if (pv_node == nullptr)
					current_node->val_head =current_node->val_head ->next;
				else
					pv_node->next = cv_node->next;

				delete cv_node;
				current_node->size--;
				return true;
			}
		}
	}
	return  false;
}

//Complexity: O(n+m), where n is the number of keys and m the number of values
vector<TValue> MultiMap::search(TKey c) const {
	vector<TValue> values;
	PNode current = head;
	while (current != nullptr && current->info != c)
		current = current->next;

	if (current != nullptr)
	{
		PVNode v_current = current->val_head;
		while (v_current != nullptr)
		{
			values.push_back(v_current->info);
			v_current = v_current->next;
		}
	}
	if(values.empty())
		return vector<TValue>();
	return values;
}

//Complexity: Theta(1)
int MultiMap::size() const {
	int nr = 0;
	PNode node = head;
	while (node != nullptr)
	{
		nr += node->size;
		node = node->next;
	}
	return nr;
}

//Complexity: Theta(1)
bool MultiMap::isEmpty() const {
	if (head == nullptr)
		return true;
	return false;
}

//Complexity: Theta(1)
MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}

//O(n)
MultiMap::~MultiMap() {
	while (head != nullptr)
	{
		PNode current_node = head;
		while (current_node->val_head != nullptr)
		{
			PVNode node = current_node->val_head;
			current_node->val_head = current_node->val_head->next;
			delete node;
		}
		head = head->next;
		delete current_node;
	}
}

//Complexity: O(n), where n is the number of keys
vector<TKey> MultiMap::keySet() const
{
	vector<TKey> v;
	PNode current_node = head;
	while (current_node != nullptr)
	{
		v.push_back(current_node->info);
		current_node = current_node->next;

	}

	return v;
}

