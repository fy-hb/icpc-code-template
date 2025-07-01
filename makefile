TEMPLATES=$(shell find template/)

all: build/main.pdf

build/main.pdf: $(TEMPLATES) makefile sections.yaml doall.py clean | build/
	python doall.py > build/main.tex
	cp template/fa-github.pdf build/
	cd build && xelatex -synctex=1 -shell-escape -8bit -interaction=nonstopmode main.tex
	cd build && xelatex -synctex=1 -shell-escape -8bit -interaction=nonstopmode main.tex
	cd build && xelatex -synctex=1 -shell-escape -8bit -interaction=nonstopmode main.tex

build/:
	mkdir -p build

clean:
	rm -rf build/

.PHONY: all clean
