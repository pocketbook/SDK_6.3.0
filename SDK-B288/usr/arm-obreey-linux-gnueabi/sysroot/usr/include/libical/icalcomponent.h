/* -*- Mode: C -*- */
/*======================================================================
 FILE: icalcomponent.h
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

  The original code is icalcomponent.h

======================================================================*/

#ifndef ICALCOMPONENT_H
#define ICALCOMPONENT_H

#include "icalproperty.h"
#include "icalvalue.h"
#include "icalenums.h" /* defines icalcomponent_kind */
#include "pvl.h"

typedef struct icalcomponent_impl icalcomponent;

#ifndef ICALTIMEZONE_DEFINED
#define ICALTIMEZONE_DEFINED
/** @brief An opaque struct representing a timezone.  
 * We declare this here to avoid a circular dependancy. 
 */
typedef struct _icaltimezone		icaltimezone;
#endif


/* This is exposed so that callers will not have to allocate and
   deallocate iterators. Pretend that you can't see it. */
typedef struct icalcompiter
{
	icalcomponent_kind kind;
	pvl_elem iter;

} icalcompiter;

icalcomponent* icalcomponent_new(icalcomponent_kind kind);
icalcomponent* icalcomponent_new_clone(icalcomponent* component);
icalcomponent* icalcomponent_new_from_string(const char* str);
icalcomponent* icalcomponent_vanew(icalcomponent_kind kind, ...);
icalcomponent* icalcomponent_new_x(const char* x_name);
void icalcomponent_free(icalcomponent* component);

char* icalcomponent_as_ical_string(icalcomponent* component);
char* icalcomponent_as_ical_string_r(icalcomponent* component);

int icalcomponent_is_valid(icalcomponent* component);

icalcomponent_kind icalcomponent_isa(const icalcomponent* component);

int icalcomponent_isa_component (void* component);

/* 
 * Working with properties
 */

void icalcomponent_add_property(icalcomponent* component,
				icalproperty* property);

void icalcomponent_remove_property(icalcomponent* component,
				   icalproperty* property);

int icalcomponent_count_properties(icalcomponent* component,
				   icalproperty_kind kind);

/* Iterate through the properties */
icalproperty* icalcomponent_get_current_property(icalcomponent* component);

icalproperty* icalcomponent_get_first_property(icalcomponent* component,
					      icalproperty_kind kind);
icalproperty* icalcomponent_get_next_property(icalcomponent* component,
					      icalproperty_kind kind);


/* 
 * Working with components
 */ 


/* Return the first VEVENT, VTODO or VJOURNAL sub-component of cop, or
   comp if it is one of those types */

icalcomponent* icalcomponent_get_inner(icalcomponent* comp);


void icalcomponent_add_component(icalcomponent* parent,
				icalcomponent* child);

void icalcomponent_remove_component(icalcomponent* parent,
				icalcomponent* child);

int icalcomponent_count_components(icalcomponent* component,
				   icalcomponent_kind kind);

/**
   This takes 2 VCALENDAR components and merges the second one into the first,
   resolving any problems with conflicting TZIDs. comp_to_merge will no
   longer exist after calling this function. */
void icalcomponent_merge_component(icalcomponent* comp,
				   icalcomponent* comp_to_merge);


/* Iteration Routines. There are two forms of iterators, internal and
external. The internal ones came first, and are almost completely
sufficient, but they fail badly when you want to construct a loop that
removes components from the container.*/


/* Iterate through components */
icalcomponent* icalcomponent_get_current_component (icalcomponent* component);

icalcomponent* icalcomponent_get_first_component(icalcomponent* component,
					      icalcomponent_kind kind);
icalcomponent* icalcomponent_get_next_component(icalcomponent* component,
					      icalcomponent_kind kind);

/* Using external iterators */
icalcompiter icalcomponent_begin_component(icalcomponent* component,
					   icalcomponent_kind kind);
icalcompiter icalcomponent_end_component(icalcomponent* component,
					 icalcomponent_kind kind);
icalcomponent* icalcompiter_next(icalcompiter* i);
icalcomponent* icalcompiter_prior(icalcompiter* i);
icalcomponent* icalcompiter_deref(icalcompiter* i);


/* Working with embedded error properties */


/* Check the component against itip rules and insert error properties*/
/* Working with embedded error properties */
int icalcomponent_check_restrictions(icalcomponent* comp);

/** Count embedded errors. */
int icalcomponent_count_errors(icalcomponent* component);

/** Remove all X-LIC-ERROR properties*/
void icalcomponent_strip_errors(icalcomponent* component);

/** Convert some X-LIC-ERROR properties into RETURN-STATUS properties*/
void icalcomponent_convert_errors(icalcomponent* component);

/* Internal operations. They are private, and you should not be using them. */
icalcomponent* icalcomponent_get_parent(icalcomponent* component);
void icalcomponent_set_parent(icalcomponent* component, 
			      icalcomponent* parent);

/* Kind conversion routines */

int icalcomponent_kind_is_valid(const icalcomponent_kind kind);

icalcomponent_kind icalcomponent_string_to_kind(const char* string);

const char* icalcomponent_kind_to_string(icalcomponent_kind kind);


