#pragma once
#include <list>
#include <vector>

#include "vector3.h"

class object;

class transform
{
public:
	vector3 position = {0.0f, 0.0f, 0.0f};
	vector3 rotation = {0.0f, 0.0f, 0.0f};
	vector3 scale = {1.0f,1.0f,1.0f};

	object* parent = nullptr;
	std::vector<object*> children;

	explicit transform(object* owner): owner_(owner) {}

	void set_parent(object* parent = nullptr);
	void add_child(const object* child_to_add) const;
	void remove_child(const object* child_to_remove);

	object* get_child(int index) const;
	int get_child_count() const;

	object* get_next_child(const object* child) const;
	object* get_prev_child(const object* child) const;

private:
	int get_child_index(const object* child) const;
	object* owner_;
};
