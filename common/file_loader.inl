// Created by Majrusz on 24/07/2021. All rights reserved.

#include "file_loader.h"

template< typename Type >
std::vector< Type > aoc::loadFile( const std::string &filename ) {
	std::ifstream file{ "../tasks/" + filename };
	std::vector< Type > objects{};

	if( !file )
		throw std::invalid_argument( "Failed to open '" + filename + "' file!" );

	Type object{};
	while( file >> object )
		objects.push_back( object );

	file.close();

	return objects;
}