TEMPLATES=$(shell find template/)

HASH=0

all: build/main.pdf

build/main.pdf: $(TEMPLATES) makefile sections.yaml doall.py clean | build/
	python doall.py --usehash "$(HASH)" > build/main.tex
	cp template/fa-github.pdf build/
	cd build && xelatex -synctex=1 -shell-escape -8bit -interaction=nonstopmode main.tex
	cd build && xelatex -synctex=1 -shell-escape -8bit -interaction=nonstopmode main.tex
	cd build && xelatex -synctex=1 -shell-escape -8bit -interaction=nonstopmode main.tex

build/:
	mkdir -p build

clean:
	rm -rf build/

.PHONY: all clean
