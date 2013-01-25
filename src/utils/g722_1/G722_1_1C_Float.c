#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "defs.h"
#include "huff_defs.h"
#include "huff_tables.h"

float dct_core_a[100];
typedef struct {
    float   cosine;
    float   minus_sine;
    } cos_msin_t;
cos_msin_t   cos_msin_5[5];      /* Not used since core_size = 10 */
cos_msin_t   cos_msin_10[10];
cos_msin_t   cos_msin_20[20];
cos_msin_t   cos_msin_40[40];
cos_msin_t   cos_msin_80[80];
cos_msin_t   cos_msin_160[160];
cos_msin_t   cos_msin_320[320];
cos_msin_t   cos_msin_640[640];  /* Used only for 640 point dct */
cos_msin_t   *cos_msin_table[] = {cos_msin_5,   cos_msin_10,
                                         cos_msin_20,  cos_msin_40,
                                         cos_msin_80,  cos_msin_160,
                                         cos_msin_320, cos_msin_640};


#define ABS(a)  (a>0?a:-a)

static int one = 0x0081;
static int zero = 0x007f;
static int frame_start = 0x6b21;


int   region_size;
float region_size_inverse;
float region_standard_deviation_table[REGION_POWER_TABLE_SIZE];
float standard_deviation_inverse_table[REGION_POWER_TABLE_SIZE];
float step_size_inverse_table[NUM_CATEGORIES];
float region_power_table[REGION_POWER_TABLE_SIZE];
float region_power_table_boundary[REGION_POWER_TABLE_SIZE-1];
int   vector_dimension[NUM_CATEGORIES] =  { 2, 2, 2, 4, 4, 5, 5, 1};
int   number_of_vectors[NUM_CATEGORIES] = {10,10,10, 5, 5, 4, 4,20};
float step_size[NUM_CATEGORIES] = {0.3536f, 0.5f, 0.7071f, 1.0f, 1.4142f, 2.0f, 2.8284f, 2.8284f};
int   max_bin[NUM_CATEGORIES] = {13, 9, 6, 4, 3, 2, 1, 1};
float dead_zone[NUM_CATEGORIES] = {0.3f, 0.33f, 0.36f, 0.39f, 0.42f, 0.45f, 0.5f, 0.5f};
static int max_bin_plus_one_inverse[NUM_CATEGORIES];
int   num_rate_control_bits;
int   num_rate_control_possibilities;


void rate_adjust_categories(int, int [], int []);
void decode_envelope(int, float[], int[]);
void decode_vector_quantized_mlt_indices(int, float [], int [], float [], int);

int number_of_bits_left;
int next_bit;
int code_word;
int code_bit_count;
short int *code_word_ptr;
#define GET_NEXT_BIT \
if (code_bit_count == 0) { \
  code_word = *code_word_ptr++; \
  code_bit_count = 16; \
} \
code_bit_count--; \
next_bit = (code_word >> code_bit_count) & 1;



void write_ITU_format(short int [], int, int, FILE *);
void mlt_based_coder_init();
void encoder(int, int, float [], short int []);
void samples_to_rmlt_coefs(float *, float *, int);
int  compute_region_powers(int, float[], int[], int[], int[]);
void vector_quantize_mlts(int, int, int, float[], int[], int[], int[], int *, int[], int[]);
int  vector_huffman(int, int, float *, int *);
void categorize(int,int, int[],int[],int[]);
static void set_up_one_table(cos_msin_t[],long);
void dct_type_iv (float[], float[],long);
int read_ITU_format(short int [], int *, int, FILE *);
void decoder(int, int, short int [], float [], int);
void rmlt_coefs_to_samples(float *, float *, int);
int index_to_array(int, int[], int);
void decode_envelope(int,float[],int[]);
void rate_adjust_categories(int,int[],int[]);
void decode_vector_quantized_mlt_indices( int,float[],int[],float[],int);

void G722_1_1C_Float_encoder(short *input,short *out_words,int bit_rate,int bandwidth)
{
    int i; 
    int number_of_regions;    
    int number_of_bits_per_frame;
    int number_of_16bit_words_per_frame;    
    int framesize;
    float scale_factor;
    float mlt_coefs[MAX_DCT_SIZE];
    float float_new_samples[MAX_DCT_SIZE];
	short int out_words1[MAX_BITS_PER_FRAME/16];
    number_of_bits_per_frame = (int)(bit_rate / 50);
    if (bandwidth == 7000)
    {
        number_of_regions = NUM_REGIONS;
        framesize = FRAME_SIZE;
        scale_factor = INTEROP_RMLT_SCALE_FACTOR_7;
    }
    else
    {
        number_of_regions = MAX_NUM_REGIONS;
        framesize = MAX_FRAME_SIZE;
        scale_factor = INTEROP_RMLT_SCALE_FACTOR_14;
    }
    number_of_16bit_words_per_frame = number_of_bits_per_frame / 16;
        for (i=0; i<framesize; i++)
		{
			float_new_samples[i] = (float)(*input);
			input++;
		}
        /* Convert input samples to rmlt coefs */
        samples_to_rmlt_coefs(float_new_samples, mlt_coefs, framesize);
        /* This was added to for fixed point interop */
        for (i=0; i<framesize; i++)
            mlt_coefs[i] /= scale_factor;
        /* Encode the mlt coefs */
        encoder(number_of_regions,
                number_of_bits_per_frame,
                mlt_coefs,
                out_words1);
		for (i=0;i<bit_rate/800;i++)
		{
			*out_words=out_words1[i];
			*out_words++;
		}
    
}
/****************************************************************************************
 Function:    mlt_based_coder_init

 Syntax:      void mlt_based_coder_init()
 
 Description: Initializes region and category related stuff
****************************************************************************************/
void mlt_based_coder_init()
{
    int i, j;
    int category;
    int number_of_indices;

    /*  region_size = (BLOCK_SIZE * 0.875)/NUM_REGIONS; */
    region_size = 20;
    region_size_inverse = (float)(1.0 / ((float)region_size));

    for (i=0; i<REGION_POWER_TABLE_SIZE; i++)
    {
        region_power_table[i] = (float) pow(10.0, 0.10 * REGION_POWER_STEPSIZE_DB *
                                ((float) (i - REGION_POWER_TABLE_NUM_NEGATIVES)));
        region_standard_deviation_table[i] = (float)sqrt(region_power_table[i]);
        standard_deviation_inverse_table[i] = (float) 1.0/region_standard_deviation_table[i];
    }

    for (i=0; i<REGION_POWER_TABLE_SIZE-1; i++)
        region_power_table_boundary[i] = (float)pow(10.0, 0.10 * REGION_POWER_STEPSIZE_DB *
                                         (0.5+((float) (i-REGION_POWER_TABLE_NUM_NEGATIVES))));

    /* Initialize category related stuff. */
    for (category=0; category<NUM_CATEGORIES; category++)
    {
        /* Rounding up by 1.0 instead of 0.5 allows us to avoid rounding every time this is used. */
        max_bin_plus_one_inverse[category] = (int) ((32768./(max_bin[category]+1.0)) + 1.0);

        /* Test division for all indices. */
        number_of_indices = 1;
        for (j=0; j<vector_dimension[category]; j++)
            number_of_indices *= (max_bin[category]+1);
        for (j=0; j<number_of_indices; j++)
        {
            if (j/(max_bin[category]+1) != ((j*max_bin_plus_one_inverse[category])>>15))
                printf("max_bin_plus_one_inverse ERROR!! %1d: %5d %3d\n",category,max_bin_plus_one_inverse[category],j);
        }
    }

    for (category=0; category<NUM_CATEGORIES; category++)
        step_size_inverse_table[category] = (float)1.0 / step_size[category];
}



/***************************************************************************
 Function:    encoder

 Syntax:      void encoder( number_of_regions,
                            number_of_available_bits,
                            mlt_coefs,
                            out_words)
              int number_of_regions;
              int number_of_available_bits;
              float mlt_coefs[MAX_DCT_SIZE];
              short int out_words[MAX_BITS_PER_FRAME/16];

              inputs:  number_of_regions
                       number_of_available_bits
                       mlt_coefs[MAX_DCT_SIZE]

              outputs: out_words[MAX_BITS_PER_FRAME/16]


 Description: Encodes the mlt coefs into out_words using G.722.1 Annex C
***************************************************************************/

void encoder(int number_of_regions,
             int number_of_available_bits,
             float mlt_coefs[MAX_DCT_SIZE],
             short int out_words[MAX_BITS_PER_FRAME/16])
    
