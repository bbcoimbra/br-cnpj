require 'rubygems'
require 'rake'

begin
  require 'jeweler'
  Jeweler::Tasks.new do |gem|
    gem.name = "br-cnpj"
    gem.summary = %Q{Calcules and validates given CNPJ}
    gem.description = %Q{Lib implemented in C that calculates and validates CNPJ.}
    gem.email = "bbcoimbra@gmail.com"
    gem.homepage = "http://github.com/bbcoimbra/br-cnpj"
    gem.authors = ["Bruno Coimbra"]
    gem.add_development_dependency "rspec", ">= 1.2.9"
    gem.files = FileList["lib/**/*.rb", "ext/**/*"]
    gem.files.exclude  'lib/*.so'
    gem.extensions = FileList["ext/**/extconf.rb"]
    # gem is a Gem::Specification... see http://www.rubygems.org/read/chapter/20 for additional settings
  end
  Jeweler::GemcutterTasks.new
rescue LoadError
  puts "Jeweler (or a dependency) not available. Install it with: gem install jeweler"
end

require 'rake/extensiontask'
Rake::ExtensionTask.new('CNPJ')
CLEAN.include('lib/**/*.so')

require 'rspec/core/rake_task'
RSpec::Core::RakeTask.new(:spec)

RSpec::Core::RakeTask.new(:rcov) do |spec|
  spec.libs << 'lib' << 'spec'
  spec.pattern = 'spec/**/*_spec.rb'
  spec.rcov = true
end

task :spec => :compile

task :default => :spec

require 'rdoc/task'
RDoc::Task.new do |rdoc|
  version = File.exist?('VERSION') ? File.read('VERSION') : ""

  rdoc.rdoc_dir = 'rdoc'
  rdoc.title = "br-cnpj #{version}"
  rdoc.rdoc_files.include('README*')
  rdoc.rdoc_files.include('lib/**/*.rb')
end
