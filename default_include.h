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

#include <boost/lexical_cast.hpp>
const auto itoa = [](int i){ return boost::lexical_cast<string>(i).c_str(); };

#endif
