#!/bin/bash

symbols="$*"

while read t
do
	ftype=`file $t | tr ' ' '-'`
	#echo "ftype=$ftype"
	case "$ftype" in
	*shared-object* | *relocatable* | *current-ar-archive* )
		case "$t" in
		*.a )
			cache=`nm -C $t 2>/dev/null | \
				sed -e 's@^[0-9a-f]* T @@g' -e '/__x86\./d'`
			;;
		*.so | *.so.* )
			cache=`objdump -T -C $t | \
				sed -e 's@^[0-9a-f]*[1-9a-f][0-9a-f]* g  *DF  *\.text [0-9a-f]*  *Base  *@@g' \
					-e 's@^__imp_@@g'`
			;;
		* )
			cache=""
			;;
		esac
		if [ -n "$cache" ]; then
			for s in $symbols
			do
				match=`echo "$cache" | grep "$s" 2>/dev/null`
				if [ -n "$match" ]; then
					echo "$s :: $t"
				fi
			done
		fi
		;;
	esac
done < <(find /usr/lib /lib -name '*.a' -o -name '*.so' -o -name '*.so.*')


