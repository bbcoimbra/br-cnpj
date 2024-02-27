require File.expand_path(File.dirname(__FILE__)) + '/spec_helper'

module BR
  
  describe CNPJ do
    
    context 'when validate instances' do
      
      it 'should return true for the cnpj valid' do
        VALID_CNPJS_INTEGER.each do |valid_cnpj|
          CNPJ.new(valid_cnpj).valid?.should be_truthy
        end
      end
      
      it 'should return false the cnpj invalid' do
        INVALID_CNPJS_INTEGER.each do |invalid_cnpj|
          CNPJ.new(invalid_cnpj).valid?.should be_falsey
        end
      end
      
    end
    
    context "when Fixnum" do

      it "should return true for valid cnpjs" do
        VALID_CNPJS_INTEGER.each do |valid_cnpj|
          CNPJ.valid?(valid_cnpj).should be_truthy
        end
      end
    
      it "should return false for invalid cnpjs" do
        INVALID_CNPJS_INTEGER.each do |invalid_cnpj|
          CNPJ.valid?(invalid_cnpj).should be_falsey
        end
      end
    
    end
  
    context "when String" do
    
      it "should return true for valid cnpjs" do
        VALID_CNPJS_STRING.each do |valid_cnpj|
          CNPJ.valid?(valid_cnpj).should be_truthy
        end
      end
    
      it "should return false for invalid cnpjs" do
        INVALID_CNPJS_STRING.each do |invalid_cnpj|
          CNPJ.valid?(invalid_cnpj).should be_falsey
        end
      end
    
    end
  
    context 'when format cnpj' do
    
      it 'should format the cnpj put zero in the left' do
        CNPJ.format(191).should eql('00.000.000/0001-91')
      end
  
      it 'should format the cnpj put zero in the left (cnpj filial)' do
        CNPJ.format(272).should  eql('00.000.000/0002-72')
      end
    
      it "should format the cnpj put period and stuff" do
        CNPJ.formatar(30553786000135).should eql("30.553.786/0001-35")
      end
    
      it "should format the cnpj" do
        CNPJ.formatar(14712911000156).should eql("14.712.911/0001-56")
      end
    
    end
    
    context 'when unformat cnpj' do

      it "should return only numbers in String" do
        CNPJ.unformat("02.716.485/0001-40").should == "02716485000140"
      end

      it "should remove the chars '.', '/' and '-'" do
        CNPJ.unformat("71.153.638/0001-00").should == "71153638000100"
      end

      it "should remove the chars with '-'" do
        CNPJ.desformatar("47.580.835/0001-21").should == "47580835000121"
      end

      it "should remove the chars with '/'" do
        CNPJ.desformatar("98.819.832/0001-32").should == "98819832000132"
      end

      it "should retorn an String" do
        CNPJ.desformatar("00.022.559/0001-13").should be_kind_of(String)
      end

    end
     
    context 'when to_s' do
      
      it "should return a String" do
        CNPJ.new(191).to_s.should be_kind_of(String)
      end
      
      it 'should return a String with 14 chars' do
        CNPJ.new(191).to_s.size.should == 14
      end
      
      it 'should return the CNPJ in string' do
        CNPJ.new(272).to_s.should == '00000000000272'
      end
      
      it 'should return the CNPJ in String' do
        CNPJ.new(191).to_s.should == '00000000000191'
      end
      
    end 
    
    context 'when to_i' do
      
      it 'should return a Fixnum' do
        CNPJ.new('191').to_i.should be_kind_of(Fixnum)
      end
      
    end
       
  end
  
end
