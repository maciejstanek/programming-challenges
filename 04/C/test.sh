#!/bin/bash

function calculateColorForStep()  {
  echo -n $((41 + $1 % 4))
}
function printStepBanner() {
  color=$(calculateColorForStep $1)
  echo -e "\n\e[${color};1m === CASE $1 === \e[0m\n"
}

printStepBanner 0
echo -n "This example has a too short key." | ./a.out 123 123 123 123 123 | cat

printStepBanner 1
echo -n "This example has a too short key." | ./a.out encrypt 123456781234567 | cat

printStepBanner 2
echo -n "Ala ma kota a sierotka ma rysia." | ./a.out encrypt my_128b_TSA_key_

printStepBanner 3
echo -n "Ala ma kota a sierotka ma rysia." | ./a.out encrypt ThisIsTheSameKey 2>/dev/null | ./a.out decrypt ThisIsTheSameKey

printStepBanner 4
echo -n "Ala ma kota a sierotka ma rysia." | ./a.out encrypt 1234567812345678 2>/dev/null | ./a.out decrypt abcdabcdabcdabcd

printStepBanner 5
echo -n 12345678X12345678 | ./a.out decrypt 1234567812345678 >/dev/null | cat

printStepBanner 6
echo -n 12345678123456781 | ./a.out decrypt 1234567812345678 >/dev/null | cat

