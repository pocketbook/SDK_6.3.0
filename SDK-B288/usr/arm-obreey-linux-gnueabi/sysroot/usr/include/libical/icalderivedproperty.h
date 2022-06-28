/* -*- Mode: C -*-
  ======================================================================
  FILE: icalderivedproperties.{c,h}
  CREATOR: eric 09 May 1999
  
  $Id: icalderivedproperty.h.in,v 1.7 2007-04-30 13:57:48 artcancro Exp $

 This program is free software; you can redistribute it and/or modify
 it under the terms of either:

    The LGPL as published by the Free Software Foundation, version
    2.1, available at: http://www.fsf.org/copyleft/lesser.html

  Or:

    The Mozilla Public License Version 1.0. You may obtain a copy of
    the License at http://www.mozilla.org/MPL/

 (C) COPYRIGHT 2000, Eric Busboom, http://www.softwarestudio.org
 ======================================================================*/


#ifndef ICALDERIVEDPROPERTY_H
#define ICALDERIVEDPROPERTY_H

#include <time.h>
#include "icalparameter.h"
#include "icalderivedvalue.h"  
#include "icalrecur.h"

typedef struct icalproperty_impl icalproperty;

typedef enum icalproperty_kind {
    ICAL_ANY_PROPERTY = 0,
    ICAL_ACCEPTRESPONSE_PROPERTY = 102, 
    ICAL_ACKNOWLEDGED_PROPERTY = 1, 
    ICAL_ACTION_PROPERTY = 2, 
    ICAL_ALLOWCONFLICT_PROPERTY = 3, 
    ICAL_ATTACH_PROPERTY = 4, 
    ICAL_ATTENDEE_PROPERTY = 5, 
    ICAL_BUSYTYPE_PROPERTY = 101, 
    ICAL_CALID_PROPERTY = 6, 
    ICAL_CALMASTER_PROPERTY = 7, 
    ICAL_CALSCALE_PROPERTY = 8, 
    ICAL_CAPVERSION_PROPERTY = 9, 
    ICAL_CARLEVEL_PROPERTY = 10, 
    ICAL_CARID_PROPERTY = 11, 
    ICAL_CATEGORIES_PROPERTY = 12, 
    ICAL_CLASS_PROPERTY = 13, 
    ICAL_CMD_PROPERTY = 14, 
    ICAL_COMMENT_PROPERTY = 15, 
    ICAL_COMPLETED_PROPERTY = 16, 
    ICAL_COMPONENTS_PROPERTY = 17, 
    ICAL_CONTACT_PROPERTY = 18, 
    ICAL_CREATED_PROPERTY = 19, 
    ICAL_CSID_PROPERTY = 20, 
    ICAL_DATEMAX_PROPERTY = 21, 
    ICAL_DATEMIN_PROPERTY = 22, 
    ICAL_DECREED_PROPERTY = 23, 
    ICAL_DEFAULTCHARSET_PROPERTY = 24, 
    ICAL_DEFAULTLOCALE_PROPERTY = 25, 
    ICAL_DEFAULTTZID_PROPERTY = 26, 
    ICAL_DEFAULTVCARS_PROPERTY = 27, 
    ICAL_DENY_PROPERTY = 28, 
    ICAL_DESCRIPTION_PROPERTY = 29, 
    ICAL_DTEND_PROPERTY = 30, 
    ICAL_DTSTAMP_PROPERTY = 31, 
    ICAL_DTSTART_PROPERTY = 32, 
    ICAL_DUE_PROPERTY = 33, 
    ICAL_DURATION_PROPERTY = 34, 
    ICAL_EXDATE_PROPERTY = 35, 
    ICAL_EXPAND_PROPERTY = 36, 
    ICAL_EXRULE_PROPERTY = 37, 
    ICAL_FREEBUSY_PROPERTY = 38, 
    ICAL_GEO_PROPERTY = 39, 
    ICAL_GRANT_PROPERTY = 40, 
    ICAL_ITIPVERSION_PROPERTY = 41, 
    ICAL_LASTMODIFIED_PROPERTY = 42, 
    ICAL_LOCATION_PROPERTY = 43, 
    ICAL_MAXCOMPONENTSIZE_PROPERTY = 44, 
    ICAL_MAXDATE_PROPERTY = 45, 
    ICAL_MAXRESULTS_PROPERTY = 46, 
    ICAL_MAXRESULTSSIZE_PROPERTY = 47, 
    ICAL_METHOD_PROPERTY = 48, 
    ICAL_MINDATE_PROPERTY = 49, 
    ICAL_MULTIPART_PROPERTY = 50, 
    ICAL_NAME_PROPERTY = 51, 
    ICAL_ORGANIZER_PROPERTY = 52, 
    ICAL_OWNER_PROPERTY = 53, 
    ICAL_PERCENTCOMPLETE_PROPERTY = 54, 
    ICAL_PERMISSION_PROPERTY = 55, 
    ICAL_POLLITEMID_PROPERTY = 103, 
    ICAL_POLLMODE_PROPERTY = 104, 
    ICAL_POLLPROPERTIES_PROPERTY = 105, 
    ICAL_POLLWINNER_PROPERTY = 106, 
    ICAL_PRIORITY_PROPERTY = 56, 
    ICAL_PRODID_PROPERTY = 57, 
    ICAL_QUERY_PROPERTY = 58, 
    ICAL_QUERYLEVEL_PROPERTY = 59, 
    ICAL_QUERYID_PROPERTY = 60, 
    ICAL_QUERYNAME_PROPERTY = 61, 
    ICAL_RDATE_PROPERTY = 62, 
    ICAL_RECURACCEPTED_PROPERTY = 63, 
    ICAL_RECUREXPAND_PROPERTY = 64, 
    ICAL_RECURLIMIT_PROPERTY = 65, 
    ICAL_RECURRENCEID_PROPERTY = 66, 
    ICAL_RELATEDTO_PROPERTY = 67, 
    ICAL_RELCALID_PROPERTY = 68, 
    ICAL_REPEAT_PROPERTY = 69, 
    ICAL_REQUESTSTATUS_PROPERTY = 70, 
    ICAL_RESOURCES_PROPERTY = 71, 
    ICAL_RESTRICTION_PROPERTY = 72, 
    ICAL_RRULE_PROPERTY = 73, 
    ICAL_SCOPE_PROPERTY = 74, 
    ICAL_SEQUENCE_PROPERTY = 75, 
    ICAL_STATUS_PROPERTY = 76, 
    ICAL_STORESEXPANDED_PROPERTY = 77, 
    ICAL_SUMMARY_PROPERTY = 78, 
    ICAL_TARGET_PROPERTY = 79, 
    ICAL_TRANSP_PROPERTY = 80, 
    ICAL_TRIGGER_PROPERTY = 81, 
    ICAL_TZID_PROPERTY = 82, 
    ICAL_TZIDALIASOF_PROPERTY = 108, 
    ICAL_TZNAME_PROPERTY = 83, 
    ICAL_TZOFFSETFROM_PROPERTY = 84, 
    ICAL_TZOFFSETTO_PROPERTY = 85, 
    ICAL_TZUNTIL_PROPERTY = 109, 
    ICAL_TZURL_PROPERTY = 86, 
    ICAL_UID_PROPERTY = 87, 
    ICAL_URL_PROPERTY = 88, 
    ICAL_VERSION_PROPERTY = 89, 
    ICAL_VOTER_PROPERTY = 107, 
    ICAL_X_PROPERTY = 90, 
    ICAL_XLICCLASS_PROPERTY = 91, 
    ICAL_XLICCLUSTERCOUNT_PROPERTY = 92, 
    ICAL_XLICERROR_PROPERTY = 93, 
    ICAL_XLICMIMECHARSET_PROPERTY = 94, 
    ICAL_XLICMIMECID_PROPERTY = 95, 
    ICAL_XLICMIMECONTENTTYPE_PROPERTY = 96, 
    ICAL_XLICMIMEENCODING_PROPERTY = 97, 
    ICAL_XLICMIMEFILENAME_PROPERTY = 98, 
    ICAL_XLICMIMEOPTINFO_PROPERTY = 99, 
    ICAL_NO_PROPERTY = 100
} icalproperty_kind;


