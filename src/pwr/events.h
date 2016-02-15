/* 
 * Copyright 2014-2016 Sandia Corporation. Under the terms of Contract
 * DE-AC04-94AL85000, there is a non-exclusive license for use of this work 
 * by or on behalf of the U.S. Government. Export of this program may require
 * a license from the United States Government.
 *
 * This file is part of the Power API Prototype software package. For license
 * information, see the LICENSE file in the top level directory of the
 * distribution.
*/

#ifndef _EVENTS_H
#define _EVENTS_H

#include <vector>
#include <string>
#include "pwrtypes.h"
#include "impTypes.h"
#include "event.h"

typedef std::string ObjID;
typedef uint64_t CommID;

struct ServerConnectEvent : public Event {
	ServerConnectEvent() : Event( ServerConnect ) {} 
	ServerConnectEvent( SerialBuf& buf ) {
		serialize_in(buf);
	}

	ObjID name; 
	virtual void serialize_out( SerialBuf& buf ) {
		Event::serialize_out(buf);
		buf << name;
	}

	virtual void serialize_in( SerialBuf& buf ) {
		buf >> name;
		Event::serialize_in(buf);
	}
};

struct CommEvent : public Event {
	CommEvent( EventType type ) : Event( type ) {}
	CommEvent() { } 

    CommID          commID;

	enum OpType { Get, Set, Start, Stop, Clear } op;

	virtual void serialize_out( SerialBuf& buf ) {
		Event::serialize_out(buf);
		buf << commID;
		buf << op;
	}

	virtual void serialize_in( SerialBuf& buf ) {
		buf >> op;
		buf >> commID;
		Event::serialize_in(buf);
	}
};

struct CommCreateEvent : public CommEvent {
	CommCreateEvent( ) : CommEvent( CommCreate )  {}
	CommCreateEvent( SerialBuf& buf ) {
		serialize_in(buf);
	}

	CommCreateEvent(const CommCreateEvent& x) : members(x.members) {}

    std::vector<ObjID> members;

	virtual void serialize_in( SerialBuf& buf ) {
		buf >> members;
		CommEvent::serialize_in(buf);
	} 

	virtual void serialize_out( SerialBuf& buf ) {
		CommEvent::serialize_out(buf);
		buf << members;
	} 
};

struct CommDestroyEvent : public CommEvent {
	CommDestroyEvent( ) : CommEvent( CommDestroy )  {}
	CommDestroyEvent( SerialBuf& buf ) {
		serialize_in(buf);
	}

	virtual void serialize_in( SerialBuf& buf ) {
		CommEvent::serialize_in(buf);
	} 

	virtual void serialize_out( SerialBuf& buf ) {
		CommEvent::serialize_out(buf);
	} 
};

struct CommReqEvent : public CommEvent {
	CommReqEvent( ) : CommEvent( CommReq )  { }
	CommReqEvent( SerialBuf& buf ) {
		serialize_in(buf);
	}

    std::vector<PWR_AttrName> attrName;
    std::vector<uint64_t> values;
	std::vector<ValueOp> valueOp;

	virtual void serialize_in( SerialBuf& buf ) {
		buf >> valueOp;
		buf >> attrName;
		buf >> values;
		CommEvent::serialize_in(buf);
	} 
	virtual void serialize_out( SerialBuf& buf ) {
		CommEvent::serialize_out(buf);
		buf << values;
		buf << attrName;
		buf << valueOp;
	} 
};

struct CommRespEvent : public CommEvent {
	CommRespEvent( ) : CommEvent( CommResp )  { }
	CommRespEvent( SerialBuf& buf ) {
		serialize_in(buf);
	}

    std::vector<PWR_Time> timeStamp;
    std::vector<uint64_t> value;

	virtual void serialize_in( SerialBuf& buf ) {
		buf >> value;
		buf >> timeStamp;
		CommEvent::serialize_in(buf);
	} 
	virtual void serialize_out( SerialBuf& buf ) {
		CommEvent::serialize_out(buf);
		buf << timeStamp;
		buf << value;
	} 
};

struct CommLogReqEvent : public CommEvent {
	CommLogReqEvent( ) : CommEvent( CommLogReq )  { }
	CommLogReqEvent( SerialBuf& buf ) {
		serialize_in(buf);
	}
    PWR_AttrName attrName;

	virtual void serialize_in( SerialBuf& buf ) {
		buf >> attrName;
		CommEvent::serialize_in(buf);
	} 
	virtual void serialize_out( SerialBuf& buf ) {
		CommEvent::serialize_out(buf);
		buf << attrName;
	} 
};

struct CommLogRespEvent : public CommEvent {
	CommLogRespEvent( ) : CommEvent( CommLogResp )  { }
	CommLogRespEvent( SerialBuf& buf ) {
		serialize_in(buf);
	}

	virtual void serialize_in( SerialBuf& buf ) {
		CommEvent::serialize_in(buf);
	} 
	virtual void serialize_out( SerialBuf& buf ) {
		CommEvent::serialize_out(buf);
	} 
};

struct CommGetSamplesReqEvent : public CommEvent {
	CommGetSamplesReqEvent( ) : CommEvent( CommGetSamplesReq )  { }
	CommGetSamplesReqEvent( SerialBuf& buf ) {
		serialize_in(buf);
	}
    PWR_AttrName attrName;
	PWR_Time startTime;
	double period;
	unsigned int count;

	virtual void serialize_in( SerialBuf& buf ) {
		buf >> attrName;
		buf >> startTime;
		buf >> period;
		buf >> count; 
		CommEvent::serialize_in(buf);
	} 
	virtual void serialize_out( SerialBuf& buf ) {
		CommEvent::serialize_out(buf);
		buf << count; 
		buf << period;
		buf << startTime;
		buf << attrName;
	} 
};

struct CommGetSamplesRespEvent : public CommEvent {
	CommGetSamplesRespEvent( ) : CommEvent( CommGetSamplesResp )  { }
	CommGetSamplesRespEvent( SerialBuf& buf ) {
		serialize_in(buf);
	}
	PWR_Time startTime;
	unsigned int count;
	std::vector< uint64_t > data;

	virtual void serialize_in( SerialBuf& buf ) {
		buf >> startTime;
		buf >> count;
		buf >> data;
		CommEvent::serialize_in(buf);
	} 
	virtual void serialize_out( SerialBuf& buf ) {
		CommEvent::serialize_out(buf);
		buf << data;
		buf << count;
		buf << startTime;
	} 
};

#endif

