
prepare_and_build_hw1:
	mkdir hw-1/build
	mkdir hw-1_executables
	cd hw-1/build
	cmake ..
	mv hw-1 ../../hw-1_executables
clean_hw1:
	rm -r hw-1/build
	rm -r hw-1_executables

clean_all: clean_hw1