{

    int number_of_bits_per_frame;
    int number_of_envelope_bits;
    int rate_control;
    int region;
    int absolute_region_power_index[MAX_NUM_REGIONS];
    int power_categories[MAX_NUM_REGIONS];
    int category_balances[MAX_NUM_RATE_CONTROL_POSSIBILITIES-1];
    int drp_num_bits[MAX_NUM_REGIONS+1];
    int drp_code_bits[MAX_NUM_REGIONS+1];

    int region_mlt_bit_counts[MAX_NUM_REGIONS];
    int region_mlt_bits[4*MAX_NUM_REGIONS];


    /* Initialize variables. */
    if (number_of_regions == NUM_REGIONS)
    {
        num_rate_control_bits = NUM_RATE_CONTROL_BITS;
        num_rate_control_possibilities = NUM_RATE_CONTROL_POSSIBILITIES;
    } 
    else
    {
        num_rate_control_bits = MAX_NUM_RATE_CONTROL_BITS;
        num_rate_control_possibilities = MAX_NUM_RATE_CONTROL_POSSIBILITIES;
    } 

    number_of_bits_per_frame = number_of_available_bits;

    /* Estimate power envelope. */
    number_of_envelope_bits = compute_region_powers(number_of_regions,
                                                    mlt_coefs,
                                                    drp_num_bits,
                                                    drp_code_bits,
                                                    absolute_region_power_index);

    number_of_available_bits -= number_of_envelope_bits;
    number_of_available_bits -= num_rate_control_bits;

    categorize(number_of_regions,
               number_of_available_bits,
               absolute_region_power_index,
               power_categories,
               category_balances);

    /* Adjust absolute_region_category_index[] for mag_shift.
       This assumes that REGION_POWER_STEPSIZE_DB is defined
       to be exactly 3.010299957 or 20.0 times log base 10
       of square root of 2. */
    for (region=0; region<number_of_regions; region++)
        absolute_region_power_index[region] += REGION_POWER_TABLE_NUM_NEGATIVES;

    for (region=0; region<number_of_regions; region++)
        region_mlt_bit_counts[region] = 0;

    vector_quantize_mlts(number_of_regions,
                         num_rate_control_possibilities,
                         number_of_available_bits,
                         mlt_coefs,
                         absolute_region_power_index,
                         power_categories,
                         category_balances,
                         &rate_control,
                         region_mlt_bit_counts,
                         region_mlt_bits);

    {
    int out_word_index;
    int j;
    short int out_word;
    int region_bit_count;
    int current_word_bits_left;
    short int slice;

    int out_word_bits_free;

    int *in_word_ptr;
    unsigned int current_word;

    out_word_index = 0;

    out_word = 0;
    out_word_bits_free = 16;

    /* First set up the rate control bits to look like one more set of region power bits. */
    drp_num_bits[number_of_regions] = num_rate_control_bits;
    drp_code_bits[number_of_regions] = rate_control;

    /* These code bits are right justified. */
    for (region=0; region <= number_of_regions; region++)
    {
        current_word_bits_left = drp_num_bits[region];
        current_word = drp_code_bits[region];
        j = current_word_bits_left-out_word_bits_free;
        if (j >= 0)
        {
            out_word += current_word >> j;
            out_words[out_word_index++] = out_word;
            out_word_bits_free = 16;
            out_word = current_word << (16 - j);
            out_word_bits_free -= j;
        }
        else
        {
            out_word += current_word << (-j);
            out_word_bits_free -= current_word_bits_left;
        }
    }

    /* These code bits are left justified. */
    for (region=0; (region<number_of_regions) && ((16*out_word_index)<number_of_bits_per_frame); region++)
    {
        in_word_ptr = &region_mlt_bits[4*region];
        region_bit_count = region_mlt_bit_counts[region];
        current_word_bits_left = MIN(32, region_bit_count);
        current_word = *in_word_ptr++;
        while ((region_bit_count>0) && ((16*out_word_index)<number_of_bits_per_frame))
        {
            if (current_word_bits_left >= out_word_bits_free)
            {
                slice = current_word >> (32 - out_word_bits_free);
                out_word += slice;
                current_word <<= out_word_bits_free;
                current_word_bits_left -= out_word_bits_free;
                out_words[out_word_index++] = out_word;
                out_word = 0;
                out_word_bits_free = 16;
            }
            else
            {
                slice = current_word >> (32 - current_word_bits_left);
                out_word += slice << (out_word_bits_free - current_word_bits_left);
                out_word_bits_free -= current_word_bits_left;
                current_word_bits_left = 0;
            }
            if (current_word_bits_left == 0)
            {
                current_word = *in_word_ptr++;
                region_bit_count -= 32;
                current_word_bits_left = MIN(32, region_bit_count);
            }
        }
    }

    /* Fill out with 1's. */
    while ((16*out_word_index)<number_of_bits_per_frame)
    {
        current_word = 0x0000ffff;
        slice = current_word >> (16 - out_word_bits_free);
        out_word += slice;
        out_words[out_word_index++] = out_word;
        out_word = 0;
        out_word_bits_free = 16;
    }
    }
}



/***************************************************************************
 Function:    compute_region_powers

 Syntax:      int compute_region_powers(number_of_regions,
                                        mlt_coefs,
                                        drp_num_bits,
                                        drp_code_bits,
                                        absolute_region_power_index)
              int number_of_regions;
              float mlt_coefs[MAX_DCT_SIZE];
              int drp_num_bits[MAX_NUM_REGIONS];
              int drp_code_bits[MAX_NUM_REGIONS];
              int absolute_region_power_index[MAX_NUM_REGIONS];

 Description: Computes the power for each of the regions
***************************************************************************/

int compute_region_powers(int number_of_regions,
                          float mlt_coefs[MAX_DCT_SIZE],
						  int drp_num_bits[MAX_NUM_REGIONS],
                          int drp_code_bits[MAX_NUM_REGIONS],
                          int absolute_region_power_index[MAX_NUM_REGIONS])
               
    
{
    float *input_ptr;
    int iterations;
    float ftemp0, ftemp1;
    int index, index_min, index_max;

    int region;
    int j;
    int differential_region_power_index[MAX_NUM_REGIONS];
    int number_of_bits;

    input_ptr = mlt_coefs;
    for (region=0; region<number_of_regions; region++)
    {
        ftemp0 = 0.0;
        for (j=0; j<region_size; j++)
        {
            ftemp1 = *input_ptr++;
            ftemp0 += ftemp1*ftemp1;
        }
        ftemp0 *= region_size_inverse;

        index_min = 0;
        index_max = REGION_POWER_TABLE_SIZE;
        for (iterations = 0; iterations < 6; iterations++)
        {
            index = (index_min + index_max) >> 1;
            if (ftemp0 < region_power_table_boundary[index-1])
                index_max = index;
            else
                index_min = index;
        }
        absolute_region_power_index[region] = index_min - REGION_POWER_TABLE_NUM_NEGATIVES;
    }

    /* Before we differentially encode the quantized region powers, adjust upward the
       valleys to make sure all the peaks can be accurately represented. */
    for (region = number_of_regions-2; region >= 0; region--)
    {
        if (absolute_region_power_index[region] < absolute_region_power_index[region+1] - DRP_DIFF_MAX)
            absolute_region_power_index[region] = absolute_region_power_index[region+1] - DRP_DIFF_MAX;
    }

    /* The MLT is currently scaled too low by the factor
       ENCODER_SCALE_FACTOR(=18318)/32768 * (1./sqrt(160).
       This is the ninth power of 1 over the square root of 2.
       So later we will add ESF_ADJUSTMENT_TO_RMS_INDEX (now 9)
       to drp_code_bits[0]. */

    /* drp_code_bits[0] can range from 1 to 31. 0 will be used only as an escape sequence. */
    if (absolute_region_power_index[0] < 1-ESF_ADJUSTMENT_TO_RMS_INDEX)
        absolute_region_power_index[0] = 1-ESF_ADJUSTMENT_TO_RMS_INDEX;
    if (absolute_region_power_index[0] > 31-ESF_ADJUSTMENT_TO_RMS_INDEX)
        absolute_region_power_index[0] = 31-ESF_ADJUSTMENT_TO_RMS_INDEX;

    differential_region_power_index[0] = absolute_region_power_index[0];
    number_of_bits = 5;
    drp_num_bits[0] = 5;
    drp_code_bits[0] = absolute_region_power_index[0] + ESF_ADJUSTMENT_TO_RMS_INDEX;

    /* Lower limit the absolute region power indices to -8 and upper limit them to 31. Such extremes
       may be mathematically impossible anyway.*/
    for (region=1; region<number_of_regions; region++)
    {
        if (absolute_region_power_index[region] < -8-ESF_ADJUSTMENT_TO_RMS_INDEX)
            absolute_region_power_index[region] = -8-ESF_ADJUSTMENT_TO_RMS_INDEX;
        if (absolute_region_power_index[region] > 31-ESF_ADJUSTMENT_TO_RMS_INDEX)
            absolute_region_power_index[region] = 31-ESF_ADJUSTMENT_TO_RMS_INDEX;
    }

    for (region=1; region<number_of_regions; region++)
    {
        j = absolute_region_power_index[region] - absolute_region_power_index[region-1];
        if (j < DRP_DIFF_MIN)
        {
            j = DRP_DIFF_MIN;
        }
        j -= DRP_DIFF_MIN;
        differential_region_power_index[region] = j;
        absolute_region_power_index[region] = absolute_region_power_index[region-1] +
                                            differential_region_power_index[region] + DRP_DIFF_MIN;

        number_of_bits += differential_region_power_bits[region][j];
        drp_num_bits[region] = differential_region_power_bits[region][j];
        drp_code_bits[region] = differential_region_power_codes[region][j];
    }

    return(number_of_bits);
}



