//	DDCPP/standard/bits/DD_bind.hpp
#ifndef _DD_BIND_HPP_INCLUDED
#	define DD_BINARY_FIND_HPP_INCLUDED 1



#	if __cplusplus < 201103L
#		error ISO/IEC 14882:2011 or a later version support is required for 'DD::bind'.



#	endif
#	include "DD_IsMemberFunctionPointer.hpp"
#	include "DD_Decay.hpp"
#	include "DD_move.hpp"
#	include "DD_Tuple.hpp"
#	include "DD_Functor.hpp"



#	define _DD_PLACE_HOLDER_BEGIN _DD_BEGIN namespace place_holder {
#	define _DD_PLACE_HOLDER_END } _DD_END

#	define DD_GENERATE_PLACE_HOLDER(_ARG_index) _DD_PLACE_HOLDER_BEGIN static PlaceHolder<_ARG_index> constexpr _##_ARG_index; _DD_PLACE_HOLDER_END



_DD_DETAIL_BEGIN
template <SubscriptType... _subscripts_c>
struct _Indexs {
};



template <SubscriptType _subscript_c, SubscriptType... subscripts_c>
struct _MakeIndexs : _MakeIndexs<_subscript_c - 1, _subscript_c - 1, subscripts_c...> {
};



template <SubscriptType... _subscripts_c>
struct _MakeIndexs<0, _subscripts_c...> {
	using Type = _Indexs<_subscripts_c...>;


};



template <SubscriptType _index_c>
struct _PlaceHolder {
	static constexpr SubscriptType index = _index_c;


};



template <typename _FunctionT>
struct _ResultOf : _ResultOf<decltype(&_FunctionT::operator ())> {
};



template <typename _FunctionT>
struct _ResultOf<_FunctionT*> : _ResultOf<_FunctionT> {
};



template <typename _ResultT, typename... _ArgumentsT>
struct _ResultOf<_ResultT(*)(_ArgumentsT...)> {
	using Type = _ResultT;


};



template <typename _ResultT, typename _ClassT, typename... _ArgumentsT>
struct _ResultOf<_ResultT(_ClassT::*)(_ArgumentsT...)> {
	using Type = _ResultT;


};



template <typename _ResultT, typename _ClassT, typename... _ArgumentsT>
struct _ResultOf<_ResultT(_ClassT::*)(_ArgumentsT...) const> {
	using Type = _ResultT;


};



template <typename _ResultT, typename _ClassT, typename... _ArgumentsT>
struct _ResultOf<_ResultT(_ClassT::*)(_ArgumentsT...) volatile> {
	using Type = _ResultT;


};



template <typename _ResultT, typename _ClassT, typename... _ArgumentsT>
struct _ResultOf<_ResultT(_ClassT::*)(_ArgumentsT...) const volatile> {
	using Type = _ResultT;


};



template <typename _ValueT, typename _TupleT>
struct _ArgumentAt {
	using Type = _ValueT const&;


};



template <SubscriptType _index_c, typename _TupleT>
struct _ArgumentAt<_PlaceHolder<_index_c>, _TupleT> {
	using Type = typename _TupleT::template At<_index_c>;


};



template <typename _ArgumentT, typename... _ArgumentsT>
inline _ArgumentT&& _select(_ArgumentT&& __argument, Tuple<_ArgumentsT...>& _arguments_pack) noexcept {
	return forward<_ArgumentT>(__argument);
}

template <SubscriptType _index_c, typename... _ArgumentsT>
inline auto _select(
	_PlaceHolder<_index_c> __place_holder,
	Tuple<_ArgumentsT...>& _arguments_pack
) noexcept(noexcept(get_value<_index_c>(_arguments_pack))) -> decltype(get_value<_index_c>(_arguments_pack)) {
	return get_value<_index_c>(_arguments_pack);
}



template <ValidityType _is_member_function_c, typename _IndexsT>
struct _BindCall;



template <SubscriptType... _indexs_c>
struct _BindCall<true, _Indexs<0, _indexs_c...>> {
	template <typename _FunctionT_, typename _TupleT1, typename _TupleT2>
	static typename _ResultOf<_FunctionT_>::Type _call(
		_FunctionT_ const& __function_,
		_TupleT1 const& __arguments_1_,
		_TupleT2&& __arguments_2_
	) noexcept(noexcept((forward<
		typename _ArgumentAt<typename _TupleT1::template At<0>, _TupleT2>::Type
	>(_select(get_value<0>(__arguments_1_), __arguments_2_)).*__function_)(
		forward<
			typename _ArgumentAt<typename _TupleT1::template At<_indexs_c>, _TupleT2>::Type
		>(_select(get_value<_indexs_c>(__arguments_1_), __arguments_2_))...
	))) {
		return (forward<
			typename _ArgumentAt<typename _TupleT1::template At<0>, _TupleT2>::Type
		>(_select(get_value<0>(__arguments_1_), __arguments_2_)).*__function_)(
			forward<
				typename _ArgumentAt<typename _TupleT1::template At<_indexs_c>, _TupleT2>::Type
			>(_select(get_value<_indexs_c>(__arguments_1_), __arguments_2_))...
		);
	}


};



