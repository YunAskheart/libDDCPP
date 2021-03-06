//	DDCPP/standard/bits/DD_generate.hpp
#ifndef DD_GENERATE_HPP_INCLUDED_
#	define DD_GENERATE_HPP_INCLUDED_ 1



#	include "DD_global_definitions.hpp"



DD_BEGIN_
template <typename UndirectionalIteratorT_, typename Generator_>
ProcessType generate(
	UndirectionalIteratorT_ begin__,
	UndirectionalIteratorT_ const& end__,
	Generator_ const& generator__
) DD_NOEXCEPT_AS(*++begin__ = generator__() DD_COMMA begin__ != end__) {
	for (; begin__ != end__; ++begin__) {
		*begin__ = generator__();
	}
}



DD_END_



#endif
