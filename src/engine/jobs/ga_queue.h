#pragma once
#include <mutex>

/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

// node structure that stores its data and the next node
struct node_t
{
	void* data;
	node_t *next;
};
// queue structure that 
struct queue_t
{
	node_t *head;
	node_t *tail;
	std::mutex h_lock;
	std::mutex t_lock;
};

/*
** Thread-safe queue.
** https://www.research.ibm.com/people/m/michael/podc-1996.pdf
*/
class ga_queue
{
public:
	// variables
	int queue_size;
	queue_t *queue;
	

	// functions
	ga_queue(int node_count);
	~ga_queue();

	void push(void* data);
	bool pop(void** data);

	int get_count() const;
};