template <SubscriptType... _indexs_c>
struct _BindCall<false, _Indexs<_indexs_c...>> {
	template <typename _FunctionT_, typename _TupleT1, typename _TupleT2>
	static typename _ResultOf<_FunctionT_>::Type _call(
		_FunctionT_ const& __function_,
		_TupleT1 const& __arguments_1_,
		_TupleT2&& __arguments_2_
	) noexcept(noexcept(__function_(forward<
		typename _ArgumentAt<typename _TupleT1::template At<_indexs_c>, _TupleT2>::Type
	>(_select(get_value<_indexs_c>(__arguments_1_), __arguments_2_))...))) {
		return __function_(forward<
			typename _ArgumentAt<typename _TupleT1::template At<_indexs_c>, _TupleT2>::Type
		>(_select(get_value<_indexs_c>(__arguments_1_), __arguments_2_))...);
	}


};



template <typename _FunctionT, typename... _ArgumentsT>
struct _BindFunctor : Functor<typename _ResultOf<_FunctionT>::Type, _ArgumentsT...> {
	public:
	using ThisType = _BindFunctor<_FunctionT, _ArgumentsT...>;
	using FunctionType = _FunctionT;
	using ArgumentsList = TypeList<_ArgumentsT...>;

	public:
	using ResultType = typename _ResultOf<_FunctionT>::Type;
	using ArgumentsPack = Tuple<_ArgumentsT...>;


	private:
	FunctionType _m_function;
	ArgumentsPack _m_arguments;


	public:
	template <typename _FunctionT_, typename... _ArgumentsT_>
	_BindFunctor(_FunctionT_&& __function_, _ArgumentsT_&&... __arguments_) noexcept(
		noexcept(FunctionType(forward<_FunctionT_>(__function_))) &&
		noexcept(ArgumentsPack(forward<_ArgumentsT_>(__arguments_)...))
	) : _m_function(forward<_FunctionT_>(__function_)), _m_arguments(forward<_ArgumentsT_>(__arguments_)...) {
	}


	public:
	template <typename... _ArgumentsT_>
	ResultType operator ()(_ArgumentsT_&&... __arguments_) noexcept(
		noexcept(_BindCall<
			IsMemberFunctionPointer<FunctionType>::value,
			typename _MakeIndexs<ArgumentsPack::length>::Type
		>::_call(
			_m_function,
			_m_arguments,
			make_tuple(forward<_ArgumentsT_>(__arguments_)...)
		))
	) {
		return _BindCall<
			IsMemberFunctionPointer<FunctionType>::value,
			typename _MakeIndexs<ArgumentsPack::length>::Type
		>::_call(
			_m_function,
			_m_arguments,
			make_tuple(forward<_ArgumentsT_>(__arguments_)...)
		);
	}


};







_DD_DETAIL_END



_DD_PLACE_HOLDER_BEGIN
template <SubscriptType _index_c>
using PlaceHolder = ::DD::_detail::_PlaceHolder<_index_c>;



_DD_PLACE_HOLDER_END



DD_GENERATE_PLACE_HOLDER(0)
DD_GENERATE_PLACE_HOLDER(1)
DD_GENERATE_PLACE_HOLDER(2)
DD_GENERATE_PLACE_HOLDER(3)
DD_GENERATE_PLACE_HOLDER(4)
DD_GENERATE_PLACE_HOLDER(5)
DD_GENERATE_PLACE_HOLDER(6)
DD_GENERATE_PLACE_HOLDER(7)
DD_GENERATE_PLACE_HOLDER(8)
DD_GENERATE_PLACE_HOLDER(9)
DD_GENERATE_PLACE_HOLDER(10)
DD_GENERATE_PLACE_HOLDER(11)
DD_GENERATE_PLACE_HOLDER(12)
DD_GENERATE_PLACE_HOLDER(13)
DD_GENERATE_PLACE_HOLDER(14)
DD_GENERATE_PLACE_HOLDER(15)
DD_GENERATE_PLACE_HOLDER(16)
DD_GENERATE_PLACE_HOLDER(17)
DD_GENERATE_PLACE_HOLDER(18)
DD_GENERATE_PLACE_HOLDER(19)
DD_GENERATE_PLACE_HOLDER(20)
DD_GENERATE_PLACE_HOLDER(21)
DD_GENERATE_PLACE_HOLDER(22)
DD_GENERATE_PLACE_HOLDER(23)
DD_GENERATE_PLACE_HOLDER(24)
DD_GENERATE_PLACE_HOLDER(25)
DD_GENERATE_PLACE_HOLDER(26)
DD_GENERATE_PLACE_HOLDER(27)
DD_GENERATE_PLACE_HOLDER(28)
DD_GENERATE_PLACE_HOLDER(29)
DD_GENERATE_PLACE_HOLDER(30)
DD_GENERATE_PLACE_HOLDER(31)



_DD_BEGIN
template <typename _FunctionT, typename... _ArgumentsT>
inline _detail::_BindFunctor<DecayType<_FunctionT>, DecayType<_ArgumentsT>...> bind(
	_FunctionT&& __function,
	_ArgumentsT&&... __arguments
) noexcept(noexcept(
	_detail::_BindFunctor<DecayType<_FunctionT>, DecayType<_ArgumentsT>...>(
		forward<_FunctionT>(__function),
		forward<_ArgumentsT>(__arguments)...
	)
)) {
	return _detail::_BindFunctor<DecayType<_FunctionT>, DecayType<_ArgumentsT>...>(
		forward<_FunctionT>(__function),
		forward<_ArgumentsT>(__arguments)...
	);
}



_DD_END



#	undef _DD_PLACE_HOLDER_BEGIN
#	undef _DD_PLACE_HOLDER_END



#endif