/* ACCEPT-RESPONSE */
icalproperty* icalproperty_new_acceptresponse(const char* v);
void icalproperty_set_acceptresponse(icalproperty* prop, const char* v);
const char* icalproperty_get_acceptresponse(const icalproperty* prop);icalproperty* icalproperty_vanew_acceptresponse(const char* v, ...);

/* ACKNOWLEDGED */
icalproperty* icalproperty_new_acknowledged(struct icaltimetype v);
void icalproperty_set_acknowledged(icalproperty* prop, struct icaltimetype v);
struct icaltimetype icalproperty_get_acknowledged(const icalproperty* prop);icalproperty* icalproperty_vanew_acknowledged(struct icaltimetype v, ...);

/* ACTION */
icalproperty* icalproperty_new_action(enum icalproperty_action v);
void icalproperty_set_action(icalproperty* prop, enum icalproperty_action v);
enum icalproperty_action icalproperty_get_action(const icalproperty* prop);icalproperty* icalproperty_vanew_action(enum icalproperty_action v, ...);

/* ALLOW-CONFLICT */
icalproperty* icalproperty_new_allowconflict(const char* v);
void icalproperty_set_allowconflict(icalproperty* prop, const char* v);
const char* icalproperty_get_allowconflict(const icalproperty* prop);icalproperty* icalproperty_vanew_allowconflict(const char* v, ...);

/* ATTACH */
icalproperty* icalproperty_new_attach(icalattach * v);
void icalproperty_set_attach(icalproperty* prop, icalattach * v);
icalattach * icalproperty_get_attach(const icalproperty* prop);icalproperty* icalproperty_vanew_attach(icalattach * v, ...);

/* ATTENDEE */
icalproperty* icalproperty_new_attendee(const char* v);
void icalproperty_set_attendee(icalproperty* prop, const char* v);
const char* icalproperty_get_attendee(const icalproperty* prop);icalproperty* icalproperty_vanew_attendee(const char* v, ...);

/* BUSYTYPE */
icalproperty* icalproperty_new_busytype(enum icalproperty_busytype v);
void icalproperty_set_busytype(icalproperty* prop, enum icalproperty_busytype v);
enum icalproperty_busytype icalproperty_get_busytype(const icalproperty* prop);icalproperty* icalproperty_vanew_busytype(enum icalproperty_busytype v, ...);

