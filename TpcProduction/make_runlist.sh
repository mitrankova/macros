#!/bin/bash

#runs=(79507 79508 79509 79510 79511 79512 76905 82626 75405 75391)
#runs=(76905  75405 75391)
#runs=(82626)
runs=(79507 79508 79509 79510 79511 79512)

output="run_list_pp_07_12.txt"

> "$output"

for run in "${runs[@]}"; do
    for i in $(seq 0 99); do
        echo "$run, $i" >> "$output"
    done
done

echo "Created $output"