// Created by Majrusz on 25/07/2021. All rights reserved.

#pragma once

#include <iostream>
#include <vector>

namespace aoc::day04 {
	struct Record {
		enum class State {
			BEGINS_SHIFT, FALLS_ASLEEP, WAKES_UP
		} state;
		size_t guardID;
		int year, month, day, hour, minute;
	};

	void start();

	size_t getTask1Result( std::vector< Record > records );

	size_t getGuardIDWithMostAsleepMinutes( const std::vector< Record > &records );

	int getMostAsleepMinute( const std::vector< Record > &records, size_t guardID );
}

namespace std {
	std::istream &operator>>( std::istream &stream, aoc::day04::Record &record );
}