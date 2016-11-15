.PHONY: examples

clean:
	rm -rf examples/bin

style:
	find inlib -type f | xargs astyle --options=dot.astylerc

examples:
	mkdir -p examples/bin
	g++ examples/wroot.cpp -o examples/bin/wroot -I. -lz
	g++ examples/rroot.cpp -o examples/bin/rroot -I. -lz
	g++ examples/wroot_tree.cpp -o examples/bin/wroot_tree -I. -lz
	g++ examples/root_ls.cpp -o examples/bin/root_ls -I. -lz

