
/*
*	COPYRIGHT: Tynes
*	Github: https://github.com/tynes0/Naz-Operator-Wrapper
*/

#pragma once

#include <type_traits>

#if _HAS_CXX17
#define _NAZ_INLINE inline
#else // _HAS_CXX17
#define _NAZ_INLINE 
#endif // _HAS_CXX17

namespace naz
{
	namespace detail
	{
		template <class _Fun>
		struct operator_wrapper
		{
			_Fun fun;
		};

		template <class _Fun, class _Ty>
		struct operator_wrapper_lhs
		{
			_Fun fun;
			_Ty val;
		};

		template <class _Fun, class _Ty>
		inline constexpr operator_wrapper_lhs<_Fun, _Ty&> operator<=(_Ty & left, const operator_wrapper<_Fun>&right)
		{
			return operator_wrapper_lhs<_Fun, _Ty&> { right.fun, left };
		}

		template <class _Fun, class _Ty>
		inline constexpr operator_wrapper_lhs<_Fun, _Ty> operator<(_Ty left, const operator_wrapper<_Fun>&right)
		{
			return operator_wrapper_lhs<_Fun, _Ty> { right.fun, left };
		}

		template <class _Fun, class _Ty1, class _Ty2>
		inline constexpr auto operator>=(const operator_wrapper_lhs<_Fun, _Ty1&>&left, _Ty2 & right)
			-> decltype(left.fun(std::declval<_Ty1&>(), std::declval<_Ty2&>()))
		{
			return left.fun(left.val, right);
		}

		template <class _Fun, class _Ty1, class _Ty2>
		inline constexpr auto operator>=(const operator_wrapper_lhs<_Fun, _Ty1>&left, _Ty2 & right)
			-> decltype(left.fun(std::declval<_Ty1>(), std::declval<_Ty2&>()))
		{
			return left.fun(left.val, right);
		}

		template <class _Fun, class _Ty1, class _Ty2>
		inline constexpr auto operator>(const operator_wrapper_lhs<_Fun, _Ty1>&left, _Ty2 right)
			-> decltype(left.fun(std::declval<_Ty1>(), std::declval<_Ty2>()))
		{
			return left.fun(left.val, right);
		}

		template <class _Fun, class _Ty1, class _Ty2>
		inline constexpr auto operator>(const operator_wrapper_lhs<_Fun, _Ty1&>&left, _Ty2 right)
			-> decltype(left.fun(std::declval<_Ty1>(), std::declval<_Ty2>()))
		{
			return left.fun(left.val, right);
		}
	}

	template <class _Fun>
	inline constexpr detail::operator_wrapper<_Fun> make_operator(_Fun fun)
	{
		return detail::operator_wrapper<_Fun> { fun };
	}
#define create_operator(operator_name, return_type, left_type, right_type) return_type __impl_of_ ## operator_name (left_type left, right_type right); _NAZ_INLINE constexpr auto operator_name = naz::make_operator(__impl_of_ ## operator_name); return_type __impl_of_ ## operator_name (left_type left, right_type right)
}
