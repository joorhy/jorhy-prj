#define MAX_FRAME_SIZE 640
#define FRAME_SIZE 320
#define MAX_DCT_SIZE 640
#define MAX_NUM_REGIONS 28 
#define NUM_REGIONS 14
#define REGION_POWER_TABLE_SIZE 64
#define REGION_POWER_TABLE_NUM_NEGATIVES 24
#define NUM_RATE_CONTROL_BITS 4
#define NUM_RATE_CONTROL_POSSIBILITIES 16
#define MAX_NUM_RATE_CONTROL_BITS 5
#define MAX_NUM_RATE_CONTROL_POSSIBILITIES 32
#define ENCODER_SCALE_FACTOR 18318.0
/* Max bit rate is now 48000 bits/sec. */
#define MAX_BITS_PER_FRAME 960
/* Scale factor used to match fixed point model results. */
#define INTEROP_RMLT_SCALE_FACTOR_7  22.0f
#define INTEROP_RMLT_SCALE_FACTOR_14 33.0f

#ifdef WIN32

#ifdef JSON_LIB_EXPORTS
#define G722_DLLAPI	_declspec(dllexport)
#else
#define G722_DLLAPI	_declspec(dllimport)
#endif

#else
#define G722_DLLAPI
#endif

extern "C"
{
extern void mlt_based_coder_init();
extern void G722_1_1C_Float_encoder(short *input,short *out_words,int bit_rate,int bandwidth);
extern void G722_1_1C_Float_decoder(short *output,short *out_words,int bit_rate,int bandwidth);
}
