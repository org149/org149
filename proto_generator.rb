#!/usr/bin/ruby

# Usage: proto_generator filename [S|L]
# S - small type
# L - large type
class ProtoGenerator

  SMALL = true
  LARGE = false

  PACKAGE = {
    SMALL => "small",
    LARGE => "large"	
  }
  COUNTS = {
    :strings => { SMALL => 5, LARGE => 50 },
    :integers => { SMALL => 5, LARGE => 50 }
  }

  STRING_FIELD = "optional string string_field%d = %d;\n"
  INT_FIELD = "optional int32 int_field%d = %d;\n"
  MSG_LINE = "message Data {\n%s\n%s\n}"

  def initialize(filename, generator_type = SMALL)
    @filename = filename
    @generator = generator_type 
  end

  def generate
    strings = ""
    integers = ""
    File.open(@filename,File::CREAT|File::RDWR, 0644) { |f|
      f.write("package #{PACKAGE[@generator]};\n")
      COUNTS[:strings][@generator].times do |c|
        strings += STRING_FIELD % [c,c + 1]
      end
      COUNTS[:integers][@generator].times do |c|
        integers += INT_FIELD % [c,c + COUNTS[:strings][@generator] + 1]
      end
      f.write(MSG_LINE % [strings, integers])
    }
  end

end

g = ProtoGenerator.new(ARGV[0], (ARGV[1] == "L" ? false : true))
g.generate
