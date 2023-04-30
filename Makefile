.PHONY: run build clean

BUILDDIR := build

run: build
	./$(BUILDDIR)/parni-pacman

build:
	mkdir -p $(BUILDDIR)
	cd $(BUILDDIR) && cmake .. && mv compile_commands.json ../ && make -j 8 
clean:
	rm -rf $(BUILDDIR)

# TODO kolo dal source soubory jinam nez do src hahaahaha
pack:
	zip xhucov00-xkolou05-xzobal01.zip Makefile README.md src/* CMakeLists.txt
