#pragma once

#define X_PL_API __stdcall
typedef long long j_pl_mtime_t;
typedef int J_PL_RESULT;
typedef int J_PL_BOOL;
typedef unsigned (X_PL_API *j_pl_entry_t)(void*);
typedef void (X_PL_API *j_pl_entry_display_t)(void*,j_pl_mtime_t);
typedef void (X_PL_API* j_pl_entry_timer_t)(void*);
typedef void (X_PL_API* j_pl_entry_end_t)(void*);

#define J_PL_FOURCC(ch0, ch1, ch2, ch3)				\
	((unsigned long)(unsigned char)(ch0) |			\
	((unsigned long)(unsigned char)(ch1) << 8) |	\
	((unsigned long)(unsigned char)(ch2) << 16) |	\
	((unsigned long)(unsigned char)(ch3) << 24 ))

#define NULL 0
#define J_PL_FALSE 0
#define J_PL_TRUE 1
#define J_PL_VERSION "1.0.0"

typedef struct
{
	long long quot; /* Quotient. */
	long long rem;  /* Remainder. */
}j_pl_lldiv_t;
