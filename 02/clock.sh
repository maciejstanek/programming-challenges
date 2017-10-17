#!/bin/bash
echo -n "Input your birth date (YYYY-MM-DD): "
read birthDate
currentTimeStamp=$(date +%s)
birthTimeStamp=$(date --date=$birthDate +%s)
timeStampDifference=$(($currentTimeStamp - $birthTimeStamp))
if [[ $timeStampDifference -lt 0 ]]; then
  echo "You weren't born yet!"
  exit
fi
echo "You live $timeStampDifference seconds."
