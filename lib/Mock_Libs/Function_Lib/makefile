
.PHONEY: clean
OS = $(shell uname -s)

ifeq ($(OS), Linux)
LIBADWFUNC = linuxlibadw.a
else ifeq ($(OS), Darwin)
LIBADWFUNC = darwinlibadw.a
endif

all: libadw.a
	@echo "************************ MADE LIBADWFUNC ***************************"

# Brings all libs into a single lib
darwinlibadw.a: 
	@echo "************** Making libadwfunc"
	libtool -static -o libadwfunc.a *.a
	@echo "************** libadwfunc made"

libadw.a:
	@echo "************** Making libadwfunc"
	ar -rv libadwfunc.a *.o
	@echo "************** libadwfunc made"

clean: 
	rm *.a
