/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

#include "ga_queue.h"

ga_queue::ga_queue(int node_count)
{
	// TODO:
	// Initialize the queue.
	// For extra credit, preallocate 'node_count' elements (instead of
	// allocating on push).
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf
	queue_size = 0;
	queue = new queue_t();
	node_t *node = new node_t();
	queue->head = node, queue->tail = node;
	queue->h_lock.unlock(), queue->t_lock.unlock();

}

ga_queue::~ga_queue()
{
	// TODO:
	// Free any resources held by the queue.
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf
	
	// first locks the head and tail
	queue->h_lock.lock(), queue->t_lock.lock();
	while (true)
	{
		void* d;
		// pops from the queue until it is empty
		if (!pop(&d))
			break;
	}
	queue->h_lock.unlock(), queue->t_lock.unlock();
	delete(queue);
	
}

void ga_queue::push(void* data)
{
	// TODO:
	// Push 'data' onto the queue in a thread-safe manner.
	// If you preallocated 'node_count' elements, and if the queue is full when
	// this function is called, you must block until another thread pops an
	// element off the queue.
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf
	node_t *node = new node_t();
	node->data = data;
	node->next = NULL;
	// locks the tail before changing it
	queue->t_lock.lock();
	queue->tail->next = node;
	queue->tail = node;
	queue->t_lock.unlock();
	queue_size++;
}

bool ga_queue::pop(void** data)
{
	// TODO:
	// Pop one element off the queue in a thread-safe manner and place it in
	// the memory pointed to by 'data'.
	// If the queue is empty when this function is called, return false.
	// Otherwise return true.
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf
	
	// locks the head before changing it
	queue->h_lock.lock();
	node_t *node = queue->head;
	node_t *new_head = node->next;
	// checks if the queue is empty
	if (new_head == NULL) {
		queue->h_lock.unlock();
		return false;
	}
	*data = new_head;
	queue->head = new_head;
	queue->h_lock.unlock();
	free(node);
	return true;
}

int ga_queue::get_count() const
{
	// TODO:
	// Get the number of elements currently in the queue.
	return queue_size;
}
