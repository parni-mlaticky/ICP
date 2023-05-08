.PHONY: run build clean

BUILDDIR := build

build:
	mkdir -p $(BUILDDIR)
	cd $(BUILDDIR) && cmake .. && mv compile_commands.json ../ && make -j 8

run: build
	./$(BUILDDIR)/parni-pacman

merlin:
	rsync -P -v -r --delete ./ merlin:icp/ &&\
	make clean &&\
	ssh -Y -C merlin 'cd icp && make run ; exit 0'
	exit 0

clean:
	rm -rf $(BUILDDIR)
	rm -rf doc

pack:
	zip -r xhucov00-xkolou05-xzobal01.zip Makefile README.txt src/* CMakeLists.txt LICENSE Doxyfile examples/* assets/*

doxygen:
	doxygen Doxyfile
