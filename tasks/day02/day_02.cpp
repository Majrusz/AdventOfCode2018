// Created by Majrusz on 24/07/2021. All rights reserved.

#include "day_02.h"

#include <algorithm>
#include <iostream>
#include <unordered_map>

#include "common/file_loader.h"

void aoc::day02::start() {
	std::vector< std::string > input{ loadFile< std::string >( "day02/input.txt" ) };

	std::cout << "Checksum is equal: " << getChecksum( input ) << std::endl;
}

size_t aoc::day02::getChecksum( const std::vector< std::string > &values ) {
	static auto itOccurs{
		[]( size_t nTimes ) {
			return [ nTimes ]( const std::pair< char, size_t > &pair ) -> bool {
				return pair.second == nTimes;
			};
		}
	};

	size_t pairs = 0, triples = 0;
	std::for_each(
		std::begin( values ), std::end( values ), [ & ]( const std::string &value ) {
			std::unordered_map< char, size_t > occurrences{};
			std::for_each(
				std::begin( value ), std::end( value ), [ & ]( char character ) {
					occurrences[ character ] += 1;
				}
			);

			if( std::find_if( std::begin( occurrences ), std::end( occurrences ), itOccurs( 2 ) ) != std::end( occurrences ) )
				++pairs;

			if( std::find_if( std::begin( occurrences ), std::end( occurrences ), itOccurs( 3 ) ) != std::end( occurrences ) )
				++triples;
		}
	);

	return pairs * triples;
}
