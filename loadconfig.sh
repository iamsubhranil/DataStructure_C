checkdef (){
	if [ "${!1}" = "y" ];
	then
		echo "#define $1 1" >> $2
	else
		echo "// $1 is not defined" >> $2
	fi
	echo >> $2
}

usage(){
	echo Usage : loadconfig.sh input_config_filename output_header_filename
	echo Example : loadconfig.sh defconfig config.h
}

if [ -z "$1" ];
then
	echo Please specify a config file to continue!
	usage
elif [ ! -e "$1" ];
then
	echo File $1 does not exist!
	usage
elif [ -z "$2" ];
then
	echo Please specify an output file to continue!
	usage
else
	if [ -e $2 ];
	then
		echo A header file with the same name exists already!
		echo Backing up previous $2..
		mv $2 $2.bak
	fi
	
	echo Loading configuration file..

	. ./$1

	echo Defining header name..

	NAME=""

	IFS='.' read -ra EXT <<< "$2"

	for i in "${EXT[@]}"; do
		NAME=$NAME"_"${i^^}
	done

	echo "#ifndef $NAME" >> $2
	echo "#define $NAME" >> $2
	echo >> $2

	echo Checking configuration options..

	for i in CONFIG_LINEAR_QUEUE CONFIG_DEQUE CONFIG_PRIORITY_QUEUE
	do
		checkdef $i $2
	done

	echo "#endif" >> $2

	echo $2 created successfully..
fi
