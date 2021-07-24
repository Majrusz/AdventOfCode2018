// Created by Majrusz on 24/07/2021. All rights reserved.

#pragma once

#include "pair_iterator.h"

namespace aoc {
	template< typename Type1, typename Type2 >
	class Zipper {
	public:
		Zipper( Type1 &data1, Type2 &data2 );

		auto begin() const;

		auto end() const;

	private:
		Type1 &data1;
		Type2 &data2;
	};

	template< typename Type1, typename Type2 >
	Zipper< Type1, Type2 > zip( Type1 &data1, Type2 &data2 ) {
		return Zipper{ data1, data2 };
	}
}

#include "zipper.inl"