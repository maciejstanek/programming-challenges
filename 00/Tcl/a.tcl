#!/usr/bin/tclsh

set vovels_list [list a e i o u ae ai ou]
set consonants_list [list b c d f g h k l m n p r s t v w z sh sch th]
set syllables_count [expr int(3*rand()+2)]

set name ""
for {set i 0} {$i < $syllables_count} {incr i} {
	set random_vovel_index [expr int([llength $vovels_list]*rand())]
	set random_consonant_index [expr int([llength $consonants_list]*rand())]
	set syllabe [lindex $consonants_list $random_consonant_index][lindex $vovels_list $random_vovel_index]
	if {[expr int(100*rand())] > 65} {
		set random_second_consonant_index [expr int([llength $consonants_list]*rand())]
		append syllabe [lindex $consonants_list $random_second_consonant_index]
	}
	append name $syllabe
}
set name [string totitle $name]

puts "Hello! My name is $name."
