// Created by Majrusz on 24/07/2021. All rights reserved.

#include "day_02.h"

#include <algorithm>
#include <iostream>
#include <unordered_map>

#include "common/file_loader.h"
#include "common/zipper.h"

void aoc::day02::start() {
	std::vector< std::string > input{ loadFile< std::string >( "day02/input.txt" ) };

	std::cout << "Checksum is equal: " << getChecksum( input ) << std::endl;
	std::cout << "Common string: " << getCommonString( input ) << std::endl;
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

std::string aoc::day02::getCommonString( const std::vector< std::string > &values ) {
	for( auto it1 = std::begin( values ); it1 != std::end( values ); ++it1 )
		for( auto it2 = it1 + 1; it2 != std::end( values ); ++it2 ) {
			const std::string &value1{ *it1 }, &value2{ *it2 };
			auto pair{ zip( value1, value2 ) };

			auto differentCharacters{
				std::count_if(
					std::begin( pair ), std::end( pair ), []( const std::pair< char, char > &pair ) -> bool {
						return pair.first != pair.second;
					}
				)
			};
			if( differentCharacters != 1 )
				continue;

			std::string commonString{ value2 };
			std::transform(
				std::begin( value1 ), std::end( value1 ), std::begin( commonString ), std::begin( commonString ), []( char a, char b ) -> char {
					return ( a == '-' || a != b ) ? '-' : a;
				}
			);
			commonString.erase(
				std::remove_if( std::begin( commonString ), std::end( commonString ), []( char c ) { return c == '-'; } ), std::end( commonString )
			);

			return commonString;
		}

	return "INVALID";
}
