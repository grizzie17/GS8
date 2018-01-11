#!/bin/bash

symbols="$*"

while read t
do
	case "$t" in
	*.a )
		cache=`nm -C $t | \
			sed -e 's@^[0-9a-f]* T @@g'`
		;;
	*.so | *.so.* )
		cache=`nm -C $t | \
			sed -e 's@^[0-9a-f]* I @@g' \
				-e 's@^__imp_@@g'`
		;;
	esac
	for s in $symbols
	do
		match=`echo "$cache" | grep "$s" 2>/dev/null`
		if [ -n "$match" ]; then
			echo "$s :: $t"
		fi
	done
done < <(find /usr/lib -name '*.a' -o -name '*.so' -o -name '*.so.*')


