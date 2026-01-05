/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * Type definitions
 */

#ifndef NSN_CORE_TYPES_H
#define NSN_CORE_TYPES_H

#include "object.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
typedef struct _object nsn_object;

/* Built-in Type Objects */
extern nsn_type Nsn_TypeType;
extern nsn_type Nsn_IntType;
extern nsn_type Nsn_FloatType;
extern nsn_type Nsn_BoolType;
extern nsn_type Nsn_StringType;
extern nsn_type Nsn_ListType;
extern nsn_type Nsn_DictType;
extern nsn_type Nsn_FunctionType;
extern nsn_type Nsn_ModuleType;
extern nsn_type Nsn_IPAddrType;
extern nsn_type Nsn_NetworkType;

/* Singleton Objects */
extern nsn_object *Nsn_True;
extern nsn_object *Nsn_False;
extern nsn_object *Nsn_None;

/* Type check macros */
#define NsnBool_Check(op) (Nsn_TYPE(op) == &Nsn_BoolType)
#define NsnInt_Check(op) (Nsn_TYPE(op) == &Nsn_IntType)
#define NsnString_Check(op) (Nsn_TYPE(op) == &Nsn_StringType)
#define NsnList_Check(op) (Nsn_TYPE(op) == &Nsn_ListType)
#define NsnDict_Check(op) (Nsn_TYPE(op) == &Nsn_DictType)
#define NsnIP_Check(op) (Nsn_TYPE(op) == &Nsn_IPAddrType)

#ifdef __cplusplus
}
#endif

#endif // NSN_CORE_TYPES_H
