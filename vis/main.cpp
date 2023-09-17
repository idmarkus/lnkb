#include "lnkb/ease.hpp"

#include <matplot/matplot.h>
#include <vector>

struct fnrow
{
    std::vector<std::function<double(double)>> vec;

    fnrow(double(args)(double)...)
        : vec {args}
    {}
};

using plotfn = double(double);

struct frow
{
    const std::string                          name;
    std::vector<std::function<double(double)>> vec;

    frow(std::string const & name, std::function<double(double)> args...)
        : name(name),
          vec {args}
    {}
};

int main()
{
    using namespace matplot;
    using namespace lnkb;

    //    std::vector<double> x = linspace(0, 1);
    std::array<double, 2> x = {0, 1};

    std::vector<frow> plotfns;

#define push_ease(NAME)                                                                                      \
    plotfns.emplace_back(#NAME, ease::NAME::in<double>, ease::NAME::out<double>, ease::NAME::inout<double>)

    push_ease(quadratic);
    push_ease(elastic);
    push_ease(sinusoidal);

    const size_t rows = plotfns.size();
    const size_t cols = plotfns[0].vec.size();

    tiledlayout(rows, cols);

    for (auto & fr : plotfns) {
        auto ax = nexttile();
        fplot(ax, fr.vec[0], x);
        title(ax, fr.name);

        for (size_t i = 1; i < fr.vec.size(); ++i) {
            auto ax1 = nexttile();
            fplot(ax1, fr.vec[i], x);
        }
    }

    show();

    //    std::vector<double> y1 = transform(x, [](auto x) { return ease::sinusoidal::inout(x); });
    //    std::vector<double> y2 = transform(x, [](auto x) { return ease::elastic::in(x); });
    //    std::vector<double> y3 = transform(x, [](auto x) { return ease::exponential::inout(x); });
    //
    //    plot(x, y1, x, y2, "--", x, y3, ":");

    show();
    return 0;
}