/* CALID */
icalproperty* icalproperty_new_calid(const char* v);
void icalproperty_set_calid(icalproperty* prop, const char* v);
const char* icalproperty_get_calid(const icalproperty* prop);icalproperty* icalproperty_vanew_calid(const char* v, ...);

/* CALMASTER */
icalproperty* icalproperty_new_calmaster(const char* v);
void icalproperty_set_calmaster(icalproperty* prop, const char* v);
const char* icalproperty_get_calmaster(const icalproperty* prop);icalproperty* icalproperty_vanew_calmaster(const char* v, ...);

/* CALSCALE */
icalproperty* icalproperty_new_calscale(const char* v);
void icalproperty_set_calscale(icalproperty* prop, const char* v);
const char* icalproperty_get_calscale(const icalproperty* prop);icalproperty* icalproperty_vanew_calscale(const char* v, ...);

/* CAP-VERSION */
icalproperty* icalproperty_new_capversion(const char* v);
void icalproperty_set_capversion(icalproperty* prop, const char* v);
const char* icalproperty_get_capversion(const icalproperty* prop);icalproperty* icalproperty_vanew_capversion(const char* v, ...);

/* CAR-LEVEL */
icalproperty* icalproperty_new_carlevel(enum icalproperty_carlevel v);
void icalproperty_set_carlevel(icalproperty* prop, enum icalproperty_carlevel v);
enum icalproperty_carlevel icalproperty_get_carlevel(const icalproperty* prop);icalproperty* icalproperty_vanew_carlevel(enum icalproperty_carlevel v, ...);

/* CARID */
icalproperty* icalproperty_new_carid(const char* v);
void icalproperty_set_carid(icalproperty* prop, const char* v);
const char* icalproperty_get_carid(const icalproperty* prop);icalproperty* icalproperty_vanew_carid(const char* v, ...);

/* CATEGORIES */
icalproperty* icalproperty_new_categories(const char* v);
void icalproperty_set_categories(icalproperty* prop, const char* v);
const char* icalproperty_get_categories(const icalproperty* prop);icalproperty* icalproperty_vanew_categories(const char* v, ...);

/* CLASS */
icalproperty* icalproperty_new_class(enum icalproperty_class v);
void icalproperty_set_class(icalproperty* prop, enum icalproperty_class v);
enum icalproperty_class icalproperty_get_class(const icalproperty* prop);icalproperty* icalproperty_vanew_class(enum icalproperty_class v, ...);

/* CMD */
icalproperty* icalproperty_new_cmd(enum icalproperty_cmd v);
void icalproperty_set_cmd(icalproperty* prop, enum icalproperty_cmd v);
enum icalproperty_cmd icalproperty_get_cmd(const icalproperty* prop);icalproperty* icalproperty_vanew_cmd(enum icalproperty_cmd v, ...);

/* COMMENT */
icalproperty* icalproperty_new_comment(const char* v);
void icalproperty_set_comment(icalproperty* prop, const char* v);
const char* icalproperty_get_comment(const icalproperty* prop);icalproperty* icalproperty_vanew_comment(const char* v, ...);

/* COMPLETED */
icalproperty* icalproperty_new_completed(struct icaltimetype v);
void icalproperty_set_completed(icalproperty* prop, struct icaltimetype v);
struct icaltimetype icalproperty_get_completed(const icalproperty* prop);icalproperty* icalproperty_vanew_completed(struct icaltimetype v, ...);

/* COMPONENTS */
icalproperty* icalproperty_new_components(const char* v);
void icalproperty_set_components(icalproperty* prop, const char* v);
const char* icalproperty_get_components(const icalproperty* prop);icalproperty* icalproperty_vanew_components(const char* v, ...);

/* CONTACT */
icalproperty* icalproperty_new_contact(const char* v);
void icalproperty_set_contact(icalproperty* prop, const char* v);
const char* icalproperty_get_contact(const icalproperty* prop);icalproperty* icalproperty_vanew_contact(const char* v, ...);

/* CREATED */
icalproperty* icalproperty_new_created(struct icaltimetype v);
void icalproperty_set_created(icalproperty* prop, struct icaltimetype v);
struct icaltimetype icalproperty_get_created(const icalproperty* prop);icalproperty* icalproperty_vanew_created(struct icaltimetype v, ...);

/* CSID */
icalproperty* icalproperty_new_csid(const char* v);
void icalproperty_set_csid(icalproperty* prop, const char* v);
const char* icalproperty_get_csid(const icalproperty* prop);icalproperty* icalproperty_vanew_csid(const char* v, ...);

/* DATE-MAX */
icalproperty* icalproperty_new_datemax(struct icaltimetype v);
void icalproperty_set_datemax(icalproperty* prop, struct icaltimetype v);
struct icaltimetype icalproperty_get_datemax(const icalproperty* prop);icalproperty* icalproperty_vanew_datemax(struct icaltimetype v, ...);

/* DATE-MIN */
icalproperty* icalproperty_new_datemin(struct icaltimetype v);
void icalproperty_set_datemin(icalproperty* prop, struct icaltimetype v);
struct icaltimetype icalproperty_get_datemin(const icalproperty* prop);icalproperty* icalproperty_vanew_datemin(struct icaltimetype v, ...);

/* DECREED */
icalproperty* icalproperty_new_decreed(const char* v);
void icalproperty_set_decreed(icalproperty* prop, const char* v);
const char* icalproperty_get_decreed(const icalproperty* prop);icalproperty* icalproperty_vanew_decreed(const char* v, ...);

