/*
 * OurOrgan - free pipe organ simulator based on MyOrgan
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#pragma once

class OrganView : public wxView
{
	DECLARE_DYNAMIC_CLASS(OrganView)
public:
    bool OnCreate(wxDocument *doc, long flags);
	void OnErase(wxEraseEvent& event);
	void OnPaint(wxPaintEvent& event);
	void OnDraw(wxDC *dc);
	void OnDrawstop(wxCommandEvent& event);
	void OnNoteOnOff(wxCommandEvent& event);
    void OnUpdate(wxView *sender, wxObject *hint = (wxObject *) NULL);
	void OnMouseLeftDown(wxMouseEvent& event);
	void OnMouseRightDown(wxMouseEvent& event);
	void OnMouseScroll(wxMouseEvent& event);
    bool OnClose(bool deleteWindow = true);

	DECLARE_EVENT_TABLE()

private:
	wxBitmap m_clientBitmap;
	wxPoint m_clientOrigin;
	wxBrush m_pedalBrush;

	void DrawClickables(wxDC* dc = NULL, int xx = 0, int yy = 0, bool right = false, int scroll = 0);

	void DrawKey(wxDC& dc, int man, int k, bool usepen = true, wxRegion* region = 0);
	void WrapText(wxDC& dc, wxString& ptr, int width);
};
