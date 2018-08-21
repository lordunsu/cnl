#include <cnl/all.h>

#include <iostream>
#include <string>
#include <type_traits>
#include <set>

using namespace cnl::literals;

template<typename Scalar>
auto divide(Scalar const& n, Scalar const& d)
-> typename std::enable_if<std::is_floating_point<Scalar>::value, decltype(n/d)>::type
{
    return n/d;
}

template<typename NumeratorRep, int NumeratorExponent, typename DenominatorRep, int DenominatorExponent>
auto divide(
        cnl::fixed_point<NumeratorRep, NumeratorExponent> const& n,
        cnl::fixed_point<DenominatorRep, DenominatorExponent> const& d)
{
    return cnl::quotient(n, d);
}

template<
        typename NumeratorNumerator, typename NumeratorDenominator,
        typename DenominatorNumerator, typename DenominatorDenominator>
auto divide(
        cnl::fraction<NumeratorNumerator, NumeratorDenominator> const& n,
        cnl::fraction<DenominatorNumerator, DenominatorDenominator> const& d)
{
    return n/d;
}

// from: https://medium.com/@bellmar/is-cobol-holding-you-hostage-with-math-5498c0eb428b
template<typename Scalar>
auto iterate_simple(Scalar const& y, Scalar const& z)
{
    auto a = divide(Scalar(1500.), z);
    auto b = Scalar(815.);
    auto c = Scalar(a);
    auto d = b-c;
    auto e = Scalar(108.)-Scalar{divide(d, y)};
    return e;
}

template<typename Scalar>
auto iterate(Scalar const& y, Scalar const& z)
{
    return iterate_simple(y, z);
}

template<typename Scalar>
auto iterate(cnl::fraction<Scalar> const& y, cnl::fraction<Scalar> const& z)
-> std::enable_if_t<cnl::is_integral<Scalar>::value, cnl::fraction<Scalar>>
{
    auto result = iterate_simple(y, z);
    while (true) {
        using limits = cnl::numeric_limits<Scalar>;

        auto const too_big = limits::max() >> ((limits::digits*3)/5);
        if (cnl::abs(result.numerator)<too_big
                && cnl::abs(result.denominator)<too_big) {
            return result;
        }

        result.numerator /= 2;
        result.denominator /= 2;
    }
}

template<typename Scalar>
void test(char const* const title)
{
    using std::cout;

    cout << '\n' << title << '\n';

    std::set<Scalar> previous;
    auto print_row = [&](int iteration, Scalar const& value) {
        cout << iteration << '\t' << cnl::to_string(value) << '\n';

        auto [position, was_inserted] = previous.insert(value);
        CNL_ASSERT(was_inserted);
    };

    auto last = Scalar(cnl::fraction(16, 4));  // 4
    print_row(0, last);

    Scalar current{cnl::fraction(17, 4)};   // 4.25
    print_row(1, current);

    for (auto iteration = 2, divergence_iteration = 0; ; ++iteration) {
        CNL_ASSERT(iteration<1000);

        Scalar const next = iterate(current, last);
        if (next==current || current!=current) {
            cout << "converged on " << static_cast<long double>(current) << " after " << iteration << " iterations" << '\n';

            if (divergence_iteration) {
                cout << "diverged from 5 at iteration " << divergence_iteration << "\n";
            }

            break;
        }
        last = current;
        current = next;

        if (!divergence_iteration && cnl::abs(current-Scalar(5.))>cnl::abs(last-Scalar(5.))) {
            divergence_iteration = iteration;
        }

        print_row(iteration, current);
    }
}

int main()
{
    test<float>("single precision floating point");
    test<double>("double precision floating point");
    test<long double>("extended precision floating point");
    test<cnl::fixed_point<cnl::int32, -20>>("cnl::fixed_point<cnl::int32, -20>");
    test<cnl::fixed_point<cnl::int64, -52>>("cnl::fixed_point<cnl::int64, -52>");
    test<cnl::fixed_point<cnl::elastic_integer<49>, -38>>("cnl::fixed_point<cnl::elastic_integer<49>, -38>");
    test<cnl::static_number<42, -30>>("cnl::static_number<42, -30>");
    test<cnl::fraction<cnl::int64>>("cnl::fraction<cnl::int64>");
//    test<cnl::fraction<cnl::int128>>("cnl::fraction<cnl::int128>");
    test<cnl::fraction<float>>("cnl::fraction<float>");
    test<cnl::fraction<double>>("cnl::fraction<double>");
    test<cnl::fraction<long double>>("cnl::fraction<long double>");
}
