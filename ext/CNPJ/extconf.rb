require 'mkmf'

dir_config('cnpj')

have_header('stdlib.h')
have_func('lldiv')
have_type('lldiv_t','stdlib.h')

cflags = '-std=c99 -U_FILE_OFFSET_BITS'
with_cflags(cflags) do
  create_makefile('CNPJ')
end
