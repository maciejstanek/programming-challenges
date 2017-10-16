#!/bin/bash

text[1]="This example has a too short key."
key[1]="123456781234567"
text[2]="1234567890"
key[2]="a1b2c3d4e5f6g7h8"
text[3]="Ala ma kota a sierotka ma rysia."
key[3]="1234567812345678"

for i in {1..3}; do
  color=$((30 + $i % 4))
  echo -e "\e[${color};1m === STEP $i === \e[0m"

  echo -e "\e[${color}m --- plaintext --- \e[0m"
  echo ${text[$i]}
  echo -e "\e[${color}m --- key --- \e[0m"
  echo ${key[$i]}

  echo -e "\e[${color}m --- encrypting --- \e[0m"
  echo -n ${text[$i]} | ./a.out encrypt ${key[$i]} > .encrypted
  echo -e "\e[${color}m --- ciphertext --- \e[0m"
  cat .encrypted
  echo

  echo -e "\e[${color}m --- decrypting --- \e[0m"
  echo TODO
  echo -e "\e[${color}m --- plaintext --- \e[0m"
  echo TODO

  echo -e "\e[${color}m --- finished --- \e[0m"
  echo
  rm -f .encrypted
  rm -f .decrypted
done

