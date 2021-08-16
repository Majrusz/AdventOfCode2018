// Created by Majrusz on 25/07/2021. All rights reserved.

#include "day_04.h"

#include <algorithm>
#include <numeric>
#include <sstream>

#include "common/file_loader.h"
#include "common/zipper.h"

void aoc::day04::start() {
	std::vector< Record > input{ loadFile< Record >( "day04/input_test.txt" ) };
}

size_t aoc::day04::getTask1Result( const std::vector< Record > &values ) {
	return 0;
}

std::istream &std::operator>>( std::istream &stream, aoc::day04::Record &record ) {
	std::string input;
	std::getline( stream, input );

	std::string dateFormat{ input.substr( 1, input.find_first_of( ']' ) ) };
	size_t index;
	while( ( index = dateFormat.find_first_not_of( "-:" ) ) != std::string::npos )
		dateFormat.replace( index, 1, " " );

	std::stringstream{ dateFormat } >> record.year >> record.month >> record.day >> record.hour >> record.minute;

	return stream;
}
