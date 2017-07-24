import os
import sys
import subprocess
import time
import random


def main(argv):

	result = {}

	min_concur = 90
	max_concur = 100

	do_attack = True

	for concur in range(min_concur, max_concur + 1):
	
		print "concur = " + str(concur)

		
		if do_attack:
			attack_proc = subprocess.Popen(["python", "/home/hongyuliu/workspace/OurBugbenchs/heartbleed/test/hb-test-concur.py", "localhost", "-c", "100"])

		ab_result = subprocess.check_output(["/home/hongyuliu/workspace/OurBugbenchs/heartbleed/siege/bin/siege", "-r100", "-c" + str(concur), "https://localhost/"])
		#ab_result = subprocess.check_output(["/home/hongyuliu/workspace/apps4doubletake/httpd/bin/ab", "-n", "10000", "-c", str(concur), "https://localhost/"])
		#ab_result = subprocess.check_output(["ab", "-t", "15", "-c", str(concur), "https://localhost/"])
		print "ab done"

		req_per_sec = 0;

		for line in ab_result.split("\n"):
			if "Requests per second:" in line:
				count = 0;				
				for _str in line.split(" "):
					count += 1
					if count > 3 and _str != "":
						req_per_sec = float(_str)
						break
				break

		result[concur] = req_per_sec

		if do_attack:
			attack_proc.wait()	
	
	f_result = open('CCS_nginx_result.csv', 'w')
	f_result.write("concur,req_per_sec\n")
	for concur in range(min_concur, max_concur + 1):
		f_result.write(str(concur) + "," + str(result[concur]) + "\n")

	f_result.close()
	
main(sys.argv)
