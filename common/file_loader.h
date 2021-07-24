// Created by Majrusz on 24/07/2021. All rights reserved.

#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace aoc {
	template< typename Type >
	std::vector< Type > loadFile( const std::string &filename );
}

#include "file_loader.inl"