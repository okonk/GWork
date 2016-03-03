/*
 *  Gwork
 *  Copyright (c) 2010 Facepunch Studios
 *  Copyright (c) 2013-16 Billy Quith
 *  See license in Gwork.h
 */


#include <Gwork/Controls/ImagePanel.h>
#include <Gwork/Controls/Label.h>
#include <Gwork/Controls/ResizableControl.h>

using namespace Gwk;
using namespace Gwk::Controls;
using namespace Gwk::ControlsInternal;

GWK_CONTROL_CONSTRUCTOR(ResizableControl)
{
    m_bResizable = true;
    m_minimumSize = Gwk::Point(5, 5);
    m_bClampMovement = false;
    m_resizer[5] = NULL;
    m_resizer[0] = NULL;
    m_resizer[2] = new Resizer(this);
    m_resizer[2]->Dock(Docking::Bottom);
    m_resizer[2]->SetResizeDir(Docking::Bottom);
    m_resizer[2]->SetTarget(this);
    m_resizer[2]->onResize.Add(this, &ResizableControl::OnResizedInternal);
    m_resizer[1] = new Resizer(m_resizer[2]);
    m_resizer[1]->Dock(Docking::Left);
    m_resizer[1]->SetResizeDir(Docking::Bottom|Docking::Left);
    m_resizer[1]->SetTarget(this);
    m_resizer[1]->onResize.Add(this, &ResizableControl::OnResizedInternal);
    m_resizer[3] = new Resizer(m_resizer[2]);
    m_resizer[3]->Dock(Docking::Right);
    m_resizer[3]->SetResizeDir(Docking::Bottom|Docking::Right);
    m_resizer[3]->SetTarget(this);
    m_resizer[3]->onResize.Add(this, &ResizableControl::OnResizedInternal);
    m_resizer[8] = new Resizer(this);
    m_resizer[8]->Dock(Docking::Top);
    m_resizer[8]->SetResizeDir(Docking::Top);
    m_resizer[8]->SetTarget(this);
    m_resizer[8]->onResize.Add(this, &ResizableControl::OnResizedInternal);
    m_resizer[7] = new Resizer(m_resizer[8]);
    m_resizer[7]->Dock(Docking::Left);
    m_resizer[7]->SetResizeDir(Docking::Top|Docking::Left);
    m_resizer[7]->SetTarget(this);
    m_resizer[7]->onResize.Add(this, &ResizableControl::OnResizedInternal);
    m_resizer[9] = new Resizer(m_resizer[8]);
    m_resizer[9]->Dock(Docking::Right);
    m_resizer[9]->SetResizeDir(Docking::Top|Docking::Right);
    m_resizer[9]->SetTarget(this);
    m_resizer[9]->onResize.Add(this, &ResizableControl::OnResizedInternal);
    m_resizer[4] = new Resizer(this);
    m_resizer[4]->Dock(Docking::Left);
    m_resizer[4]->SetResizeDir(Docking::Left);
    m_resizer[4]->SetTarget(this);
    m_resizer[4]->onResize.Add(this, &ResizableControl::OnResizedInternal);
    m_resizer[6] = new Resizer(this);
    m_resizer[6]->Dock(Docking::Right);
    m_resizer[6]->SetResizeDir(Docking::Right);
    m_resizer[6]->SetTarget(this);
    m_resizer[6]->onResize.Add(this, &ResizableControl::OnResizedInternal);
}

void ResizableControl::DisableResizing()
{
    for (Base::List::iterator it = Children.begin(); it != Children.end(); ++it)
    {
        Resizer* resizer = gwk_cast<Resizer>(*it);

        if (!resizer)
            continue;

        resizer->SetMouseInputEnabled(false);
        resizer->SetHidden(false);
        SetPadding(Padding(resizer->Width(), resizer->Width(), resizer->Width(),
                           resizer->Width()));
    }
}

bool ResizableControl::SetBounds(int x, int y, int w, int h)
{
    Gwk::Point minSize = GetMinimumSize();

    // Clamp Minimum Size
    w = Max(w, minSize.x);
    h = Max(h, minSize.y);

    // Clamp to parent's window
    Base* parent = GetParent();

    if (parent && m_bClampMovement)
    {
        if (x+w > parent->Width())
            x = parent->Width()-w;

        if (x < 0)
            x = 0;

        if (y+h > parent->Height())
            y = parent->Height()-h;

        if (y < 0)
            y = 0;
    }

    return ParentClass::SetBounds(x, y, w, h);
}

void ResizableControl::OnResizedInternal(Controls::Base* /*control*/)
{
    onResize.Call(this);
    OnResized();
}