#!/usr/bin/tclsh

set default 100
if {[llength $argv] < 1} {
  puts stderr "Argument not given, assuming $default."
  set limit $default
} else {
  set limit [lindex $argv 0]
}
if {![string is integer -strict $limit]} {
  puts stderr "Argument is not an integer, assuming $default."
  set limit $default
}
if {$limit < 1} {
  puts stderr "Argument has to be 1 or more, assuming $default."
  set limit $default
}

for {set i 1} {$i < $limit + 1} {incr i} {
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
