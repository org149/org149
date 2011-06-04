#!/usr/bin/ruby

require 'rubygems'
require 'large.pb'
require 'small.pb'

SMALL = true
LARGE = false

HEADERS = "
using namespace std;
"

ROW = 'if (name == "%s") { 
  data->%s(%s);
}'

LOOKUP = "bool lookup_and_call_%s( %s::Data* data, string name, string value )
  {
    %s
    return true;
  }
"

bufclass = (ARGV[0] == "small")

case bufclass
when SMALL
  data = Small::Data.new
when LARGE
  data = Large::Data.new
else
  raise "Unknown error"
end

fields = []
data.inspect.split("\n").each do |d|
  field = "set_" + d.split(":")[0]
  strint = field.include?("string")
  if strint
   fields += [ROW % [field, field, "value"]]
  else
   fields += [ROW % [field, field, "atoi(value.c_str())"]]
  end
end
fields = fields.join("\n")
lookup = (bufclass ? "small" : "large")
func_table = LOOKUP % [lookup,lookup, fields]
puts "#{HEADERS}\n\n#{func_table}"

