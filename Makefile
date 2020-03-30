###############################################
# Sylvain Benilan                             #
# How to recompile entire claire from sources #
###############################################


SUFFIXE= .o .cpp .h .in .cl

all: public/ccmain.cl


#########################################
# first we need a stable claire version #
#########################################


./stable2/claire:
	@echo --------------------
	@echo - ./stable2/claire -
	@echo --------------------
	make -C stable2 -f stable.mk
	@echo -----------------------
	@echo - OK ./stable2/claire -
	@echo -----------------------


##################################
# and we configure various files #
##################################


configure: configure.in unix_step2.cl.in tmpclaire.mk.in
	@echo -------------
	@echo - configure -
	@echo -------------
	rm -f config.*
	autoheader -I include
	autoconf;
	./configure
	touch configure
	@echo ----------------
	@echo - OK configure -
	@echo ----------------



############################################################
# secondly we rebuild all the meta with our stable version #
# we generate here a tmpclaire1 binary                     #
############################################################


.claire_tmpclaire1: stable2/claire upgrade.cl compile/*.cl configure include/claire.h include/marie.h include/Kernel.h
	@echo ----------------------
	@echo - claire_tmpclaire1 stable2  -
	@echo ----------------------
	time ./stable2/claire -color -s 5 0 -n -f upgrade  -f step1.cl -q
	touch .claire_tmpclaire1
	@echo -------------------------
	@echo - OK claire_tmpclaire1  -
	@echo -------------------------

tmpclaire1: .claire_tmpclaire1
	@echo ---------------
	@echo - tmpclaire1  -
	@echo ---------------
	rm -f console/*.o
	rm -f kernel/*.o
	time make -j 4 -f tmpclaire.mk tmpclaire1
	@echo ------------------
	@echo - OK tmpclaire1  -
	@echo ------------------


###########################################################################
# thirdly we rebuild all meta with the updated compiler (i.e. tmpclaire1) #
# and we generate a tmpclaire2 binary                                     #
###########################################################################


.claire_tmpclaire2: tmpclaire1 meta/*.cl step2.cl version.cl
	@echo --------------
	@echo - tmpclaire2 -
	@echo --------------
	time ./tmpclaire1 -color -s 5 0 -n -f unix_step2.cl -f step2.cl -q
	touch .claire_tmpclaire2
	@echo -----------------
	@echo - OK tmpclaire2 -
	@echo -----------------

tmpclaire2: .claire_tmpclaire2 console/clConsole.cpp kernel/*.cpp
	@echo --------------
	@echo - tmpclaire2 -
	@echo --------------
	rm -f console/*.o
	rm -f kernel/*.o
	time make -j 4 -f tmpclaire.mk tmpclaire2
	@echo -----------------
	@echo - OK tmpclaire2 -
	@echo -----------------


release/configure: release/configure.in.unix
	autoheader -I include release/configure.in.unix
	autoconf -o release/configure release/configure.in.unix


#####################################
# How to create a public xl version #
#####################################

public/ccmain.cl: doc/claire.html ./tmpclaire2 release/ccmain.cl release/configure release/Makefile.in.unix release/Makefile.in.mvs release/init.cl release/Makefile.nt
	@echo -------
	@echo - pub -
	@echo -------
	mkdir -p public
	rm -drf public/*
	mkdir -p public/csrc
	cp -R meta public
	rm -drf public/meta/CVS
	rm -drf public/meta/.svn
	cp -R include public
	cp -R doc public
	rm -drf public/doc/CVS
	rm -drf public/doc/.svn
	rm -f public/include/config.h
	rm -f public/include/acconfig.h
	rm -drf public/include/CVS
	rm -drf public/include/.svn
	cp -R csrc public
	rm public/csrc/*.o
	cp kernel/*.cpp public/csrc
	cp release/Makefile.in.unix public/Makefile.in
	cp release/Makefile.in.mvs public/Makefile.mvs.in
	cp release/configure public
	cp release/init.cl public
	cp console/*.cpp public/csrc
	cp release/install.cl public
	cp release/README.txt public
	cp csrc/Optimize.cpp public/csrc/Optimize.cpp.in
	cp csrc/Generate.cpp public/csrc/Generate.cpp.in
	mv public/csrc/claire-s.cpp public/csrc/sclaire-s.cpp
	cp release/Makefile.nt public/Makefile.nt
	cp release/ccmain.cl public
	rm -drf xlclaire-`./tmpclaire2 -eval 'printf("v~A",release())' -q`
	cp -R public xlclaire-`./tmpclaire2 -eval 'printf("v~A",release())' -q`
	tar -czf xlclaire-`./tmpclaire2 -eval 'printf("v~A",release())' -q`.tgz \
		xlclaire-`./tmpclaire2 -eval 'printf("v~A",release())' -q`
	./cleantar.pl xlclaire-`./tmpclaire2 -eval 'printf("v~A",release())' -q`.tgz
	@echo ----------
	@echo - OK pub -
	@echo ----------


doc/claire.html: tmpclaire2 meta/*.cl
	./tmpclaire2 -s 5 0 -apidoc claire -q


a:
	touch upgrade.cl
	make

aa:
	touch configure.in
	make a

d:
	make
	cp release/Makefile.in.unix.debug xlclaire-`./tmpclaire2 -eval 'printf("v~A",release())' -q`/Makefile.in
	cp release/init.cl.debug xlclaire-`./tmpclaire2 -eval 'printf("v~A",release())' -q`/init.cl
	tar -czf xlclaire-`./tmpclaire2 -eval 'printf("v~A",release())' -q`.tgz xlclaire-`./tmpclaire2 -eval 'printf("v~A",release())' -q`


install: d
	cp kernel/*.o xlclaire-`./tmpclaire2 -eval 'printf("v~A",release())' -q`/csrc
	cp console/*.o xlclaire-`./tmpclaire2 -eval 'printf("v~A",release())' -q`/csrc
	cp csrc/*.o xlclaire-`./tmpclaire2 -eval 'printf("v~A",release())' -q`/csrc
	./tmpclaire2 \
			-chdir xlclaire-`./tmpclaire2 -eval 'printf("v~A",release())' -q` \
			-eval 'shell("./configure")' -q
	make -C xlclaire-`./tmpclaire2 -eval 'printf("v~A",release())' -q`
	sudo make -C xlclaire-`./tmpclaire2 -eval 'printf("v~A",release())' -q` install


moduled:
	claire -s 5 0 -v 2 -chdir ../modules -D -call -sudo -ov -publish

module:
	claire -s 5 0 -v 2 -chdir ../modules -O -os 5 -call -sudo -ov -publish
	

ad:
	make a
	make d


h:
	@echo "---- Claire Makefile ----"
	@echo "Usage : make [aa | a | d | ad | install]"
	@echo "This makefile builds a public claire tgz archive"
	@echo "Options :"
	@echo "  aa - rebuild all including configured files"
	@echo "  ad - rebuild all source files and produce an archive ready for debug"
	@echo "  a  - rebuild all source files"
	@echo "  d  - build source files and produce an archive ready for debug"
	@echo "  install - fast install of claire with the current debug tmpclaire2"



################################################################
# How to commit the public xl version as the new stable claire #
#  (the next 'make' will generate a new stable claire)         #
################################################################


commit_stable:
	@echo -----------------
	@echo - commit_stable -
	@echo -----------------
	rm -f stable/include/*.h
	rm -f stable/include/*.h.in
	rm -f stable/csrc/*.o
	rm -f stable/csrc/*.cpp
	rm -f stable/csrc/*.cpp.in
	cp include/*.h stable/include
	cp include/*.h.in stable/include
	cp csrc/*.cpp stable/csrc
	cp kernel/*.cpp stable/csrc
	cp console/*.cpp stable/csrc
	mv stable/csrc/Optimize.cpp stable/csrc/Optimize.cpp.in
	mv stable/csrc/gusage.cpp stable/csrc/gusage.cpp.in
	mv stable/csrc/claire-s.cpp stable/csrc/sclaire-s.cpp
	cp release/Makefile.in.unix stable/Makefile.in
	cp release/configure stable
	cp release/init.cl stable
	cp release/ccmain.cl stable
	rm -f stable/sclaire
	rm -f stable/cclaire
	@echo --------------------
	@echo - OK commit_stable -
	@echo --------------------


clean:
	@echo ---------
	@echo - clean -
	@echo ---------
	rm -rf autom4te.cache
	rm -f config.*
	rm -f configure
	rm -f csrc/*.o
	rm -f csrc/*.obj
	rm -f csrc1/*.o
	rm -f csrc1/*.obj
	rm -f stable/csrc/*.o
	rm -f stable/csrc1/*.obj
	rm -rf stable/lib
	rm -rf stable/sclaire*
	rm -rf stable/sclaire
	rm -rf stable/cclaire*
	rm -rf stable/cclaire
	rm -rf stable/sclaire.mk
	rm -f stable/Makefile
	rm -f stable/config.*
	rm -f include/config.h
	rm -f include/config.h.in~
	rm -f include/Core.h
	rm -f include/Reader.h
	rm -f include/Language.h
	rm -f include/Optimize.h
	rm -f include/Generate.h
	rm -f include/Serialize.h
	rm -f include/Serialize.h
	rm -f last_claire.*
	rm -rf public
	rm -f tmpclaire.mk
	rm -f tmpclaire1
	rm -f tmpclaire2
	rm -f unix_step2.cl
	rm -rf csrc/*
	rm -rf csrc1/*
	rm -rf xlclaire-*
	rm -rf doc
	rm -f release/configure
	@echo ------------
	@echo - OK clean -
	@echo ------------
	
