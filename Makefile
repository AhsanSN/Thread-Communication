
all:
	gcc -o threads threads.c -lpthread

clean:
	rm threads producer.txt consumer.txt

rebuild: clean all
