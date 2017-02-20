LIN_Q="CONFIG_LINEAR_QUEUE=y"
DE_Q="CONFIG_DEQUE=y"
PR_Q="CONFIG_PRIORITY_QUEUE=y"
CONFIGS=$LIN_Q
dialog --title "Configure libqueue build options" --msgbox "libqueue can be compiled to
	perform operations on any of the following queue combinations : \n1. Linear Queue
	\n2. Linear Queue and Deque\n3. Priority Queue\n4. Linear Queue, Deque and Priority Queue" 10 70

if [ "$?" = "0" ]
	then
	dialog --title "Configure libqueue build options" --msgbox "Choosing any one of these options in the next screen will compile the queue library with the capability to handle _ONLY_ that type of queue(s).\nThis is will result in a very memory efficient and less complicated library.\nJust remember, after recompiling this library, all the programs using this library will also have to be recompiled, as the methods and structures in the library will be changed." 10 100
	if [ "$?" = "0" ]
	then
		exec 3>&1;
		SEL=$(dialog --backtitle "Select the queue types" \
			--radiolist "Queue types (Press space to select) : " 11 55 5 \
	       		1 "Linear Queue" on 2 "Linear Queue and Dequeue" off \
			3 "Priority Queue" off 4 "Linear Queue, Deque and Priority Queue" off \
			2>&1  1>&3);
		if [ "$?" = "0" ]
		then
			case $SEL in
				2)CONFIGS=$CONFIGS'\n'$DE_Q;;
				3)CONFIGS=$PR_Q;;
				4)CONFIGS=$CONFIGS'\n'$DE_Q'\n'$PR_Q;;
			esac
			dialog --msgbox "You've selected option $SEL.\nlibqueue will now be recompiled with the following configuration :\n$CONFIGS" 11 50
			if [ "$?" = "0" ]
			then
				printf $CONFIGS > configs/queue_defconfig
				exec 2>&1
				make all | dialog --title "Compiling" --gauge "Please wait..." 10 70 0
			fi

		else
			dialog --msgbox "You've canceled libqueue recompilation!" 10 50
		fi
		exec 3>&-;
	else
		dialog --msgbox "You've canceled libqueue recompilation!" 10 50
	fi
else
	dialog --msgbox "You've canceled libqueue recompilation!" 10 50
fi
