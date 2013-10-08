#ifndef __DEFAULT__INCLUDE__
#define __DEFAULT__INCLUDE__

#include <string>
using std::string;

#include <stdexcept>
struct ConnectionError : std::runtime_error {
	ConnectionError(string s) : std::runtime_error(s) { };
};

#include <memory>
using std::move;
using std::unique_ptr;

#include <tuple>
using std::pair;
using std::make_pair;

#endif
