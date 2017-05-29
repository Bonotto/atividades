#### MAKEFILE #####

# @Author: ismaelseidel
# @Date:   2016-08-12 17:18:46
# @Last Modified by:   ismaelseidel
# @Last Modified time: 2016-08-12 17:38:38

SRCDIR=./src
OBJDIR=./obj
DISTDIR=./dist
TESTDIR=./test
LANGDIR=./lang
DOCSDIR=./doc


SRC=$(subst .c,,$(notdir $(wildcard $(SRCDIR)/*.c)))

ALLOBJS=$(addprefix $(OBJDIR)/, $(addsuffix .o,$(SRC)))

BMP2CUIFOBJS=$(filter-out $(OBJDIR)/cuif2bmp.o,$(ALLOBJS))
CUIF2BMPBJS=$(filter-out $(OBJDIR)/bmp2cuif.o,$(ALLOBJS))

LIBS=-lm

COMPILER=gcc
FLAGS=-Wall -O3

##bmp2cuif
##

execs: bmp2cuif cuif2bmp

all: bmp2cuif cuif2bmp docs

bmp2cuif: $(DISTDIR)/bmp2cuif

cuif2bmp: $(DISTDIR)/cuif2bmp

$(DISTDIR)/bmp2cuif: $(BMP2CUIFOBJS)
	$(COMPILER) $(FLAGS) -o $(DISTDIR)/bmp2cuif $^ $(LIBS)

$(DISTDIR)/cuif2bmp: $(CUIF2BMPBJS)
	$(COMPILER) $(FLAGS) -o $(DISTDIR)/cuif2bmp $^ $(LIBS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c 
	$(COMPILER) $(FLAGS) -c -o $@ $<



docs: 
	doxygen Doxyfile


.PHONY: veryclean clean-all clean clean-objs clean-tests clean-lang

veryclean: clean-all clean-lang
	rm -rf $(DISTDIR)/*

clean-all: clean clean-tests clean-docs

clean: clean-objs

clean-objs:
	rm -rf $(OBJDIR)/*

clean-tests:
	rm -rf $(TESTDIR)/*

clean-docs:
	rm -rf $(DOCSDIR)/*

clean-lang:
	rm -rf $(LANGDIR)/*