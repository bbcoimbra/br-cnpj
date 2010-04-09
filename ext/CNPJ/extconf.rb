require 'mkmf'

dir_config('cnpj')

have_header('stdlib.h')

create_makefile('CNPJ')
