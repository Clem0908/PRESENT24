#include "../../headers/Attaque/Attack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>

double g_liste_encryption[SIZE_ALL]; //Stockage des résultats obtenus suite au chiffrement du message clair
double g_liste_decryption[SIZE_ALL]; //Stockage des résultats obtenus suite au déchiffrement du message crypté

void init_couple(Couple_strings * couple,char * str1 , char * str2)
{
    if(couple != NULL)
    {
        int size = sizeof(str1) + 1;
        couple->strA = malloc(size);
        couple->strB = malloc(size);

        for(int i = 0 ; i < size ; i++ )
        {
            couple->strA[i] = str1[i];
            couple->strB[i] = str2[i];
        }
        couple->strA[size-1] = '\0';
        couple->strB[size-1] = '\0';
    }
}

void iteration_to_key(char * entry_params, int number)
{
    int exposant = 23;
    int comparator = pow(2,exposant);
    int cmp = 0;

    while(exposant >= 0)
    {
        if (number >= comparator)
        {
            entry_params[cmp] = '1';
            number = number - comparator;
        }
        else
        {
            entry_params[cmp] = '0';
        }
        exposant--;
        cmp++;
        comparator = pow(2, exposant);
    }
}


void * calcul_encryption_A(void * message)
{
    char * input = (char *) (message);
    char *tmp1 = malloc(sizeof(char) * 25);
    Keys *tmp2 = malloc(sizeof(Keys));

    for(int i = 0 ; i < SIZE_ALL/2 ; i++)
    {
	    iteration_to_key(tmp1,i);
        init_key(tmp2,tmp1);

	    present(tmp2,input,tmp1);
	    g_liste_encryption[i] = char_to_double(tmp1);
    }

    free(tmp1);
    free(tmp2);
    pthread_exit(NULL);
}
void * calcul_encryption_B(void * message)
{
    char * input = (char *) (message);
    
    char *tmp1 = malloc(sizeof(char) * 25);
    Keys *tmp2 = malloc(sizeof(Keys));

    for(int i = SIZE_ALL/2 ; i < SIZE_ALL ; i++)
    {
	    iteration_to_key(tmp1,i);
        init_key(tmp2,tmp1);

	    present(tmp2,input,tmp1);
	    g_liste_encryption[i] = char_to_double(tmp1);
    }

    free(tmp1);
    free(tmp2);
    pthread_exit(NULL);
}
void * calcul_encryption_C(void * message)
{
    char * input = (char *) (message);
    
    char *tmp1 = malloc(sizeof(char) * 25);
    Keys *tmp2 = malloc(sizeof(Keys));

    for(int i = SIZE_ALL/2 ; i < (SIZE_ALL/2+SIZE_ALL/4) ; i++)
    {
	    iteration_to_key(tmp1,i);
        init_key(tmp2,tmp1);

	    unpresent(tmp2,input,tmp1);
	    g_liste_encryption[i] = char_to_double(tmp1);
    }
    free(tmp1);
    free(tmp2);
    pthread_exit(NULL);
}
void * calcul_encryption_D(void * message)
{
    char * input = (char *) (message);

    char *tmp1 = malloc(sizeof(char) * 25);
    Keys *tmp2 = malloc(sizeof(Keys));

    for(int i = (SIZE_ALL/2+SIZE_ALL/4); i < SIZE_ALL  ; i++)
    {
	    iteration_to_key(tmp1,i);
        init_key(tmp2,tmp1);

	    unpresent(tmp2,input,tmp1);
	    g_liste_encryption[i] = char_to_double(tmp1);
    }
    free(tmp1);
    free(tmp2);
    pthread_exit(NULL);
}


