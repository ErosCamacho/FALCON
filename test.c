#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "katrng.h"
#include "api.h"
#include "utilities.h"

#define	MAX_MARKER_LEN		50

#define KAT_SUCCESS          0
#define KAT_FILE_OPEN_ERROR -1
#define KAT_DATA_ERROR      -3
#define KAT_CRYPTO_FAILURE  -4


void main(int argc, char** argv)
{
	// Inicializacion de parámetros
	static unsigned char       seed[48];
	static unsigned char       entropy_input[48];
	static unsigned char       msg[3300];
	static unsigned char       pk[CRYPTO_PUBLICKEYBYTES], sk[CRYPTO_SECRETKEYBYTES];

	unsigned char		*m, *sm, *m1;
	unsigned long long  mlen, smlen, mlen1;
	int                 count;
	int                 done;
	int                 ret_val;

	int DBG = 10;

	// Inicializacion de la fuente de entropia
	for (int i = 0; i < 48; i++)
		entropy_input[i] = i;
	randombytes_init(entropy_input, NULL, 256);

	// Genero la semilla de forma aleatoria
	randombytes(seed, 48);

	// Genero el mensaje con la maxima longitud de forma aleatoria
	mlen = 3300; // Máximo (se puede modificar) 
	randombytes(msg, mlen);

	// Generacion par de claves (DBG = 1X)
	crypto_sign_keypair(pk, sk);
	
	if (DBG == 10) {
		printchar("pk", pk, CRYPTO_PUBLICKEYBYTES);
		printchar("sk", sk, CRYPTO_SECRETKEYBYTES);
	}

	// Firma Digital (DBG = 2X)
	crypto_sign(sm, &smlen, m, mlen, sk);
	if (DBG == 20) {
		printchar("m", m, mlen);
		printchar("sm", sm, smlen);
	}
}