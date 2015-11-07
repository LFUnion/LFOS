.SILENT:build, mkiso

build:
	cd kernel; make

test:
	cd kernel; make test

testATA:
	cd kernel; make testATA

mkiso:
	cd iso; make

todo:
	python3 tools/todo.py

clean:
	cd kernel; make clean
	cd iso; make clean
