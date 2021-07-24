// Created by Majrusz on 24/07/2021. All rights reserved.

#pragma once

#include <iterator>

namespace aoc {
	template< typename IteratorType1, typename IteratorType2 >
	class IteratorPair {
	public:
		using Type1 = typename std::iterator_traits< IteratorType1 >::value_type;
		using Type2 = typename std::iterator_traits< IteratorType2 >::value_type;
		using Data = std::pair< Type1, Type2 >;

		IteratorPair( IteratorType1 iterator1, IteratorType2 iterator2 );

		bool operator==( const IteratorPair &other ) const;

		bool operator!=( const IteratorPair &other ) const;

		Data operator*() const;

		IteratorPair &operator++();

	private:
		IteratorType1 iterator1;
		IteratorType2 iterator2;
	};
}

namespace std {
	template< typename IteratorType1, typename IteratorType2 >
	struct iterator_traits< aoc::IteratorPair< IteratorType1, IteratorType2 > > {
		using iterator_category = std::forward_iterator_tag;
		using value_type = typename aoc::IteratorPair< IteratorType1, IteratorType2 >::Data;
		using difference_type = int;
	};
}

#include "pair_iterator.inl"