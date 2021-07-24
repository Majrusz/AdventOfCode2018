// Created by Majrusz on 24/07/2021. All rights reserved.

#include "day_03.h"

#include <algorithm>
#include <numeric>
#include <sstream>

#include "common/file_loader.h"
#include "common/zipper.h"

void aoc::day03::start() {
	std::vector< Data > input{ loadFile< Data >( "day03/input.txt" ) };

	std::cout << "Amount of overlapping elements: " << getAmountOfOverlappingElements( input ) << std::endl;
	std::cout << "ID of element not overlapping with others: " << getIDOfNotOverlappingElement( input ) << std::endl;
}

size_t aoc::day03::getAmountOfOverlappingElements( const std::vector< Data > &values ) {
	std::vector< std::string > elements{ getGrid( values ) };

	size_t sum{};
	std::for_each(
		std::begin( elements ), std::end( elements ), [ &sum ]( const std::string &line ) {
			sum += std::count_if( std::begin( line ), std::end( line ), []( char c ) { return c == 'X'; } );
		}
	);

	return sum;
}

size_t aoc::day03::getIDOfNotOverlappingElement( const std::vector< Data > &values ) {
	std::vector< std::string > elements{ getGrid( values ) };

	for( auto &[id, x, y, w, h] : values )
		if( std::all_of(
			std::begin( elements ) + x, std::begin( elements ) + x + w, [ & ]( const std::string &line ) {
				return std::all_of(
					std::begin( line ) + y, std::begin( line ) + y + h, []( char c ) {
						return c == '1';
					}
				);
			}
		) )
			return id;

	return 0;
}

std::vector< std::string > aoc::day03::getGrid( const std::vector< Data > &values ) {
	size_t gridWidth{}, gridHeight{};
	std::for_each(
		std::begin( values ), std::end( values ), [ & ]( const Data &data ) {
			if( size_t width{ data.x + data.w }; width > gridHeight )
				gridWidth = width;
			if( size_t height{ data.y + data.h }; height > gridHeight )
				gridHeight = height;
		}
	);

	std::vector< std::string > elements{ gridWidth, std::string( gridHeight, '.' ) };
	for( auto &[id, x, y, w, h] : values )
		for( int i = 0; i < w; ++i )
			for( int j = 0; j < h; ++j )
				elements[ x + i ][ y + j ] = elements[ x + i ][ y + j ] == '.' ? '1' : 'X';

	return elements;
}

std::istream &std::operator>>( std::istream &stream, aoc::day03::Data &data ) {
	std::string input;
	std::getline( stream, input );

	size_t index;
	while( ( index = input.find_first_not_of( "1234567890 " ) ) != std::string::npos )
		input.replace( index, 1, " " );

	std::stringstream{ input } >> data.id >> data.x >> data.y >> data.w >> data.h;

	return stream;
}
