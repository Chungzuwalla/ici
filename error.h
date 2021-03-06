// -*- mode:c++ -*-

#ifndef ICI_ERROR_H
#define ICI_ERROR_H

#include "object.h"

namespace ici
{

/*
 * The following portion of this file exports to ici.h. --ici.h-start--
 */

/*
 * This --const-- forms part of the --ici-api--.
 */
constexpr int max_error_msg = 1024;

/*
 * Set the global ici::error value and return
 * non-zero as per the error returning convention.
 *
 * This --func-- forms part of the --ici-api--.
 */
int set_error(const char *, ...);

/*
 * Set the global ici::error value and return
 * non-zero as per the error returning convention.
 *
 * This --func-- forms part of the --ici-api--.
 */
int set_errorv(const char *, va_list);

/*
 * End of ici.h export. --ici.h-end--
 */

} // namespace ici

#endif /* ICI_ERROR_H */
