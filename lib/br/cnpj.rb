require File.join(File.dirname(__FILE__), '../CNPJ')

module BR
  class CNPJ
    class << self
        
        alias_method :orig_valid?, :valid?
        
        # Format unformated Cnpj
        #
        # Cnpj.format(191) # => '00.000.000/0001-91'
        # Cnpj.formatar(30553786000135) # => "30.553.786/0001-35"
        #
        def format(cnpj)
          cnpj = cnpj.to_s.rjust(14, "0")
          "%s.%s.%s/%s-%s" % [cnpj[0,2], cnpj[2,3], cnpj[5,3], cnpj[8,4], cnpj[12,2]]
        end

        ### pt-BR method name
        alias_method :formatar, :format
        
        # Unformat formated Cnpj
        #
        # Cnpj.desformatar("02.716.485/0001-40") # => "02716485000140"
        # Cnpj.unformat("00.086.001/0001-04")    # => "00086001000104"
        #
        def unformat(cnpj)
           cnpj.gsub(/\D/, '')
        end

        ### pt-BR method name
        alias_method :desformatar, :unformat
        
        # Returns true if Cnpj is valid
        # Retorns false if Cnpj is invalid
        #
        # CNPJ.valid?(191)           # => true
        # CNPJ.valid?(123456789101)  # => false
        #
        def valid?(cnpj)
          if cnpj.is_a? String
            orig_valid?(cnpj.to_i)
          else
            orig_valid?(cnpj)
          end
        end
        
    end
    attr_reader :filial, :valid, :radix, :digit

    # Return if the instance CNPJ is valid?
    #
    # Cnpj.new(191).valid? # => true
    #
    def valid?
      @valid
    end
    
    def to_i
      @radix * 1_000_000 + @filial * 100 + @digit
    end

    # Return the CNPJ with 14 characters
    #
    # CNPJ.new(191).to_s # => '00000000000191'
    #
    def to_s
      "%014d" % to_i
    end
    
  end
end
