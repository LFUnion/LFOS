# Copyright LFUnion
# 2016
# GNU

# the effect of this python file
# start of this file is tools

#includes
from os import listdir
from os.path import isfile
from os.path import isdir
from os import chdir
from os.path import abspath
from os import environ

#time
from time import sleep

#multiprocessing
from multiprocessing import Process
from multiprocessing import cpu_count

def tabreplace(filename):
	try:
		fileo = open(filename, "r")
		content = fileo.read()
		fileo.close()

		content = content.replace("\t", "    ")
		
		fileo = open(filename, "w")
		fileo.write(content)
		fileo.close()

	except UnicodeDecodeError:
		print("in "+abspath("")+"/"+filename + " is a Unicode character")



def searchfiles(i): 

	print(i)
	allfiles = listdir(i)
	
	
	if "tabreplacerecursiv.py" in allfiles:
		allfiles.remove("tabreplacerecursiv.py")
	if "Makefile" in allfiles:
		allfiles.remove("Makefile")


	for ff in allfiles:
		
		if isfile(i+ "/" +ff):
			tabreplace(i+ "/" +ff)
		elif isdir(i+ "/" +ff):
			searchfiles(i+ "/" +ff)
		else:
			pass

def main():

	print("Start")
	processlist = []
	count = 0

	chdir("..")

	lfosfolder = listdir()

	if "kernel" in lfosfolder:
		chdir("kernel")
	else:
		print("Wrong folder")
		return 1
	
	startfiles = listdir()

	i = abspath("")


	if "tabreplacerecursiv.py" in startfiles:
		startfiles.remove("tabreplacerecursiv.py")
	if "Makefile" in startfiles:
		startfiles.remove("Makefile")

	for pp in startfiles:
		if isdir(pp):

			pro = Process(target=searchfiles, args=(i + "/" +pp,))
			pro.start()

			processlist.append(pro)
			
	for fil in startfiles:
		if isfile(fil):		
			tabreplace(fil)

	startfiles2 = []

	for cc in startfiles:
		
		if not(isdir(cc) or isfile(cc)):
			startfiles2.append(cc)

	strvar=  ""

	for nf in startfiles2:
		strvar += nf + " "

	numberofprocess=len(processlist)

	while count<numberofprocess:

		if not(processlist[count].is_alive()):
			count +=1
		sleep(0.01)

	count = 0

	while count<numberofprocess:
		del processlist[0]
		count += 1

	print("these are no files or folder\n")
	print(strvar)

	return 0

# main part
if __name__=="__main__":
	# cores = environ["NUMBER_OF_PROCESSORS"]
	cores = cpu_count()
	print("Number of cores:", cores)

	main()

	print("Finish\n")