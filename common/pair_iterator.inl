// Created by Majrusz on 24/07/2021. All rights reserved.

#include "pair_iterator.h"

template< typename IteratorType1, typename IteratorType2 >
aoc::IteratorPair< IteratorType1, IteratorType2 >::IteratorPair( IteratorType1 iterator1, IteratorType2 iterator2 ) : iterator1{ iterator1 }, iterator2{ iterator2 } {
}

template< typename IteratorType1, typename IteratorType2 >
bool aoc::IteratorPair< IteratorType1, IteratorType2 >::operator==( const aoc::IteratorPair< IteratorType1, IteratorType2 > &other ) const {
	return this->iterator1 == other.iterator1 && this->iterator2 == other.iterator2;
}

template< typename IteratorType1, typename IteratorType2 >
bool aoc::IteratorPair< IteratorType1, IteratorType2 >::operator!=( const aoc::IteratorPair< IteratorType1, IteratorType2 > &other ) const {
	return !( *this == other );
}

template< typename IteratorType1, typename IteratorType2 >
typename aoc::IteratorPair< IteratorType1, IteratorType2 >::Data aoc::IteratorPair< IteratorType1, IteratorType2 >::operator*() const {
	return { *this->iterator1, *this->iterator2 };
}

template< typename IteratorType1, typename IteratorType2 >
aoc::IteratorPair< IteratorType1, IteratorType2 > &aoc::IteratorPair< IteratorType1, IteratorType2 >::operator++() {
	++this->iterator1;
	++this->iterator2;

	return *this;
}
