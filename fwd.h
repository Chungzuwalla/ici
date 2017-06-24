// -*- mode:c++ -*-

#ifndef ICI_FWD_H
#define ICI_FWD_H

/*
 * fwd.h - basic configuration defines, universally used macros and
 * forward type, data and function defintions. Almost every ICI source
 * file needs this.
 */

/*
 * In general CONFIG_FILE is defined by the external build environment,
 * but for some common cases we have standard settings that can be used
 * directly. Windows in particular, because it is such a pain to handle
 * setting like this in Visual C, Project Builder and similar "advanced"
 * development environments.
 */
#if !defined(CONFIG_FILE)
#    if defined(_WINDOWS)
#        define CONFIG_FILE "conf/windows.h"
#    elif defined(__MACH__) && defined(__APPLE__)
#        define CONFIG_FILE "conf/darwin.h"
#    elif defined(__linux__)
#        define CONFIG_FILE "conf/linux.h"
#    elif defined(__FreeBSD__)
#        define CONFIG_FILE "conf/freebsd.h"
#    elif defined(__CYGWIN__)
#        define CONFIG_FILE "conf/cygwin.h"
#    endif
#endif

#ifndef CONFIG_FILE
/*
 * CONFIG_FILE is supposed to be set from some makefile with some compile
 * line option to something like "conf/sun.h" (including the quotes).
 */
#error "The preprocessor define CONFIG_FILE has not been set."
#endif

#ifndef ICI_CONF_H
#include CONFIG_FILE
#endif

/*
 * Configuration files MAY defines the UNLIKELY() and LIKELY() macros
 * used to inform the compiler of the likelihood of a condition.  If
 * either of these are not defined we use the expression as-is.
 */
#ifndef UNLIKELY
#define UNLIKELY(X) (X)
#endif
#ifndef LIKELY
#define LIKELY(X) (X)
#endif

/*
 * Turn on extra bug hunting in non-release builds.
 */
#ifndef NDEBUG
#define BUGHUNT
#endif

#include <cassert>

/*
 * The following portion of this file exports to ici.h. --ici.h-start--
 */
#include <cstddef>
#include <cstdlib>
#include <cstdint>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <csignal>
#include <cerrno>
#include <cmath>

#undef isset

