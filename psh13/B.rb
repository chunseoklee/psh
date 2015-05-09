#!/usr/bin/ruby

# STDIN.read.split("\n").each do |a|
#    puts a
# end

N = (STDIN.gets).to_i

while line = STDIN.gets do
  if line.length > 1
    aline = line.split /a/ ;
    op = aline[0].gsub(/\s+/,"");
    if op == 'throw'
  end
end
