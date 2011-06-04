#!/usr/bin/ruby

require 'rubygems'
require 'large.pb'
require 'small.pb'

SMALL = true
LARGE = false

SMALL_T = 5
LARGE_T = 50

l = ARGV[0].split(":")[1].to_i

bufclass = (ARGV[1] == "small")

fields = 0

case bufclass
when SMALL
  data = Small::Data.new
  fields = SMALL_T
when LARGE
  data = Large::Data.new
  fields = LARGE_T
else
  raise "Unknown error"
end

fields.times do |i|
  data["int_field#{i}"] = i+1
  data["string_field#{i}"] = (i+1).to_s *l
end
counter = 0 
while true
  puts data.to_s
  counter += 1
  if counter % 10000 == 0 
    warn "WRITER: #{counter} records passed..."
  end
end

