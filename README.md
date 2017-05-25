# Ftrace
Ftrace will allow you to generate a call-graph, which will explain a program's execution flow in detail.

Usage: ./ftrace [<options>] [<command>]
		
    -s, --strace	Display the details of the  arguments.

		-c, --counter	Display the number of timethat a function was called.

		-o [value], --output=value	Write the trace output to thefile filename rather than to stderr.

		--dotfile=value	Write the graph to the file.

		-t, -time	Prefix each line of the tracewith the time of day.

		-a [value], --align=value	Align return values in aspecific column (default column 40).
