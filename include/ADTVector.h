///////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT Vector μέσω Dynamic Array.
//
///////////////////////////////////////////////////////////
#include <typedefs.h>

// Το αρχικό μέγεθος που δεσμεύουμε
#define VECTOR_MIN_CAPACITY 10

// Ένα VectorNode είναι pointer σε αυτό το struct. (το struct περιέχει μόνο ένα στοιχείο, οπότε θα μπροούσαμε και να το αποφύγουμε, αλλά κάνει τον κώδικα απλούστερο)
struct vector_node {
	Pointer value;				// Η τιμή του κόμβου.
};

// Ενα Vector είναι pointer σε αυτό το struct
struct vector {
	VectorNode array;			// Τα δεδομένα, πίνακας από struct vector_node
	int size;					// Πόσα στοιχεία έχουμε προσθέσει
	int capacity;				// Πόσο χώρο έχουμε δεσμεύσει (το μέγεθος του array). Πάντα capacity >= size, αλλά μπορεί να έχουμε
	DestroyFunc destroy_value;	// Συνάρτηση που καταστρέφει ένα στοιχείο του vector.
};


Vector vector_create(int size, DestroyFunc destroy_value);

int vector_size(Vector vec);

Pointer vector_get_at(Vector vec, int pos);

void vector_set_at(Vector vec, int pos, Pointer value);

void vector_insert_last(Vector vec, Pointer value);

void vector_remove_last(Vector vec);

Pointer vector_find(Vector vec, Pointer value, CompareFunc compare);

DestroyFunc vector_set_destroy_value(Vector vec, DestroyFunc destroy_value);

void vector_destroy(Vector vec);


// Συναρτήσεις για διάσχιση μέσω node /////////////////////////////////////////////////////

VectorNode vector_first(Vector vec);

VectorNode vector_last(Vector vec);

VectorNode vector_next(Vector vec, VectorNode node);

VectorNode vector_previous(Vector vec, VectorNode node);

Pointer vector_node_value(Vector vec, VectorNode node);

VectorNode vector_find_node(Vector vec, Pointer value, CompareFunc compare);