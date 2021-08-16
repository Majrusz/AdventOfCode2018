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
		size_t year, month, day, hour, minute;
	};

	void start();

	size_t getTask1Result( const std::vector< Record > &values );
}

namespace std {
	std::istream &operator>>( std::istream &stream, aoc::day04::Record &record );
}