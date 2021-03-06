//	DDCPP/standard/bits/DD_IsNoexceptMoveConstructible.hpp
#ifndef DD_IS_NOEXCEPT_MOVE_CONSTRUCTIBLE_HPP_INCLUDED_
#	define DD_IS_NOEXCEPT_MOVE_CONSTRUCTIBLE_HPP_INCLUDED_ 1


#	if __cplusplus < 201103L
#		error ISO/IEC 14882:2011 or a later version support is required for 'DD::IsNoexceptMoveConstructible'.



#	endif
#	include <type_traits>
#	include "DD_Or.hpp"
#	include "DD_And.hpp"



DD_DETAIL_BEGIN_
template <typename ObjectT_>
struct IsNoexceptMoveConstructible_ : OrType<StdBoolConstant<std::is_nothrow_move_constructible<ObjectT_>>> {
};



DD_DETAIL_END_



DD_BEGIN_
template <typename... ObjectsT_>
using IsNoexceptMoveConstructible = AndType<detail_::IsNoexceptMoveConstructible_<ObjectsT_>...>;



DD_END_



#endif
