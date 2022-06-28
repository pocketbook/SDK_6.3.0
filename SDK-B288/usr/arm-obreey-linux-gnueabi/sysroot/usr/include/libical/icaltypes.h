/* -*- Mode: C -*- */
/*======================================================================
 FILE: icaltypes.h
 CREATOR: eric 20 March 1999


 (C) COPYRIGHT 2000, Eric Busboom <eric@softwarestudio.org>
     http://www.softwarestudio.org

 This program is free software; you can redistribute it and/or modify
 it under the terms of either: 

    The LGPL as published by the Free Software Foundation, version
    2.1, available at: http://www.fsf.org/copyleft/lesser.html

  Or:

    The Mozilla Public License Version 1.0. You may obtain a copy of
    the License at http://www.mozilla.org/MPL/

  The original code is icaltypes.h

======================================================================*/

#ifndef ICALTYPES_H
#define ICALTYPES_H

#include <time.h>
#include "icalenums.h"
#include "icaltime.h"
#include "icalduration.h"
#include "icalperiod.h"


struct icalgeotype 
{
	double lat;
	double lon;
};


struct icaldatetimeperiodtype 
{
	struct icaltimetype time;
	struct icalperiodtype period;
};


struct icaltriggertype 
{
	struct icaltimetype time; 
	struct icaldurationtype duration;
};

struct icaltriggertype icaltriggertype_from_int(const int reltime);
struct icaltriggertype icaltriggertype_from_string(const char* str);

int icaltriggertype_is_null_trigger(struct icaltriggertype tr);
int icaltriggertype_is_bad_trigger(struct icaltriggertype tr);

/* struct icalreqstattype. This struct contains two string pointers,
but don't try to free either of them. The "desc" string is a pointer
to a static table inside the library.  Don't try to free it. The
"debug" string is a pointer into the string that the called passed
into to icalreqstattype_from_string. Don't try to free it either, and
don't use it after the original string has been freed.

BTW, you would get that original string from
*icalproperty_get_requeststatus() or icalvalue_get_text(), when
operating on the value of a request_status property. */

struct icalreqstattype {

	icalrequeststatus code;
	const char* desc;
	const char* debug;
};

struct icalreqstattype icalreqstattype_from_string(const char* str);
const char* icalreqstattype_as_string(struct icalreqstattype);
char* icalreqstattype_as_string_r(struct icalreqstattype);



struct icaltimezonephase {
    const char* tzname;
    int is_stdandard; /* 1 = standard tme, 0 = daylight savings time */
    struct icaltimetype dtstart;
    int offsetto;
    int tzoffsetfrom;
    const char* comment;
    struct icaldatetimeperiodtype rdate;
    const char* rrule;    
};


struct icaltimezonetype {
    const char* tzid;
    struct icaltimetype last_mod;
    const char* tzurl;
    
    /* Array of phases. The end of the array is a phase with tzname == 0 */
    struct icaltimezonephase *phases;
};

void icaltimezonetype_free(struct icaltimezonetype tzt);

/* ical_unknown_token_handling :
 *    How should the ICAL library handle components, properties and parameters with
 *    unknown names?
 *    FIXME:  Currently only affects parameters.  Extend to components and properties.
 */
typedef enum ical_unknown_token_handling {
    ICAL_ASSUME_IANA_TOKEN = 1, 
    ICAL_DISCARD_TOKEN = 2,
    ICAL_TREAT_AS_ERROR = 3 
} ical_unknown_token_handling;

ical_unknown_token_handling ical_get_unknown_token_handling_setting(void);
void ical_set_unknown_token_handling_setting(ical_unknown_token_handling newSetting);

#endif /* !ICALTYPES_H */
