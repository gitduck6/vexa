#include "alt/SDL3.hpp"
#include <thread>
#include "time.hpp"
NAMESPACE_BEGIN(monako::time)

namespace chrono = std::chrono;


template<DurationConcept Duration>
static void _sleepFor(Duration amount) {
    using namespace std::this_thread;

    if constexpr (is_same_t<Duration, Nanos>)
    {
        sleep_for(chrono::duration<Nanos::Value, std::nano>{ amount.value });
    }
    else if constexpr (is_same_t<Duration, Micros>)
    {
        sleep_for(chrono::duration<Micros::Value, std::micro>{ amount.value });
    }
    else if constexpr (is_same_t<Duration, Millis>)
    {
        sleep_for(chrono::duration<Millis::Value, std::milli>{ amount.value });
    }
    else if constexpr (is_same_t<Duration, Seconds>)
    {
        sleep_for(chrono::duration<Seconds::Value>{ amount.value });
    }
    else { static_assert(false, "Unknown type occured!\n"); }
}


void sleepNanos(Nanos::Value amount) {
    _sleepFor(Nanos{amount});
}

void sleepMicros(Micros::Value amount) {
    _sleepFor(Micros{amount});
}

void sleepMillis(Millis::Value amount) {
    _sleepFor(Millis{amount});
}

void sleepSeconds(Seconds::Value amount) {
    _sleepFor(Seconds{amount});
}



template<DurationConcept Duration>
TimePoint<Duration> now() {
    using namespace std::chrono;
    auto now_tp = steady_clock::now().time_since_epoch();

    typename Duration::Value converted_value{};

    if constexpr (is_same_t<Duration, Nanos>) {
        converted_value = duration_cast<duration<Nanos::Value, std::nano>>(now_tp).count();
    } 
    else if constexpr (is_same_t<Duration, Micros>) {
        converted_value = duration_cast<duration<Micros::Value, std::micro>>(now_tp).count();
    } 
    else if constexpr (is_same_t<Duration, Millis>) {
        converted_value = duration_cast<duration<Millis::Value, std::milli>>(now_tp).count();
    } 
    else if constexpr (is_same_t<Duration, Seconds>) {
        converted_value = duration_cast<duration<Seconds::Value>>(now_tp).count();
    }

    return TimePoint<Duration>{ Duration{ converted_value } };
}



template TimePoint<Nanos> now<Nanos>();
template TimePoint<Micros> now<Micros>();
template TimePoint<Millis> now<Millis>();
template TimePoint<Seconds> now<Seconds>();

template struct TimePoint<Nanos>;
template struct TimePoint<Micros>;
template struct TimePoint<Millis>;
template struct TimePoint<Seconds>;

NAMESPACE_END(monako::time)
