
prepare_and_build_hw1:
	mkdir hw-1/build 
	cd hw-1/build && cmake .. && make

rebuild_hw1:
	cd hw-1/build && make

run_hw1:
	./hw-1/build/hw-1

clean_hw1:
	rm -r hw-1/build

clean_all: clean_hw1