/* DEFAULT-CHARSET */
icalproperty* icalproperty_new_defaultcharset(const char* v);
void icalproperty_set_defaultcharset(icalproperty* prop, const char* v);
const char* icalproperty_get_defaultcharset(const icalproperty* prop);icalproperty* icalproperty_vanew_defaultcharset(const char* v, ...);

/* DEFAULT-LOCALE */
icalproperty* icalproperty_new_defaultlocale(const char* v);
void icalproperty_set_defaultlocale(icalproperty* prop, const char* v);
const char* icalproperty_get_defaultlocale(const icalproperty* prop);icalproperty* icalproperty_vanew_defaultlocale(const char* v, ...);

/* DEFAULT-TZID */
icalproperty* icalproperty_new_defaulttzid(const char* v);
void icalproperty_set_defaulttzid(icalproperty* prop, const char* v);
const char* icalproperty_get_defaulttzid(const icalproperty* prop);icalproperty* icalproperty_vanew_defaulttzid(const char* v, ...);

/* DEFAULT-VCARS */
icalproperty* icalproperty_new_defaultvcars(const char* v);
void icalproperty_set_defaultvcars(icalproperty* prop, const char* v);
const char* icalproperty_get_defaultvcars(const icalproperty* prop);icalproperty* icalproperty_vanew_defaultvcars(const char* v, ...);

/* DENY */
icalproperty* icalproperty_new_deny(const char* v);
void icalproperty_set_deny(icalproperty* prop, const char* v);
const char* icalproperty_get_deny(const icalproperty* prop);icalproperty* icalproperty_vanew_deny(const char* v, ...);

/* DESCRIPTION */
icalproperty* icalproperty_new_description(const char* v);
void icalproperty_set_description(icalproperty* prop, const char* v);
const char* icalproperty_get_description(const icalproperty* prop);icalproperty* icalproperty_vanew_description(const char* v, ...);

/* DTEND */
icalproperty* icalproperty_new_dtend(struct icaltimetype v);
void icalproperty_set_dtend(icalproperty* prop, struct icaltimetype v);
struct icaltimetype icalproperty_get_dtend(const icalproperty* prop);icalproperty* icalproperty_vanew_dtend(struct icaltimetype v, ...);

/* DTSTAMP */
icalproperty* icalproperty_new_dtstamp(struct icaltimetype v);
void icalproperty_set_dtstamp(icalproperty* prop, struct icaltimetype v);
struct icaltimetype icalproperty_get_dtstamp(const icalproperty* prop);icalproperty* icalproperty_vanew_dtstamp(struct icaltimetype v, ...);

/* DTSTART */
icalproperty* icalproperty_new_dtstart(struct icaltimetype v);
void icalproperty_set_dtstart(icalproperty* prop, struct icaltimetype v);
struct icaltimetype icalproperty_get_dtstart(const icalproperty* prop);icalproperty* icalproperty_vanew_dtstart(struct icaltimetype v, ...);

/* DUE */
icalproperty* icalproperty_new_due(struct icaltimetype v);
void icalproperty_set_due(icalproperty* prop, struct icaltimetype v);
struct icaltimetype icalproperty_get_due(const icalproperty* prop);icalproperty* icalproperty_vanew_due(struct icaltimetype v, ...);

/* DURATION */
icalproperty* icalproperty_new_duration(struct icaldurationtype v);
void icalproperty_set_duration(icalproperty* prop, struct icaldurationtype v);
struct icaldurationtype icalproperty_get_duration(const icalproperty* prop);icalproperty* icalproperty_vanew_duration(struct icaldurationtype v, ...);

/* EXDATE */
icalproperty* icalproperty_new_exdate(struct icaltimetype v);
void icalproperty_set_exdate(icalproperty* prop, struct icaltimetype v);
struct icaltimetype icalproperty_get_exdate(const icalproperty* prop);icalproperty* icalproperty_vanew_exdate(struct icaltimetype v, ...);

/* EXPAND */
icalproperty* icalproperty_new_expand(int v);
void icalproperty_set_expand(icalproperty* prop, int v);
int icalproperty_get_expand(const icalproperty* prop);icalproperty* icalproperty_vanew_expand(int v, ...);

/* EXRULE */
icalproperty* icalproperty_new_exrule(struct icalrecurrencetype v);
void icalproperty_set_exrule(icalproperty* prop, struct icalrecurrencetype v);
struct icalrecurrencetype icalproperty_get_exrule(const icalproperty* prop);icalproperty* icalproperty_vanew_exrule(struct icalrecurrencetype v, ...);

/* FREEBUSY */
icalproperty* icalproperty_new_freebusy(struct icalperiodtype v);
void icalproperty_set_freebusy(icalproperty* prop, struct icalperiodtype v);
struct icalperiodtype icalproperty_get_freebusy(const icalproperty* prop);icalproperty* icalproperty_vanew_freebusy(struct icalperiodtype v, ...);

/* GEO */
icalproperty* icalproperty_new_geo(struct icalgeotype v);
void icalproperty_set_geo(icalproperty* prop, struct icalgeotype v);
struct icalgeotype icalproperty_get_geo(const icalproperty* prop);icalproperty* icalproperty_vanew_geo(struct icalgeotype v, ...);

