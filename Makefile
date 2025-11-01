.PHONY: all clean ultraclean test

all:
	make -C src SCAT3

clean:
	make -C src clean
	rm -r tests/new_results tests/ref_results

ultraclean: clean
	make -C src ultraclean

test:
	./tests/compare_results.sh