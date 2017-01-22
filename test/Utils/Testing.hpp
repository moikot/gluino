// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef TESTING
#define TESTING

#if defined(_MSC_VER)
	#pragma warning( push )
	// Disabling warning C4515: 'namespace': namespace uses itself
	#pragma warning( disable : 4515)
	// Disabling warning C4100 : 'method' : unreferenced formal parameter
	#pragma warning( disable : 4100)
#endif

#if defined(__clang__)
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Winconsistent-missing-override"
#endif

#include "catch.hpp"
#include "fakeit.hpp"

#if defined(__clang__)
	#pragma clang diagnostic pop
#endif

#if defined(_MSC_VER)
	#pragma warning( pop )
#endif

#endif /* end of include guard: TESTING */
