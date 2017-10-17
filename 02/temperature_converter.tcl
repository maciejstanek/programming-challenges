#!/usr/bin/tclsh

puts "This converter can process"
puts "the following temperature scales:"
puts " - Kelvin \[K\],"
puts " - Farenheit \[F\] and"
puts " - Celsius \[C\]."
puts ""

puts "Input a temperature with a unit:"
set input [gets stdin]
if {![regexp {([KFC])} [string index $input end] -> input_unit]} {
  puts "Input unit not specified or not recognized."
  exit 1
}
set input_value [string range $input 0 end-1]
if {[regexp {^\s*$} $input_value] ||
    [catch {set input_value [expr $input_value+0]}]} {
  puts "Input value is not a number."
  exit 1
}
if {$input_unit eq ""} {
  puts "Unit not specified."
  exit 1
}

puts "Input a target scale unit:"
set output_unit [gets stdin]
if {![regexp {^[KFC]$} $output_unit]} {
  puts "Output scale unit not valid."
  exit 1
}

if {$input_unit eq $output_unit} {
  set output_value $input_value
} else {
  # Convert from [1] to Celsius and then to [2].
  set intermediate_celsius_value $input_value
  if {$input_unit eq "K"} {
    set intermediate_celsius_value [expr $input_value-273.15]
  } elseif {$input_unit eq "F"} {
    set intermediate_celsius_value [expr 5.0/9.0*($input_value-32)]
  }
  set output_value $intermediate_celsius_value
  if {$output_unit eq "K"} {
    set output_value [expr $intermediate_celsius_value+273.15]
  } elseif {$output_unit eq "F"} {
    set output_value [expr 9.0/5.0*$intermediate_celsius_value+32]
  }
}
puts "It is [format "%.2f" $output_value]$output_unit after conversion."

