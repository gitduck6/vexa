#pragma once
#include "core/defs.hpp"
NAMESPACE_BEGIN(monako::time)

struct Nanos { using Value = uint64; Value value; };
struct Micros { using Value = uint64; Value value; };
struct Millis { using Value = fp32; Value value; };
struct Seconds { using Value = fp32; Value value; };

template<class T>
concept DurationConcept = (
    is_same_t<T, Nanos> || is_same_t<T, Micros> ||
    is_same_t<T, Millis> || is_same_t<T, Seconds>
);

template<DurationConcept Duration>
struct TimePoint {
    Duration date;

    TimePoint<Duration> elapsed() {
        TODO(__func__);
    }
};


void sleepNanos(Nanos::Value duration);
void sleepMicros(Micros::Value duration);
void sleepMillis(Millis::Value duration);
void sleepSeconds(Seconds::Value duration);


template<DurationConcept Duration>
TimePoint<Duration> now();


NAMESPACE_END(monako::time)
