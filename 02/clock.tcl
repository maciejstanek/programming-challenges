#!/usr/bin/tclsh

puts "Enter your birth date (YYYY-MM-DD):"
set birth_date_string [gets stdin]
if {[catch {set birth_date [clock scan $birth_date_string -format %Y-%m-%d]}]} {
  puts "This input is not matching a specified format."
  exit 1
}
set current_datetime [clock seconds]
if {$current_datetime < $birth_date} {
  puts "The specified time is referring to a future."
  exit 1
}
puts "$current_datetime - $birth_date"
set difference_in_seconds [expr wide($current_datetime)-wide($birth_date_string)]
puts "You lived about $difference_in_seconds seconds."

set halBirthBook "Jan 12, 1993"
set halBirthMovie "Jan 12, 1992"
set bookSeconds [clock scan $halBirthBook -format {%b %d, %Y}]
set movieSeconds [set movieSeconds [clock scan $halBirthMovie -format {%b %d, %Y}]]

puts "The book and movie versions of '2001, A Space Oddysey' had a"
puts "discrepancy of [expr {$bookSeconds - $movieSeconds}] seconds in how"
puts "soon we would have sentient computers like the HAL 9000"
