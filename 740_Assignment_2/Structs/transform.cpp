#include "transform.h"

#include "../object.h"

void transform::set_parent(object* parent)
{
	if (this->parent == parent)
		return;

	if (this->parent)
		parent->transform->remove_child(owner_);

	parent->transform->children.push_back(owner_);
	this->parent = parent;
}

void transform::add_child(const object* child_to_add) const
{
	child_to_add->transform->set_parent(owner_);
}

void transform::remove_child(const object* child_to_remove)
{
	const auto child_index = get_child_index(child_to_remove);
	if (child_index < 0 && child_index >= get_child_count())
		return;

	auto it = children.begin();
	std::advance(it, child_index);
	children.erase(it);
}

object* transform::get_child(const int index) const
{
	if (index < 0 || index >= get_child_count())
		return nullptr;

	return children[index];
}

int transform::get_child_count() const
{
	return static_cast<int>(children.size());
}

int transform::get_child_index(const object* child) const
{
	const int size = get_child_count();
	int i;
	for (i = 0; i < size; i++)
	{
		if (children[i] == child)
			break;
	}

	return i;
}

object* transform::get_next_child(const object* child) const
{
	auto index = get_child_index(child);
	if (index < 0 && index >= get_child_count())
		return nullptr;

	++index %= get_child_count();

	return children[index];
}


object* transform::get_prev_child(const object* child) const
{
	auto index = get_child_index(child);
	int prev_index = index;
	prev_index--; // Decrement before any checks

	if (prev_index < 0)
	{
		prev_index += get_child_count(); // Add count to wrap around
	}

	prev_index %= get_child_count();

	return children[prev_index];

	// if (index < 0 && index >= get_child_count())
	// 	return nullptr;
	//
	// --index;
	// index = static_cast<unsigned int>(index) % get_child_count();
	//
	// return children[index];
}
