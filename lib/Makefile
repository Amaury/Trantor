INCLUDES	= gc.h \
		  gc_config_macros.h \
		  gc_version.h
LIB		= libgc.so

.PHONY: compile clean

compile:
	cd gc-7.4.0 ; make
	cd gc-7.4.0/include ; cp $(INCLUDES) ../../../include/
	cp gc-7.4.0/.libs/$(LIB) ./

clean:
	rm -f ./$(LIB)
	cd ../include ; rm -f $(INCLUDES)

