#!/bin/bash

usage(){
	echo Usage : loadconfig.sh input_config_filename output_header_filename
	echo Example : loadconfig.sh defconfig config.h
}

CONFIG=configs/$1

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
	HEADER=include/$2

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
			else
				echo "// $ITEM is not defined" >> $HEADER
			fi
			echo >> $HEADER
		fi
	done < $CONFIG

echo "#endif" >> $HEADER

	echo $2 created successfully..
fi
