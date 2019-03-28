#include "FixtureList.hpp"

FixtureList::FixtureList(b2Fixture* internalList) : beginPtr(internalList) { }

FixtureList::iterator::iterator(b2Fixture* ptr) : ptr(ptr) { }
FixtureList::const_iterator::const_iterator(b2Fixture* ptr) : ptr(ptr) { }

bool FixtureList::iterator::operator==(const FixtureList::iterator& other) { return this->ptr == other.ptr; }
bool FixtureList::const_iterator::operator==(const FixtureList::const_iterator& other) { return this->ptr == other.ptr; }
bool FixtureList::iterator::operator!=(const FixtureList::iterator& other) { return !operator==(other); }
bool FixtureList::const_iterator::operator!=(const FixtureList::const_iterator& other) { return !operator==(other); }

FixtureList::iterator::reference FixtureList::iterator::operator*() {
	return *static_cast<FixtureList::iterator::pointer>(ptr->GetUserData());
}
FixtureList::const_iterator::reference FixtureList::const_iterator::operator*() {
	return *static_cast<FixtureList::const_iterator::pointer>(ptr->GetUserData());
}

FixtureList::iterator& FixtureList::iterator::operator++() {
	ptr = ptr->GetNext();
	return *this;
}
FixtureList::const_iterator& FixtureList::const_iterator::operator++() {
	ptr = ptr->GetNext();
	return *this;
}
FixtureList::iterator FixtureList::iterator::operator++(int) {
	FixtureList::iterator clone(*this);
	ptr = ptr->GetNext();
	return clone;
}
FixtureList::const_iterator FixtureList::const_iterator::operator++(int) {
	FixtureList::const_iterator clone(*this);
	ptr = ptr->GetNext();
	return clone;
}

FixtureList::iterator FixtureList::begin() { return FixtureList::iterator(headptr); }
FixtureList::const_iterator FixtureList::cbegin() const { return FixtureList::const_iterator(headptr); }
FixtureList::iterator FixtureList::end() { return FixtureList::iterator(nullptr); }
FixtureList::const_iterator FixtureList::cend() const { return FixtureList::const_iterator(nullptr); }