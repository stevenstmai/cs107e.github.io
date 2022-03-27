P = slides

default: $(P).pdf

open: $(P).pdf
	xdg-open $< &

%.pdf: %.tex Makefile
	pdflatex --shell-escape $<

clean:
	rm -f *.aux *.log

.PHONY: open clean
