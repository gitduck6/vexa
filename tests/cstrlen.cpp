#include "monako.hpp"

namespace mnk = monako;

int main() {
    constexpr const char* cstr = "123456789012";

    using Dur = mnk::time::Nanos;
    const char* dur_type = "";
    if constexpr (is_same_t<Dur, mnk::time::Nanos>) dur_type = "ns";
    if constexpr (same_t<Dur, mnk::time::Micros>) dur_type = "micros";
    if constexpr (same_t<Dur, mnk::time::Millis>) dur_type = "ms";
    if constexpr (same_t<Dur, mnk::time::Seconds>) dur_type = "secs";

    mnk::log::print(cstr);
    auto start = mnk::time::now<Dur>();
    auto sz = mnk::cstr_len(cstr);
    auto finish = mnk::time::now<Dur>();
    mnk::log::print(cstr);

    auto elapsed = finish.m_date.m_value - start.m_date.m_value;
    mnk::log::print("\n\nelapsed-time: {}{}", elapsed, dur_type);
    mnk::log::print("lenght of c-string '{}' is: {}\n\n\n", cstr, sz);
}
