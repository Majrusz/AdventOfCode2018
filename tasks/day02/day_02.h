// Created by Majrusz on 24/07/2021. All rights reserved.

#pragma once

#include <string>
#include <vector>

namespace aoc::day02 {
	void start();

	size_t getChecksum( const std::vector< std::string > &values );

	std::string getCommonString( const std::vector< std::string > &value2 );
}