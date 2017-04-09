echo >> "$HEADER"

if [ "$COUNT" -eq "0" ];
then
	echo "#define DEF_QUEUE_TYPE LINEAR" >> "$HEADER"
	echo "#define DEF_QUEUE_STRING \"Linear Queue\"" >> "$HEADER"
	echo "#define CONFIG_LINEAR_QUEUE" >> "$HEADER"
elif [ "$COUNT" -eq "1" ];
then
	case $LASTITEM in
		*"LINEAR_QUEUE") echo "#define DEF_QUEUE_TYPE LINEAR" >> "$HEADER"
		echo "#define DEF_QUEUE_STRING \"Linear Queue\"" >> "$HEADER"
				;;
		*"DEQUE") echo "#define DEF_QUEUE_TYPE DEQUE" >> "$HEADER"
			echo "#define DEF_QUEUE_STRING \"Deque\"" >> "$HEADER"
				;;
		*"PRIORITY_QUEUE") echo "#define DEF_QUEUE_TYPE PRIORITY" >> "$HEADER"
			echo "#define DEF_QUEUE_STRING \"Priority Queue\"" >> "$HEADER"
				;;
	esac
else
	echo "#define MULQUEUE" >> "$HEADER"
fi

echo >> "$HEADER"
