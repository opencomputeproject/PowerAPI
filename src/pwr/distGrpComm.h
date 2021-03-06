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

#ifndef _DIST_GRP_COMM_H
#define _DIST_GRP_COMM_H

//#include <vector>
#include "distComm.h"

namespace PowerAPI {

class DistObject;

class DistGrpComm : public DistComm {

  public:

	DistGrpComm( DistCntxt*, std::vector<DistObject*>& objs );
	~DistGrpComm() {}

  private:
};

}

#endif
