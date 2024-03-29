#ifndef _H_ATTACK
#define _H_ATTACK

#include "../Chiffrement/keys.h"
#include "../Chiffrement/Encryption.h"
#include "../Dechiffrement/Decryption.h"


typedef struct couple_strings
{
    char * strA;
    char * strB;
}
Couple_strings;

#define SIZE_ALL 200000//16777216

void init_couple(Couple_strings * couple, char * str1 , char * str2);

void calculate_possibilities(char * message, char * crypted);
void * calcul_encryption_A(void * message);
void * calcul_encryption_B(void * message);
void * calcul_encryption_C(void * message);
void * calcul_encryption_D(void * message);
void * calcul_decryption_A(void * crypted);
void * calcul_decryption_B(void * crypted);
void * calcul_decryption_C(void * crypted);
void * calcul_decryption_D(void * crypted);

void iteration_to_key(char * entry_params, int number);

/* Search functions */

typedef struct tables
{
	double *left_array;
	double *right_array;
} Tables;

Couple_strings search_collisions(Tables *tables);
void *search_top(void *tables);
void *search_down(void  *tables);


double char_to_double(char *entry);


#endif
