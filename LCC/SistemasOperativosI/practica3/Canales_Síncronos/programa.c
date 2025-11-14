#include <pthread.h>
#include <semaphore.h>
struct channel {
	sem_t lector, escritor,leido,escrito;
	int data;
};

void channel_init(struct channel* c){
	sem_init(&c->lector, 0, 1);
	sem_init(&c->escritor,0,1);
	sem_init(&c->leido,0,0);
	sem_init(&c->leido,0,0);
	int data = 0;
}
void chan_write(struct channel *c, int v){
	sem_wait(&c->escritor);
	c->data = v;
	sem_post(&c->escrito);
	sem_wait(&c->leido);
	sem_post(&c->escritor);
}
int chan_read(struct channel *c){
	sem_wait(&c->lector);
	sem_wait(&c->escrito);
	int v = c->data;
	sem_post(&c->leido);
	sem_post(&c->lector);
	return v;
}
