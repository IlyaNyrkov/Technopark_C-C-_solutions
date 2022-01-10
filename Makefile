# hw1
prepare_and_build_hw1:
	mkdir hw-1/build 
	cd hw-1/build && cmake .. && make

rebuild_hw1:
	cd hw-1/build && make

run_hw1:
	./hw-1/build/hw-1

run_hw1_tests:
	./hw-1/build/tests

clean_hw1:
	rm -r hw-1/build

# hw2
prepare_and_build_hw2:
	mkdir hw-2/build 
	cd hw-2/build && cmake .. && make

rebuild_hw2:
	cd hw-2/build && make

run_hw2_stress_test:
	./hw-2/build/stress_test

clean_hw2:
	rm -r hw-2/build

clean_all: clean_hw1 clean_hw2