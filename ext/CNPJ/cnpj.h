#ifndef _CNPJ_H
#define _CNPJ_H

#ifdef __cplusplus
extern "C" {
#endif

long long calcula_digito_cnpj(int raiz, int filial);
int calcula_digito(int raiz, int filial);
int e_cnpj(long long cnpj_l);
int e_cgc(long long cgc_l);

#ifdef __cplusplus
}
#endif

#endif /* _CNPJ_H */
