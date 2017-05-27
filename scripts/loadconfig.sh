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
	done <<< $(basename $2)

	echo Internal header name : $NAME..

	echo //Automatically generated by loadconfig > $HEADER
	echo "#ifndef $NAME" >> $HEADER
	echo "#define $NAME" >> $HEADER
	echo >> $HEADER

	echo Checking configuration options..

	# Read the file line by line
	LASTNODEITEM=""
	LASTITEM=""
	NODECOUNT=0
	COUNT=0
	NODECONFIG=include/node_config.h
	rm $NODECONFIG
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
				if [[ $ITEM = "CONFIG_NODE"* ]];
				then
					if [ "$NODECOUNT" -eq "0" ];
					then
						echo "#ifndef NODE_CONFIG_H" > $NODECONFIG
						echo -e "#define NODE_CONFIG_H\n" >> $NODECONFIG
					fi
					echo "#define $ITEM" >> $NODECONFIG
					if [[ ! "$ITEM" = "CONFIG_NODE_PRIORITY" ]];
					then
						LASTNODEITEM=$ITEM
						let "NODECOUNT++"
					fi
				else
					echo "#define $ITEM" >> $HEADER
					LASTITEM=$ITEM
					let "COUNT++"
				fi

			else
				echo "// $ITEM is not defined" >> $HEADER
			fi
			echo >> $HEADER
		fi
	done < $CONFIG

	if [ "$NODECOUNT" -eq "0" ];
	then
		echo "#ifndef NODE_CONFIG_H" >> $NODECONFIG
		echo -e "#define NODE_CONFIG_H\n" >> $NODECONFIG
	fi
	if [ "$NODECOUNT" -eq "0" ] || ([ "$NODECOUNT" -eq "1" ] && [[ "$LASTNODEITEM" = *"INTEGER" ]]);
	then
		echo "#define DEF_NODE_TYPE INTEGER" >> $NODECONFIG
		echo "#define DEF_NODE_FS \"%d\"" >> $NODECONFIG
		echo "#define DEF_NODE_BIT ival" >> $NODECONFIG
		echo "#define DEF_NODE_STRING \"integer\"" >> $NODECONFIG
	elif [ "$NODECOUNT" -eq "1" ];
	then
		case $LASTNODEITEM in
			*"REAL") echo "#define DEF_NODE_TYPE REAL" >> $NODECONFIG
				echo "#define DEF_NODE_FS \"%f\"" >> $NODECONFIG
				echo "#define DEF_NODE_BIT fval" >> $NODECONFIG
				echo "#define DEF_NODE_STRING \"float\"" >> $NODECONFIG
					;;
			*"CHARACTER") echo "#define DEF_NODE_TYPE CHARACTER" >> $NODECONFIG
				echo "#define DEF_NODE_FS \" %c\"" >> $NODECONFIG
				echo "#define DEF_NODE_BIT cval" >> $NODECONFIG
				echo "#define DEF_NODE_STRING \"character\"" >> $NODECONFIG
					;;
		esac
	else
		echo "#define MULVALUE" >> $NODECONFIG
	fi

	echo -e "\n#endif" >> $NODECONFIG

	if [ ! -z "$3" ];
	then
		source $3
	fi

	echo "#endif" >> $HEADER

	echo $2 created successfully..
fi
