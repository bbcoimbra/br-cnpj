#include <stdlib.h>
#include "cnpj.h"

#define DIGIT1 0
#define DIGIT2 1

long long calculate_cnpj_digit(int radix, int filial){
    return (long long)radix*1000000 + filial*100 + calculate_digit(radix, filial);
}

int calculate_digit(int radix, int filial){
    int digit1=0, digit2=0, i;
    int vet[14];
    int weights[][13] = {{5,4,3,2,9,8,7,6,5,4,3,2,0},
                       {6,5,4,3,2,9,8,7,6,5,4,3,2}};
    long long cnpj;
    div_t division;

    cnpj = (long long)radix*1000000 + filial*100;
    for (i=0;i<14;i++){
        lldiv_t division;

        division = lldiv(cnpj,10);
        vet[13-i] = (int) division.rem;
        cnpj = division.quot;
    }
    for(i=0;i<12;i++)
        digit1 += vet[i] * weights[DIGIT1][i];
    division = div(digit1,11);
    digit1 = division.rem<2 ? 0 : 11-division.rem;
    vet[12]=digit1;
    for(i=0;i<13;i++)
        digit2 += vet[i] * weights[DIGIT2][i];
    division = div(digit2,11);
    digit2 = division.rem<2 ? 0 : 11- division.rem;

    return digit1*10 + digit2;
}

int is_cnpj(long long cnpj_l){
    int radix, filial;
    lldiv_t division;

    division = lldiv(cnpj_l,1000000);
    radix = division.quot;
    division = lldiv(division.rem,100);
    filial=division.quot;
    return cnpj_l == calculate_cnpj_digit(radix, filial);
}

int is_cgc(long long cgc_l){
    if(is_cnpj(cgc_l)){
        int weights[]={2,1,2,1,2,1,2,1};
        int sum=0, radix=0, i=0;
        lldiv_t division;

        division = lldiv(cgc_l, 1000000);
        radix = (int)division.quot;
        for (i=0;i<8;i++){
            int product=0;

            division = lldiv(radix,10);
            product = division.rem*weights[7-i];
            sum += (product>9) ? product-9 : product;
            radix = division.quot;
        }

        division=lldiv(sum, 10);
        return !division.rem;
    }
    return 0;
}
