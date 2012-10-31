/*

We don't want BOOST_USE_WINDOWS_H set globally for all Boost includes,
as that will generate some naming conflicts with some of our enum values and types.
If we wait until just before including Boost Thread, and this is the last include,
then things should work okay.

*/

#ifdef POLLUTE_GLOBAL_NAMESPACE_WITH_WINDOWS_H
#define BOOST_USE_WINDOWS_H
#endif

#include <boost/thread.hpp>
