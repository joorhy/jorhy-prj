#pragma once

#define BTKAPI __stdcall
typedef long long btk_mtime_t;
typedef int BTK_RESULT;
typedef int BTK_BOOL;
typedef unsigned (BTKAPI *btk_entry_t)(void*);
typedef void (BTKAPI *btk_entry_display_t)(void*,btk_mtime_t);
typedef void (BTKAPI* btk_entry_timer_t)(void*);
typedef void (BTKAPI* btk_entry_end_t)(void*);

#define BTK_FOURCC(ch0, ch1, ch2, ch3)				\
	((unsigned long)(unsigned char)(ch0) |			\
	((unsigned long)(unsigned char)(ch1) << 8) |	\
	((unsigned long)(unsigned char)(ch2) << 16) |	\
	((unsigned long)(unsigned char)(ch3) << 24 ))

#define NULL 0
#define BTK_FALSE 0
#define BTK_TRUE 1
#define BTK_VERSION "1.0.0"

typedef struct
{
	long long quot; /* Quotient. */
	long long rem;  /* Remainder. */
}btk_lldiv_t;



