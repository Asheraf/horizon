CC = gcc
CFLAGS = $(shell grep '^CFLAGS = ' crypt_blowfish-1.3/Makefile | cut -d= -f2-)
.PHONY: crypt_blowfish-1.3

all: bcrypt.a

test: bcrypt.c crypt_blowfish-1.3
	$(CC) $(CFLAGS) -DTEST_BCRYPT -c bcrypt.c
	$(CC) -o bcrypt_test bcrypt.o crypt_blowfish-1.3/*.o

bcrypt.a: bcrypt.o crypt_blowfish
	ar r bcrypt.a bcrypt.o crypt_blowfish-1.3/*.o

bcrypt.o: bcrypt.c
	$(CC) $(CFLAGS) -c bcrypt.c

crypt_blowfish:
	$(MAKE) -C crypt_blowfish-1.3

clean:
	rm -f *.o bcrypt_test bcrypt.a *~ core
	$(MAKE) -C crypt_blowfish-1.3 clean