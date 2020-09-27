all:cada_segundo cada_segundo_sigchld_activa cada_segundo_sigchld_bloqueo NProcesos NProcesosExit plauncher plauncherN signal_basico
cada_segundo:cada_segundo.c
	gcc -o cada_segundo cada_segundo.c 
cada_segundo_sigchld_activa:cada_segundo_sigchld_activa.c
	gcc -o cada_segundo_sigchld_activa cada_segundo_sigchld_activa.c 
cada_segundo_sigchld_bloqueo:cada_segundo_sigchld_bloqueo.c
	gcc -o cada_segundo_sigchld_bloqueo cada_segundo_sigchld_bloqueo.c 
NProcesos:NProcesos.c
	 gcc -o NProcesos NProcesos.c
NProcesosExit:NProcesosExit.c
	gcc -o NProcesosExit NProcesosExit.c 
plauncher:plauncher.c
	gcc -o plauncher plauncher.c 
plauncherN:plauncherN.c
	gcc -o plauncherN plauncherN.c
signal_basico:signal_basico.c
	gcc -o signal_basico signal_basico.c
clean:
	rm -f cada_segundo cada_segundo_sigchld_activa cada_segundo_sigchld_bloqueo NProcesos NProcesosExit plauncher plauncherN signal_basico
