//	DDCPP/standard/bits/DD_Pool.hpp
#ifndef _DD_POOL_HPP_INCLUDED
#	define _DD_POOL_HPP_INCLUDED 1



#	include "DD_FreeList.hpp"



_DD_BEGIN
template <ValidityType _is_thread_safe_c>
class Pool {



};



template <>
class Pool<true> {
};



_DD_END



#endif
