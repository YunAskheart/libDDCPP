//	DDCPP/standard/bits/DD_IsEnum.hpp
#ifndef DD_IS_ENUM_HPP_INCLUDED_
#	define DD_IS_ENUM_HPP_INCLUDED_ 1



#	if __cplusplus < 201103L
#		error ISO/IEC 14882:2011 or a later version support is required for'DD::IsEnum'.



#	endif
#	include <type_traits>

#	include "DD_And.hpp"



DD_BEGIN_
template <typename... ObjectsT_>
using IsEnum = AndType<StdBoolConstant<std::is_enum<ObjectsT_>>...>;



DD_END_



#endif