/***************************************************************************
 Function:    vector_quantize_mlts

 Syntax:      void vector_quantize_mlts(number_of_regions,
                                        num_rate_control_possibilities,
                                        number_of_available_bits,
                                        mlt_coefs,
                                        absolute_region_power_index,
                                        power_categories,
                                        category_balances,
                                        p_rate_control,
                                        region_mlt_bit_counts,
                                        region_mlt_bits)
              int number_of_regions;
              int num_rate_control_possibilities,
              int number_of_available_bits;
              float mlt_coefs[MAX_DCT_SIZE];
              int absolute_region_power_index[MAX_NUM_REGIONS];
              int power_categories[MAX_NUM_REGIONS];
              int category_balances[MAX_NUM_RATE_CONTROL_POSSIBILITIES-1];
              int *p_rate_control;
              int region_mlt_bit_counts[MAX_NUM_REGIONS];
              int region_mlt_bits[4*MAX_NUM_REGIONS];

 Description: Scalar quantized vector Huffman coding (SQVH)
***************************************************************************/

void vector_quantize_mlts(int number_of_regions,
     int num_rate_control_possibilities,
     int number_of_available_bits,
     float mlt_coefs[MAX_DCT_SIZE],
     int absolute_region_power_index[MAX_NUM_REGIONS],
     int power_categories[MAX_NUM_REGIONS],
     int category_balances[MAX_NUM_RATE_CONTROL_POSSIBILITIES-1],
     int *p_rate_control,
     int region_mlt_bit_counts[MAX_NUM_REGIONS],
     int region_mlt_bits[4*MAX_NUM_REGIONS])
     
{
    float *raw_mlt_ptr;
    int region;
    int category;
    int total_mlt_bits;

    total_mlt_bits = 0;

    /* Start in the middle of the rate control range. */
    for (*p_rate_control=0; *p_rate_control<((num_rate_control_possibilities>>1)-1); (*p_rate_control)++)
    {
        region = category_balances[*p_rate_control];
        power_categories[region]++;
    }

    for (region=0; region<number_of_regions; region++)
    {
        category = power_categories[region];
        raw_mlt_ptr = &mlt_coefs[region*region_size];
        if (category < NUM_CATEGORIES-1)
        {
            region_mlt_bit_counts[region] = vector_huffman(category,
                                            absolute_region_power_index[region],
                                            raw_mlt_ptr,
                                            &region_mlt_bits[4*region]);
        }
        else
        {
            region_mlt_bit_counts[region] = 0;
        }
        total_mlt_bits += region_mlt_bit_counts[region];
    }

    /* If too few bits... */
    while ((total_mlt_bits < number_of_available_bits) && (*p_rate_control > 0))
    {
        (*p_rate_control)--;
        region = category_balances[*p_rate_control];
        power_categories[region]--;
        total_mlt_bits -= region_mlt_bit_counts[region];

        category = power_categories[region];
        raw_mlt_ptr = &mlt_coefs[region*region_size];
        if (category < NUM_CATEGORIES-1)
        {
            region_mlt_bit_counts[region] = vector_huffman(category,
                                                           absolute_region_power_index[region],
                                                           raw_mlt_ptr,
                                                           &region_mlt_bits[4*region]);
        }
        else
        {
            region_mlt_bit_counts[region] = 0;
        }
        total_mlt_bits += region_mlt_bit_counts[region];
    }

    /* If too many bits... */
    while ((total_mlt_bits>number_of_available_bits) && (*p_rate_control<num_rate_control_possibilities-1))
    {
        region = category_balances[*p_rate_control];
        power_categories[region]++;
        total_mlt_bits -= region_mlt_bit_counts[region];

        category = power_categories[region];
        raw_mlt_ptr = &mlt_coefs[region*region_size];
        if (category < NUM_CATEGORIES-1)
        {
            region_mlt_bit_counts[region] = vector_huffman(category,
                                                           absolute_region_power_index[region],
                                                           raw_mlt_ptr,
                                                           &region_mlt_bits[4*region]);
        }
        else
        {
            region_mlt_bit_counts[region] = 0;
        }
        total_mlt_bits += region_mlt_bit_counts[region];
        (*p_rate_control)++;
    }
}



/********************************************************************************
 Function:    vector_huffman

 Syntax:      int vector_huffman(category,
                                 power_index,
                                 raw_mlt_ptr,
                                 word_ptr)
              int category;
              int power_index;
              float *raw_mlt_ptr;
              int *word_ptr;     

              inputs:  int   category
                       int   power_index
                       float *raw_mlt_ptr
             
              outputs: int   *word_ptr
                                      

 Description: Huffman encoding for each region based on category and power_index  
********************************************************************************/

int vector_huffman(int category,
    int power_index,
    float *raw_mlt_ptr,
    int *word_ptr)
    
{
    float inv_of_step_size_times_std_dev;
    int j, n;
    int k;
    int number_of_region_bits;
    int number_of_non_zero;
    int vec_dim;
    int num_vecs;
    int kmax, kmax_plus_one;
    int index, signs_index;
    int *bitcount_table_ptr;
    int *code_table_ptr;
    int code_bits;
    int number_of_code_bits;
    int current_word;
    int current_word_bits_free;

    vec_dim = vector_dimension[category];
    num_vecs = number_of_vectors[category];
    kmax = max_bin[category];
    kmax_plus_one = kmax + 1;

    current_word = 0;
    current_word_bits_free = 32;

    number_of_region_bits = 0;

    bitcount_table_ptr = (int *) table_of_bitcount_tables[category];
    code_table_ptr = (int *) table_of_code_tables[category];

    inv_of_step_size_times_std_dev = step_size_inverse_table[category] *
                                     standard_deviation_inverse_table[power_index];

    for (n=0; n<num_vecs; n++)
    {
        index = 0;
        signs_index = 0;
        number_of_non_zero = 0;
        for (j=0; j<vec_dim; j++)
        {
            k = (int)(fabs(*raw_mlt_ptr) * inv_of_step_size_times_std_dev + dead_zone[category]);
            if (k != 0)
            {
                number_of_non_zero++;
                signs_index <<= 1;
                if (*raw_mlt_ptr > 0)
                    signs_index++;
                if (k > kmax)
                    k = kmax;
            }
            index = index * (kmax_plus_one) + k;
            raw_mlt_ptr++;
        }

        code_bits = *(code_table_ptr+index);
        number_of_code_bits = *(bitcount_table_ptr+index) + number_of_non_zero;
        number_of_region_bits += number_of_code_bits;

        code_bits = (code_bits << number_of_non_zero) + signs_index;

        /* msb of codebits is transmitted first. */
        j = current_word_bits_free - number_of_code_bits;
        if (j >= 0)
        {
            current_word += code_bits << j;
            current_word_bits_free = j;
        }
        else
        {
            j = -j;
            current_word += code_bits >> j;
            *word_ptr++ = current_word;
            current_word_bits_free = 32 - j;
            current_word = code_bits << current_word_bits_free;
        }
    }

    *word_ptr++ = current_word;

    return(number_of_region_bits);
}



