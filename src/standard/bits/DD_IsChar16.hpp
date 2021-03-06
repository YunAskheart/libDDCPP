//	DDCPP/standard/bits/DD_IsChar16.hpp
#ifndef DD_IS_CHAR_16_HPP_INCLUDED_
#	define DD_IS_CHAR_16_HPP_INCLUDED_ 1



#	if __cplusplus < 201103L
#		error ISO/IEC 14882:2011 or a later version support is required for'DD::IsChar16'.
#	endif



#	include "DD_And.hpp"
#	include "DD_RemoveCV.hpp"



DD_DETAIL_BEGIN_
template <typename ObjectT_>
struct IsChar16_ : FalseType {
};



template <>
struct IsChar16_<char16_t> : TrueType {
};



DD_DETAIL_END_



DD_BEGIN_
template <typename... ObjectsT_>
using IsChar16 = AndType<detail_::IsChar16_<RemoveCVType<ObjectsT_>>...>;



DD_END_



#endif
