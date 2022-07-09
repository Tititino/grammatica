#include <stdlib.h>

#define INIT_LLIST_TYPE(type, func)				          		\
	void do_nothing_##type(type) {							\
		return;									\
	}										\
											\
	(void) ll_node_destroy_element_##type(type) = func ? func : do_nothing_##type;	\
	typedef struct ll_node_##type {							\
		type value;								\
		struct ll_node_##type* next;						\
	} ll_node_##type;								\
											\
	typedef struct linked_list_##type {						\
		ll_node_##type* head;							\
		ll_node_##type* end;							\
		size_t len;								\
	} linked_list_##type;								\
											\
	ll_node_##type* ll_node_new_##type(type v) {					\
		ll_node_##type new_node = malloc(sizeof(struct ll_node_##type));	\
		new_node -> value = v;							\
		new_node -> next = NULL;						\
		return new_node;							\
	}										\
	 										\
	void ll_node_destroy_##type(ll_node_##type* node) {				\
		if (node == NULL) return;						\
											\
		ll_node_destroy_element_##(node -> value);				\
		free(node);								\
	}										\
											\
	linked_list_##type* ll_new_##type() {						\
		linked_list_##type new_list = malloc(sizeof(struct linked_list_##type));\
		new_list -> head = NULL;						\
		new_list -> end  = NULL;						\
		new_list -> len  = 0;							\
		return new_list;							\
	}										\
											\
	void ll_destroy_##type(linked_list_##type* l) {					\
		if (l == NULL)								\
			return;								\
											\
		int i;									\
		ll_node_##type* actual_node = l -> head, prec_node = NULL;		\
											\
		while (actual_node != NULL) {						\
			prec_node = actual_node;					\
			actual_node = actual_node -> next;				\
			ll_node_destroy_##type(prec_node);				\
		}									\
											\
		free(l);								\
	}							
