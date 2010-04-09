#include <stdlib.h>
#include "cnpj.h"

#define DIGITO1 0
#define DIGITO2 1

long long calcula_digito_cnpj(int raiz, int filial){
    return (long long)raiz*1000000 + filial*100 + calcula_digito(raiz, filial);
}

int calcula_digito(int raiz, int filial){
    int digito1=0, digito2=0, i;
    int vet[14];
    int pesos[][13] = {{5,4,3,2,9,8,7,6,5,4,3,2,0},
                       {6,5,4,3,2,9,8,7,6,5,4,3,2}};
    long long cnpj;
    div_t divisao;

    cnpj = (long long)raiz*1000000 + filial*100;
    for (i=0;i<14;i++){
        lldiv_t divisao;

        divisao = lldiv(cnpj,10);
        vet[13-i] = (int) divisao.rem;
        cnpj = divisao.quot;
    }
    for(i=0;i<12;i++)
        digito1 += vet[i] * pesos[DIGITO1][i];
    divisao = div(digito1,11);
    digito1 = divisao.rem<2 ? 0 : 11-divisao.rem;
    vet[12]=digito1;
    for(i=0;i<13;i++)
        digito2 += vet[i] * pesos[DIGITO2][i];
    divisao = div(digito2,11);
    digito2 = divisao.rem<2 ? 0 : 11- divisao.rem;

    return digito1*10 + digito2;
}

int e_cnpj(long long cnpj_l){
    int raiz, filial;
    lldiv_t divisao;

    divisao = lldiv(cnpj_l,1000000);
    raiz = divisao.quot;
    divisao = lldiv(divisao.rem,100);
    filial=divisao.quot;
    return cnpj_l == calcula_digito_cnpj(raiz, filial);
}

int e_cgc(long long cgc_l){
    if(e_cnpj(cgc_l)){
        int pesos[]={2,1,2,1,2,1,2,1};
        int acumulador=0, raiz=0, i=0;
        lldiv_t divisao;

        divisao = lldiv(cgc_l, 1000000);
        raiz = (int)divisao.quot;
        for (i=0;i<8;i++){
            int produto=0;

            divisao = lldiv(raiz,10);
            produto = divisao.rem*pesos[7-i];
            acumulador += (produto>9) ? produto-9 : produto;
            raiz = divisao.quot;
        }

        divisao=lldiv(acumulador, 10);
        return !divisao.rem;
    }
    return 0;
}