/************* Derived class methods.  ****************************

If the code was in an OO language, the remaining routines would be
members of classes derived from icalcomponent. Don't call them on the
wrong component subtypes. */

/** For VCOMPONENT: Return a reference to the first VEVENT, VTODO or
   VJOURNAL */
icalcomponent* icalcomponent_get_first_real_component(icalcomponent *c);

/** For VEVENT, VTODO, VJOURNAL and VTIMEZONE: report the start and end
   times of an event in UTC */
struct icaltime_span icalcomponent_get_span(icalcomponent* comp);

/******************** Convienience routines **********************/

void icalcomponent_set_dtstart(icalcomponent* comp, struct icaltimetype v);
struct icaltimetype icalcomponent_get_dtstart(icalcomponent* comp);

/* For the icalcomponent routines only, dtend and duration are tied
   together. If you call the set routine for one and the other exists,
   the routine will calculate the change to the other. That is, if
   there is a DTEND and you call set_duration, the routine will modify
   DTEND to be the sum of DTSTART and the duration. If you call a get
   routine for one and the other exists, the routine will calculate
   the return value. If you call a set routine and neither exists, the
   routine will create the apcompriate comperty */


struct icaltimetype icalcomponent_get_dtend(icalcomponent* comp);
void icalcomponent_set_dtend(icalcomponent* comp, struct icaltimetype v);

struct icaltimetype icalcomponent_get_due(icalcomponent* comp);
void icalcomponent_set_due(icalcomponent* comp, struct icaltimetype v);

void icalcomponent_set_duration(icalcomponent* comp, 
				struct icaldurationtype v);
struct icaldurationtype icalcomponent_get_duration(icalcomponent* comp);

void icalcomponent_set_method(icalcomponent* comp, icalproperty_method method);
icalproperty_method icalcomponent_get_method(icalcomponent* comp);

struct icaltimetype icalcomponent_get_dtstamp(icalcomponent* comp);
void icalcomponent_set_dtstamp(icalcomponent* comp, struct icaltimetype v);

void icalcomponent_set_summary(icalcomponent* comp, const char* v);
const char* icalcomponent_get_summary(icalcomponent* comp);

void icalcomponent_set_comment(icalcomponent* comp, const char* v);
const char* icalcomponent_get_comment(icalcomponent* comp);

void icalcomponent_set_uid(icalcomponent* comp, const char* v);
const char* icalcomponent_get_uid(icalcomponent* comp);

void icalcomponent_set_relcalid(icalcomponent* comp, const char* v);
const char* icalcomponent_get_relcalid(icalcomponent* comp);

void icalcomponent_set_recurrenceid(icalcomponent* comp, 
				    struct icaltimetype v);
struct icaltimetype icalcomponent_get_recurrenceid(icalcomponent* comp);

void icalcomponent_set_description(icalcomponent* comp, const char* v);
const char* icalcomponent_get_description(icalcomponent* comp);

void icalcomponent_set_location(icalcomponent* comp, const char* v);
const char* icalcomponent_get_location(icalcomponent* comp);

void icalcomponent_set_sequence(icalcomponent* comp, int v);
int icalcomponent_get_sequence(icalcomponent* comp);

void icalcomponent_set_status(icalcomponent* comp, enum icalproperty_status v);
enum icalproperty_status icalcomponent_get_status(icalcomponent* comp);


/** Calls the given function for each TZID parameter found in the
    component, and any subcomponents. */
void icalcomponent_foreach_tzid(icalcomponent* comp,
				void (*callback)(icalparameter *param, void *data),
				void *callback_data);

/** Returns the icaltimezone in the component corresponding to the
    TZID, or NULL if it can't be found. */
icaltimezone* icalcomponent_get_timezone(icalcomponent* comp,
					 const char *tzid);

int icalproperty_recurrence_is_excluded(icalcomponent *comp,
                                       struct icaltimetype *dtstart,
                                       struct icaltimetype *recurtime); 

void icalcomponent_foreach_recurrence(icalcomponent* comp,
				      struct icaltimetype start,
				      struct icaltimetype end,
			void (*callback)(icalcomponent *comp, 
                                         struct icaltime_span *span, 
                                         void *data),
			      void *callback_data);


/*************** Type Specific routines ***************/

icalcomponent* icalcomponent_new_vcalendar(void);
icalcomponent* icalcomponent_new_vevent(void);
icalcomponent* icalcomponent_new_vtodo(void);
icalcomponent* icalcomponent_new_vjournal(void);
icalcomponent* icalcomponent_new_valarm(void);
icalcomponent* icalcomponent_new_vfreebusy(void);
icalcomponent* icalcomponent_new_vtimezone(void);
icalcomponent* icalcomponent_new_xstandard(void);
icalcomponent* icalcomponent_new_xdaylight(void);
icalcomponent* icalcomponent_new_vagenda(void);
icalcomponent* icalcomponent_new_vquery(void);
icalcomponent* icalcomponent_new_vavailability(void);
icalcomponent* icalcomponent_new_xavailable(void);
icalcomponent* icalcomponent_new_vpoll(void);

#endif /* !ICALCOMPONENT_H */
