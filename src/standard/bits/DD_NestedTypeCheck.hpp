//	standard/bits/DD_NestedTypeCheck.hpp
#ifndef _DD_NESTED_TYPE_CHECK_HPP_INCLUDED
#	define _DD_NESTED_TYPE_CHECK_HPP_INCLUDED 1



#	include "DD_Nil.hpp"
#	include "DD_IntegralConstant.hpp"
#	include "DD_meta_definitions.hpp"
#	include "DD_SizeTrait.hpp"
#	include "DD_Matcher.hpp"



#	if __cplusplus >= 201103L
#		define DD_NESTED_TYPE_CHECK(_ARG_Checker, ...)\
			DD_MACRO_DETAIL_BEGIN\
			template <typename _MACRO_ObjectT>\
			struct _##_ARG_Checker {\
				private:\
				template <typename _MACRO_ObjectT_>\
				static ValidityType constexpr _match(Matcher<typename _MACRO_ObjectT_::__VA_ARGS__>*) noexcept(true) {\
					return true;\
				}\
				\
				private:\
				template <typename _MACRO_ObjectT_>\
				static ValidityType constexpr _match(...) noexcept(true) {\
					return false;\
				}\
				\
				\
				public:\
				static ValidityType constexpr value = _match<_MACRO_ObjectT>(nil_pointer);\
				\
				\
			};\
			\
			\
			\
			DD_MACRO_DETAIL_END\
			\
			\
			\
			template <typename _MACRO_ObjectT>\
			using _ARG_Checker = BoolConstant<_MACRO_detail::_##_ARG_Checker<_MACRO_ObjectT>::value>;



#		define DD_NESTED_TYPE_TRAIT(_ARG_Checker, _ARG_Target, ...)\
			template <typename _MACRO_ObjectT>\
			struct _ARG_Checker {\
				private:\
				template <typename _MACRO_ObjectT_>\
				static typename _MACRO_ObjectT_::_ARG_Target _match(Matcher<typename _MACRO_ObjectT_::_ARG_Target>*) noexcept(true);\
				\
				private:\
				template <typename _MACRO_ObjectT_>\
				static __VA_ARGS__ _match(...) noexcept(true);\
				\
				\
				public:\
				using Type = decltype(_ARG_Checker<_MACRO_ObjectT>::_match<_MACRO_ObjectT>(nil_pointer));\
				\
				\
			};
#	else
#		define DD_NESTED_TYPE_CHECK(_ARG_Checker, _ARG_Target)\
			DD_MACRO_DETAIL_BEGIN\
			template <typename _MACRO_ObjectT>\
			struct _##_ARG_Checker {\
				template <typename _MACRO_ObjectT_>\
				static SizeTrait<1> _match(Matcher<typename _MACRO_ObjectT_::_ARG_Target>*);\
				\
				template <typename _MACRO_ObjectT_>\
				static SizeTrait<2> _match(...);\
				\
				\
				static ValidityType const value = sizeof(_match<_MACRO_ObjectT>(0)) == sizeof(SizeTrait<1>);\
				\
				\
			};\
			\
			\
			\
			DD_MACRO_DETAIL_END\
			\
			\
			\
			template <typename _MACRO_ObjectT>\
			struct _ARG_Checker : BoolConstant<_MACRO_detail::_##_ARG_Checker<_MACRO_ObjectT>::value> {\
			};



#		define DD_NESTED_TYPE_TRAIT(_ARG_Checker, _ARG_Target, _ARG_Default)\
			DD_MACRO_DETAIL_BEGIN\
			DD_NESTED_TYPE_CHECK(_CHECK_##_ARG_Checker, _ARG_Target)\
			\
			\
			\
			template <typename _MACRO_ObjectT, ValidityType _MACRO_has_target_c>\
			struct _##_ARG_Checker {\
				typedef _ARG_Default Type;\
				\
				\
			};\
			\
			\
			\
			template <typename _MACRO_ObjectT>\
			struct _##_ARG_Checker<_MACRO_ObjectT, true> {\
				typedef typename _MACRO_ObjectT::_ARG_Target Type;\
				\
				\
			};\
			\
			\
			\
			DD_MACRO_DETAIL_END\
			\
			\
			\
			template <typename _MACRO_ObjectT>\
			struct _ARG_Checker {\
				typedef typename _MACRO_detail::_##_ARG_Checker<\
					_MACRO_ObjectT,\
					_MACRO_detail::_CHECK_##_ARG_Checker<_MACRO_ObjectT>::value\
				>::Type Type;\
				\
				\
			};
#	endif



#endif