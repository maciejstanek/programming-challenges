#!/usr/bin/tclsh
# Parse arguments {{{
if {$argc != 1} {
  puts "Please provide one argument."
  exit 1
}
set iter [lindex $argv 0]
if {![string is integer $iter]} {
  puts "Argument is not a number."
  exit 1
}
if {$iter < 1} {
  puts "Argument must be greater than or equal to 1."
  exit 1
}
# }}}
# Generate Pascal triangle {{{
set pascal_line [list 1]
puts $pascal_line
for {set i 1} {$i < $iter} {incr i} {
  set new_pascal_line [list 1]
  for {set j 0; set j1 1} {$j < [expr [llength $pascal_line]-1]} {incr j; incr j1} {
    lappend new_pascal_line [expr [lindex $pascal_line $j]+[lindex $pascal_line $j1]]
  }
  lappend new_pascal_line 1
  set pascal_line $new_pascal_line
  puts $pascal_line
}
# }}}
