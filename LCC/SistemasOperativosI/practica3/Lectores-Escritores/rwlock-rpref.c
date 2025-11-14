#include <semaphore.h>
#include <stdlib.h>
#include "rwlock.h"

/* Read-preferring */

struct rwlock {
	int nr; // Numero de lectores
	sem_t sn; // Semaforos que funcionan como lock de escritura y lectura.
	sem_t sl;
};

struct rwlock * rwlock_init()
{
	struct rwlock *rwl = malloc(sizeof *rwl);
	sem_init(&rwl->sn, 0, 1); // Locks
	sem_init(&rwl->sl, 0, 1); // Locks
	rwl->nr = 0;
	return rwl;
}

void rwlock_destroy(struct rwlock *rwl)
{
	sem_destroy(&rwl->sn);
	sem_destroy(&rwl->sl);
	free(rwl);
}

void lock_r(struct rwlock *rwl)
{
	sem_wait(&rwl->sn); // Tomamos uno de los locks
	if (rwl->nr == 0)
		sem_wait(&rwl->sl); // Si somos el primer escritor, entonces tomamos el otro lock
	rwl->nr++; // Ahora hay al menos un escritor.
	sem_post(&rwl->sn); // Aumentamos el otro lock por si quiere entrar otro lector
}

void unlock_r(struct rwlock *rwl)
{
	sem_wait(&rwl->sn); // Hay que tomar el lock para actualizar nr
	rwl->nr--; // Decrementamos
	if (rwl->nr == 0)
		sem_post(&rwl->sl); // Devolvemos el lock a los escritores
	sem_post(&rwl->sn); // Devolvemos el lock para que los otros readers puedan desbloquear
}

void lock_w(struct rwlock *rwl)
{
	sem_wait(&rwl->sl); //lock de escritura
}

void unlock_w(struct rwlock *rwl)
{
	sem_post(&rwl->sl); // lock de escritura
}
