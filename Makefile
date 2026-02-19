merge:
	gcc "./Part 4/queue_func.c" "./Part 4/mergeSort.c" -o mergeSort
	./mergeSort

regex:
	gcc "./Part 4/queue_func.c" "./Part 4/regexSort.c" -o regexSort
	./regexSort

clean:
	find . -type f ! -name "*.c" ! -name "*.h" ! -name "*.txt" ! -name "Makefile" -delete
