#ifndef FT_LS_FLAGS_H
# define FT_LS_FLAGS_H

#include <inttypes.h>

// тип флага
// A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z.
typedef enum		t_flags
{
	fl_noex = -1,
	fl_a,
	fl_l,
	fl_r,
	fl_t,
	fl_R
}					e_flags;

# define ISFLAG(fl) ({update_flags(-1) & 1 << fl;})

int32_t		update_flags(const int8_t shift);

#endif
