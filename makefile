# The makefile for MP2.
# Type:
#   make         -- to build program lab2
#   make driver -- to compile testing program
#   make clean   -- to delete object files, executable, and core
#   make design  -- check for simple design errors (incomplete)
#   make list.o  -- to compile only list.o (or: use lab2.o, sas_support.o)
#
# You should not need to change this file.  
#
# Format for each entry
#    target : dependency list of targets or files
#    <tab> command 1
#    <tab> command 2
#    ...
#    <tab> last command
#    <blank line>   -- the list of commands must end with a blank line

lab2 : list.o sas_support.o lab2.o
	gcc -Wall -g list.o sas_support.o lab2.o -o lab2

list.o : list.c datatypes.h list.h
	gcc -Wall -g -c list.c

sas_support.o : sas_support.c datatypes.h list.h sas_support.h
	gcc -Wall -g -c sas_support.c

lab2.o : lab2.c datatypes.h list.h sas_support.h
	gcc -Wall -g -c lab2.c

driver : driver.o list.o sas_support.o
	gcc -Wall -g list.o sas_support.o driver.o -o driver

driver.o : driver.c datatypes.h list.h sas_support.h
	gcc -Wall -g -c driver.c

#  @ prefix suppresses output of shell command
#  - prefix ignore errors
#  @command || true to avoid Make's error
#  : is shorthand for true
design :
	@grep -e "-> *head" lab2.c sas_support.c ||:
	@grep -e "-> *tail" lab2.c sas_support.c ||:
	@grep -e "-> *current_list_size" lab2.c sas_support.c ||:
	@grep -e "-> *list_sorted_state" lab2.c sas_support.c ||:
	@grep -e "-> *next" lab2.c sas_support.c ||:
	@grep -e "-> *prev" lab2.c sas_support.c ||:
	@grep -e "-> *data_ptr" lab2.c sas_support.c ||:
	@grep "list_node_t" lab2.c sas_support.c ||:
	@grep "su_id" list.c ||:
	@grep "channel" list.c ||:
	@grep "sas_" list.c ||:

clean :
	rm -f *.o lab2 driver core a.out

