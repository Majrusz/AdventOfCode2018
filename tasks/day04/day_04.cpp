// Created by Majrusz on 25/07/2021. All rights reserved.

#include "day_04.h"

#include <algorithm>
#include <map>
#include <set>
#include <sstream>

#include "common/file_loader.h"
#include "common/zipper.h"

void aoc::day04::start() {
	std::vector< Record > records{ loadFile< Record >( "day04/input.txt" ) };

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

	std::cout << "Task1 result: " << getTask1Result( records ) << std::endl;
	std::cout << "Task2 result: " << getTask2Result( records ) << std::endl;
}

size_t aoc::day04::getTask1Result( const std::vector< Record > &records ) {
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

std::map< int, size_t > aoc::day04::getMostAsleepMinutes( const std::vector< Record > &records, size_t guardID ) {
	std::map< int, size_t > minuteOccurrences{};
	auto increaseIndex = [&minuteOccurrences]( int index ){
		if( minuteOccurrences.count( index ) > 0 )
			++minuteOccurrences[ index ];
		else
			minuteOccurrences[ index ] = 1;
	};

	const Record *previousRecord{};
	std::for_each( std::begin( records ), std::end( records ), [&]( const Record &record ){
		if( record.guardID != guardID )
			return;

		if( record.state == Record::State::WAKES_UP ) {
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

	return minuteOccurrences;
}

int aoc::day04::getMostAsleepMinute( const std::vector< Record > &records, size_t guardID ) {
	auto minuteOccurrences{ getMostAsleepMinutes( records, guardID ) };

	return std::max_element( std::begin( minuteOccurrences ), std::end( minuteOccurrences ), []( const auto &a, const auto &b ){
		return a.second < b.second;
	} )->first;
}

size_t aoc::day04::getTask2Result( const std::vector< Record > &records ) {
	std::set< size_t > guardIDs;
	std::for_each( std::begin( records ), std::end( records ), [&guardIDs]( const Record &record ){
		guardIDs.insert( record.guardID );
	} );

	int mostAsleepMinute{}, mostOccurrences{};
	size_t mostAsleepGuardID{};
	std::for_each( std::begin( records ), std::end( records ), [&]( size_t guardID ){
		auto minuteOccurrences{ getMostAsleepMinutes( records, guardID ) };
		auto mostAsleepMinutePair{ std::max_element( std::begin( minuteOccurrences ), std::end( minuteOccurrences ), []( const auto &a, const auto &b ){
			return a.second < b.second;
		} ) };

		if( mostAsleepMinutePair->second > mostOccurrences ) {
			mostAsleepMinute = mostAsleepMinutePair->first;
			mostOccurrences = mostAsleepMinutePair->second;
			mostAsleepGuardID = guardID;
		}
	} );

	return mostAsleepMinute * mostAsleepGuardID;
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
