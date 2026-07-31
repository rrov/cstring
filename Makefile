STRICT_CFLAGS = -std=c90 -pedantic -Wall -Wextra -Werror \
                -Wshadow -Wundef -Wconversion -Wsign-conversion \
                -Wcast-qual -Wcast-align -Wstrict-prototypes \
                -Wmissing-prototypes -Wmissing-declarations \
                -Wredundant-decls -Wnested-externs -Wuninitialized \
                -Winit-self -Wfloat-equal -Wbad-function-cast \
                -Wwrite-strings -Wpointer-arith -Wswitch \
                -Waggregate-return

DEV_CFLAGS = -std=c90 -pedantic -Wall -Wextra

lib-dev:
	cc -c $(DEV_CFLAGS) CString.c -o CString.o
	ar rcs libCString.a CString.o
lib:
	cc -c $(STRICT_CFLAGS) CString.c -o CString.o
	ar rcs libCString.a CString.o
test:
	cc -o tests $(DEV_CFLAGS) tests.c libCString.a
clean:
	rm -rf ./CString.o
	rm -rf ./libCString.a
	rm -rf ./tests
