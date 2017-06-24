// -*- mode:c++ -*-

#ifndef ICI_PTR_H
#define ICI_PTR_H

#include "object.h"

namespace ici
{

/*
 * The following portion of this file exports to ici.h. --ici.h-start--
 */
struct ptr : object
{
    object   *p_aggr;        /* The aggregate which contains the object. */
    object   *p_key;         /* The key which references it. */
};

inline ici_ptr_t *ici_ptrof(object *o) { return static_cast<ici_ptr_t *>(o); }
inline bool ici_isptr(object *o) { return o->isa(ICI_TC_PTR); }

/*
 * End of ici.h export. --ici.h-end--
 */

class ptr_type : public type
{
public:
    ptr_type() : type("ptr", sizeof (struct ptr), type::has_call) {}

    size_t mark(object *o) override;
    int cmp(object *o1, object *o2) override;
    unsigned long hash(object *o) override;
    object *fetch(object *o, object *k) override;
    int assign(object *o, object *k, object *v) override;
    int call(object *o, object *subject) override;
};

} // namespace ici

#endif  /* ICI_PTR_H */
