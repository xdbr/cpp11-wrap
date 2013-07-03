require 'rake/clean'

CXX      = 'g++'
CXXFLAGS = '-std=c++11 -Wall -Wextra'
SOURCES  = FileList['test*.cpp']
OBJECTS  = SOURCES.map { |file| file.ext('.o') }
EXE      = SOURCES.map { |file| file.ext('.test') }
LIBDIR   = [ "#{ENV['HOME']}/local/lib", '/opt/local/lib', '/usr/lib64', '/usr/local/lib', '/usr/lib' ]
LIBS     = [ 'boost_unit_test_framework' ]
TRACE    = 0
DEBUG    = 0

CLEAN.include(OBJECTS, EXE)

task :default => :test

desc "Run all tests (default)"
task :test => EXE do
  EXE.each do |e|
    sh "./#{e}"
  end
end

rule '.o' => ['.cpp'] do |t|
  sh "#{CXX} #{CXXFLAGS} #{t.source} -c -o #{t.name}"
end

rule '.test' => ['.o'] do |t|
  sh "#{CXX} #{CXXFLAGS} #{t.source} -o #{t.name} #{find_deps(LIBS).join ' '}"
end



def find_deps libnames=[]
  puts "-- Searching for libraries needed ..." if TRACE > 0
  dirs_from ||= LIBDIR

  found = []
  libending = ['a', 'so', 'dll', 'dylib']

  search = {}
  libnames.each do |libname|
    search[libname] = []
    search[libname] << libname
    search[libname] << "lib#{libname}"
    search[libname].concat libending.map {|ending| "lib#{libname}.#{ending}" }.flatten
    search[libname].concat dirs_from.map {|dir| libending.map {|ending| "#{dir}/lib#{libname}.#{ending}" } }.flatten
    
  end

  puts "searchspace: #{search}" if DEBUG > 0

  search.keys.each do |f|
    found << search[f].select {|s| File.exist? s }.first
  end

  puts "Libs found (before uniq): #{found}" if DEBUG > 0

  found
end

