/**
 * @file
 *
 * @brief
 *
 * @copyright BSD License (see LICENSE.md or https://www.libelektra.org)
 *
 */


#ifndef ELEKTRA_PLUGIN_NEWTYPE_H
#define ELEKTRA_PLUGIN_NEWTYPE_H

#include <stdbool.h>

#include <kdbplugin.h>
#include <kdbtypes.h>

#ifdef __cplusplus
extern "C" {
namespace ckdb
{
#endif

typedef struct _Type Type;

struct boolean_pair
{
	const char * trueValue;
	const char * falseValue;
};

typedef struct
{
	kdb_long_long_t booleanCount;
	struct boolean_pair * booleans;
} NewTypeData;

int elektraNewTypeOpen (Plugin * handle, Key * errorKey);
int elektraNewTypeGet (Plugin * handle, KeySet * ks, Key * parentKey);
int elektraNewTypeSet (Plugin * handle, KeySet * ks, Key * parentKey);
int elektraNewTypeClose (Plugin * handle, Key * errorKey);
int elektraNewTypeCheckConf (Key * errorKey, KeySet * conf);

bool elektraNewTypeCheckType (const Key * key);
bool elektraNewTypeValidateKey (Plugin * handle, Key * key, Key * errorKey);

Plugin * ELEKTRA_PLUGIN_EXPORT;

#ifdef __cplusplus
}
};
#endif

#endif
