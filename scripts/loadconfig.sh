#!/bin/bash

usage(){
	echo Usage : loadconfig.sh input_config_filename output_header_filename
	echo Example : loadconfig.sh defconfig config.h
}

CONFIG=$1

if [ -z "$CONFIG" ];
then
	echo Please specify a config file to continue!
	usage
elif [ ! -e "$CONFIG" ];
then
	echo File $1 does not exist!
	usage
elif [ -z "$2" ];
then
	echo Please specify an output file to continue!
	usage
else
	echo Generating header from config..
	HEADER=$2

	echo Defining header name..

	NAME=""

	EXT=""

	while IFS='.' read -ra EXT;
	do
      		for i in "${EXT[@]}"; do
          		NAME=$NAME"_"${i^^}
      		done
 	done <<< "$2"

	echo Internal header name : $NAME..

	echo //Automatically generated by loadconfig > $HEADER
	echo "#ifndef $NAME" >> $HEADER
	echo "#define $NAME" >> $HEADER
	echo >> $HEADER

	echo Checking configuration options..

	# Read the file line by line
	LASTNODEITEM=""
	LASTQUEUEITEM=""
	NODECOUNT=0
	QUEUECOUNT=0
	while IFS='' read -r line || [[ -n $line ]];
	do
		echo $line

		# Split each line in "="
		IFS='=' read -ra PART <<< $line

		# Check if size of array is 2
		if [[ ! $line = "#"* ]] && [[ "${#PART[@]}" = "2" ]];
		then
			# Store the config name
			ITEM=${PART[0]}
			# Check the value
			VAL=${PART[1]}
			if [ $VAL = "y" ];
			then
				echo "#define $ITEM" >> $HEADER
				if [[ $ITEM = "CONFIG_NODE"* ]];
				then
					LASTNODEITEM=$ITEM
					let "NODECOUNT++"
				else
					LASTQUEUEITEM=$ITEM
					let "QUEUECOUNT++"
				fi

			else
				echo "// $ITEM is not defined" >> $HEADER
			fi
			echo >> $HEADER
		fi
	done < $CONFIG

	
	if [ "$NODECOUNT" -eq "0" ];
	then
		echo "#define DEF_NODE_TYPE INTEGER" >> $HEADER
		echo "#define DEF_NODE_FS \"%d\"" >> $HEADER
		echo "#define DEF_NODE_BIT ivalue" >> $HEADER
	elif [ "$NODECOUNT" -eq "1" ];
	then
		case $LASTNODEITEM in
			*"INTEGER") echo "#define DEF_NODE_TYPE INTEGER" >> $HEADER
				echo "#define DEF_NODE_FS \"%d\"" >> $HEADER
				echo "#define DEF_NODE_BIT ival" >> $HEADER
				echo "#define DEF_NODE_STRING \"integer\"" >> $HEADER
					;;
			*"REAL") echo "#define DEF_NODE_TYPE REAL" >> $HEADER
				echo "#define DEF_NODE_FS \"%f\"" >> $HEADER
				echo "#define DEF_NODE_BIT fval" >> $HEADER
				echo "#define DEF_NODE_STRING \"float\"" >> $HEADER
					;;
			*"CHARACTER") echo "#define DEF_NODE_TYPE CHARACTER" >> $HEADER
				echo "#define DEF_NODE_FS \" %c\"" >> $HEADER
				echo "#define DEF_NODE_BIT cval" >> $HEADER
				echo "#define DEF_NODE_STRING \"character\"" >> $HEADER
					;;
		esac
	else
		echo "#define MULVALUE" >> $HEADER
	fi

	echo >> $HEADER

	if [ "$QUEUECOUNT" -eq "0" ];
	then
		echo "#define DEF_QUEUE_TYPE LINEAR" >> $HEADER
	elif [ "$QUEUECOUNT" -eq "1" ];
	then
		case $LASTQUEUEITEM in
			*"LINEAR_QUEUE") echo "#define DEF_QUEUE_TYPE LINEAR" >> $HEADER
				echo "#define DEF_QUEUE_STRING \"Linear Queue\"" >> $HEADER
					;;
			*"DEQUE") echo "#define DEF_QUEUE_TYPE DEQUE" >> $HEADER
				echo "#define DEF_QUEUE_STRING \"Deque\"" >> $HEADER
					;;
			*"PRIORITY_QUEUE") echo "#define DEF_QUEUE_TYPE PRIORITY" >> $HEADER
				echo "#define DEF_QUEUE_STRING \"Priority Queue\"" >> $HEADER
					;;
		esac
	else
		echo "#define MULQUEUE" >> $HEADER
	fi
	
	echo >> $HEADER

	echo "#endif" >> $HEADER

	echo $2 created successfully..
fi
