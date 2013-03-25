# br-cnpj ![travis-ci build status](https://secure.travis-ci.org/bbcoimbra/br-cnpj.png?branch=master) [![Code Climate](https://codeclimate.com/github/bbcoimbra/br-cnpj.png)](https://codeclimate.com/github/bbcoimbra/br-cnpj)

Ruby native extension that calculates and validades CNPJ (Cadastro Nacional de
Pessoas Jurídicas)

## Install

```bash
sudo gem install br-cnpj
```

## Examples

```ruby
require 'rubygems'
require 'br/cnpj'

BR::CNPJ.valid? '00000000000191'
 #> true

BR::CNPJ.valid? 191
 #> true

BR::CNPJ.valid? 192
 #> false

radix = 0
filial = 1
BR::CNPJ.new(radix, filial).to_s
 #> '00000000000191'

BR::CNPJ.new(191).valid?
 #> true

BR::CNPJ.new(1234567891011).valid?
 #> false

BR::CNPJ.format(191)
 #> '00.000.000/0001-91'

BR::CNPJ.unformat('00.000.000/0001-91')
 #> '00000000000191'
```

## Copyright

MIT Licence. Copyright (c) 2009-2013 Bruno Coimbra. Veja o arquivo LICENSE para mais detalhes.
