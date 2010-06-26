#ifndef _CNPJ_H
#define _CNPJ_H

#ifdef __cplusplus
extern "C" {
#endif

long long calculate_cnpj_digit(int radix, int filial);
int calculate_digit(int radix, int filial);
int is_cnpj(long long cnpj_l);
int is_cgc(long long cgc_l);

#ifdef __cplusplus
}
#endif

#endif /* _CNPJ_H */
