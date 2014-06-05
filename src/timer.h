#ifndef timer_h__
#define timer_h__

namespace hpgc {
    inline double Now() {
        timespec tp;
        clock_gettime(CLOCK_MONOTONIC, &tp);
        return tp.tv_sec + 1e-9 * tp.tv_nsec;
    }
}

#endif // timer_h__
