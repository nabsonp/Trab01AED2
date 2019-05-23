#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "aluno.h"

noAVL* gerarAlunosID(FILE* arq, int tam) {
    aluno a;
    noAVL *arv = criarAVL();
    time_t t;
    srand((unsigned) time(&t));
    for(int i=0; i<tam; i++) {
        a.id = 2019000 + i;
        a.cr = (rand() % 10);
        a.idade = 18 + (rand() % 10);
        strcpy(a.curso,"Ciência da Computação");
        strcpy(a.nome,"Aluno");
        fwrite(&a,sizeof(aluno),1,arq);
        arv = inserirEmAVL(arv, a.id, i);
    }
    return arv;
}

noAVL* gerarAlunosCR(FILE* arq, int tam) {
    aluno a;
    noAVL *arv = criarAVL();
    time_t t;
    srand((unsigned) time(&t));
    for(int i=0; i<tam; i++) {
        a.id = 2019000 + i;
        a.cr = (rand() % 10);
        a.idade = 18 + (rand() % 10);
        strcpy(a.curso,"Ciência da Computação");
        strcpy(a.nome,"NOME");
        fwrite(&a,sizeof(aluno),1,arq);
        arv = inserirEmAVL(arv, a.cr, i);
    }
    return arv;
}

aluno pesqID(FILE *arq, noAVL *indice, int id) {
    noAVL *no = buscaAVL(indice,id);
    aluno a;
    a.id = -1;
    if (no) {
      fseek(arq,0,SEEK_SET);
      fseek(arq,no->indice*sizeof(aluno),SEEK_SET);
      fread(&a,sizeof(aluno),1,arq);
    }
    return a;
}
