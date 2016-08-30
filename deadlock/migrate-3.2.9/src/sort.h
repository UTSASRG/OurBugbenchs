/* --------------------------------------------*
 * sort.h             
 * comparison routines for the different sorts
 * part of the lamarc package   
 * --------------------------------------------*
 * Peter Beerli 1994                            
 */
#ifndef MIGRATION_SORT
#define MIGRATION_SORT
/*-------------------------------------------
 * comparison between characters
 * used in qsort()
 */
extern int charcmp (const void *v1, const void *v2);

/*-------------------------------------------
 * comparison between strings
 * used in qsort()
 */
extern int stringcmp (const void *v1, const void *v2);


/*-------------------------------------------
 * comparison between numbers (doubles, floats, longs,
 *  and ints) used in qsort()
 */
extern int numcmp (const void *v1, const void *v2);
extern int floatcmp (const void *v1, const void *v2);
extern int longcmp (const void *v1, const void *v2);
extern int intcmp (const void *v1, const void *v2);


/*-------------------------------------------
* comparison between pairs of doubles
* used in qsort()
* -- using the second value for comparison
*/
extern int
paircmp (const void *v1, const void *v2);
/* --using the first value for comparison */
extern int
paircmp_first (const void *v1, const void *v2);

/*-------------------------------------------
 * sort first the second element and then sort
 * those elements that are the same using the first element
 */
extern void  paired_qsort2(pair *x, long xelem);

/*-------------------------------------------
 * comparison between the times in the
 * the timevector (vtlist) and a given time
 * used in qsort()
 */
extern int agecmp (const void *x, const void *y);

/*-------------------------------------------
 * comparison in nodep->v 
 * used only for the tipnodes, sorts the
 * tips=2=having '?' alleles
 * to the end of nodelist.
 * used in qsort()
 */
extern int delcmp (const void *x, const void *y);


/*------------------------------------------
 * compares migr_table time entries
 * used in qsort of the migr_table
 */
extern int migr_time_cmp (const void *x, const void *y);


/*-------------------------------------------
 * comparison between the times in the
 * the timevector (vtlist) and a given time
 * used in bsearch()
 */
extern int searchagecmp (const void *x, const void *y);


/*-------------------------------------------
 * comparison between aic in the aicvec
 * produces a sorted list of aic values
 * for model selection
 */
extern int aiccmp (const void *x, const void *y);
#endif
