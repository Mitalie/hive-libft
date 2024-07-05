#!/bin/bash

flags=('#' 0 - ' ' +)

function generate_permutations() {
	echo \""$1"\",
	for f in "${flags[@]}"; do
		if [[ $1 != *$f* ]]; then
			generate_permutations "$1$f"
		fi
	done
}

generate_permutations
