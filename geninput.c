/* geninput.c
 * MP3
 * Harlan Russell
 * ECE 2230, Fall 2018
 *
 * Compile with 
 *     gcc -g -Wall geninput.c -o geninput 
 *
 * Purpose: Generate an input file for MP3 
 * Assumptions: Input file is for testing sort.  Creates
 *              an unsorted list, uses ADDTAIL to insert items, and
 *              calls SORT to sort the list
 *
 * Command line arguments:
 *    1st -- number of records to create
 *    2nd -- type of list to create
 *           1: random addresses [0, 3/4 number records)
 *           2: assending and sequential
 *           3: descending and sequential 
 *    3rd -- type of sort
 *           1: Insertion
 *           2: Recursive Selection
 *           3: Iterative Selection
 *           4: Merge
 *    optional 4th argument to change the seed
 *
 * Pipe the output of this program into lab3. For example
 *     ./geninput 10000 1 1 | ./lab3
 *
 * See also mp3test.sh 
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int records = 0, list_type = -1, sort_type = -1;
    int addr_range;
    int su_id;
    int seed = 1473633460;

    if (argc != 4 && argc != 5) {
        printf("Usage: ./geninput listsize listype sorttype [seed]\n");
        printf("\tlistsize: number of records to create\n");
        printf("\tlisttype: {1, 2, 3} for random, ascending or descending\n");
        printf("\tsorttype: 1: Insertion\n");
        printf("\t          2: Recursive Selection\n");
        printf("\t          3: Iterative Selection\n");
        printf("\t          4: Merge\n");
        printf("\tseed: optional seed for random number generator\n");
        exit(1);
    }
    records = atoi(argv[1]);
    if (records < 2) {
        printf("genniput has invalid number records: %d\n", records);
        exit(2);
    }
    list_type = atoi(argv[2]);
    sort_type = atoi(argv[3]);
    if (sort_type < 1 || sort_type > 4) {
        printf("genniput has invalid type of sort: %d\n", sort_type);
        exit(2);
    }

    if (argc == 5) {
        int temp_seed = -1;
        temp_seed = atoi(argv[4]);
        if (temp_seed > 0)
            seed = temp_seed;
    }
    //printf("Seed %d\n", seed);
    addr_range = records * 0.75;
    srand48(seed);

    printf("CREATE %d\n", records);
    int i;
    if (list_type == 1) {
        // random addresses, 
        for (i = 0; i < records; i++) {
            if (i == records/4 || i == records/2 || i == 3*records/4) {
                su_id = records;
            } else {
                su_id = (int) (addr_range * drand48()) + 1;
            }
            printf("ADDTAIL %d\n", su_id);
        }
    }
    else if (list_type == 2) {
        // ascending addresses
        for (i = 0; i < records; i++) {
            printf("ADDTAIL %d\n", i+1);
        }
    }
    else if (list_type == 3) {
        // descending addresses
        for (i = 0; i < records; i++) {
            printf("ADDTAIL %d\n", records - i);
        }
    }
    else {
        printf("geninput has invalid list type: %d\n", list_type);
        exit(3);
    }
    printf("SORT %d\n", sort_type);
    //printf("PRINTWAITING\n");
    printf("QUIT\n");
    exit(0);
}

