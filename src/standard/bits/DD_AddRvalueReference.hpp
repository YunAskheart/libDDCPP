//	DDCPP/standard/bits/DD_AddRvalueReference.hpp
#ifndef DD_ADD_RVALUE_REFERENCE_HPP_INCLUDED_
#	define DD_ADD_RVALUE_REFERENCE_HPP_INCLUDED_ 1



#	if __cplusplus < 201103L
#		error ISO/IEC 14882:2011 or a later version support is required for 'DD::AddRvalueReference'.



#	endif
#	include <type_traits>
#	include "DD_IsReferable.hpp"



DD_DETAIL_BEGIN_
template <typename ObjectT_, ValidityType is_referenceable_c_>
struct AddRvalueReference_ {
	DD_ALIAS(Type, ObjectT_);


};



template <typename ObjectT_>
struct AddRvalueReference_<ObjectT_, true> {
	DD_ALIAS(Type, ObjectT_&&);


};



DD_DETAIL_END_



DD_BEGIN_
template <typename ObjectT_>
struct AddRvalueReference {
	DD_ALIAS(Type, typename detail_::AddRvalueReference_<ObjectT_ DD_COMMA IsReferable<ObjectT_>::value>::Type);


};



DD_TRAIT_MODIFIER(AddRvalueReference)



DD_END_



#endif
