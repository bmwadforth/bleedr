#ifndef BLEEDR_WRAPPERS_H
#define BLEEDR_WRAPPERS_H

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC void json_writer_bridge(char* buff, char* filename);

#undef EXTERNC
// ...

#endif //BLEEDR_WRAPPERS_H
