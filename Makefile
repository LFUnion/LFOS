.SILENT:build, mkiso

all:
	make build

build:
	cd kernel; make

test:
	cd kernel; make test

testATA:
	cd kernel; make testATA

dbochs:
	bochs -f bochs.conf

mkiso:
	cd iso; make

todo:
	python3 tools/todo.py

clean:
	cd kernel; make clean
	cd iso; make clean
