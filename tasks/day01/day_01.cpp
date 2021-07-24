// Created by Majrusz on 24/07/2021. All rights reserved.

#include "day_01.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_set>

#include "common/file_loader.h"

void aoc::day01::start() {
	std::vector< int > input{ loadFile< int >( "day01/input.txt" ) };

	std::cout << "Sum is equal: " << getSum( input ) << std::endl;
	std::cout << "First value that repeated twice is: " << getFirstNumberThatRepeatsTwice( input ) << std::endl;
}

int aoc::day01::getSum( const std::vector< int > &values ) {
	return std::accumulate( std::begin( values ), std::end( values ), 0 );
}

int aoc::day01::getFirstNumberThatRepeatsTwice( const std::vector< int > &values ) {
	std::vector< int > sums{};
	std::unordered_set< int > uniqueValues{};

	while( true ) {
		sums.reserve( values.size() );
		std::transform( std::begin( values ), std::end( values ), std::back_inserter( sums ), []( int value ){
			static int sum = 0;

			return sum += value;
		} );

		for( int value : sums ) {
			if( uniqueValues.find( value ) != std::end( uniqueValues ) )
				return value;

			uniqueValues.insert( value );
		}
		sums.clear();
	}
}
