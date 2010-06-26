#include "ruby.h"
#include "cnpj.h"

static VALUE t_init_cnpj(int argc, VALUE *argv, VALUE self)
{
    int radix = 0;
    int filial = 0;
    int verif = 0;
    VALUE valid = Qnil;

    if (argc == 2) {
        radix = FIX2INT(argv[0]);
        if( radix >= 100000000 || radix < 0 )
            rb_raise(rb_eArgError, "radix should be greater than -1 or lesser than 10_000_000");
        filial = NUM2INT(argv[1]);
        if( filial >= 10000 || filial < 1)
            rb_raise(rb_eArgError, "filial should be greater than 0 or lesser than 10_000");
        verif = calculate_digit(radix,filial);
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
        radix = (int)v.quot;
        valid = (verif == calculate_digit(radix,filial)) ? Qtrue : Qfalse;
    }

    rb_iv_set(self, "@radix", INT2FIX(radix));
    rb_iv_set(self, "@filial", INT2FIX(filial));
    rb_iv_set(self, "@digit", INT2FIX(verif));
    rb_iv_set(self, "@valid", valid);

    return self;
}

static VALUE rb_is_cgc(VALUE self){
    long long radix=0;
    int filial = 0, verify_digit = 0;
    radix = NUM2INT(rb_iv_get(self, "@radix"));
    filial = NUM2INT(rb_iv_get(self, "@filial"));
    verify_digit = NUM2INT(rb_iv_get(self, "@digit"));
    return is_cgc((long long)radix * 1000000 + filial * 100 + verify_digit) ? Qtrue : Qfalse;
}

static VALUE valid_cnpj(VALUE self, VALUE ruby_cnpj){
    long long cnpj=0;
    cnpj = (long long)NUM2LL(ruby_cnpj);
    if(cnpj == 0) return Qfalse;
    return is_cnpj(cnpj) ? Qtrue : Qfalse;
}

VALUE mBR, cCNPJ;
void Init_CNPJ(){
    mBR = rb_define_module("BR");
    cCNPJ = rb_define_class_under(mBR, "CNPJ", rb_cObject);
    rb_define_method(cCNPJ, "initialize", t_init_cnpj, -1);
    rb_define_singleton_method(cCNPJ, "valid?", valid_cnpj, 1);
    rb_define_method(cCNPJ, "is_cgc?", rb_is_cgc, 0);
}
