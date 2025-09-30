///////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT List μέσω συνδεδεμένης λίστας.
//
///////////////////////////////////////////////////////////
// Ενα List είναι pointer σε αυτό το struct
#include <typedefs.h>

struct list {
	ListNode dummy;				// χρησιμοποιούμε dummy κόμβο, ώστε ακόμα και η κενή λίστα να έχει έναν κόμβο.
	ListNode last;				// δείκτης στον τελευταίο κόμβο, ή στον dummy (αν η λίστα είναι κενή)
	int size;					// μέγεθος, ώστε η list_size να είναι Ο(1)
	DestroyFunc destroy_value;	// Συνάρτηση που καταστρέφει ένα στοιχείο της λίστας.
};

struct list_node {
	ListNode next;		// Δείκτης στον επόμενο
	Pointer value;		// Η τιμή που αποθηκεύουμε στον κόμβο
};


List list_create(DestroyFunc destroy_value);

int list_size(List list);

void list_insert(List list, Pointer value);

ListNode list_previous(List list, ListNode current_node);

void list_delete(List list, ListNode node);

DestroyFunc list_set_destroy_value(List list, DestroyFunc destroy_value);

void list_destroy(List list);


// Διάσχιση της λίστας /////////////////////////////////////////////

ListNode list_first(List list);

ListNode list_last(List list);

ListNode list_next(List list, ListNode node);

Pointer list_node_value(List list, ListNode node);

ListNode list_find_node(List list, Pointer value, CompareFunc compare);

Pointer list_find(List list, Pointer value, CompareFunc compare);