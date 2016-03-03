/*
 *  Gwork
 *  Copyright (c) 2010 Facepunch Studios
 *  Copyright (c) 2013-16 Billy Quith
 *  See license in Gwork.h
 */

#include <Gwork/Test/Test.h>
#include <Gwork/Controls/NumericUpDown.h>

using namespace Gwk;

class Numeric : public GUnit
{
public:

    GWK_CONTROL_INLINE(Numeric, GUnit)
    {
        Controls::NumericUpDown* ctrl = new Controls::NumericUpDown(this);
        ctrl->SetBounds(10, 10, 50, 20);
        ctrl->SetIntValue(50);
        ctrl->SetMax(1000);
        ctrl->SetMin(-1000);
        //	ctrl->onPress.Add( this, &ThisClass::onButtonA );
    }

    void onButtonA(Controls::Base* control)
    {
        //	UnitPrint( "Button Pressed (using 'OnPress' event)" );
    }

};


DEFINE_UNIT_TEST(Numeric);