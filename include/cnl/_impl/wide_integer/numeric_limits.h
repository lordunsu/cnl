
//          Copyright John McFarlane 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(CNL_IMPL_WIDE_INTEGER_NUMERIC_LIMITS_H)
#define CNL_IMPL_WIDE_INTEGER_NUMERIC_LIMITS_H

#include "../../limits.h"
#include "../limits/lowest.h"
#include "from_rep.h"
#include "type.h"

/// compositional numeric library
namespace cnl {
    ////////////////////////////////////////////////////////////////////////////////
    // cnl::numeric_limits specialization for overflow_integer

    template<int Digits, typename Narrowest>
    struct numeric_limits<_impl::wide_integer<Digits, Narrowest, _impl::enable_if_not_multiword_t<Digits, Narrowest>>>
            : numeric_limits<typename _impl::wide_integer<Digits, Narrowest>::rep> {
        static constexpr bool is_integer = true;
        // wide_integer-specific helpers
        using _narrowest_numeric_limits = numeric_limits<Narrowest>;
        using _value_type = _impl::wide_integer<Digits, Narrowest>;
        using _rep = typename _value_type::rep;
        using _rep_numeric_limits = numeric_limits<_rep>;

        static constexpr _rep _rep_max() noexcept
        {
            return static_cast<_rep>(_rep_numeric_limits::max() >> (_rep_numeric_limits::digits-digits));
        }

        // standard members
        static constexpr int digits = Digits;

        static constexpr _value_type min() noexcept
        {
            return _impl::from_rep<_value_type>(1);
        }

        static constexpr _value_type max() noexcept
        {
            return _impl::from_rep<_value_type>(_rep_max());
        }

        static constexpr _value_type lowest() noexcept
        {
            return _impl::lowest<_rep, _narrowest_numeric_limits::is_signed>()(_rep_max());
        }
    };

    template<int Digits, typename Narrowest>
    struct numeric_limits<_impl::wide_integer<Digits, Narrowest, _impl::enable_if_multiword_t<Digits, Narrowest>>>
            : numeric_limits<Narrowest> {
        static constexpr bool is_integer = true;
        // wide_integer-specific helpers
        using _narrowest_numeric_limits = numeric_limits<Narrowest>;
        using _value_type = _impl::wide_integer<Digits, Narrowest>;
        using _rep = typename _value_type::_base;
        using _rep_numeric_limits = numeric_limits<_rep>;

        static constexpr _rep _rep_max() noexcept
        {
            return static_cast<_rep>(_rep_numeric_limits::max() >> (_rep_numeric_limits::digits-digits));
        }

        // standard members
        static constexpr int digits = Digits;

        static constexpr _value_type min() noexcept
        {
            return _impl::from_rep<_value_type>(1);
        }

        static constexpr _value_type max() noexcept
        {
            return _impl::from_rep<_value_type>(_rep_max());
        }

        static constexpr _value_type lowest() noexcept
        {
            return _impl::lowest<_rep, _narrowest_numeric_limits::is_signed>()(_rep_max());
        }
    };

    template<int Digits, typename Narrowest>
    struct numeric_limits<_impl::wide_integer<Digits, Narrowest> const>
            : numeric_limits<_impl::wide_integer<Digits, Narrowest>> {
        static constexpr bool is_integer = true;
    };
}

#endif  // CNL_IMPL_WIDE_INTEGER_NUMERIC_LIMITS_H
