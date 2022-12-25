#include <climits>
#include <stdint.h>
#include <stdio.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" char * elektraStrip(char * text);

extern "C" int LLVMFuzzerTestOneInput (const uint8_t * data, size_t size)
{
	FuzzedDataProvider provider (data, size);
	char * str = strdup (provider.ConsumeRandomLengthString ().c_str ());

	elektraStrip (str);

	free (str);
	return 0;
}
