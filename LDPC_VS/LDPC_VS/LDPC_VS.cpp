// LDPC_VS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ldpc.h"
#include "stdio.h"

#pragma warning	(disable: 4996)

#define nldpc 16200
#define rate 5

int _tmain(int argc, _TCHAR* argv[])
{
	ldpc teste;

	unsigned char *in_enc = new unsigned char[nldpc];
	unsigned char *out_enc = new unsigned char[nldpc];
	unsigned char *out_dec = new unsigned char[nldpc];

	teste.init(nldpc, nldpc*rate/15);

	for(int j = 0; j < (nldpc); j++)
	{
		in_enc[j] = j%2;
	}

	teste.encode(in_enc, out_enc);

	FILE *G = fopen("out_enc.txt", "w");
	for (unsigned short j = 0; j < (nldpc); j++)
	{
		fprintf(G, "%i", out_enc[j]);
	}
	fclose(G);
	printf("OK out_enc\n");

	teste.alocar_hard();

	//inserindo erro
	//out_enc[0] ^= 1;
	//out_enc[10] ^= 1;
	//out_enc[500] ^= 1;
	//out_enc[1000] ^= 1;
	//out_enc[1200] ^= 1;
	//out_enc[1800] ^= 1;
	//out_enc[2300] ^= 1;
	out_enc[2700] ^= 1;
	//out_enc[3100] ^= 1;
	//out_enc[3400] ^= 1;
	//out_enc[3900] ^= 1;
	//out_enc[4300] ^= 1;
	out_enc[4700] ^= 1;
	//out_enc[5000] ^= 1;
	//out_enc[5200] ^= 1;
	//out_enc[5399] ^= 1;

	//teste.decode_hard(out_enc, out_dec);
	//teste.decode_hard2(out_enc, out_dec);
	//teste.decode_hard3(out_enc, out_dec);
	teste.decode_hard4(out_enc, out_dec);

	teste.free_hard();

	int e = 0;
	for(int i = 0; i < nldpc*rate/15; i++)
	{
		if(in_enc[i] != out_dec[i])
		{
			printf("ERRO POSICAO %i\n", i);
			e++;
		}
	}

	printf("\nTOTAL: %i ERROS\n", e);

	printf("");
	return 0;
}

