"""
This program will walk through a directory containing malware files
and analyze libraries being exported by a portable executable.

If the memory addresses of the libraries repeat, if an export 
library name repeats, or if a memory offset repeats, then the script
will print that to stdout and continue walking through the directory.
"""

import collections
import os
import pefile
import sys

home = os.path.expanduser('~')
malware_files = os.path.join(home, 'malware_lab_1')
file_list = []

for root, dirs, files in os.walk(malware_files):
	for name in files:
		file_list.append(os.path.join(root, name))

for malware_file in file_list:
	pe = pefile.PE(malware_file)
	
	hex_addresses = [hex(x.address + pe.OPTIONAL_HEADER.ImageBase) for x in pe.DIRECTORY_ENTRY_EXPORT.symbols]
	duplicate_hex = [item for item, count in collections.Counter(hex_addresses).items() if count >= 3]
	if duplicate_hex:
		f = os.path.basename(malware_file)
		print(f + ' has duplicate hex addresses')
	
	lib_name = [x.name for x in pe.DIRECTORY_ENTRY_EXPORT.symbols]
	duplicate_lib = [item for item, count in collections.Counter(lib_name).items() if count >= 2]
	if duplicate_lib:
		f = os.path.basename(malware_file)
		print(f + ' has duplicate libraries exported')
		
	count = len(hex_addresses) - 1
	increments = []
	while count != 0:
		val1 = int(hex_addresses[count - 1], 16)
		val2 = int(hex_addresses[count], 16)
		increments.append(val2 - val1)
		count -= 1
	incre_dups = [item for item, count in collections.Counter(increments).items() if count >= 3]
	if incre_dups:
		f = os.path.basename(malware_file)
		print(f + ' violates the memory offset rule.')
		
	
	