/*********************************************************************************
 Function:    samples_to_rmlt_coefs 

 Syntax:      void samples_to_rmlt_coefs(new_samples,
                                         coefs,
                                         dct_size)
              float *new_samples;
              float *coefs;
              int dct_size;
 
 Description: Convert Samples to Reversed Modulated Lapped Transform Coefficients

     The "Reversed MLT" is an overlapped block transform which uses even symmetry
 on the left, odd symmetry on the right and a Type IV DCT as the block transform.
 It is thus similar to a MLT which uses odd symmetry on the left, even symmetry
 on the right and a Type IV DST as the block transform.  In fact, it is equivalent
 to reversing the order of the samples, performing an MLT and then negating all
 the even-numbered coefficients.
*********************************************************************************/

void samples_to_rmlt_coefs( float *new_samples,
     float *coefs,
     int dct_size)
    
{
    extern void dct_type_iv(float *, float *, long);

    static float old_samples[MAX_DCT_SIZE];
    static float window[MAX_DCT_SIZE];
    static int   here_before = 0;

    int index, vals_left;
    float sum;
    double angle;
    float windowed_data[MAX_DCT_SIZE];
    float *new_ptr, *old_ptr, *sam_low, *sam_high;
    float *win_low, *win_high;
    float *dst_ptr;
    int half_dct_size;

    half_dct_size = dct_size>>1;
   
    /*++++++++++++++++++++++++++++++++++++++*/
    /* Set up some data the first time here */
    /*++++++++++++++++++++++++++++++++++++++*/
    if (here_before == 0)
    {
        for (index=0; index<dct_size; index++)
        {
            angle = (PI / 2.0) * ((double) index + 0.5) / (double)dct_size;
            window[index] = (float)sin(angle);
        }
        for (index=0; index < dct_size; index++)
            old_samples[index] = 0.0;
        here_before = 1;
    }

    /*++++++++++++++++++++++++++++++++++++++++++++*/
    /* Get the first half of the windowed samples */
    /*++++++++++++++++++++++++++++++++++++++++++++*/
    dst_ptr  = windowed_data;
    win_high = window + half_dct_size;
    win_low  = win_high;

    sam_high = old_samples + half_dct_size;
    sam_low  = sam_high;
    for (vals_left=half_dct_size; vals_left>0; vals_left--)
    {
        sum = *--win_low *  *--sam_low;
        sum += *win_high++ * *sam_high++;
       *dst_ptr++ = sum;
    }

    /*+++++++++++++++++++++++++++++++++++++++++++++*/
    /* Get the second half of the windowed samples */
    /*+++++++++++++++++++++++++++++++++++++++++++++*/
    sam_low  = new_samples;
    sam_high = new_samples + dct_size;
    for (vals_left=half_dct_size; vals_left>0; vals_left--)
    {
        sum = *--win_high * *sam_low++;
        sum -= *win_low++ * *--sam_high;
        *dst_ptr++ = sum;
    }
      
    /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    /* Save the new samples for next time, when they will be the old samples */
    /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    new_ptr = new_samples;
    old_ptr = old_samples;
    for (vals_left=dct_size; vals_left>0; vals_left--)
        *old_ptr++ = *new_ptr++;
   
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    /* Perform a Type IV DCT on the windowed data to get the coefficients */
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    dct_type_iv(windowed_data, coefs, dct_size);

}


/****************************************************************************************
 Function:    categorize

 Syntax:      void categorize(number_of_regions,
                              number_of_available_bits,
                              rms_index,
                              power_categories,
                              category_balances)

              inputs:  number_of_regions
                       number_of_available_bits
                       rms_index[MAX_NUM_REGIONS]

              outputs: power_categories[MAX_NUM_REGIONS]
                       category_balances[MAX_NUM_RATE_CONTROL_POSSIBILITIES-1]

 Description: Computes a series of categorizations	
****************************************************************************************/

void categorize(int number_of_regions,
     int number_of_available_bits,
     int rms_index[MAX_NUM_REGIONS],
     int power_categories[MAX_NUM_REGIONS],
     int category_balances[MAX_NUM_RATE_CONTROL_POSSIBILITIES-1])
     
{
    int region;
    int j;
    int expected_number_of_code_bits;

    int delta;
    int offset;
    int test_offset;

    int num_rate_control_possibilities;


    if (number_of_regions == NUM_REGIONS)
        num_rate_control_possibilities = NUM_RATE_CONTROL_POSSIBILITIES;
    else
        num_rate_control_possibilities = MAX_NUM_RATE_CONTROL_POSSIBILITIES;


    /* At higher bit rates, there is an increase for most categories in average bit
       consumption per region. We compensate for this by pretending we have fewer
       available bits. 
    */
    if (number_of_regions == NUM_REGIONS) 
    {
        if (number_of_available_bits > FRAME_SIZE)
            number_of_available_bits =
            FRAME_SIZE + (((number_of_available_bits - FRAME_SIZE)*5) >> 3);
    }
    else if (number_of_regions == MAX_NUM_REGIONS)
    {
        if (number_of_available_bits > MAX_FRAME_SIZE)
            number_of_available_bits =
            MAX_FRAME_SIZE + (((number_of_available_bits - MAX_FRAME_SIZE)*5) >> 3);
    }

    offset = -32;
    delta = 32;
    do {
        test_offset = offset + delta;
        for (region=0; region<number_of_regions; region++)
        {
            j = (test_offset-rms_index[region]) >> 1;
            if (j < 0)
                j = 0;
            if (j > NUM_CATEGORIES-1)
                j = NUM_CATEGORIES-1;
            power_categories[region] = j;
        }
        expected_number_of_code_bits = 0;
        for (region=0; region<number_of_regions; region++)
             expected_number_of_code_bits += expected_bits_table[power_categories[region]];

        if (expected_number_of_code_bits >= number_of_available_bits - 32)
            offset = test_offset;

        delta >>= 1;
    } while (delta > 0);

    for (region=0; region<number_of_regions; region++)
    {
        j = (offset-rms_index[region]) >> 1;
        if (j < 0)
            j = 0;
        if (j > NUM_CATEGORIES-1)
            j = NUM_CATEGORIES-1;
        power_categories[region] = j;
    }
    expected_number_of_code_bits = 0;
    for (region=0; region<number_of_regions; region++)
         expected_number_of_code_bits += expected_bits_table[power_categories[region]];

    {
    int max_rate_categories[MAX_NUM_REGIONS];
    int min_rate_categories[MAX_NUM_REGIONS];
    int temp_category_balances[2*MAX_NUM_RATE_CONTROL_POSSIBILITIES];

    int raw_max, raw_min;
    int raw_max_index, raw_min_index;
    int max_rate_pointer, min_rate_pointer;
    int max, min;
    int itemp0;

    for (region=0; region<number_of_regions; region++)
    {
        max_rate_categories[region] = power_categories[region];
        min_rate_categories[region] = power_categories[region];
    }

    max = expected_number_of_code_bits;
    min = expected_number_of_code_bits;
    max_rate_pointer = num_rate_control_possibilities;
    min_rate_pointer = num_rate_control_possibilities;

    for (j=0; j<num_rate_control_possibilities-1; j++)
    {
        if (max+min <= 2*number_of_available_bits)
        {
            raw_min = 99;

            /* Search from lowest freq regions to highest for best region to reassign to
               a higher bit rate category. */
            for (region=0; region<number_of_regions; region++)
            {
                if (max_rate_categories[region] > 0)
                {
                    itemp0 = offset - rms_index[region] - 2*max_rate_categories[region];
                    if (itemp0 < raw_min)
                    {
                        raw_min = itemp0;
                        raw_min_index = region;
                    }
                }
            }
            max_rate_pointer--;
            temp_category_balances[max_rate_pointer] = raw_min_index;

            max -= expected_bits_table[max_rate_categories[raw_min_index]];
            max_rate_categories[raw_min_index] -= 1;
            max += expected_bits_table[max_rate_categories[raw_min_index]];
        }
        else
        {
            raw_max = -99;

            /* Search from highest freq regions to lowest for best region to reassign to
               a lower bit rate category. */
            for (region=number_of_regions-1; region >= 0; region--)
            {
                if (min_rate_categories[region] < NUM_CATEGORIES-1)
                {
                    itemp0 = offset - rms_index[region] - 2 * min_rate_categories[region];
                    if (itemp0 > raw_max)
                    {
                        raw_max = itemp0;
                        raw_max_index = region;
                    }
                }
            }
            temp_category_balances[min_rate_pointer] = raw_max_index;
            min_rate_pointer++;

            if (raw_max_index < 0 || raw_max_index > 28)
            	raw_max_index = 0;

            min -= expected_bits_table[min_rate_categories[raw_max_index]];
            min_rate_categories[raw_max_index] += 1;
            min += expected_bits_table[min_rate_categories[raw_max_index]];
        }
    }

    for (region=0; region<number_of_regions; region++)
        power_categories[region] = max_rate_categories[region];

    for (j=0; j<num_rate_control_possibilities-1; j++)
        category_balances[j] = temp_category_balances[max_rate_pointer++];
    }
}


