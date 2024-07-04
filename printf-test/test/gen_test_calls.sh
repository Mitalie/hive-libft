#!/bin/bash

for spec in c s p d i u x X %; do
	case $spec in
		c)
			args=(0 32 65 97 240)
			;;
		s)
			args=('""' '"abc"' '"\0"' '"Hello,\nworld!"')
			;;
		p)
			args=('(void*)0' main ft_printf)
			;;
		d|i)
			args=(INT_MIN -123 -10 -9 -1 0 1 9 10 123 INT_MAX)
			;;
		u|x|X)
			args=(0 1 9 10 123 INT_MAX UINT_MAX)
			;;
		%)
			args=()
			;;
		*)
			args=()
			;;
	esac
	echo "sprintf(fmt, \"%%%s%s%s%c\", flags[flagidx], widthstr, precstr, '$spec');"
	if [[ $spec == % ]]; then
		echo '#pragma GCC diagnostic push'
		echo '#pragma GCC diagnostic ignored "-Wformat-security"'
		echo 'test(fmt);'
		echo '#pragma GCC diagnostic pop'
	else
		for arg in "${args[@]}"; do
			echo "test(fmt, $arg);"
		done
	fi
done