/* GRANT */
icalproperty* icalproperty_new_grant(const char* v);
void icalproperty_set_grant(icalproperty* prop, const char* v);
const char* icalproperty_get_grant(const icalproperty* prop);icalproperty* icalproperty_vanew_grant(const char* v, ...);

/* ITIP-VERSION */
icalproperty* icalproperty_new_itipversion(const char* v);
void icalproperty_set_itipversion(icalproperty* prop, const char* v);
const char* icalproperty_get_itipversion(const icalproperty* prop);icalproperty* icalproperty_vanew_itipversion(const char* v, ...);

/* LAST-MODIFIED */
icalproperty* icalproperty_new_lastmodified(struct icaltimetype v);
void icalproperty_set_lastmodified(icalproperty* prop, struct icaltimetype v);
struct icaltimetype icalproperty_get_lastmodified(const icalproperty* prop);icalproperty* icalproperty_vanew_lastmodified(struct icaltimetype v, ...);

/* LOCATION */
icalproperty* icalproperty_new_location(const char* v);
void icalproperty_set_location(icalproperty* prop, const char* v);
const char* icalproperty_get_location(const icalproperty* prop);icalproperty* icalproperty_vanew_location(const char* v, ...);

/* MAX-COMPONENT-SIZE */
icalproperty* icalproperty_new_maxcomponentsize(int v);
void icalproperty_set_maxcomponentsize(icalproperty* prop, int v);
int icalproperty_get_maxcomponentsize(const icalproperty* prop);icalproperty* icalproperty_vanew_maxcomponentsize(int v, ...);

/* MAXDATE */
icalproperty* icalproperty_new_maxdate(struct icaltimetype v);
void icalproperty_set_maxdate(icalproperty* prop, struct icaltimetype v);
struct icaltimetype icalproperty_get_maxdate(const icalproperty* prop);icalproperty* icalproperty_vanew_maxdate(struct icaltimetype v, ...);

/* MAXRESULTS */
icalproperty* icalproperty_new_maxresults(int v);
void icalproperty_set_maxresults(icalproperty* prop, int v);
int icalproperty_get_maxresults(const icalproperty* prop);icalproperty* icalproperty_vanew_maxresults(int v, ...);

/* MAXRESULTSSIZE */
icalproperty* icalproperty_new_maxresultssize(int v);
void icalproperty_set_maxresultssize(icalproperty* prop, int v);
int icalproperty_get_maxresultssize(const icalproperty* prop);icalproperty* icalproperty_vanew_maxresultssize(int v, ...);

/* METHOD */
icalproperty* icalproperty_new_method(enum icalproperty_method v);
void icalproperty_set_method(icalproperty* prop, enum icalproperty_method v);
enum icalproperty_method icalproperty_get_method(const icalproperty* prop);icalproperty* icalproperty_vanew_method(enum icalproperty_method v, ...);

/* MINDATE */
icalproperty* icalproperty_new_mindate(struct icaltimetype v);
void icalproperty_set_mindate(icalproperty* prop, struct icaltimetype v);
struct icaltimetype icalproperty_get_mindate(const icalproperty* prop);icalproperty* icalproperty_vanew_mindate(struct icaltimetype v, ...);

/* MULTIPART */
icalproperty* icalproperty_new_multipart(const char* v);
void icalproperty_set_multipart(icalproperty* prop, const char* v);
const char* icalproperty_get_multipart(const icalproperty* prop);icalproperty* icalproperty_vanew_multipart(const char* v, ...);

/* NAME */
icalproperty* icalproperty_new_name(const char* v);
void icalproperty_set_name(icalproperty* prop, const char* v);
const char* icalproperty_get_name(const icalproperty* prop);icalproperty* icalproperty_vanew_name(const char* v, ...);

/* ORGANIZER */
icalproperty* icalproperty_new_organizer(const char* v);
void icalproperty_set_organizer(icalproperty* prop, const char* v);
const char* icalproperty_get_organizer(const icalproperty* prop);icalproperty* icalproperty_vanew_organizer(const char* v, ...);

/* OWNER */
icalproperty* icalproperty_new_owner(const char* v);
void icalproperty_set_owner(icalproperty* prop, const char* v);
const char* icalproperty_get_owner(const icalproperty* prop);icalproperty* icalproperty_vanew_owner(const char* v, ...);

/* PERCENT-COMPLETE */
icalproperty* icalproperty_new_percentcomplete(int v);
void icalproperty_set_percentcomplete(icalproperty* prop, int v);
int icalproperty_get_percentcomplete(const icalproperty* prop);icalproperty* icalproperty_vanew_percentcomplete(int v, ...);

/* PERMISSION */
icalproperty* icalproperty_new_permission(const char* v);
void icalproperty_set_permission(icalproperty* prop, const char* v);
const char* icalproperty_get_permission(const icalproperty* prop);icalproperty* icalproperty_vanew_permission(const char* v, ...);

/* POLL-ITEM-ID */
icalproperty* icalproperty_new_pollitemid(int v);
void icalproperty_set_pollitemid(icalproperty* prop, int v);
int icalproperty_get_pollitemid(const icalproperty* prop);icalproperty* icalproperty_vanew_pollitemid(int v, ...);