static void set_up_one_table(cos_msin_t table[],
            long       length)
            
{
    double  angle, scale;
    int     index;

    scale  = PI / (double)(4 * length);
    for (index=0; index<length; index++)
    {
        angle                   = scale * ((double)index + 0.5);
        table[index].cosine     = (float) cos(angle);
        table[index].minus_sine = (float)(-sin(angle));
    }
}


/*********************************************************************************
 Function:    set_up_table s

 Syntax:      static void set_up_tables (long dct_size)
               
 Description: Set Up Tables of Cosine and Minus Sine Values	
               
*********************************************************************************/
static void set_up_tables(long dct_size)
{
    int length_log;
    int i, k;
    double scale;

    scale = sqrt(2.0 / dct_size);

    if (dct_size <= 0)
        printf("wrong dct size"), exit(1);

    length_log=0;

    while ((dct_size&1) == 0)
    {
        length_log++;
        dct_size >>= 1;
    }

    for (k=0; k<10; ++k)
    {
        for (i=0; i<10; ++i)
            dct_core_a[10*k+i] = (float)(cos(PI*(k+0.5) * (i+0.5)/10.) * scale); 
    }

    for (i=0; i<=length_log; i++)
        set_up_one_table (cos_msin_table[i], dct_size<<i);
}


/*********************************************************************************
 Function:    dct_type_iv 

 Syntax:      dct_type_iv (input, output, dct_length)
              float	input[], output[];
              long	dct_length;

 Description: Discrete Cosine Transform, Type IV
*********************************************************************************/

void dct_type_iv (float input[], float output[],
     long dct_length)
     
