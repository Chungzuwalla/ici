#define ICI_CORE
#include "fwd.h"
#include "int.h"
#include "primes.h"

namespace ici
{

ici_int *small_ints[small_int_count];

/*
 * Return the int object with the value 'v'.  The returned object has had its
 * ref count incremented.  Returns NULL on error, usual convention.  Note that
 * ints are intrinsically atomic, so if the given integer already exists, it
 * will just incref it and return it.
 *
 * Note, 0 and 1 are available directly as 'ici_zero' and 'ici_one'.
 *
 * This --func-- forms part of the --ici-api--.
 */
ici_int *
ici_int_new(int64_t i)
{
    object *o;
    object **po;

    if ((i & ~small_int_mask) == 0 && (o = small_ints[i]) != NULL)
    {
        o->incref();
        return ici_intof(o);
    }
    for
    (
        po = &ici_atoms[ici_atom_hash_index((unsigned long)i * INT_PRIME)];
        (o = *po) != NULL;
        --po < ici_atoms ? po = ici_atoms + ici_atomsz - 1 : NULL
    )
    {
        if (ici_isint(o) && ici_intof(o)->i_value == i)
        {
            o->incref();
            return ici_intof(o);
        }
    }
    ++ici_supress_collect;
    if ((o = ici_talloc(ici_int)) == NULL)
    {
        --ici_supress_collect;
        return NULL;
    }
    ICI_OBJ_SET_TFNZ(o, ICI_TC_INT, ICI_O_ATOM, 1, sizeof (ici_int));
    ici_rego(o);
    ici_intof(o)->i_value = i;
    --ici_supress_collect;
    ICI_STORE_ATOM_AND_COUNT(po, o);
    return ici_intof(o);
}

/*
 * Returns 0 if these objects are equal, else non-zero.
 * See the comments on t_cmp() in object.h.
 */
int int_type::cmp(object *o1, object *o2)
{
    return ici_intof(o1)->i_value != ici_intof(o2)->i_value;
}

/*
 * Return a hash sensitive to the value of the object.
 * See the comment on t_hash() in object.h
 */
unsigned long int_type::hash(object *o)
{
    /*
     * There are in-line versions of this in object.c and binop.h.
     */
    return (unsigned long)ici_intof(o)->i_value * INT_PRIME;
}

} // namespace ici