/* POLL-MODE */
icalproperty* icalproperty_new_pollmode(enum icalproperty_pollmode v);
void icalproperty_set_pollmode(icalproperty* prop, enum icalproperty_pollmode v);
enum icalproperty_pollmode icalproperty_get_pollmode(const icalproperty* prop);icalproperty* icalproperty_vanew_pollmode(enum icalproperty_pollmode v, ...);

/* POLL-PROPERTIES */
icalproperty* icalproperty_new_pollproperties(const char* v);
void icalproperty_set_pollproperties(icalproperty* prop, const char* v);
const char* icalproperty_get_pollproperties(const icalproperty* prop);icalproperty* icalproperty_vanew_pollproperties(const char* v, ...);

/* POLL-WINNER */
icalproperty* icalproperty_new_pollwinner(int v);
void icalproperty_set_pollwinner(icalproperty* prop, int v);
int icalproperty_get_pollwinner(const icalproperty* prop);icalproperty* icalproperty_vanew_pollwinner(int v, ...);

/* PRIORITY */
icalproperty* icalproperty_new_priority(int v);
void icalproperty_set_priority(icalproperty* prop, int v);
int icalproperty_get_priority(const icalproperty* prop);icalproperty* icalproperty_vanew_priority(int v, ...);

/* PRODID */
icalproperty* icalproperty_new_prodid(const char* v);
void icalproperty_set_prodid(icalproperty* prop, const char* v);
const char* icalproperty_get_prodid(const icalproperty* prop);icalproperty* icalproperty_vanew_prodid(const char* v, ...);

/* QUERY */
icalproperty* icalproperty_new_query(const char* v);
void icalproperty_set_query(icalproperty* prop, const char* v);
const char* icalproperty_get_query(const icalproperty* prop);icalproperty* icalproperty_vanew_query(const char* v, ...);

/* QUERY-LEVEL */
icalproperty* icalproperty_new_querylevel(enum icalproperty_querylevel v);
void icalproperty_set_querylevel(icalproperty* prop, enum icalproperty_querylevel v);
enum icalproperty_querylevel icalproperty_get_querylevel(const icalproperty* prop);icalproperty* icalproperty_vanew_querylevel(enum icalproperty_querylevel v, ...);

/* QUERYID */
icalproperty* icalproperty_new_queryid(const char* v);
void icalproperty_set_queryid(icalproperty* prop, const char* v);
const char* icalproperty_get_queryid(const icalproperty* prop);icalproperty* icalproperty_vanew_queryid(const char* v, ...);

/* QUERYNAME */
icalproperty* icalproperty_new_queryname(const char* v);
void icalproperty_set_queryname(icalproperty* prop, const char* v);
const char* icalproperty_get_queryname(const icalproperty* prop);icalproperty* icalproperty_vanew_queryname(const char* v, ...);

/* RDATE */
icalproperty* icalproperty_new_rdate(struct icaldatetimeperiodtype v);
void icalproperty_set_rdate(icalproperty* prop, struct icaldatetimeperiodtype v);
struct icaldatetimeperiodtype icalproperty_get_rdate(const icalproperty* prop);icalproperty* icalproperty_vanew_rdate(struct icaldatetimeperiodtype v, ...);

/* RECUR-ACCEPTED */
icalproperty* icalproperty_new_recuraccepted(const char* v);
void icalproperty_set_recuraccepted(icalproperty* prop, const char* v);
const char* icalproperty_get_recuraccepted(const icalproperty* prop);icalproperty* icalproperty_vanew_recuraccepted(const char* v, ...);

/* RECUR-EXPAND */
icalproperty* icalproperty_new_recurexpand(const char* v);
void icalproperty_set_recurexpand(icalproperty* prop, const char* v);
const char* icalproperty_get_recurexpand(const icalproperty* prop);icalproperty* icalproperty_vanew_recurexpand(const char* v, ...);

/* RECUR-LIMIT */
icalproperty* icalproperty_new_recurlimit(const char* v);
void icalproperty_set_recurlimit(icalproperty* prop, const char* v);
const char* icalproperty_get_recurlimit(const icalproperty* prop);icalproperty* icalproperty_vanew_recurlimit(const char* v, ...);

/* RECURRENCE-ID */
icalproperty* icalproperty_new_recurrenceid(struct icaltimetype v);
void icalproperty_set_recurrenceid(icalproperty* prop, struct icaltimetype v);
struct icaltimetype icalproperty_get_recurrenceid(const icalproperty* prop);icalproperty* icalproperty_vanew_recurrenceid(struct icaltimetype v, ...);

/* RELATED-TO */
icalproperty* icalproperty_new_relatedto(const char* v);
void icalproperty_set_relatedto(icalproperty* prop, const char* v);
const char* icalproperty_get_relatedto(const icalproperty* prop);icalproperty* icalproperty_vanew_relatedto(const char* v, ...);

/* RELCALID */
icalproperty* icalproperty_new_relcalid(const char* v);
void icalproperty_set_relcalid(icalproperty* prop, const char* v);
const char* icalproperty_get_relcalid(const icalproperty* prop);icalproperty* icalproperty_vanew_relcalid(const char* v, ...);

/* REPEAT */
icalproperty* icalproperty_new_repeat(int v);
void icalproperty_set_repeat(icalproperty* prop, int v);
int icalproperty_get_repeat(const icalproperty* prop);icalproperty* icalproperty_vanew_repeat(int v, ...);

