.PHONY: run build clean

BUILDDIR := build

run: build

build:
	mkdir -p $(BUILDDIR)
	cd $(BUILDDIR) && cmake .. && make

clean:
	rm -rf $(BUILDDIR)

