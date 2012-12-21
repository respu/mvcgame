/*
 *  UnitTests.cp
 *  UnitTests
 *
 *  Created by Miguel Ibero on 21/12/12.
 *  Copyright (c) 2012 Social Point. All rights reserved.
 *
 */

#include "UnitTests.h"
#include "UnitTestsPriv.h"

CFStringRef UnitTestsUUID(void)
{
	CUnitTests* theObj = new CUnitTests;
	return theObj->UUID();
}

CFStringRef CUnitTests::UUID()
{
	return CFSTR("0001020304050607");
}