/* REQUEST-STATUS */
icalproperty* icalproperty_new_requeststatus(struct icalreqstattype v);
void icalproperty_set_requeststatus(icalproperty* prop, struct icalreqstattype v);
struct icalreqstattype icalproperty_get_requeststatus(const icalproperty* prop);icalproperty* icalproperty_vanew_requeststatus(struct icalreqstattype v, ...);

/* RESOURCES */
icalproperty* icalproperty_new_resources(const char* v);
void icalproperty_set_resources(icalproperty* prop, const char* v);
const char* icalproperty_get_resources(const icalproperty* prop);icalproperty* icalproperty_vanew_resources(const char* v, ...);

/* RESTRICTION */
icalproperty* icalproperty_new_restriction(const char* v);
void icalproperty_set_restriction(icalproperty* prop, const char* v);
const char* icalproperty_get_restriction(const icalproperty* prop);icalproperty* icalproperty_vanew_restriction(const char* v, ...);

/* RRULE */
icalproperty* icalproperty_new_rrule(struct icalrecurrencetype v);
void icalproperty_set_rrule(icalproperty* prop, struct icalrecurrencetype v);
struct icalrecurrencetype icalproperty_get_rrule(const icalproperty* prop);icalproperty* icalproperty_vanew_rrule(struct icalrecurrencetype v, ...);

/* SCOPE */
icalproperty* icalproperty_new_scope(const char* v);
void icalproperty_set_scope(icalproperty* prop, const char* v);
const char* icalproperty_get_scope(const icalproperty* prop);icalproperty* icalproperty_vanew_scope(const char* v, ...);

/* SEQUENCE */
icalproperty* icalproperty_new_sequence(int v);
void icalproperty_set_sequence(icalproperty* prop, int v);
int icalproperty_get_sequence(const icalproperty* prop);icalproperty* icalproperty_vanew_sequence(int v, ...);

/* STATUS */
icalproperty* icalproperty_new_status(enum icalproperty_status v);
void icalproperty_set_status(icalproperty* prop, enum icalproperty_status v);
enum icalproperty_status icalproperty_get_status(const icalproperty* prop);icalproperty* icalproperty_vanew_status(enum icalproperty_status v, ...);

/* STORES-EXPANDED */
icalproperty* icalproperty_new_storesexpanded(const char* v);
void icalproperty_set_storesexpanded(icalproperty* prop, const char* v);
const char* icalproperty_get_storesexpanded(const icalproperty* prop);icalproperty* icalproperty_vanew_storesexpanded(const char* v, ...);

/* SUMMARY */
icalproperty* icalproperty_new_summary(const char* v);
void icalproperty_set_summary(icalproperty* prop, const char* v);
const char* icalproperty_get_summary(const icalproperty* prop);icalproperty* icalproperty_vanew_summary(const char* v, ...);

/* TARGET */
icalproperty* icalproperty_new_target(const char* v);
void icalproperty_set_target(icalproperty* prop, const char* v);
const char* icalproperty_get_target(const icalproperty* prop);icalproperty* icalproperty_vanew_target(const char* v, ...);

/* TRANSP */
icalproperty* icalproperty_new_transp(enum icalproperty_transp v);
void icalproperty_set_transp(icalproperty* prop, enum icalproperty_transp v);
enum icalproperty_transp icalproperty_get_transp(const icalproperty* prop);icalproperty* icalproperty_vanew_transp(enum icalproperty_transp v, ...);

/* TRIGGER */
icalproperty* icalproperty_new_trigger(struct icaltriggertype v);
void icalproperty_set_trigger(icalproperty* prop, struct icaltriggertype v);
struct icaltriggertype icalproperty_get_trigger(const icalproperty* prop);icalproperty* icalproperty_vanew_trigger(struct icaltriggertype v, ...);

/* TZID */
icalproperty* icalproperty_new_tzid(const char* v);
void icalproperty_set_tzid(icalproperty* prop, const char* v);
const char* icalproperty_get_tzid(const icalproperty* prop);icalproperty* icalproperty_vanew_tzid(const char* v, ...);

/* TZID-ALIAS-OF */
icalproperty* icalproperty_new_tzidaliasof(const char* v);
void icalproperty_set_tzidaliasof(icalproperty* prop, const char* v);
const char* icalproperty_get_tzidaliasof(const icalproperty* prop);icalproperty* icalproperty_vanew_tzidaliasof(const char* v, ...);

/* TZNAME */
icalproperty* icalproperty_new_tzname(const char* v);
void icalproperty_set_tzname(icalproperty* prop, const char* v);
const char* icalproperty_get_tzname(const icalproperty* prop);icalproperty* icalproperty_vanew_tzname(const char* v, ...);

/* TZOFFSETFROM */
icalproperty* icalproperty_new_tzoffsetfrom(int v);
void icalproperty_set_tzoffsetfrom(icalproperty* prop, int v);
int icalproperty_get_tzoffsetfrom(const icalproperty* prop);icalproperty* icalproperty_vanew_tzoffsetfrom(int v, ...);

/* TZOFFSETTO */
icalproperty* icalproperty_new_tzoffsetto(int v);
void icalproperty_set_tzoffsetto(icalproperty* prop, int v);
int icalproperty_get_tzoffsetto(const icalproperty* prop);icalproperty* icalproperty_vanew_tzoffsetto(int v, ...);

