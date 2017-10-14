#!/usr/bin/tclsh

for {set i 1} {$i < 100} {incr i} {
  set output {}
  if {$i % 3 == 0} {
    append output Fizz
  }
  if {$i % 5 == 0} {
    append output Buzz
  }
  if {$output eq {}} {
    set output $i
  }
  puts $output
}
