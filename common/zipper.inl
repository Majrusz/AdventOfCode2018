// Created by Majrusz on 24/07/2021. All rights reserved.

#include "zipper.h"

template< typename Type1, typename Type2 >
aoc::Zipper< Type1, Type2 >::Zipper( Type1 &data1, Type2 &data2 ) : data1{ data1 }, data2{ data2 } {
}

template< typename Type1, typename Type2 >
auto aoc::Zipper< Type1, Type2 >::begin() const {
	return IteratorPair{ std::begin( this->data1 ), std::begin( this->data2 ) };
}

template< typename Type1, typename Type2 >
auto aoc::Zipper< Type1, Type2 >::end() const {
	return IteratorPair{ std::end( this->data1 ), std::end( this->data2 ) };
}
