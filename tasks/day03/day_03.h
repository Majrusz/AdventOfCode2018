// Created by Majrusz on 24/07/2021. All rights reserved.

#pragma once

#include <iostream>
#include <vector>

namespace aoc::day03 {
	struct Data {
		size_t id;
		size_t x, y, w, h;
	};

	void start();

	size_t getAmountOfOverlappingElements( const std::vector< Data > &values );

	size_t getIDOfNotOverlappingElement( const std::vector< Data > &values );

	std::vector< std::string > getGrid( const std::vector< Data > &values );
}

namespace std {
	std::istream &operator>>( std::istream &istream, aoc::day03::Data &data );
}