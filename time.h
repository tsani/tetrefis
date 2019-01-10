#ifndef TIME_H
#define TIME_H

/**
 * \brief
 * Represents a timer that waits a given amount of time.
 */
typedef struct timer {
  EFI_EVENT event;
  UINT32 duration_ms;
} timer;

/**
 * \brief
 * Initializes a timer with the given duration.
 * The result is undefined if ok is false.
 */
timer make_timer(int * ok, uint32_t duration_ms);

/**
 * \brief
 * Blocks until the given timer elapses.
 *
 * Returns false iff a timer operation could not proceed.
 */
int await_timer(timer * const timer);

#endif
