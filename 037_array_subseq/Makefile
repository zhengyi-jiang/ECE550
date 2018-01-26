maxSeq:maxSeq.o test-subseq.o
	gcc -o test-subseq maxSeq.o test-subseq.o
maxSeq.o:maxSeq.c
	gcc  -Wall -Werror -std=gnu99 -pedantic -c maxSeq.c
test-subseq.o:test-subseq.c
	gcc  -Wall -Werror -std=gnu99 -pedantic -c test-subseq.c
clean:
	rm *.o *~ test-subseq
