
//          Copyright John McFarlane 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

/// \file
/// \brief tests for <cnl/_impl/multiword_integer/type.h>

#include <cnl/_impl/multiword_integer/type.h>

#include <cnl/_impl/type_traits/identical.h>

using cnl::_impl::identical;

namespace {
    namespace test_parameters {
        static_assert(
                identical(123, cnl::_impl::multiword_integer<int, 123>::size),
                "cnl::_impl::multiword_integer::size");
    }

    namespace test_bool {
        static_assert(!cnl::_impl::multiword_integer<int, 20>{}, "constructor taking multiword_integer");
    }
}
