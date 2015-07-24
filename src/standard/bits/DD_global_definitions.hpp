//	standard/bits/DD_global_definitions.hpp
#ifndef _DD_GLOBAL_DEFINITIONS_HPP_INCLUDED
#	define _DD_GLOBAL_DEFINITIONS_HPP_INCLUDED 1



#	include <cstddef>



#	define _DDCPP 1000

#	define DDCPP_ON 1
#	define DDCPP_OFF 0

#	if !defined(DDCPP_DEFAULT_WARNING_OPTION)
#		define DDCPP_DEFAULT_WARNING_OPTION DD_OFF
#	endif

#	if !defined(DDCPP_VERSION_WARNING)
#		define DDCPP_VERSION_WARNING DDCPP_DEFAULT_WARNING_OPTION
#	endif

#	if !defined(DDCPP_IMPERFECT_REALIZATION_WARNING)
#		define DDCPP_IMPERFECT_REALIZATION_WARNING DDCPP_DEFAULT_WARNING_OPTION
#	endif

#	if !defined(DDCPP_DEPRECATION_WARNING)
#		define DDCPP_DEPRECATION_WARNING DDCPP_DEFAULT_WARNING_OPTION
#	endif

#	if !defined(DDCPP_COMPAT_DEPRECATION)
#		define DDCPP_COMPAT_DEPRECATION DDCPP_OFF
#	endif

#	if !defined(DDCPP_COMPAT_STL)
#		define DDCPP_COMPAT_STL DDCPP_ON
#	endif

#	if !defined(__cplusplus)
#		error Compiler should support ISO C++.
#	elif __cplusplus < 201103L && DDCPP_VERSION_WARNING
#		warning ISO/IEC 14882:2011 or a later version support is recommended. Define 'DDCPP_VERSION_WARNING' as 'DDCPP_OFF' to ignore this warning.
#	endif

#	define DD_BEGIN namespace DD {
#	define DD_END }
#	define DD_DETAIL_BEGIN DD_BEGIN namespace detail {
#	define DD_DETAIL_END } DD_END

#	define DD_TO_STRING(literal) #literal

#	define DD_BACKUP_CODE 0

#	include "DD_compatibility_definitions.hpp"



DD_BEGIN
DD_ALIAS(ProcessType, void)

DD_ALIAS(ValidityType, bool)
DD_ALIAS(CheckType, bool)

DD_ALIAS(SizeType, std::size_t)
DD_ALIAS(LengthType, SizeType)
DD_ALIAS(QuantityType, SizeType)

DD_ALIAS(PointerDifferenceType, std::ptrdiff_t)
DD_ALIAS(DifferenceType, PointerDifferenceType)
DD_ALIAS(CounterType, PointerDifferenceType)
DD_ALIAS(SubscriptType, PointerDifferenceType)

#	if __cplusplus >= 201103L
template <typename ValueT>
using ReferenceType = ValueT&;

template <typename ValueT, LengthType LengthT>
using ArrayType = ValueT[LengthT];

template <typename ValueT>
using PointerType = ValueT*;

#	endif
DD_ALIAS(GlobalPointerType, void*)

DD_ALIAS(CStringType, char*)

DD_ALIAS(CStringConstType, char const*)
DD_ALIAS(PromptType, CStringConstType)



#	if __cplusplus >= 201103L
enum class Direction {
	unknown,
	forward,
	backward
	
};
#	else
struct Direction {
	public:
	static Direction const unknown;
	static Direction const forward;
	static Direction const backward;
	
	
	public:
	int _m_value;
	
	
};



inline ValidityType operator ==(Direction _direction_1, Direction _direction_2) {
	return _direction_1._m_value == _direction_2._m_value;
}


inline ValidityType operator !=(Direction _direction_1, Direction _direction_2) {
	return !(_direction_1._m_value == _direction_2._m_value);
}



Direction const Direction::unknown = {0};
Direction const Direction::forward = {1};
Direction const Direction::backward = {2};
#	endif



#	if __cplusplus >= 201103L
LengthType constexpr operator ""_DD_Length(unsigned long long length) {
	return length;
}



CounterType constexpr operator ""_DD_Counter(unsigned long long counter) {
	return counter;
}



#	endif
DD_END



#endif