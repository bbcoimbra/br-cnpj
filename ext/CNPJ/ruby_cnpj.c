#include "ruby.h"
#include "cnpj.h"

static VALUE t_init_cnpj(int argc, VALUE *argv, VALUE self)
{
    int raiz = 0;
    int filial = 0;
    int verif = 0;
    VALUE valid = Qnil;

    if (argc == 2) {
        raiz = FIX2INT(argv[0]);
        if( raiz >= 100000000 || raiz < 0 )
            rb_raise(rb_eArgError, "raiz should be greater than -1 or lesser than 10_000_000");
        filial = NUM2INT(argv[1]);
        if( filial >= 10000 || filial < 1)
            rb_raise(rb_eArgError, "filial should be greater than 0 or lesser than 10_000");
        verif = calcula_digito(raiz,filial);
        valid = Qtrue;
    }
    else if (argc == 1) {
        lldiv_t v;
        long long cnpj = 0;

        if (rb_class_of(argv[0]) == rb_cString) 
            cnpj = NUM2LL(rb_str_to_inum(argv[0], 10, 0));
        else
            if (rb_class_of(argv[0]) == rb_cFixnum ||
                rb_class_of(argv[0]) == rb_cBignum)
                cnpj = NUM2LL(argv[0]);

        v = lldiv(cnpj, (long long)100);
        verif = (int)v.rem;
        v = lldiv(v.quot, (long long)10000);
        filial = (int)v.rem;
        raiz = (int)v.quot;
        valid = verif == calcula_digito(raiz,filial) ? Qtrue : Qfalse;
    }

    rb_iv_set(self, "@raiz", INT2FIX(raiz));
    rb_iv_set(self, "@filial", INT2FIX(filial));
    rb_iv_set(self, "@verif", INT2FIX(verif));
    rb_iv_set(self, "@valid", valid);

    return self;
}

static VALUE is_cgc(VALUE self){
    long long raiz=0;
    int filial = 0, dv = 0;
    raiz = NUM2INT(rb_iv_get(self, "@raiz"));
    filial = NUM2INT(rb_iv_get(self, "@filial"));
    dv = NUM2INT(rb_iv_get(self, "@verif"));
    return e_cgc((long long)raiz * 1000000 + filial * 100 + dv) ? Qtrue : Qfalse;
}

static VALUE valid_cnpj(VALUE self, VALUE ruby_cnpj){
    long long cnpj=0;
    cnpj = (long long)NUM2LL(ruby_cnpj);
    if(cnpj == 0) return Qfalse;
    return e_cnpj(cnpj) ? Qtrue : Qfalse;
}

VALUE mBR, cCNPJ;
void Init_CNPJ(){
    mBR = rb_define_module("BR");
    cCNPJ = rb_define_class_under(mBR, "CNPJ", rb_cObject);
    rb_define_method(cCNPJ, "initialize", t_init_cnpj, -1);
    rb_define_singleton_method(cCNPJ, "valid?", valid_cnpj, 1);
    rb_define_method(cCNPJ, "is_cgc?", is_cgc, 0);
}
