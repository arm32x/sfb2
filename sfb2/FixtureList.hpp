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
				typedef Fixture& reference;
				typedef Fixture* pointer;
				typedef std::forward_iterator_tag iterator_category;
				
				bool operator==(const iterator& other);
				bool operator!=(const iterator& other);
				reference operator*();
				iterator& operator++();
				iterator  operator++(int);
				
			private:
				iterator(b2Fixture* ptr);
				
				b2Fixture* ptr;
		};
		
		class const_iterator {
			friend class FixtureList;
			public:
				typedef std::ptrdiff_t difference_type;
				typedef unsigned int size_type;
				typedef const Fixture& reference;
				typedef const Fixture* pointer;
				typedef std::forward_iterator_tag iterator_category;
				
				bool operator==(const const_iterator& other);
				bool operator!=(const const_iterator& other);
				reference operator*();
				const_iterator& operator++();
				const_iterator  operator++(int);
				
			private:
				const_iterator(b2Fixture* ptr);
				
				b2Fixture* ptr;
		};
		
		iterator begin();
		const_iterator cbegin() const;
		iterator end();
		const_iterator cend() const;
		
		FixtureList(b2Fixture* internalList);
		
	private:
		b2Fixture* headptr;
	
};