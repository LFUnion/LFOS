.SILENT:build

build:
	cd kernel; make

test:
	cd kernel; make test

clean:
	cd kernel; make clean