namespace ici
{

/*
 * ICI version number. Note that this occurs in a string in conf.c too.
 *
 * ANICI uses a major version of 5 and the word 'ANICI' in the string.
 */
constexpr int major_version   = 5;
constexpr int minor_version   = 0;
constexpr int release_number  = 0;

/*
 * The ICI version number composed into an 8.8.16 unsigned long for simple
 * comparisons. The components of this are also available as 'major_version',
 * 'minor_version', and 'release_number'.
 *
 * This --constant-- forms part of the --ici-api--.
 */
constexpr unsigned long version_number = (
    ((unsigned long)major_version << 24) |
    ((unsigned long)minor_version << 16) |
    release_number
);

/*
 * The oldet version number for which the binary interface for seperately
 * compiled modules is backwards compatible. This is updated whenever
 * the exernal interface changes in a way that could break already compiled
 * modules. We aim to never to do that again. See 'check_interface()'.
 *
 * This --constant-- forms part of the --ici-api--.
 */
constexpr unsigned long back_compat_version = (5UL << 24) | (0UL << 16) | 0;

/*
 * DLI is defined in some configurations (Windows, in the conf include file)
 * to be a declaration modifier which must be applied to data objects being
 * referenced from a dynamically loaded DLL.
 *
 * If it hasn't been defined yet, define it to be null. Most system don't
 * need it.
 */
#ifndef DLI
#define DLI
#endif

#ifndef ICI_PATH_SEP
/*
 * The character which seperates directories in a path list on this
 * architecture.
 *
 * This --macro-- forms part of the --ici-api--.
 */
#define ICI_PATH_SEP    ':' /* Default, may have been set in config file */
#endif

/*
 * The character which seperates segments in a path on this
 * architecture. This is the default value, it may have been set in
 * the config file.
 */
#ifndef ICI_DIR_SEP
/*
 * The character which seperates segments in a path on this
 * architecture.
 *
 * This --macro-- forms part of the --ici-api--.
 */
#define ICI_DIR_SEP    '/' /* Default, may have been set in config file */
#endif

#ifndef ICI_DLL_EXT
/*
 * The string which is the extension of a dynamicly loaded library on this
 * architecture.
 *
 * This --macro-- forms part of the --ici-api--.
 */
#define ICI_DLL_EXT     ".so" /* Default, may have been set in config file */
#endif

/*
 * A hash function for pointers.  This is used in a few places.  Notably in
 * the hash of object addresses for struct lookup.  It is a balance between
 * effectiveness, speed, and machine knowledge.  It may or may not be right
 * for a given machine, so we allow it to be defined in the config file.  But
 * if it wasn't, this is what we use.
 */
#ifndef ICI_PTR_HASH
#define ICI_PTR_HASH(p) (crc_table[((size_t)(p) >>  4) & 0xFF] ^ crc_table[((size_t)(p) >> 12) & 0xFF])

/*
 * This is an alternative that avoids looking up the crc table.
#define ICI_PTR_HASH(p) (((unsigned long)(p) >> 12) * 31 ^ ((unsigned long)(p) >> 4) * 17)
*/
#endif

/*
 * A 'random' value for Windows event handling functions to return
 * to give a better indication that an ICI style error has occured which
 * should be propagated back. See events.c
 */
constexpr int ICI_EVENT_ERROR = 0x7A41B291;

#ifndef nels
#define nels(a)         (sizeof (a) / sizeof (a)[0])
#endif

/*
 * Size of a char arrays used to hold formatted object names.
 */
constexpr int objnamez = 32;

/*
 * Standard types.
 */
typedef class  archive          ici_archive_t;
typedef struct array            ici_array_t;
typedef struct catcher          ici_catcher_t;
typedef struct sslot            ici_sslot_t;
typedef struct set              ici_set_t;
typedef struct ici_struct       ici_struct_t;
typedef struct exec             ici_exec_t;
typedef struct ici_float        ici_float_t;
typedef struct file             ici_file_t;
typedef struct func             ici_func_t;
typedef struct cfunc            ici_cfunc_t;
typedef struct method           ici_method_t;
typedef struct ici_int          ici_int_t;
typedef struct mark             ici_mark_t;
typedef struct null             ici_null_t;
typedef struct object           ici_obj_t;
typedef struct objwsup          ici_objwsup_t;
typedef struct op               op_t;
typedef struct pc               ici_pc_t;
typedef struct ptr              ici_ptr_t;
typedef struct regexp           ici_regexp_t;
typedef struct src              ici_src_t;
typedef struct str              ici_str_t;
typedef class  type             type_t;
typedef struct wrap             ici_wrap_t;
typedef class  ftype            ici_ftype_t;
typedef struct forall           ici_forall_t;
typedef struct parse            ici_parse_t;
typedef struct mem              ici_mem_t;
typedef struct handle           ici_handle_t;
typedef struct debug            ici_debug_t;
typedef struct name_id          ici_name_id_t;
typedef struct restorer         restorer_t;
typedef struct saver            saver_t;
typedef struct expr             expr_t;

constexpr int                   nsubexp = 10;

extern DLI ici_int              *o_zero;
extern DLI ici_int              *o_one;
extern DLI char                 *error;
extern DLI exec                 *execs;
extern DLI exec                 *ex;
extern DLI array                xs;
extern DLI array                os;
extern DLI array                vs;
extern DLI uint32_t             vsver;
extern DLI int                  re_bra[(nsubexp + 1) * 3];
extern DLI int                  re_nbra;
extern DLI volatile int         aborted;                        /* See exec.c */
extern DLI int                  record_line_nums;               /* See lex.c */
extern DLI char                 *buf;                           /* See buf.h */
extern DLI size_t               bufz;                           /* See buf.h */
extern DLI mark                 o_mark;
extern DLI null                 o_null;
extern DLI ici_debug_t          *debugfunc;
extern char                     version_string[];
extern unsigned long const      crc_table[256];
extern int                      exec_count;
extern DLI ftype                *stdio_ftype;
extern DLI ftype                *popen_ftype;
extern DLI ftype                *parse_ftype;

/*
 * This ICI NULL object. It is of type '(object *)'.
 *
 * This --macro-- forms part of the --ici-api--.
 */
#define ici_null                (&o_null)

/*
 * Use 'return null_ret();' to return a ICI NULL from an intrinsic
 * fuction.
 *
 * This --macro-- forms part of the --ici-api--.
 */
extern object        *atom_probe(object *o);
extern object        *atom(object *, int);

extern int           parse_file(const char *, char *, ftype *);
extern int           parse_file(file *, objwsup *);
extern int           parse_file(const char *);

extern array         *new_array(ptrdiff_t);
extern exec          *new_exec();
extern file          *new_file(void *, ftype *, str *, object *);
extern handle        *new_handle(void *, str *, objwsup *);
extern ici_float     *new_float(double);
extern ici_int       *new_int(int64_t);
extern ici_struct    *new_struct();
extern mem           *new_mem(void *, size_t, int, void (*)(void *));
extern method        *new_method(object *, object *);
extern objwsup       *new_class(cfunc *cf, objwsup *super);
extern objwsup       *new_module(cfunc *cf);
extern ptr           *new_ptr(object *, object *);
extern regexp        *new_regexp(str *, int);
extern set           *new_set();
extern src           *new_src(int, str *);
extern str           *new_str(const char *, size_t);
extern str           *new_str_nul_term(const char *);

extern str           *str_alloc(size_t);
extern str           *str_get_nul_term(const char *);

extern int            check_interface(unsigned long, unsigned long, char const *);

extern file          *open_charbuf(char *, int, object *, int);
extern int            get_last_errno(const char *, const char *);

extern int            argcount(int);
extern int            argcount2(int, int);
extern int            argerror(int);

extern int            unassign(ici_struct *, object *);
extern int            unassign(set *, object *);

extern char          *objname(char [objnamez], object *);

extern int            close_file(file *f);

extern int            ret_with_decref(object *);
extern int            ret_no_decref(object *);
#define null_ret()    ret_no_decref(ici_null)
extern int            int_ret(int64_t);
extern int            float_ret(double);
extern int            str_ret(const char *);

extern int            typecheck(const char *, ...);
extern int            retcheck(const char *, ...);

extern int            main(int, char **);
extern int            init();
extern void           uninit();

extern file          *need_stdin();
extern file          *need_stdout();
extern array         *need_path();

extern void           reclaim();

extern int            call(object *, const char *, ...);
extern int            call(object *, object *, const char *, va_list);
extern int            call(str *, const char *, ...);
extern int            call(str *, const char *, va_list);
extern int            call_method(object *, str *, const char *, ...);

extern int            cmkvar(objwsup *, const char *, int, void *);
extern int            set_val(objwsup *, str *, int, void *);

extern int            fetch_num(object *, object *, double *);
extern int            fetch_int(object *, object *, long *);

extern handle        *handle_probe(void *, str *);

extern int            assign_cfuncs(objwsup *, cfunc *);
extern int            define_cfuncs(cfunc *);
extern int            register_type(type *);

extern void           invalidate_struct_lookaside(ici_struct *);
extern int            engine_stack_check();

extern void           ici_atexit(void (*)(), wrap *);

extern int            handle_method_check(object *, str *, handle **, void **);
extern int            method_check(object *o, int tcode);

extern unsigned long  crc(unsigned long, unsigned char const *, ptrdiff_t);

extern int            str_need_size(str *, size_t);
extern str           *new_str_buf(size_t);

extern object        *eval(str *);

extern object        *make_handle_member_map(ici_name_id_t *);

extern exec          *leave();
extern void           enter(exec *);
extern void           yield();
extern int            waitfor(object *);
extern int            wakeup(object *);

extern DLI int        ici_debug_enabled;
extern int            ici_debug_ign_err;
extern DLI void       ici_debug_ignore_errors();
extern DLI void       ici_debug_respect_errors();

/*
 * ici_sopen() is now a macro that calls ici_open_charbuf() for read-only access.
 * Included only for backward compatibility; use open_charbuf() instead.
 */
#define sopen(data, sz, ref) open_charbuf((data), (sz), (ref), 1)

#ifdef NODEBUGGING
    /*
     * If debug is not compiled in, we let the compiler use it's sense to
     * remove a lot of the debug code in performance critical areas.
     * Just to save on lots of ifdefs.
     */
#   define ici_debug_active     0
#else
    /*
     * Debugging is compiled-in. It is active if it is enabled at
     * run-time.
     */
#   define ici_debug_active     ici_debug_enabled
#endif

extern volatile sigset_t        signals_pending;
extern volatile long            signal_count[];
extern void                     signals_init();
extern int                      invoke_signal_handlers();
extern int                      blocking_syscall(int);

/*
 * End of ici.h export. --ici.h-end--
 */

extern object         *evaluate(object *, int);
extern char          **smash(char *, int);
extern char          **ssmash(char *, char *);
extern void            grow_atoms(ptrdiff_t newz);
extern const char     *binop_name(int);
extern sslot          *find_raw_slot(ici_struct *, object *);
extern object         *atom_probe2(object *, object ***);
extern int             parse_exec();

extern catcher        *new_catcher(object *, int, int, int);
extern cfunc          *new_cfunc(str *, int (*)(...), void *, void *);
extern pc             *new_pc();
extern func           *new_func();
extern op             *new_op(int (*)(), int16_t, int16_t);

extern parse          *new_parse(file *);

extern catcher        *unwind();

extern void            collect();

extern unsigned long   hash_float(double);
extern unsigned long   hash_string(object *);

extern int             op_binop();
extern int             op_onerror();
extern int             op_for();
extern int             op_andand();
extern int             op_switcher();
extern int             op_switch();
extern int             op_forall();
extern int             op_return();
extern int             op_call();
extern int             op_mkptr();
extern int             op_openptr();
extern int             op_fetch();
extern int             op_unary();
extern int             op_call();

extern void            grow_objs(object *);
extern int             set_error(const char *, ...);
extern void            expand_error(int, str *);
extern int             lex(parse *, array *);
extern void            uninit_compile();
extern void            uninit_cfunc();
extern int             exec_forall();
extern int             compile_expr(array *, expr *, int);
extern int             set_issubset(set *, set *);
extern int             set_ispropersubset(set *, set *);
extern int64_t         xstrtol(char const *, char **, int);
extern int             init_path(objwsup *externs);
extern int             find_on_path(char [FILENAME_MAX], const char *);
extern int             init_sstrings();
extern void            drop_all_small_allocations();
extern objwsup        *outermost_writeable_struct();
extern int             str_char_at(str *, size_t);

extern int             supress_collect;
extern int             ncollects;

extern object        **objs;
extern object        **objs_top;
extern object        **objs_limit;

extern object        **atoms;
extern size_t        natoms;
extern size_t        atomsz;

#if !defined(ICI_HAS_BSD_STRUCT_TM)
extern int set_timezone_vals(ici_struct *);
#endif

template <typename T> inline T *ptr_to_instance_of() {
    static T value;
    return &value;
}

} // namespace ici

#include "alloc.h"

#if defined(_WIN32) && !defined(NDEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#endif /* ICI_FWD_H */
