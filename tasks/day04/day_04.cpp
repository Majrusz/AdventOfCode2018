// Created by Majrusz on 25/07/2021. All rights reserved.

#include "day_04.h"

#include <algorithm>
#include <map>
#include <sstream>

#include "common/file_loader.h"
#include "common/zipper.h"

void aoc::day04::start() {
	std::vector< Record > input{ loadFile< Record >( "day04/input.txt" ) };

	std::cout << "Task1 result: " << getTask1Result( input ) << std::endl;
}

size_t aoc::day04::getTask1Result( std::vector< Record > records ) {
	std::sort( std::begin( records ), std::end( records ), []( const Record &a, const Record &b ){
		return a.year < b.year || a.year == b.year && ( a.month < b.month || a.month == b.month && ( a.day < b.day || a.day == b.day && ( a.hour < b.hour || a.hour == b.hour && a.minute < b.minute ) ) );
	} );

	size_t currentGuardID;
	std::for_each( std::begin( records ), std::end( records ), [&currentGuardID]( Record &record ){
		if( record.state == Record::State::BEGINS_SHIFT )
			currentGuardID = record.guardID;
		else
			record.guardID = currentGuardID;
	} );

	size_t guardID{ getGuardIDWithMostAsleepMinutes( records ) };

	return getMostAsleepMinute( records, guardID ) * guardID;
}

size_t aoc::day04::getGuardIDWithMostAsleepMinutes( const std::vector< Record > &records ) {
	std::map< size_t, size_t > minutes;

	const Record *previousRecord{};
	std::for_each( std::begin( records ), std::end( records ), [&previousRecord, &minutes]( const Record &record ){
		if( record.state == Record::State::WAKES_UP )
			minutes[ record.guardID ] += record.minute - previousRecord->minute + ( record.hour - previousRecord->hour )*60 + ( record.day - previousRecord->day )*60*24;
		previousRecord = &record;
	} );

	return std::max_element( std::begin( minutes ), std::end( minutes ), []( const auto &a, const auto &b ){
		return a.second < b.second;
	} )->first;
}

int aoc::day04::getMostAsleepMinute( const std::vector< Record > &records, size_t guardID ) {
	std::map< int, size_t > minuteOccurrences{};
	static auto increaseIndex = [&minuteOccurrences]( int index ){
		if( minuteOccurrences.count( index ) > 0 )
			++minuteOccurrences[ index ];
		else
			minuteOccurrences[ index ] = 1;
	};

	const Record *previousRecord{};
	std::for_each( std::begin( records ), std::end( records ), [&guardID, &previousRecord]( const Record &record ){
		if( record.state == Record::State::WAKES_UP && record.guardID == guardID ) {
			if( record.minute > previousRecord->minute ) {
				for( int minute{ previousRecord->minute }; minute < record.minute; ++minute )
					increaseIndex( minute );
			} else {
				for( int minute{ 0 }; minute < record.minute; ++minute )
					increaseIndex( minute );
				for( int minute{ previousRecord->minute }; minute <= 60; ++minute )
					increaseIndex( minute );
			}
		}

		previousRecord = &record;
	} );

	return std::max_element( std::begin( minuteOccurrences ), std::end( minuteOccurrences ), []( const auto &a, const auto &b ){
		return a.second < b.second;
	} )->first;
}

std::istream &std::operator>>( std::istream &stream, aoc::day04::Record &record ) {
	std::string input;
	std::getline( stream, input );

	if( !input.empty() ) {
		size_t dateEndIndex{ input.find_first_of( ']' ) };
		std::string dateFormat{ input.substr( 1, dateEndIndex - 1 ) };
		size_t index;
		while( ( index = dateFormat.find_first_of( "-:" ) ) != std::string::npos )
			dateFormat.replace( index, 1, " " );

		std::stringstream{ dateFormat } >> record.year >> record.month >> record.day >> record.hour >> record.minute;

		if( std::string information{ input.substr( dateEndIndex + 2 ) }; information == "falls asleep" ) {
			record.state = aoc::day04::Record::State::FALLS_ASLEEP;
		} else if( information == "wakes up" ) {
			record.state = aoc::day04::Record::State::WAKES_UP;
		} else {
			record.state = aoc::day04::Record::State::BEGINS_SHIFT;
			information[ information.find( '#' ) ] = ' ';
			std::stringstream{ information } >> input >> record.guardID;
		}
	}

	return stream;
}
