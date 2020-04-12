/**
 * @file clock.h
 */

#ifndef CLOCK_H
#define CLOCK_H

typedef enum 
{
    clock_src_low_power_xtal = 0,
    clock_src_full_swing_xtal,
    clock_src_internal_128k_rc,
    clock_src_calibrated_internal_rc,
    clock_src_external
} clock_src;

#endif // CLOCK_H
