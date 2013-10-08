#ifndef __DEFAULT__INCLUDE__
#define __DEFAULT__INCLUDE__

#include <string>
using std::string;

#include <stdexcept>
struct ConnectionError : std::runtime_error {
	using runtime_error::runtime_error;
};

#include <memory>
using std::move;
using std::unique_ptr;

#include <boost/lexical_cast.hpp>
inline const char* itoa(int i) {
	return boost::lexical_cast<string>(i).c_str();
};

#endif
