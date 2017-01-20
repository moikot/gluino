// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef TESTING
#define TESTING

#if (_MSC_VER)
	#pragma warning( push )
	// Disabling warning C4515: 'namespace': namespace uses itself
	#pragma warning( disable : 4515)
	// Disabling warning C4100 : 'method' : unreferenced formal parameter
	#pragma warning( disable : 4100)
#endif

#include "catch.hpp"
#include "fakeit.hpp"

#if (_MSC_VER)
	#pragma warning( pop ) 
#endif

#endif /* end of include guard: TESTING */
