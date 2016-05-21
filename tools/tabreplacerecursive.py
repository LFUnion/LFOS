from os import listdir
from os.path import isfile
from os.path import isdir
from os import chdir
from os.path import abspath
from time import sleep

print (abspath(""))

def tabreplace(filename):
	try:
		fileo = open(filename, "r")
		content = fileo.read()
		fileo.close()

		content = content.replace("\t", "    ")
		print(content)
		fileo = open(filename, "w")
		fileo.write(content)
		fileo.close()
	except UnicodeDecodeError:
		print(abspath("")+filename + "is a Unicode character")

def searchfiles(i):
	chdir(i) 
	print(abspath(""))
	#sleep(1)
	allfiles = listdir()
	
	
	if "tabreplacerecursiv.py" in allfiles:
		allfiles.remove("tabreplacerecursiv.py")
	if "Makefile" in allfiles:
		allfiles.remove("Makefile")


	print(allfiles)

	for ff in allfiles:
		
		if isfile(ff):
			tabreplace(ff)
		elif isdir(ff):
			searchfiles(ff)
		else:
			pass
	chdir("..")

def main():
	i = abspath("")
	searchfiles(i)


main()
