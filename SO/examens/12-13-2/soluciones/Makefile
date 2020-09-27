all:controla_run  cuantos_running  FAT  generaFAT  lee_num  SumaVector_pth

controla_run:controla_run.c
	gcc -o controla_run controla_run.c

cuantos_running:cuantos_running.c
	gcc -o cuantos_running cuantos_running.c

FAT:FAT.c
	gcc -o FAT FAT.c

generaFAT:generaFAT.c
	gcc -o generaFAT generaFAT.c

lee_num:lee_num.c
	gcc -o lee_num lee_num.c

SumaVector_pth:SumaVector_pth.c
	gcc -o SumaVector_pth SumaVector_pth.c -lpthread

clean:
	rm -rf *.o controla_run  cuantos_running  FAT  generaFAT  lee_num  SumaVector_pth
