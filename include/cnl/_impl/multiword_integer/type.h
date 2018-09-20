
//          Copyright John McFarlane 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(CNL_IMPL_MULTIWORD_INTEGER_TYPE_H)
#define CNL_IMPL_MULTIWORD_INTEGER_TYPE_H 1

#include "../algorithm/all_of.h"
#include "../type_traits/set_signedness.h"
#include "forward_declaration.h"

#include <iterator>

/// compositional numeric library
namespace cnl {
    namespace _impl {
        template<typename Word, int Size>
        class multiword_integer {
        public:
            static constexpr int size = Size;

            constexpr multiword_integer() = default;

            constexpr operator bool() const
            {
                return all_of([](auto const& word) { return word; });
            }

        private:
            template<typename Predicate>
            constexpr bool all_of(Predicate f) const
            {
                return f(head) && _impl::all_of(std::begin(body), std::end(body), f);
            }

            using head_word = Word;

            using body_word = set_signedness_t<head_word, false>;
            static constexpr int body_size = size-1;
            using array = body_word[body_size];

            head_word head;
            array body;
        };
    }
}

#endif  // CNL_IMPL_MULTIWORD_INTEGER_TYPE_H
