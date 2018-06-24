#ifndef LDPC_H
#define LDPC_H

class ldpc
{
private:
	unsigned short n; //quantidade de bits de entrada
	unsigned short k; //quantidade de bits de saída
	unsigned short r; //code rate
	unsigned short max_it; //numero de iterações
	unsigned short Q_ldpc; //constante que vem da norma
	unsigned short M1; //constante da norma para LDPC tipo A
	unsigned short M2; //constante da norma para LDPC tipo A
	unsigned short Q1; //constante da norma para LDPC tipo A
	unsigned short Q2; //constante da norma para LDPC tipo A
	bool tipo; //false = tipo A, true = tipo B
	int n_group; //tamanho do grupo

	unsigned short **C; // matriz de check nodes
	unsigned short *INDX; // indices para calcular a matriz C, numero de 1s por linha

	unsigned short **err; //contagem de 1s e 0s no hard-decision
	unsigned char *r_aux; //in para eu manipular
	float *LLR_aux; //in em formato LLR pra eu manipular
	unsigned char *SIN; //sindrome

	unsigned short *p_erros; //posicao dos erros
	float** R; //matriz R
	float** Q; //matriz Q

public:
	void init(unsigned short N, unsigned short K); //inicializa variavais

	float aTanh(float x); //arco tangente hiperbólico

	void alocar_hard();//alocação de variáveis para hard_decision
	void alocar_soft();//alocação de variáveis para soft_decision

	void free_hard();//desalocação de variáveis para hard_decision
	void free_soft();//desalocação de variáveis para soft_decision

	bool decode_hard(const unsigned char *r, unsigned char *u); //decodifica [r] em [u] -> hard-decision - voto majoritário
	bool decode_hard2(const unsigned char *r, unsigned char *u); //decodifica [r] em [u] -> hard-decision - maior numero de erros, inverte todos
	bool decode_hard3(const unsigned char *r, unsigned char *u); //decodifica [r] em [u] -> hard-decision - maior numero de erros, inverte 1 por vez
	bool decode_hard4(const unsigned char *r, unsigned char *u); //decodifica [r] em [u] -> hard-decision - maior numero de erros, inverte 1 por vez, com a % de check nodes errados 
	
	bool decode_soft_DESATIVADO(const float *r, unsigned char *u); //decodifica [r] em [u] -> soft-decision
	bool decode_soft_new(const float *r, unsigned char *u); //decodifica [r] em [u] -> soft-decision - otimizado

	bool encode(const unsigned char *u, unsigned char *v); //codifica [u] em [v]
};

#endif
