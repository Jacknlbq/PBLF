src = putout.o main.o init.o queue.o menu.o user.o Igd_res.o Strategy.o


Test.out : $(src)
	gcc $^ -o $@
putout.o : putout.c
	gcc -c $< -o $@
init.o : init.c
	gcc -c $< -o $@
main.o : main.c
	gcc -c $< -o $@
queue.o : queue.c
	gcc -c $< -o $@	
menu.o : menu.c
	gcc -c $< -o $@
user.o : user.c
	gcc -c $< -o $@	
Igd_res.o : Igd_res.c
	gcc -c $< -o $@	
Strategy.o : Strategy.c	
	gcc -c $< -o $@
clean :
	-rm -rf $(src)
