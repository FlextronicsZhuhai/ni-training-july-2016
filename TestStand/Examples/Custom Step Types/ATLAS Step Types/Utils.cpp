#include "stdafx.h"
#include "Utils.h"

CString GetResourceString (
    const TS::IEnginePtr& engine, 
    LPCTSTR category, 
    LPCTSTR symbol)
    {
    _variant_t defaultString = _T("RESOURCE_STRING_NOT_FOUND");
    _variant_t foundVar;
    return (LPCTSTR) engine->GetResourceString(category, symbol, defaultString, &foundVar);
    }

void CalculateTextSize(CWnd &control, CString &text, CSize &size)
    {
    CFont *savedFont;
    BOOL result;

    // Then get the device context and select the right font for it.
    CDC *deviceContext = control.GetDC();
    savedFont = deviceContext->SelectObject(control.GetFont());

    // Use the device context to calculate the size of the text.
    result = ::GetTextExtentPoint32(deviceContext->m_hAttribDC, text, text.GetLength(), &size);

    // Release the device context.
    (void) deviceContext->SelectObject(savedFont);
    control.ReleaseDC(deviceContext);
    }

// inorder for this to work the checkbox must already be sized as small as possible
// so that just the checkbox is showing.
void SizeCheckBoxToContent(CButton &checkBox)
    {
    CSize textSize, checkSize, spaceSize, size;
    CString text;
    RECT            rect1;

    // First get the text from the check box.
    checkBox.GetWindowText(text);

    // calculate checkbox size
    checkBox.GetClientRect(&rect1);
    checkSize.cx = rect1.right + 1;
    checkSize.cy = rect1.bottom + 1;

    // calculate text size
    CalculateTextSize(checkBox, text, textSize);
    CalculateTextSize(checkBox, CString("  "), spaceSize);

    // Calculate total size.
    size.cx = spaceSize.cx + checkSize.cx + textSize.cx;
    size.cy = checkSize.cy < textSize.cy ? textSize.cy : checkSize.cy;

    // Set the width and height only.
    checkBox.SetWindowPos(NULL, 0, 0, size.cx, size.cy, 
        SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER);

    // Must set the text after resizing to avoid some refresh problem.
    checkBox.SetWindowText(text);
    }

