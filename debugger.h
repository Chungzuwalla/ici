// -*- mode:c++ -*-

#ifndef ICI_DEBUGGER_H
#define ICI_DEBUGGER_H

#include "object.h"

namespace ici
{

/*
 * The following portion of this file exports to ici.h. --ici.h-start--
 */

/*
 * ICI debug interface.
 *
 * A debugger is an instance of the 'ici::debugger' class, a base
 * class for ICI debuggers who's member functions define the interface
 * to a debugger.
 *
 * The interpreter has a global flag 'ici::debug_enabled' and a global
 * pointer to the debugger instance, 'ici::o_debug'. If the flag is
 * set, the interpreter calls the debugger's member functions.  See
 * 'ici::o_debug' and 'ici::debug_enabled'.
 *
 * The ici::debugger base-class provides default implementations of
 * the debugging functions. The default implementations do nothing.
 *
 * errorset()           Called with the value of error that IS TO BE
 *                      set. This is called immediately prior to setting
 *                      the error value visible to ICI code.
 *
 * error()              Called with the current value of error (redundant,
 *                      but retained for historical reasons) and a source line
 *                      marker object ('ici::src') on an uncaught error.
 *                      This is is called AFTER the stack has been unwound
 *                      so is of limited use.
 *
 * fncall()             Called with the object being called, the pointer to
 *                      the first actual argument (see 'ARGS()' and the number
 *                      of actual arguments just before control is transfered
 *                      to a callable object (function, method or anything
 *                      else).
 *
 * fnresult()           Called with the object being returned from any call.
 *
 * src()                Called each time execution passes into the region of a
 *                      new source line marker.  These typically occur before
 *                      any of the code generated by a particular line of
 *                      source.
 *
 * watch()              In theory, called when assignments are made.  However
 *                      optimisations in the interpreter have made this
 *                      difficult to support without performance penalties
 *                      even when debugging is not enabled.  So it is
 *                      currently disabled.  The function remains here pending
 *                      discovery of a method of achieving it efficiently.
 *
 * This --class-- forms part of the --ici-api--.
 */
class debugger {
public:
    virtual ~debugger();
    virtual void errorset(char *, struct src *);
    virtual void error(char *, struct src *);
    virtual void fncall(object *, object **, int);
    virtual void fnresult(object *);
    virtual void src(struct src *);
    virtual void watch(object *, object *, object *);
};

/*
 * End of ici.h export. --ici.h-end--
 */


} // namespace ici

#endif
