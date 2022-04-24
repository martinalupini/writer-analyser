
all:
	gcc writer.c -o writer
	gcc redirector.c -o write_on_file
	gcc analyser.c -o analyser

remove:
	rm writer
	rm write_on_file
	rm analyser
