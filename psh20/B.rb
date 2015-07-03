#!/usr/bin/ruby
n = gets
nums = gets.scan(/\d+/).map(&:to_i).sort
for i in 0..(nums.length-1)
  if nums[i] > 5 then
    break
  end
  puts nums.at(i)
end
#print nums
#print "\n"
