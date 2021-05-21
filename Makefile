all : ls mkdir cat rm date file

ls : 
	gcc -o ls ls_code.c

mkdir : 
	gcc -o mkdir mkdir_code.c

cat : 
	gcc -o cat cat_code.c

rm : 
	gcc -o rm rm_code.c

date : 
	gcc -o date date_code.c

file : 
	gcc -o file ques_2.c
	./file

clean : 	
	rm -rf ls mkdir cat rm date file
	
