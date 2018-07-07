// LDPC_VS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ldpc.h"
#include "stdio.h"

#pragma warning	(disable: 4996)

#define nldpc 64800
#define rate 10

int _tmain(int argc, _TCHAR* argv[])
{
	bool hard = false;

	ldpc teste;

	unsigned char *in_enc = new unsigned char[nldpc];
	unsigned char *out_enc_hard = new unsigned char[nldpc];
	float *out_enc_soft = new float[nldpc];
	unsigned char *out_dec = new unsigned char[nldpc];

	teste.init(nldpc, nldpc*rate/15);

	for(int j = 0; j < (nldpc); j++)
	{
		in_enc[j] = j%2;
	}

	teste.encode(in_enc, out_enc_hard);

	for (unsigned short j = 0; j < (nldpc); j++)
	{
		out_enc_soft[j] = (out_enc_hard[j]*2-1)*100;
	}

	FILE *G = fopen("out_enc_hard.txt", "w");
	FILE *H = fopen("out_enc_soft.txt", "w");
	for (unsigned short j = 0; j < (nldpc); j++)
	{
		fprintf(G, "%i", out_enc_hard[j]);
		fprintf(H, "%.2lf ", out_enc_soft[j]);
	}
	fclose(G);
	fclose(H);
	printf("OK out_enc\n");

	if(hard)
		teste.alocar_hard();
	else
		teste.alocar_soft();

	//inserindo erro
	//out_enc_hard[0] ^= 1; out_enc_soft[0] = out_enc_soft[0]*(-0.01);
	out_enc_hard[10] ^= 1; out_enc_soft[10] = out_enc_soft[10]*(-0.2);
	//out_enc_hard[500] ^= 1; out_enc_soft[500] = out_enc_soft[500]*(-0.01);
	//out_enc_hard[1000] ^= 1; out_enc_soft[1000] = out_enc_soft[1000]*(-0.01);
	//out_enc_hard[1200] ^= 1; out_enc_soft[1200] = out_enc_soft[1200]*(-0.01);
	//out_enc_hard[1800] ^= 1; out_enc_soft[1800] = out_enc_soft[1800]*(-0.01);
	//out_enc_hard[2300] ^= 1; out_enc_soft[2300] = out_enc_soft[2300]*(-0.01);
	//out_enc_hard[2700] ^= 1; out_enc_soft[2700] = out_enc_soft[2700]*(-0.01);
	//out_enc_hard[3100] ^= 1; out_enc_soft[3100] = out_enc_soft[3100]*(-0.01);
	//out_enc_hard[3400] ^= 1; out_enc_soft[3400] = out_enc_soft[3400]*(-0.01);
	//out_enc_hard[3900] ^= 1; out_enc_soft[3900] = out_enc_soft[3900]*(-0.01);
	//out_enc_hard[4300] ^= 1; out_enc_soft[4300] = out_enc_soft[4300]*(-0.01);
	//out_enc_hard[4700] ^= 1; out_enc_soft[4700] = out_enc_soft[4700]*(-0.01);
	//out_enc_hard[5000] ^= 1; out_enc_soft[5000] = out_enc_soft[5000]*(-0.01);
	//out_enc_hard[5200] ^= 1; out_enc_soft[5200] = out_enc_soft[5200]*(-0.01);
	//out_enc_hard[5399] ^= 1; out_enc_soft[5399] = out_enc_soft[5399]*(-0.01);

	if(nldpc == 7)
	{
		out_enc_hard[0] = 4.2; out_enc_soft[0] = 4.2; 
		out_enc_hard[1] = 3.05; out_enc_soft[1] = 3.05; 
		out_enc_hard[2] = -1.2; out_enc_soft[2] = -1.2; 
		out_enc_hard[3] = 2.2; out_enc_soft[3] = 2.2;		//ERRO AQUI
		out_enc_hard[4] = -3.3; out_enc_soft[4] = -3.3; 
		out_enc_hard[5] = 2.8; out_enc_soft[5] = 2.8; 
		out_enc_hard[6] = 1.2; out_enc_soft[6] = 1.2; 

		in_enc[0] = 1;
		in_enc[1] = 1;
		in_enc[2] = 0;
		in_enc[3] = 0;
		in_enc[4] = 0;
		in_enc[5] = 1;
		in_enc[6] = 1;
	}

	if(hard)
	{
		teste.decode_hard(out_enc_hard, out_dec);
		//teste.decode_hard2(out_enc_hard, out_dec);
		//teste.decode_hard3(out_enc_hard, out_dec);
		//teste.decode_hard4(out_enc_hard, out_dec);
	}
	else
		//teste.decode_soft_DESATIVADO(out_enc_soft, out_dec);
		teste.decode_soft_new(out_enc_soft, out_dec);

	if(hard)
		teste.free_hard();
	else
		teste.free_soft();

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

