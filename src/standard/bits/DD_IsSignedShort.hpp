//	DDCPP/standard/bits/DD_IsSignedShort.hpp
#ifndef _DD_IS_SIGNED_SHORT_HPP_INCLUDED
#	define _DD_IS_SIGNED_SHORT_HPP_INCLUDED 1



#	if __cplusplus >= 201103L
#		include "DD_And.hpp"
#	else
#		include "DD_IntegralConstant.hpp"
#	endif
#	include "DD_RemoveCV.hpp"



DD_DETAIL_BEGIN
template <typename _ObjectT>
struct _IsSignedShort : FalseType {
};



template <>
struct _IsSignedShort<signed short> : TrueType {
};



DD_DETAIL_END



DD_BEGIN
#	if __cplusplus >= 201103L
template <typename... _ObjectsT>
using IsSignedShort = AndType<detail::_IsSignedShort<RemoveCVType<_ObjectsT>>...>;
#	else
template <typename _ObjectT>
struct IsSignedShort : detail::_IsSignedShort<typename RemoveCV<_ObjectT>::Type> {
};
#	endif



DD_END



#endif