/* TZUNTIL */
icalproperty* icalproperty_new_tzuntil(struct icaltimetype v);
void icalproperty_set_tzuntil(icalproperty* prop, struct icaltimetype v);
struct icaltimetype icalproperty_get_tzuntil(const icalproperty* prop);icalproperty* icalproperty_vanew_tzuntil(struct icaltimetype v, ...);

/* TZURL */
icalproperty* icalproperty_new_tzurl(const char* v);
void icalproperty_set_tzurl(icalproperty* prop, const char* v);
const char* icalproperty_get_tzurl(const icalproperty* prop);icalproperty* icalproperty_vanew_tzurl(const char* v, ...);

/* UID */
icalproperty* icalproperty_new_uid(const char* v);
void icalproperty_set_uid(icalproperty* prop, const char* v);
const char* icalproperty_get_uid(const icalproperty* prop);icalproperty* icalproperty_vanew_uid(const char* v, ...);

/* URL */
icalproperty* icalproperty_new_url(const char* v);
void icalproperty_set_url(icalproperty* prop, const char* v);
const char* icalproperty_get_url(const icalproperty* prop);icalproperty* icalproperty_vanew_url(const char* v, ...);

/* VERSION */
icalproperty* icalproperty_new_version(const char* v);
void icalproperty_set_version(icalproperty* prop, const char* v);
const char* icalproperty_get_version(const icalproperty* prop);icalproperty* icalproperty_vanew_version(const char* v, ...);

/* VOTER */
icalproperty* icalproperty_new_voter(const char* v);
void icalproperty_set_voter(icalproperty* prop, const char* v);
const char* icalproperty_get_voter(const icalproperty* prop);icalproperty* icalproperty_vanew_voter(const char* v, ...);

/* X */
icalproperty* icalproperty_new_x(const char* v);
void icalproperty_set_x(icalproperty* prop, const char* v);
const char* icalproperty_get_x(const icalproperty* prop);icalproperty* icalproperty_vanew_x(const char* v, ...);

/* X-LIC-CLASS */
icalproperty* icalproperty_new_xlicclass(enum icalproperty_xlicclass v);
void icalproperty_set_xlicclass(icalproperty* prop, enum icalproperty_xlicclass v);
enum icalproperty_xlicclass icalproperty_get_xlicclass(const icalproperty* prop);icalproperty* icalproperty_vanew_xlicclass(enum icalproperty_xlicclass v, ...);

/* X-LIC-CLUSTERCOUNT */
icalproperty* icalproperty_new_xlicclustercount(const char* v);
void icalproperty_set_xlicclustercount(icalproperty* prop, const char* v);
const char* icalproperty_get_xlicclustercount(const icalproperty* prop);icalproperty* icalproperty_vanew_xlicclustercount(const char* v, ...);

/* X-LIC-ERROR */
icalproperty* icalproperty_new_xlicerror(const char* v);
void icalproperty_set_xlicerror(icalproperty* prop, const char* v);
const char* icalproperty_get_xlicerror(const icalproperty* prop);icalproperty* icalproperty_vanew_xlicerror(const char* v, ...);

/* X-LIC-MIMECHARSET */
icalproperty* icalproperty_new_xlicmimecharset(const char* v);
void icalproperty_set_xlicmimecharset(icalproperty* prop, const char* v);
const char* icalproperty_get_xlicmimecharset(const icalproperty* prop);icalproperty* icalproperty_vanew_xlicmimecharset(const char* v, ...);

/* X-LIC-MIMECID */
icalproperty* icalproperty_new_xlicmimecid(const char* v);
void icalproperty_set_xlicmimecid(icalproperty* prop, const char* v);
const char* icalproperty_get_xlicmimecid(const icalproperty* prop);icalproperty* icalproperty_vanew_xlicmimecid(const char* v, ...);

/* X-LIC-MIMECONTENTTYPE */
icalproperty* icalproperty_new_xlicmimecontenttype(const char* v);
void icalproperty_set_xlicmimecontenttype(icalproperty* prop, const char* v);
const char* icalproperty_get_xlicmimecontenttype(const icalproperty* prop);icalproperty* icalproperty_vanew_xlicmimecontenttype(const char* v, ...);

/* X-LIC-MIMEENCODING */
icalproperty* icalproperty_new_xlicmimeencoding(const char* v);
void icalproperty_set_xlicmimeencoding(icalproperty* prop, const char* v);
const char* icalproperty_get_xlicmimeencoding(const icalproperty* prop);icalproperty* icalproperty_vanew_xlicmimeencoding(const char* v, ...);

/* X-LIC-MIMEFILENAME */
icalproperty* icalproperty_new_xlicmimefilename(const char* v);
void icalproperty_set_xlicmimefilename(icalproperty* prop, const char* v);
const char* icalproperty_get_xlicmimefilename(const icalproperty* prop);icalproperty* icalproperty_vanew_xlicmimefilename(const char* v, ...);

/* X-LIC-MIMEOPTINFO */
icalproperty* icalproperty_new_xlicmimeoptinfo(const char* v);
void icalproperty_set_xlicmimeoptinfo(icalproperty* prop, const char* v);
const char* icalproperty_get_xlicmimeoptinfo(const icalproperty* prop);icalproperty* icalproperty_vanew_xlicmimeoptinfo(const char* v, ...);


#endif /*ICALPROPERTY_H*/