{
    static int	here_before = 0;
    float       buffer_a[MAX_DCT_SIZE], buffer_b[MAX_DCT_SIZE], buffer_c[MAX_DCT_SIZE];
    float       *in_ptr, *in_ptr_low, *in_ptr_high, *next_in_base;
    float       *out_ptr_low, *out_ptr_high, *next_out_base;
    float       *out_buffer, *in_buffer, *buffer_swap;
    float       in_val_low, in_val_high;
    float       *fptr0, *fptr1, *fptr2;
    float       cos_even, cos_odd, msin_even, msin_odd;
    int         set_span, set_count, set_count_log, pairs_left, sets_left;
    cos_msin_t  **table_ptr_ptr, *cos_msin_ptr;
    int         i, k;
    float       sum;
    int         dct_length_log;
    int         core_size;

    /*++++++++++++++++++++++++++++++++++++++++++++++++++*/
    /* Set up the tables if this is the first time here */
    /*++++++++++++++++++++++++++++++++++++++++++++++++++*/
    if (here_before == 0)
    {
        set_up_tables(dct_length);
        here_before = 1;
    }

    dct_length_log=1;
    core_size=dct_length;

    while ((core_size&1) == 0)
    {
        dct_length_log++;
        core_size >>= 1;
    }

    core_size <<= 1;
    dct_length_log--;

    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    /* Do the sum/difference butterflies, the first part of */
    /* converting one N-point transform into N/2 two-point  */
    /* transforms, where N = 1 << dct_length_log.           */
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    in_buffer  = input;
    out_buffer = buffer_a;
    for (set_count_log=0; set_count_log<=dct_length_log-2; set_count_log++) 
    {
        /*===========================================================*/
        /* Initialization for the loop over sets at the current size */
        /*===========================================================*/
        set_span      = dct_length >> set_count_log;

        set_count     = 1 << set_count_log;
        in_ptr        = in_buffer;
        next_out_base = out_buffer;

        /*=====================================*/
        /* Loop over all the sets of this size */
        /*=====================================*/
        for (sets_left=set_count; sets_left>0; sets_left--)
        {
            /*||||||||||||||||||||||||||||||||||||||||||||*/
            /* Set up output pointers for the current set */
            /*||||||||||||||||||||||||||||||||||||||||||||*/
            out_ptr_low    = next_out_base;
            next_out_base += set_span;
            out_ptr_high   = next_out_base;

            /*||||||||||||||||||||||||||||||||||||||||||||||||||*/
            /* Loop over all the butterflies in the current set */
            /*||||||||||||||||||||||||||||||||||||||||||||||||||*/
            do {
                in_val_low      = *in_ptr++;
                in_val_high     = *in_ptr++;
                *out_ptr_low++  = in_val_low + in_val_high;
                *--out_ptr_high = in_val_low - in_val_high;
            } while (out_ptr_low < out_ptr_high);
        } /* End of loop over sets of the current size */

        /*============================================================*/
        /* Decide which buffers to use as input and output next time. */
        /* Except for the first time (when the input buffer is the    */
        /* subroutine input) we just alternate the local buffers.     */
        /*============================================================*/
        in_buffer = out_buffer;
        if (out_buffer == buffer_a)
            out_buffer = buffer_b;
        else
            out_buffer = buffer_a;
    } /* End of loop over set sizes */


    /*+++++++++++++++++++++++++++++++++++++*/
    /* Do dct_size/10 ten-point transforms */
    /*+++++++++++++++++++++++++++++++++++++*/
    fptr0       = in_buffer;
    buffer_swap = buffer_c;

    for (pairs_left = 1<<(dct_length_log-1); pairs_left > 0; pairs_left--) 
    {
        fptr2 = dct_core_a;
        for (k=0; k<core_size; k++ )
        {
            fptr1 = fptr0;
            sum=0;
            for (i=0; i<core_size; i++)
                sum += *fptr1++ * *fptr2++;
            buffer_swap[k] = sum;
        }
        fptr0 += core_size;
        buffer_swap += core_size;
    }

    memcpy(in_buffer, buffer_c, dct_length*sizeof(float));

    table_ptr_ptr = cos_msin_table;

    /*++++++++++++++++++++++++++++++*/
    /* Perform rotation butterflies */
    /*++++++++++++++++++++++++++++++*/
    for (set_count_log = dct_length_log-2; set_count_log >= 0; set_count_log--)
    {
        /*===========================================================*/
        /* Initialization for the loop over sets at the current size */
        /*===========================================================*/
        set_span      = dct_length >> set_count_log;

        set_count     = 1 << set_count_log;
        next_in_base  = in_buffer;
        if (set_count_log == 0)
            next_out_base = output;
        else
            next_out_base = out_buffer;
        ++table_ptr_ptr;

        /*=====================================*/
        /* Loop over all the sets of this size */
        /*=====================================*/

        for (sets_left=set_count; sets_left>0; sets_left--)
        {
            /*|||||||||||||||||||||||||||||||||||||||||*/
            /* Set up the pointers for the current set */
            /*|||||||||||||||||||||||||||||||||||||||||*/
            in_ptr_low     = next_in_base;
            in_ptr_high    = in_ptr_low + (set_span >> 1);
            next_in_base  += set_span;
            out_ptr_low    = next_out_base;
            next_out_base += set_span;
            out_ptr_high   = next_out_base;
            cos_msin_ptr   = *table_ptr_ptr;

            /*||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
            /* Loop over all the butterfly pairs in the current set */
            /*||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
            do {
                cos_even        = (*cos_msin_ptr).cosine;
                msin_even       = (*cos_msin_ptr++).minus_sine;
                *out_ptr_low++  = cos_even * *in_ptr_low - msin_even * *in_ptr_high;
                *--out_ptr_high = msin_even * *in_ptr_low++ +  cos_even * *in_ptr_high++;

                cos_odd         = (*cos_msin_ptr).cosine;
                msin_odd        = (*cos_msin_ptr++).minus_sine;
                *out_ptr_low++  =  cos_odd  * *in_ptr_low  + msin_odd  * *in_ptr_high;
                *--out_ptr_high = msin_odd  * *in_ptr_low++  -  cos_odd  * *in_ptr_high++;

            } while (out_ptr_low < out_ptr_high);
        } /* End of loop over sets of the current size */

        /*=============================================*/
        /* Swap input and output buffers for next time */
        /*=============================================*/
        buffer_swap = in_buffer;
        in_buffer   = out_buffer;
        out_buffer  = buffer_swap;
    }
}




/************************************************************************************
 Function:     G722.1 Annex C main decoder function (floating-point)

 Syntax:       decode <data format> <input file> <output file> <bit rate> <bandwidth>

                      <data format> - 0 for packed format/1 for ITU format
                      <input file>  - encoded bitstream file
                      <output file> - output audio file
                      <bit rate>    - 24, 32, and 48 kbps
                      <bandwidth>   - 7 or 14 kHz

 Description:  Main processing loop for the G.722.1 Annex C decoder (floating-point)

 Design Notes: 16kbit/sec is also supported for bandwidth of 7kHz

************************************************************************************/

void G722_1_1C_Float_decoder(short *output,short *out_words,int bit_rate,int bandwidth)
{
    int i;
    int number_of_regions;   
    float decoder_mlt_coefs[MAX_DCT_SIZE];
    float float_out_samples[MAX_DCT_SIZE];
    int number_of_bits_per_frame;
    int number_of_16bit_words_per_frame;  
    int framesize; 
	int frame_error_flag=0;
	short int out_words1[MAX_BITS_PER_FRAME/16];
	short int output1[MAX_DCT_SIZE];
    number_of_bits_per_frame = (int)(bit_rate / 50);
    if (bandwidth == 7000)
    {
        number_of_regions = NUM_REGIONS;
        framesize = FRAME_SIZE;       
    }
    else
    {
        number_of_regions = MAX_NUM_REGIONS;
        framesize = MAX_FRAME_SIZE;
    }

    number_of_16bit_words_per_frame = number_of_bits_per_frame / 16;

	for(i=0;i<MAX_BITS_PER_FRAME/16;i++)
	{
		out_words1[i]=*out_words;
		out_words++;
	}
        /* Decode the mlt coefs */
        decoder(number_of_regions,
                number_of_bits_per_frame,
                out_words1,
                decoder_mlt_coefs,
                frame_error_flag);

        /* Convert rmlt coefs to output samples */
        rmlt_coefs_to_samples(decoder_mlt_coefs, float_out_samples, framesize);

        /* Convert the floating-point output to 16-b integer output */
        {
        float ftemp0;
        for (i=0; i<framesize; i++)
        {
            ftemp0 = float_out_samples[i];

            if (ftemp0 >= 0.0)
            {
                if (ftemp0 < 32767.0)
                    output1[i] = (int)(ftemp0 + 0.5);
                else
                    output1[i] = 32767;
            }
            else 
            {
                if (ftemp0 > -32768.0)
                    output1[i] = (int) (ftemp0 - 0.5);
                else
                    output1[i] = -32768;
            }
        }
        }

        /* For ITU testing and off the 2 lsbs. */
        for (i=0; i<framesize; i++)
             output[i] &= 0xfffc;
		for (i=0;i<MAX_DCT_SIZE;i++)
		{
			*output=output1[i];
			*output++;
		}
}
/*********************************************************************************
 Function:    rmlt_samples_to_coefs

 Syntax:      void rmlt_coefs_to_samples(coefs,
                                         out_samples,
                                         dct_size)
              float *coefs;
              float *out_samples;
              int   dct_size;

              inputs:  float *coefs
                       int dct_size

              outputs: float *out_samples

 Description: Converts the mlt_coefs to samples
*********************************************************************************/

void rmlt_coefs_to_samples(float *coefs,
     float *out_samples,
     int   dct_size)

{
    extern void dct_type_iv(float *, float *, long);

    static float old_samples[MAX_DCT_SIZE>>1];
    static float window[MAX_DCT_SIZE];
    static int   here_before = 0;

    float sum;
    int index, vals_left;
    double angle;
    float new_samples[MAX_DCT_SIZE];
    float *new_ptr, *old_ptr;
    float *win_new, *win_old;
    float *out_ptr;
    int half_dct_size;


    half_dct_size = dct_size>>1;

    /*++++++++++++++++++++++++++++++++++++++*/
    /* Set up some data the first time here */
    /*++++++++++++++++++++++++++++++++++++++*/

    if (here_before==0)
	{
        for (index=0; index<dct_size; index++)
        {
            angle = (PI / 2.0) * ((double) index + 0.5) / (double)dct_size;

            /* This changed when ENCODER_SCALE_FACTOR changed from 20853.0 to 18318.0. */
            /*       window[index] = 2.20895 * sin(angle); */
            /*       window[index] = (2.20895 * 129.5704536) * sin(angle); */
            /*       window[index] = (2.20895 * 129.6) * sin(angle); */

            window[index] = (float)sin(angle);
        }
        for (index=0; index<half_dct_size; index++)
            old_samples[index] = 0.0;
        here_before = 1;
    }

    /*+++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    /* Perform a Type IV (inverse) DCT on the coefficients */
    /*+++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    dct_type_iv(coefs, new_samples, dct_size);

    /*++++++++++++++++++++++++++++++++++++++++++++*/
    /* Get the first half of the windowed samples */
    /*++++++++++++++++++++++++++++++++++++++++++++*/
    out_ptr = out_samples;
    win_new = window;
    win_old = window + dct_size;
    old_ptr = old_samples;
    new_ptr = new_samples + half_dct_size;

    for (vals_left=half_dct_size;  vals_left>0;  vals_left--)
    {
        sum = *win_new++ * *--new_ptr;
        sum += *--win_old * *old_ptr++;
        *out_ptr++ = sum;
    }

    /*+++++++++++++++++++++++++++++++++++++++++++++*/
    /* Get the second half of the windowed samples */
    /*+++++++++++++++++++++++++++++++++++++++++++++*/
    for (vals_left=half_dct_size;  vals_left>0;  vals_left--)
    {
       sum = *win_new++ *  *new_ptr++;
       sum -= *--win_old *  *--old_ptr;
       *out_ptr++ = sum;
    }

    /*+++++++++++++++++++++++++++++++++++++++++++++++*/
    /* Save the second half of the new samples for   */
    /* next time, when they will be the old samples. */
    /*+++++++++++++++++++++++++++++++++++++++++++++++*/
    new_ptr = new_samples + half_dct_size;
    old_ptr = old_samples;
    for (vals_left=half_dct_size; vals_left>0; vals_left--)
        *old_ptr++ = *new_ptr++;
}



/***************************************************************************
 Function:    decoder

 Syntax:      void decoder(number_of_regions,
                           number_of_bits_per_frame,
                           bitstream,
                           decoder_mlt_coefs,
                           frame_error_flag)
              int number_of_regions;
              int number_of_bits_per_frame;
              short int bitstream[];
              float decoder_mlt_coefs[MAX_DCT_SIZE];
              int frame_error_flag;

              inputs:  int number_of_regions
                       int number_of_bits_per_frame
                       short int bitstream[]
                       int frame_error_flag

              outputs: float decoder_mlt_coefs[]

 Description: Decodes the bitstream into mlt coefs using G.722.1 Annex C
***************************************************************************/

void decoder(int number_of_regions,
     int number_of_bits_per_frame,
     short int bitstream[],
     float decoder_mlt_coefs[MAX_DCT_SIZE],
     int frame_error_flag)
     
{
    extern void categorize(int, int, int[], int[], int[]);

    static float old_decoder_mlt_coefs[MAX_DCT_SIZE];
    int absolute_region_power_index[MAX_NUM_REGIONS];
    int decoder_power_categories[MAX_NUM_REGIONS];
    int decoder_category_balances[MAX_NUM_RATE_CONTROL_POSSIBILITIES-1];
    int rate_control;
    int num_rate_control_bits;
    int num_rate_control_possibilities;
    float decoder_region_standard_deviation[MAX_NUM_REGIONS];
    int number_of_coefs;
    int number_of_valid_coefs;
    int rmlt_scale_factor;


    number_of_valid_coefs = number_of_regions * region_size;

    /*
    ** Get some parameters based solely on the bitstream style
    */
    if (number_of_regions==NUM_REGIONS)
    {
      number_of_coefs                = FRAME_SIZE;
      num_rate_control_bits          = NUM_RATE_CONTROL_BITS;
      num_rate_control_possibilities = NUM_RATE_CONTROL_POSSIBILITIES;
      rmlt_scale_factor              = (int)INTEROP_RMLT_SCALE_FACTOR_7;
    }
    else
    {
      number_of_coefs                = MAX_FRAME_SIZE;
      num_rate_control_bits          = MAX_NUM_RATE_CONTROL_BITS;
      num_rate_control_possibilities = MAX_NUM_RATE_CONTROL_POSSIBILITIES;
      rmlt_scale_factor              = (int)INTEROP_RMLT_SCALE_FACTOR_14;
    }

    if (frame_error_flag == 0)
    {
        code_word_ptr = bitstream;
        code_bit_count = 0;

        number_of_bits_left = number_of_bits_per_frame;

        decode_envelope(number_of_regions,
                        decoder_region_standard_deviation,
                        absolute_region_power_index);

        {
        int i;
        rate_control = 0;
        for (i=0; i<num_rate_control_bits; i++)
        {
            GET_NEXT_BIT;
            rate_control <<= 1;
            rate_control += next_bit;
        }
        }
        number_of_bits_left -= num_rate_control_bits;

        categorize(number_of_regions,
                   number_of_bits_left,
                   absolute_region_power_index,
                   decoder_power_categories,
                   decoder_category_balances);

        rate_adjust_categories(rate_control,
                               decoder_power_categories,
                               decoder_category_balances);

        decode_vector_quantized_mlt_indices(number_of_regions,
                                            decoder_region_standard_deviation,
                                            decoder_power_categories,
                                            decoder_mlt_coefs,
                                            rmlt_scale_factor);

        /* Test for bit stream errors. */
        if (number_of_bits_left > 0)
		{
            {
            int i;
            for (i=0; i<number_of_bits_left; i++)
            {
                GET_NEXT_BIT;
                if (next_bit == 0)
                    frame_error_flag = 1;
            }	
            }
        }
        else
        {
            if (rate_control < num_rate_control_possibilities-1)
            {
                if (number_of_bits_left < 0)
                    frame_error_flag |= 2;
            }
        }

        {
        int region;
        for (region=0; region<number_of_regions; region++)
        {
            if ((absolute_region_power_index[region]+ESF_ADJUSTMENT_TO_RMS_INDEX > 31) ||
                (absolute_region_power_index[region]+ESF_ADJUSTMENT_TO_RMS_INDEX < -8))
                frame_error_flag |= 4;
        }
        }
    }


    /* If both the current and previous frames are errored,
       set the mlt coefficients to 0. If only the current frame
       is errored, then repeat the previous frame's mlt coefficients. */
    {
    int i;
    if (frame_error_flag != 0)
    {
        for (i = 0; i < number_of_valid_coefs; i++)
            decoder_mlt_coefs[i] = old_decoder_mlt_coefs[i];
        for (i = 0; i < number_of_valid_coefs; i++)
            old_decoder_mlt_coefs[i] = 0;
    }
    else
    {
        /* Store in case next frame is errored. */
		for (i = 0; i < number_of_valid_coefs; i++)
            old_decoder_mlt_coefs[i] = decoder_mlt_coefs[i];
    }
    }


    /* Zero out the upper 1/8 of the spectrum. */
    {
    int i;
    for (i = number_of_valid_coefs; i < number_of_coefs; i++)
        decoder_mlt_coefs[i] = 0;
    }
}


/***************************************************************************
 Function:    decode_envelope

 Syntax:      void decode_envelope(number_of_regions,
                                   decoder_region_standard_deviation,
                                   absolute_region_power_index)
              int   number_of_regions;
              float decoder_region_standard_deviation[MAX_NUM_REGIONS];
              int   absolute_region_power_index[MAX_NUM_REGIONS]

              inputs:  int   number_of_regions

              outputs: float decoder_region_standard_deviation[MAX_NUM_REGIONS];
                       int   absolute_region_power_index[MAX_NUM_REGIONS];

 Description: Recover differential_region_power_index from code bits
***************************************************************************/

void decode_envelope(int   number_of_regions,
     float decoder_region_standard_deviation[MAX_NUM_REGIONS],
     int   absolute_region_power_index[MAX_NUM_REGIONS])
     
{
    int region;
    int i;
    int index;
    int differential_region_power_index[MAX_NUM_REGIONS];

    /* Recover differential_region_power_index[] from code_bits[]. */
    index = 0;
    for (i=0; i<5; i++)
    {
        GET_NEXT_BIT;
        index <<= 1;
        index += next_bit;
    }

    /* ESF_ADJUSTMENT_TO_RMS_INDEX compensates for the current (9/30/96)
       IMLT being scaled to high by the ninth power of sqrt(2). */
    differential_region_power_index[0] = index-ESF_ADJUSTMENT_TO_RMS_INDEX;
    number_of_bits_left -= 5;

    for (region=1; region<number_of_regions; region++)
    {
        index = 0;
        do {
            GET_NEXT_BIT;
            if (next_bit == 0)
                index = differential_region_power_decoder_tree[region][index][0];
            else
                index = differential_region_power_decoder_tree[region][index][1];
            number_of_bits_left--;
        } while (index > 0);
        differential_region_power_index[region] = -index;
    }

    /* Reconstruct absolute_region_power_index[] from differential_region_power_index[]. */
    absolute_region_power_index[0] = differential_region_power_index[0];
  
    for (region=1; region<number_of_regions; region++)
    {
        absolute_region_power_index[region] = absolute_region_power_index[region-1] +
                                              differential_region_power_index[region] + DRP_DIFF_MIN;
    }

    /* Reconstruct decoder_region_standard_deviation[] from absolute_region_power_index[]. */
    for (region=0; region<number_of_regions; region++)
    {
        i = absolute_region_power_index[region]+REGION_POWER_TABLE_NUM_NEGATIVES;
        decoder_region_standard_deviation[region] = region_standard_deviation_table[i];
    }
}


/***************************************************************************
 Function:    rate_adjust_categories

 Syntax:      void rate_adjust_categories(rate_control,
                                          decoder_power_categories,
                                          decoder_category_balances)
              int rate_control;
              int decoder_power_categories[MAX_NUM_REGIONS];
              int decoder_category_balances[MAX_NUM_RATE_CONTROL_POSSIBILITIES-1];
 

              inputs:  int rate_control,
                       int *decoder_power_categories,
                       int *decoder_category_balances,

              outputs: int *decoder_power_categories,

 Description: Adjust the power categories based on the categorization control
***************************************************************************/

void rate_adjust_categories(int rate_control,
     int decoder_power_categories[MAX_NUM_REGIONS],
     int decoder_category_balances[MAX_NUM_RATE_CONTROL_POSSIBILITIES-1])
     
{
    int i;
    int region;

    i = 0;
    while (rate_control > 0)
	{
        region = decoder_category_balances[i++];
        if (region < 0 || region > 28)
        	region = 0;
        decoder_power_categories[region]++;
        rate_control--;
    }
}

#define get_rand() \
random_word = b0+b3; \
if ((random_word & 32768) != 0) random_word++; \
b3 = b2; \
b2 = b1; \
b1 = b0; \
b0 = random_word;



/***************************************************************************
 Function:    decode_vector_quantized_mlt_indices

 Syntax:      void decode_vector_quantized_mlt_indices(number_of_regions,
                                                       decoder_region_standard_deviation,
                                                       decoder_power_categories,
                                                       decoder_mlt_coefs,
                                                       rmlt_scale_factor)
              int   number_of_regions;
              float decoder_region_standard_deviation[MAX_NUM_REGIONS];
              int   decoder_power_categories[MAX_NUM_REGIONS];
              float decoder_mlt_coefs[MAX_DCT_SIZE];
              int   rmlt_scale_factor;

              inputs:  int   number_of_regions
                       float *decoder_region_standard_deviation
                       int   *decoder_power_categories
                       int   rmlt_scale_factor;

              outputs: float decoder_mlt_coefs[MAX_DCT_SIZE]


 Description: Decode MLT coefficients
***************************************************************************/

void decode_vector_quantized_mlt_indices( int   number_of_regions,
    float decoder_region_standard_deviation[MAX_NUM_REGIONS],
    int   decoder_power_categories[MAX_NUM_REGIONS],
    float decoder_mlt_coefs[MAX_DCT_SIZE],
    int   rmlt_scale_factor)
   
{
    float standard_deviation;
    float *decoder_mlt_ptr;
    float decoder_mlt_value;
    float temp1;
    float noifillpos;
    float noifillneg;

    static float noise_fill_factor_cat5[20] = {0.70711f, 0.6179f,  0.5005f,  0.3220f,
                                               0.17678f, 0.17678f, 0.17678f, 0.17678f,
                                               0.17678f, 0.17678f, 0.17678f, 0.17678f,
                                               0.17678f, 0.17678f, 0.17678f, 0.17678f,
                                               0.17678f, 0.17678f, 0.17678f, 0.17678f};

    static float noise_fill_factor_cat6[20] = {0.70711f, 0.5686f,  0.3563f,  0.25f,
                                               0.25f,    0.25f,    0.25f,    0.25f,
                                               0.25f,    0.25f,    0.25f,    0.25f,
                                               0.25f,    0.25f,    0.25f,    0.25f,
                                               0.25f,    0.25f,    0.25f,    0.25f};

    int region;
    int category;
    int j, n;
    int k[MAX_VECTOR_DIMENSION];
    int vec_dim;
    int num_vecs;
    int index, signs_index;
    int bit;
    int num_sign_bits;
    int num_bits;
    int ran_out_of_bits_flag;
    int *decoder_table_ptr;

    static int here_before = 0;
    static int b0, b1, b2, b3;
    int random_word;

    if (here_before == 0)
    {
        here_before = 1;
        b0 = 1;
        b1 = 1;
        b2 = 1;
        b3 = 1;
    }         

    ran_out_of_bits_flag = 0;
    for (region=0; region<number_of_regions; region++)
    {
        category = decoder_power_categories[region];
        decoder_mlt_ptr = &decoder_mlt_coefs[region*region_size];
        standard_deviation = decoder_region_standard_deviation[region];
        if (category < NUM_CATEGORIES-1)
        {
            decoder_table_ptr = (int *) table_of_decoder_tables[category];
            vec_dim = vector_dimension[category];
            num_vecs = number_of_vectors[category];

            for (n=0; n<num_vecs; n++)
            {
                num_bits = 0;

                index = 0;
                do {
                    if (number_of_bits_left <= 0)
                    {
                        ran_out_of_bits_flag = 1;
                        break;
                    }

                    GET_NEXT_BIT;
                    if (next_bit == 0)
                        index = *(decoder_table_ptr + 2*index);
                    else
                        index = *(decoder_table_ptr + 2*index + 1);

                    number_of_bits_left--;
                } while (index > 0);

                if (ran_out_of_bits_flag == 1)
                    break;
                index = -index;
                num_sign_bits = index_to_array(index,k,category);

                if (number_of_bits_left >= num_sign_bits)
                {
                    if (num_sign_bits != 0)
                    {
                        signs_index = 0;
                        for (j=0; j<num_sign_bits; j++)
                        {
                            GET_NEXT_BIT;
                            signs_index <<= 1;
                            signs_index += next_bit;
                            number_of_bits_left--;
                        }
                        bit = 1 << (num_sign_bits-1);
                    }
                    for (j=0; j<vec_dim; j++)
                    {
                        /*
                        ** This was changed to for fixed point interop
                        ** A scale factor is used to adjust the decoded mlt value. 
                        */
                        decoder_mlt_value = standard_deviation * mlt_quant_centroid[category][k[j]]
                                            * (float)rmlt_scale_factor;

                        if (decoder_mlt_value != 0)
                        {
                            if ((signs_index & bit) == 0)
                                decoder_mlt_value *= -1;
                            bit >>= 1;
                        }

                        *decoder_mlt_ptr++ = decoder_mlt_value;
                    }
                }
                else
                {
                    ran_out_of_bits_flag = 1;
                    break;
                }
            }

            /* If ran out of bits during decoding do noise fill for remaining regions. */
            if (ran_out_of_bits_flag == 1)
            {
                for (j=region+1; j<number_of_regions; j++)
                    decoder_power_categories[j] = NUM_CATEGORIES-1;
                category = NUM_CATEGORIES-1;
                decoder_mlt_ptr = &decoder_mlt_coefs[region*region_size];
            }
        }


        if (category == NUM_CATEGORIES-3)
        {
            decoder_mlt_ptr = &decoder_mlt_coefs[region*region_size];
            n = 0;
            for (j=0; j<region_size; j++)
            {
                if (*decoder_mlt_ptr != 0)
                {
                    n++;
                    if (fabs(*decoder_mlt_ptr) > (2.0*(float)rmlt_scale_factor*standard_deviation))
                    {
                        n += 3;
                    }
                }
                decoder_mlt_ptr++;
            }
            if (n>19)
                n=19;
            temp1 = noise_fill_factor_cat5[n];

            decoder_mlt_ptr = &decoder_mlt_coefs[region*region_size];

            /* noifillpos = standard_deviation * 0.17678; */
            noifillpos = standard_deviation * temp1;

            noifillneg = -noifillpos;

            /* This assumes region_size = 20 */
            get_rand();
            for (j=0; j<10; j++)
            {
                if (*decoder_mlt_ptr == 0)
                {
                    temp1 = noifillpos;
                    if ((random_word & 1) == 0)
                        temp1 = noifillneg;
                    *decoder_mlt_ptr = temp1 * (float)rmlt_scale_factor;
                    random_word >>= 1;
                }
                decoder_mlt_ptr++;
            }
            get_rand();
            for (j=0; j<10; j++)
            {
                if (*decoder_mlt_ptr == 0)
                {
                    temp1 = noifillpos;
                    if ((random_word & 1) == 0)
                        temp1 = noifillneg;
                    *decoder_mlt_ptr = temp1 * (float)rmlt_scale_factor;
                    random_word >>= 1;
                }
                decoder_mlt_ptr++;
            }
        }

        if (category == NUM_CATEGORIES-2)
        {
            decoder_mlt_ptr = &decoder_mlt_coefs[region*region_size];
            n = 0;
            for (j=0; j<region_size; j++)
            {
                if (*decoder_mlt_ptr++ != 0)
                    n++;
            }
            temp1 = noise_fill_factor_cat6[n];

            decoder_mlt_ptr = &decoder_mlt_coefs[region*region_size];

            noifillpos = standard_deviation * temp1;

            noifillneg = -noifillpos;

            /* This assumes region_size = 20 */
            get_rand();
            for (j=0; j<10; j++)
			{
			    if (*decoder_mlt_ptr == 0)
			    {
			        temp1 = noifillpos;
			        if ((random_word & 1) == 0)
			            temp1 = noifillneg;
			        *decoder_mlt_ptr = temp1 * (float)rmlt_scale_factor;
			        random_word >>= 1;
			    }
			decoder_mlt_ptr++;
			}
			get_rand();
			for (j=0; j<10; j++)
			{
			    if (*decoder_mlt_ptr == 0)
			    {
			        temp1 = noifillpos;
			        if ((random_word & 1) == 0)
			            temp1 = noifillneg;
			        *decoder_mlt_ptr = temp1 * (float)rmlt_scale_factor;
			        random_word >>= 1;
			    }
			decoder_mlt_ptr++;
			}
        }

        if (category == NUM_CATEGORIES-1)
        {
            noifillpos =  (float)( standard_deviation * 0.70711);

            noifillneg = -noifillpos;

            /* This assumes region_size = 20 */
            get_rand();
            for (j=0; j<10; j++)
            {
                temp1 = noifillpos;
                if ((random_word & 1) == 0)
                temp1 = noifillneg;
                *decoder_mlt_ptr++ = temp1 * (float)rmlt_scale_factor;
                random_word >>= 1;
            }
            get_rand();
            for (j=0; j<10; j++)
            {
                temp1 = noifillpos;
                if ((random_word & 1) == 0)
                    temp1 = noifillneg;
                *decoder_mlt_ptr++ = temp1 * (float)rmlt_scale_factor;
                random_word >>= 1;
            }
        }
    }

    if (ran_out_of_bits_flag)
        number_of_bits_left = -1;

}


/****************************************************************************************
 Function:    index_to_array 

 Syntax:      number_of_non_zero = index_to_array(int index,
                                                  int array[MAX_VECTOR_DIMENSION],
                                                  int category)

              inputs:  int index
                       int category

              outputs: int array[MAX_VECTOR_DIMENSION] - used in decoder to access
                                                         mlt_quant_centroid table
                       int number_of_non_zero          - number of non zero elements
                                                         in the array

 Description: Computes an array of sign bits with the length of the category vector
              Returns the number of sign bits and the array
****************************************************************************************/

int index_to_array(int index,
    int array[MAX_VECTOR_DIMENSION],
    int category)
    
{
    int j, q, p;
    int number_of_non_zero;
    int max_bin_plus_one;
    int inverse_of_max_bin_plus_one;

    number_of_non_zero = 0;
    p = index;
    max_bin_plus_one = max_bin[category] + 1;
    inverse_of_max_bin_plus_one = max_bin_plus_one_inverse[category];

    for (j=vector_dimension[category]-1; j>=0; j--)
    {
        /* q = p/max_bin_plus_one; */
        q = (p*inverse_of_max_bin_plus_one) >> 15;
        array[j] = p - q*max_bin_plus_one;
        p = q;
        if (array[j] != 0)
            number_of_non_zero++;
    }

    return(number_of_non_zero);
}











