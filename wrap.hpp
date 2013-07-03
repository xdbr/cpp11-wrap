#ifndef WRAP_HPP
#define WRAP_HPP

#include <functional>

template<typename W, typename F>
std::function<void()>
before(std::function<W> w, std::function<F> f);

// template<typename W, typename F>
std::function<void()>
before(std::function<void()> w, std::function<void()> f);

template<typename W, typename F>
std::function<void()>
before(std::function<W> w, std::function<F> f) {
    return [&]{
        f();
        w();
    };
}

// template<typename W, typename F>
std::function<void()>
before(std::function<void()> w, std::function<void()> f) {
    return [&]{
        f();
        w();
    };
}

template<typename W, typename F>
std::function<void()>
after(std::function<W> w, std::function<F> f) {

    struct After {
        std::function<F> f_;
        After(std::function<F> x): f_{x}{}
        ~After() { f_(); }
    };

    return [&]{
        auto y = After(f);
        w();
    };
}

#endif /* end of include guard: WRAP_HPP */
