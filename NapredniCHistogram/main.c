/***********************************************************************************************
 * Autor: Krsto Zarić  RA 229/2020                                                       	   *
 *                                                                                             *
 * Zadatak:                                                                                    *
 *																	   	                       *
 * Napisati program koji sracunava histogram za niz elemenata zadata na ulazu. Napraviti od    *
 * toga modul i realizovati ga kao staticku biblioteku. Tu biblioteku ukljuciti u glavni 	   *
 * program koji ce obavljati komunikaciju sa okruzenjem (unos/ispis i sl.)                     *
 *                                                                                             *
 * Resenje:                                                                                    *
 *                                                                                             *
 * Zadatak je realizovan tako sto su napravljena dva modula. Prvi modul "calculateHistogram"   *
 * i drugi modul "printHistogram". Oba modula imaju samo po jednu primarnu funkciju u sebi,    *
 * a to su, funkcija void calculateHistogram(), koja izracunava histogram na osnovu unesenih   *
 * vrijednosti i funckija void printHistogram(), koja ispisuje histogram na standardni izlaz   *
 *                                                                                             *
 * Funkcija void calculateHistogram() prima sledece argumente:                                 *
 * 		-values ---> pokazivac na niz cijelih brojeva koje je korisnik unijeo                  *
 *      -n      ---> broj elemenata u nizu                                                     *
 *      -histogram-> pokazivac na niz u kojem ce histogram biti spremljen                      *
 *      -maxValue -> najveca vrijednost u nizu                                                 *
 *      -minValue -> najmanja vrijednost u nizu                                                *
 * Najprije inicijalizujemo niz "histogram" na nulu a zatim racunamo histogram                 *
 *                                                                                             *
 * Funkcija void printHistogram() prima sledece argumente:                                     *
 *      -histogram ---> pokazivac na niz cijelih brojeva koji predstavljaju histogram          *
 *      -maxValue  ---> najveca vrijednost u nizu                                              *
 *      -minValue  ---> najmanja vrijednost u nizu                                             *
 * main.c fajl je glavni dio programa i u njemu koristimo gore navede module. U mainu se vrsi  *
 *  ucitavanje niza sa ulaza koji korisnik unosi i dinamicki se zauzima memorija za unos kao   *
 *  i za histogram. Pored funkcija "printHistogram" i "calculateHistogram" koristimo jos i     *
 *  funkcije findeMaxElement i findeMinElement koje nam sluze za pronalazenje maksimalnog i    *
 *  minimalnog elementa koje kasnije koristimo u izracunavanju histograma i ispisivanju istog  *
 *                                                                                             *
 * Kada je u pitanju prevodjenje programa, potrebno je da izvrsimo sledece korake:             *
 * 		1. gcc -c calculateHistogram.c -o calculateHistogram.o                                 *
 * 				-kreiramo objektu datoteku calculateHistogram.o                                *
 * 		2. gcc -c printHistogram.c -o printHistogram.o                                         *
 * 				-kreiramo objektu datoteku calculateHistogram.o                                *
 * 		3. ar -rs libHistogram.a *.o                                                           *
 * 				-vrsimo stvaranje staticke biblioteke od objektni                              *
 * 		4. gcc -o main main.c -L. -lHistogram -static                                          *
 * 				-kompajliramo glavni program i ukljucujemo staticku biblioteku libHistogram.a  *
 * 		5. ./main                                                                              *
 * 				-vrsimo pokretanje programa                                                    *
 *                                                                                             *
 * MISRA pravila koja nisu ispostovana:                                                        *
 * 		-20.9/R ---> Ovo pravilo ima za cilj da zabrani upotrebu standardnih funkcija za unos i*
 * izlaz podataka (npr. printf, scanf, fopen, fclose, itd.) u ugrađenim sistemima.             *
 * 		-6.3/A  ---> Ovo pravilo preporučuje da se znak za produžetak linija ne koristi.       *
 * Umesto toga, preporučuje se da se kôd piše u jednom redu                                    *
 * 		-8.1/R  ---> pravilo 8.1 propisuje da funkcije koje nemaju parametre treba da budu     *
 * deklarisane i definisane sa parametarskom listom void.                                      *
 * 		-9.1/R  ---> (nazivi funkcija i promenljivih koje su dostupne izvan                    *
 * trenutnog prevodjenog modula ili programa) treba da budu jedinstveni.                       *
 * 		-20.4/R ---> dinamicko alociranje memorije ne bi trebalo da se koristi                 *
 *  	-20.11/R---> ne bi trebalo koristiti exit(0)                                           *
 * 		-5.7/R  ---> ne bi trebalo ponovo da koristimo i                                       *
 *                                                                                             *
 * Testiranje:                                                                                 *
 *                                                                                             *
 * Kada je u pitanju testiranje, vrsena su obicna testiranja sa razlicitim nizovima, koristeni *
 * su pozitivni i negativni brojevi. Ogranicenja koje program ima su da ne moze da radi sa raz-*
 * lomljenim vrijednostima, sto znaci da ne podrzava vrijednosti tipa doble i float, zbog      *
 * portabilnosti najcesce su koristeni tipovi int_least16_t i uint_least16_t tako da je        *
 * minimalna ocekivana vrijednosti short int koji je najcesce 16 biti sto znaci da su          *
 * vrijednosti ogranicene izmedju -32767 i +32767                                              *
 ***********************************************************************************************/


#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include "calculateHistogram.h"
#include "printHistogram.h"


void findMaxElement(int_least16_t* values, uint_least16_t n, int_least16_t* maxValue);
void findMinElement(int_least16_t* values, uint_least16_t n, int_least16_t* minValue);



int main()
{
	uint_least16_t n;

    printf("Number of elements: ");
    scanf("%" SCNdLEAST16, &n);
    printf("\n");

    int_least16_t* values = (int_least16_t*)malloc(n * sizeof(int_least16_t));

    if (values == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(0);
    }

    for (uint_fast16_t i = 0; i < n; i++)
    {
        printf("%" PRIdFAST16 ". element: ", i);
        scanf("%" SCNdLEAST16, &values[i]);
        printf("\n");
    }

    int_least16_t maxValue = values[0];
    findMaxElement(values, n, &maxValue);

	int_least16_t minValue = values[0];
    findMinElement(values, n, &minValue);

	int_least16_t range = maxValue - minValue + 1;

    int_least16_t* histogram = (int_least16_t*)malloc(range * sizeof(int_least16_t));

    if (histogram == NULL)
    {
        printf("Memory allocation failed.\n");
        free(values);
        exit(0);
    }

    calculateHistogram(values, n, histogram, maxValue, minValue);

    printHistogram(histogram, maxValue, minValue);

    free(values);
    free(histogram);

    return 0;
}


void findMaxElement(int_least16_t* values, uint_least16_t n, int_least16_t* maxValue)
{

	for (uint_fast16_t i = 0; i < n; i++)
	{
		if (values[i] > *maxValue)
        {
            *maxValue = values[i];
        }
	}
}


void findMinElement(int_least16_t* values, uint_least16_t n, int_least16_t* minValue)
{

	for (uint_fast16_t i = 0; i < n; i++)
	{
		if (values[i] < *minValue)
        {
            *minValue = values[i];
        }
	}
}