void * calcul_decryption_A(void * crypted)
{
    char * input = (char *) (crypted);
    char *tmp1 = malloc(sizeof(char) * 25);
    Keys *tmp2 = malloc(sizeof(Keys));

    for(int i = 0 ; i < SIZE_ALL/2 ; i++)
    {
        iteration_to_key(tmp1,i);
        init_key(tmp2,tmp1);

        unpresent(tmp2,input,tmp1);
        g_liste_decryption[i] = char_to_double(tmp1);
    }

    free(tmp1);
    free(tmp2);
    pthread_exit(NULL);
}
void * calcul_decryption_B(void * crypted)
{
    char * input = (char *) (crypted);

    char *tmp1 = malloc(sizeof(char) * 25);
    Keys *tmp2 = malloc(sizeof(Keys));

    for(int i = SIZE_ALL/2 ; i < SIZE_ALL ; i++)
    {
        iteration_to_key(tmp1,i);
        init_key(tmp2,tmp1);

        unpresent(tmp2,input,tmp1);
        g_liste_decryption[i] = char_to_double(tmp1);
    }

    free(tmp1);
    free(tmp2);
    pthread_exit(NULL);
}
void * calcul_decryption_C(void * crypted)
{
    char * input = (char *) (crypted);

    char *tmp1 = malloc(sizeof(char) * 25);
    Keys *tmp2 = malloc(sizeof(Keys));

    for(int i = SIZE_ALL/2 ; i < (SIZE_ALL/2+SIZE_ALL/4) ; i++)
    {
        iteration_to_key(tmp1,i);
        init_key(tmp2,tmp1);

        unpresent(tmp2,input,tmp1);
        g_liste_decryption[i] = char_to_double(tmp1);
    }
    free(tmp1);
    free(tmp2);
    pthread_exit(NULL);
}
void * calcul_decryption_D(void * crypted)
{
    char * input = (char *) (crypted);

    char *tmp1 = malloc(sizeof(char) * 25);
    Keys *tmp2 = malloc(sizeof(Keys));

    for(int i = (SIZE_ALL/2+SIZE_ALL/4); i < SIZE_ALL  ; i++)
    {
        iteration_to_key(tmp1,i);
        init_key(tmp2,tmp1);

        unpresent(tmp2,input,tmp1);
        g_liste_decryption[i] = char_to_double(tmp1);
    }
    free(tmp1);
    free(tmp2);
    pthread_exit(NULL);
}


double char_to_double(char *entry)
{
	if(!entry) 
		return -1;

	double res = 0.0;
	int entry_size = strlen(entry);
	int cmp = entry_size - 1;

	for(int i = 0; i < entry_size; i++)
	{
		if(entry[i] == '1')
			res += pow(2,cmp);
			cmp--;
	}

return res;
}


void calculate_possibilities(char * message, char * crypted)
{
	pthread_t threads[4];
	int check = 0;

	check = pthread_create(&threads[0],NULL, calcul_encryption_A,message);
	check = pthread_create(&threads[1],NULL, calcul_encryption_B,message);
	check = pthread_create(&threads[2],NULL, calcul_decryption_A,crypted);
	check = pthread_create(&threads[3],NULL, calcul_decryption_B,crypted);


	pthread_join(threads[0],NULL); 
	pthread_join(threads[1],NULL);
	pthread_join(threads[2],NULL);
	pthread_join(threads[3],NULL);


/* Partie pour les nuls
 *
	char tmp[25];
    tmp[24] = '\0';
	Keys *tmp3 = malloc(sizeof(Keys));

    for(int i = 0; i < SIZE_ALL; i++)
    {
	
	iteration_to_key(tmp,i);
        init_key(tmp3,tmp);

	present(tmp3,message,tmp);
	g_liste_encryption[i] = char_to_double(tmp);
	unpresent(tmp3,crypted,tmp);
	g_liste_decryption[i] = char_to_double(tmp);
	printf("\nPotit CPU i : %d\n",i);
    }
*/
}

void *search_top(void *tables)
{
	Tables *arg = (Tables *) tables;

	for(int i = 0; i < SIZE_ALL/2; i++)
	{
		for(int j = 0; j < SIZE_ALL/2; j++)
		{
			if(arg->left_array[j] == arg->right_array[i])
			{
				printf("\n Collision trouvée ! (haut - gauche, pos : %d ; haut - droite, pos %d)\n",j,i);
			}
		}
	}
}

void *search_down(void *tables)
{
	Tables *arg = (Tables *) tables;

	for(int i = SIZE_ALL/2; i < SIZE_ALL; i++)
	{
		for(int j = SIZE_ALL/2; j < SIZE_ALL; j++)
		{
			if(arg->left_array[j] == arg->right_array[i])
			{
				printf("\n Collision trouvée ! (bas - gauche, pos : %d ; bas - droite, pos %d)\n",j,i);
			}
		}
	}
}

Couple_strings search_collisions(Tables *tables)
{
	pthread_t tids[2];
	pthread_create(&tids[0], NULL, search_top, tables);
	pthread_create(&tids[1], NULL, search_down, tables);

	pthread_join(tids[0], NULL);
	pthread_join(tids[1], NULL);
}
