#include "FixtureList.hpp"

using iterator = FixtureList::iterator;
using const_iterator = FixtureList::const_iterator;

FixtureList::FixtureList(iterator::internal_pointer internalList) : headptr(internalList) { }

iterator::iterator(iterator::internal_pointer ptr) : ptr(ptr) { }
const_iterator::const_iterator(const_iterator::internal_pointer ptr) : ptr(ptr) { }

bool iterator::operator==(const iterator& other) { return this->ptr == other.ptr; }
bool const_iterator::operator==(const const_iterator& other) { return this->ptr == other.ptr; }
bool iterator::operator!=(const iterator& other) { return !operator==(other); }
bool const_iterator::operator!=(const const_iterator& other) { return !operator==(other); }

iterator::reference iterator::operator*() {
	return *static_cast<iterator::pointer>(ptr->GetUserData());
}
const_iterator::reference const_iterator::operator*() {
	return *static_cast<const_iterator::pointer>(ptr->GetUserData());
}

iterator& iterator::operator++() {
	ptr = ptr->GetNext();
	return *this;
}
const_iterator& const_iterator::operator++() {
	ptr = ptr->GetNext();
	return *this;
}
iterator iterator::operator++(int) {
	iterator clone(*this);
	ptr = ptr->GetNext();
	return clone;
}
const_iterator const_iterator::operator++(int) {
	const_iterator clone(*this);
	ptr = ptr->GetNext();
	return clone;
}

iterator FixtureList::begin() { return iterator(headptr); }
const_iterator FixtureList::cbegin() const { return const_iterator(headptr); }
iterator FixtureList::end() { return iterator(nullptr); }
const_iterator FixtureList::cend() const { return const_iterator(nullptr); }

iterator::reference FixtureList::operator[](iterator::size_type index) {
	iterator iter = begin();
	std::advance(iter, index);
	return *iter;
}
const_iterator::reference FixtureList::operator[](const_iterator::size_type index) const {
	const_iterator iter = cbegin();
	std::advance(iter, index);
	return *iter;
}