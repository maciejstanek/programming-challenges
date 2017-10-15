#!/bin/bash

text[0]="This example has a too short key."
key[0]="123456781234567"
text[1]="1234567890"
key[1]="a1b2c3d4e5f6g7h8"
text[2]="Ala ma kota a sierotka ma rysia."
key[2]="1234567812345678"

for i in {0..2}; do
  # TODO: Fix this and a Makefile
  echo -n ${text[$i]} | ./a.out encrypt ${key[$i]} 2> .stderr 1> .stdout
done

