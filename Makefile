all:
	cd src; make

test : 
	cd src; make test

clean:
	cd src; make clean

test-gui:
	cd src; make test-gui

test-comm:
	cd src; make test-comm

tar:
	gtar cvzf Chat_V1.0_src.tar.gz README Icons INSTALL COPYRIGHT Makefile src doc bin --exclude=src/CVS --exclude=doc/CVS --exclude=bin/CVS --exclude=Icons/CVS --exclude=src/Icons/CVS --exclude=bin/Icons/CVS
