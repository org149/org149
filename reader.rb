#!/usr/bin/ruby

require 'rubygems'
require 'large.pb'
require 'small.pb'

SMALL = true
LARGE = false

SMALL_T = 5
LARGE_T = 50

bufclass = (ARGV[0] == "small")

fields = 0

case bufclass
when SMALL
  data = Small::Data.new
when LARGE
  data = Large::Data.new
else
  raise "Unknown error"
end
counter = 0
while ((s = STDIN.readline) rescue false)
  s = STDIN.readline
  s.gsub!("\n", "")
  s.gsub!("\r", "")
  data.parse_from_string(s)
  counter += 1
  if counter % 10000 == 0 
    warn "READER: #{counter} records passed..."
  end
end

