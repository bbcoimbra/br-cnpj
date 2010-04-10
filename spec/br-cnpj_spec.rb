require 'spec_helper'

describe BR::CNPJ do
      
  context "when Fixnum" do

    it "should return true for valid cnpjs" do
      VALID_CNPJS_INTEGER.each do |valid_cnpj|
        BR::CNPJ.valid?(valid_cnpj).should be_true
      end
    end
    
    it "should return false for invalid cnpjs" do
      INVALID_CNPJS_INTEGER.each do |invalid_cnpj|
        BR::CNPJ.valid?(invalid_cnpj).should be_false
      end
    end
    
  end
  
  context "when String" do
    
    it "should return true for valid cnpjs" do
      VALID_CNPJS_STRING.each do |valid_cnpj|
        BR::CNPJ.valid?(valid_cnpj).should be_true
      end
    end
    
    it "should return false for invalid cnpjs" do
      INVALID_CNPJS_STRING.each do |invalid_cnpj|
        BR::CNPJ.valid?(invalid_cnpj).should be_false
      end
    end
    
  end
  
end
