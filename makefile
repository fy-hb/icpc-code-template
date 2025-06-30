SRCS=$(shell find template/)

build/main.pdf: $(SRCS) makefile sections.yaml clean
	mkdir -p build/
	cp template/fa-github.svg build/
	python doall.py > build/main.tex
	cd build && xelatex -synctex=1 -shell-escape -8bit -interaction=nonstopmode main.tex
	cd build && xelatex -synctex=1 -shell-escape -8bit -interaction=nonstopmode main.tex
	cd build && xelatex -synctex=1 -shell-escape -8bit -interaction=nonstopmode main.tex


.PHONY: clean check
check:
	true # code valid check

clean:
	rm -rf build/
