merge:
	gcc "./Part 4/linkedList_func.c" "./Part 4/mergeSort.c" -o mergeSort
	./mergeSort

radix:
	gcc "./Part 4/linkedList_func.c" "./Part 4/radixSort.c" -o radixSort
	./radixSort

clean:
	find . -type f ! -name "*.c" ! -name "*.h" ! -name "*.txt" ! -name "Makefile" -delete
