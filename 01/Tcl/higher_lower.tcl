#!/usr/bin/tclsh

set secret_number [expr int(100*rand()+1)]
puts "I think of a number between 1 and 100."
puts "What do you think it is?"

set guessed_number 0
set guesses_count 0
while {$guessed_number != $secret_number} {
	incr guesses_count
	puts "Guess: "
	set guessed_number [gets stdin]
	if {![string is integer $guessed_number]} {
		puts "This is not a number. Try again."
	} elseif {$guessed_number > $secret_number} {
		puts "Your number is too big."
	} elseif {$guessed_number < $secret_number} {
		puts "Your number is too small."
	}
}

puts "That's right! It was $secret_number."
puts "It took you $guesses_count attempts to guess it."

