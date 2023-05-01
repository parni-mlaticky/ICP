.PHONY: run build clean

BUILDDIR := build

build:
	mkdir -p $(BUILDDIR)
	cd $(BUILDDIR) && cmake .. && mv compile_commands.json ../ && make -j 8

run: build
	./$(BUILDDIR)/parni-pacman

clean:
	rm -rf $(BUILDDIR)

# TODO kolo dal source soubory jinam nez do src hahaahaha
pack:
	zip xhucov00-xkolou05-xzobal01.zip Makefile README.md src/* CMakeLists.txt
