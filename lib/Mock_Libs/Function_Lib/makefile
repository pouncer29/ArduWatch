
.PHONEY: clean

all: libadwfunc.a 
	@echo "************************ MADE LIBADWFUNC ***************************"

# Brings all libs into a single lib
libadwfunc.a: 
	@echo "************** Making libadwfunc"
	libtool -static -o libadwfunc.a *.a
	@echo "************** libadwfunc made"

clean: 
	rm *.a
