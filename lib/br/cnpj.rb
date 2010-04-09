require File.join(File.dirname(__FILE__), '../CNPJ')

module BR
  class CNPJ
    class << self
        alias_method :orig_valid?, :valid?
    end

    def self.valid?(cnpj)
      if cnpj.is_a? String
        orig_valid?(cnpj.to_i)
      else
        orig_valid?(cnpj)
      end
    end

    def to_i
      @raiz * 1_000_000 + @filial * 100 + @verif
    end

    def to_s
      "%014d" % to_i
    end
  end
end
