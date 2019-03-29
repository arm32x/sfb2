#pragma once

#include <iterator>

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
using namespace sf;

#include "Fixture.hpp"

class FixtureList {
	
	public:
		class iterator {
			friend class FixtureList;
			public:
				typedef std::ptrdiff_t difference_type;
				typedef unsigned int size_type;
				typedef Fixture value_type;
				typedef Fixture& reference;
				typedef Fixture* pointer;
				typedef std::forward_iterator_tag iterator_category;
				
				bool operator==(const iterator& other);
				bool operator!=(const iterator& other);
				reference operator*();
				iterator& operator++();
				iterator  operator++(int);
				
			private:
				typedef b2Fixture* internal_pointer;
				
				iterator(internal_pointer ptr);
				internal_pointer ptr;
		};
		
		class const_iterator {
			friend class FixtureList;
			public:
				typedef std::ptrdiff_t difference_type;
				typedef unsigned int size_type;
				typedef const Fixture value_type;
				typedef const Fixture& reference;
				typedef const Fixture* pointer;
				typedef std::forward_iterator_tag iterator_category;
				
				bool operator==(const const_iterator& other);
				bool operator!=(const const_iterator& other);
				reference operator*();
				const_iterator& operator++();
				const_iterator  operator++(int);
				
			private:
				typedef b2Fixture* internal_pointer;
				
				const_iterator(internal_pointer ptr);
				internal_pointer ptr;
		};
		
		iterator begin();
		const_iterator cbegin() const;
		iterator end();
		const_iterator cend() const;
		
		iterator::reference operator[](iterator::size_type index);
		const_iterator::reference operator[](const_iterator::size_type index) const;
		
		FixtureList(b2Fixture* internalList);
		
	private:
		b2Fixture* headptr;
	
};