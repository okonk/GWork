
To add the unit test in your engine you need to compile it, include the lib, include the header:

	#include "Gwork/Test/Test.h"

then the unit test is simply a control that you create like any other

	UnitTest* pUnit = new UnitTest( pCanvas );