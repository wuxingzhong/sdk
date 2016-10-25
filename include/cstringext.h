#ifndef _cstringext_h_
#define _cstringext_h_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

// inline keyword
#if !defined(__cplusplus) && !defined(inline)
	#if _MSC_VER
		#define inline __inline
	#elif __GNUC__ && !__GNUC_STDC_INLINE__ && !__GNUC_GNU_INLINE__
		#define inline static __inline__ //__attribute__((unused))
		//#define inline static __inline__ __attribute__((always_inline))
	#endif
#endif

// UNUSED
#if defined(__cplusplus)
	#define UNUSED(x)
#else
	#if defined(_MSC_VER)
		#define UNUSED(x) x
	#elif defined(__GNUC__)
		#define UNUSED(x) x __attribute__((unused))
	#else
		#define UNUSED(x) x
	#endif
#endif

#if defined(OS_WINDOWS)
	#if !defined(stricmp)
		#define stricmp		_stricmp
	#endif

	#if !defined(strnicmp)
		#define strnicmp	_strnicmp
	#endif

	#if !defined(strdup)
		#define strdup		_strdup
	#endif

	#if !defined(atoll)
		#define atoll	_atoi64
	#endif

	#if defined(snprintf)
		#undef snprintf
	#endif
#else
	#ifndef stricmp
		#define stricmp strcasecmp
	#endif

	#ifndef strnicmp
		#define strnicmp strncasecmp
	#endif
#endif

//#define char_isnum(c)				('0'<=(c) && '9'>=(c))
//#define char_isalpha(c)				(('a'<=(c) && 'z'>=(c)) || ('A'<=(c) && 'Z'>=(c)))
//#define char_isalnum(c)				(char_isnum(c) || char_isalpha(c))

#define strempty(s)					((!s || 0==*s) ? 1 : 0)
#define streq(s, t)					(strcmp(s, t) ? 0 : 1)
#define strieq(s, t)				(stricmp(s, t) ? 0 : 1)
#define strneq(s, t, n)				(strncmp(s, t, n) ? 0 : 1)
#define strnieq(s, t, n)			(strnicmp(s, t, n) ? 0 : 1)
#define strstartswith(p, prefix)	(strncmp(p, prefix, strlen(prefix))? 0 : 1)
#define strendswith(p, suffix)		(strncmp(p+strlen(p)-strlen(suffix), suffix, strlen(suffix))? 0 : 1)

#define STRLEN(s)					(s?strlen(s):0)
#define FREE(p)						do{if(p){free(p); p=NULL;}}while(p)

#ifndef MAX
#define MAX(a, b)					((a)<(b)?(b):(a))
#endif

#ifndef MIN
#define MIN(a, b)					((a)<(b)?(a):(b))
#endif

#ifndef MAX_PATH
#define MAX_PATH					260
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/// get token(trim prefix/suffix)
/// @param[in] s source string(value will be changed '\0')
/// e.g.
/// strtoken("abc def", " ") => "abc"
/// strtoken("abc def", " c") => "ab"
char *strtoken(char *s, const char *delim, char **saveptr);

#if defined(OS_WINDOWS)
char* strndup(const char* p, size_t n);

#if _MSC_VER < 1900
int snprintf(char *str, size_t size, const char *format, ...);
#endif

#else

#ifndef GetLastError
	#define GetLastError() errno
#endif

#endif

#if !defined(OS_MAC)

size_t strlcpy(char *dst, const char *src, size_t siz);
size_t strlcat(char *dst, const char *src, size_t siz);

#endif


#if defined(__cplusplus)
}
#endif
#endif /* !_cstringext_h_ */
