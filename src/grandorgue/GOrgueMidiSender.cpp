/*
 * GrandOrgue - free pipe organ simulator
 *
 * Copyright 2006 Milan Digital Audio LLC
 * Copyright 2009-2012 GrandOrgue contributors (see AUTHORS)
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "GOrgueMidiSender.h"
#include "GrandOrgueFile.h"
#include "GOrgueConfigReader.h"
#include "GOrgueConfigWriter.h"

GOrgueMidiSender::GOrgueMidiSender(GrandOrgueFile* organfile, MIDI_SENDER_TYPE type) :
	m_organfile(organfile),
	m_type(type),
	m_events()
{
}

GOrgueMidiSender::~GOrgueMidiSender()
{
}

MIDI_SENDER_TYPE GOrgueMidiSender::GetType() const
{
	return m_type;
}

const struct IniFileEnumEntry GOrgueMidiSender::m_MidiTypes[] = {
	{ wxT("Note"), MIDI_S_NOTE },
	{ wxT("ControlChange"), MIDI_S_CTRL },
	{ wxT("ProgramOn"), MIDI_S_PGM_ON },
	{ wxT("ProgramOff"), MIDI_S_PGM_OFF },
	{ wxT("NoteOn"), MIDI_S_NOTE_ON },
	{ wxT("NoteOff"), MIDI_S_NOTE_OFF },
	{ wxT("ControlOn"), MIDI_S_CTRL_ON },
	{ wxT("ControlOff"), MIDI_S_CTRL_OFF },
};

void GOrgueMidiSender::Load(GOrgueConfigReader& cfg, wxString group)
{
	wxString buffer;
	m_events.resize(0);

	int event_cnt = cfg.ReadInteger(CMBSetting, group, wxT("NumberOfMIDISendEvents"), 0, 255, false);

	m_events.resize(event_cnt);
	for(unsigned i = 0; i < m_events.size(); i++)
	{
		buffer.Printf(wxT("MIDISendDevice%03d"), i + 1);
		m_events[i].device = cfg.ReadString(CMBSetting, group, buffer, 100, false);
		buffer.Printf(wxT("MIDISendChannel%03d"), i + 1);
		m_events[i].channel = cfg.ReadInteger(CMBSetting, group, buffer, 1, 16);
		buffer.Printf(wxT("MIDISendEventType%03d"), i + 1);
		m_events[i].type = (midi_send_message_type)cfg.ReadEnum(CMBSetting, group, buffer, m_MidiTypes, sizeof(m_MidiTypes)/sizeof(m_MidiTypes[0]));
		if (m_type != MIDI_SEND_MANUAL)
		{
			buffer.Printf(wxT("MIDISendKey%03d"), i + 1);
			m_events[i].key = cfg.ReadInteger(CMBSetting, group, buffer, 0, 0x200000);
		}
		if (m_events[i].type == MIDI_S_NOTE_ON ||
		    m_events[i].type == MIDI_S_CTRL_ON ||
		    m_events[i].type == MIDI_S_PGM_ON ||
		    m_events[i].type == MIDI_S_NOTE ||
		    m_events[i].type == MIDI_S_CTRL)
		{
			buffer.Printf(wxT("MIDISendLowValue%03d"), i + 1);
			m_events[i].low_value = cfg.ReadInteger(CMBSetting, group, buffer, 0, 0x7f);
		}
		if (m_events[i].type == MIDI_S_NOTE_OFF ||
		    m_events[i].type == MIDI_S_CTRL_OFF ||
		    m_events[i].type == MIDI_S_PGM_OFF ||
		    m_events[i].type == MIDI_S_NOTE ||
		    m_events[i].type == MIDI_S_CTRL)
		{
			buffer.Printf(wxT("MIDISendHighValue%03d"), i + 1);
			m_events[i].high_value = cfg.ReadInteger(CMBSetting, group, buffer, 0, 0x7f);
		}
	}
}

void GOrgueMidiSender::Save(GOrgueConfigWriter& cfg, wxString group)
{
	wxString buffer;

	cfg.Write(group, wxT("NumberOfMIDISendEvents"), (int)m_events.size());
	for(unsigned i = 0; i < m_events.size(); i++)
	{
		buffer.Printf(wxT("MIDISendDevice%03d"), i + 1);
		cfg.Write(group, buffer, m_events[i].device);
		buffer.Printf(wxT("MIDISendChannel%03d"), i + 1);
		cfg.Write(group, buffer, (int)m_events[i].channel);
		buffer.Printf(wxT("MIDISendEventType%03d"), i + 1);
		cfg.Write(group, buffer, m_events[i].type, m_MidiTypes, sizeof(m_MidiTypes)/sizeof(m_MidiTypes[0]));
		if (m_type != MIDI_SEND_MANUAL)
		{
			buffer.Printf(wxT("MIDISendKey%03d"), i + 1);
			cfg.Write(group, buffer, (int)m_events[i].key);
		}
		if (m_events[i].type == MIDI_S_NOTE_ON ||
		    m_events[i].type == MIDI_S_CTRL_ON ||
		    m_events[i].type == MIDI_S_PGM_ON ||
		    m_events[i].type == MIDI_S_NOTE ||
		    m_events[i].type == MIDI_S_CTRL)
		{
			buffer.Printf(wxT("MIDISendLowValue%03d"), i + 1);
			cfg.Write(group, buffer, (int)m_events[i].low_value);
		}
		if (m_events[i].type == MIDI_S_NOTE_OFF ||
		    m_events[i].type == MIDI_S_CTRL_OFF ||
		    m_events[i].type == MIDI_S_PGM_OFF ||
		    m_events[i].type == MIDI_S_NOTE ||
		    m_events[i].type == MIDI_S_CTRL)
		{
			buffer.Printf(wxT("MIDISendHighValue%03d"), i + 1);
			cfg.Write(group, buffer, (int)m_events[i].high_value);
		}
	}
}

unsigned GOrgueMidiSender::GetEventCount() const
{
	return m_events.size();
}

MIDI_SEND_EVENT& GOrgueMidiSender::GetEvent(unsigned index)
{
	return m_events[index];
}

unsigned GOrgueMidiSender::AddNewEvent()
{
	MIDI_SEND_EVENT m = { wxT(""), MIDI_S_NONE, 1, 1, 0, 127};
	m_events.push_back(m);
	return m_events.size() - 1;
}

void GOrgueMidiSender::DeleteEvent(unsigned index)
{
	m_events.erase(m_events.begin() + index);
}

void GOrgueMidiSender::SetDisplay(bool state)
{
	for(unsigned i = 0; i < m_events.size(); i++)
	{
		if (m_events[i].type == MIDI_S_NOTE)
		{
			GOrgueMidiEvent e;
			e.SetDevice(m_events[i].device);
			e.SetMidiType(MIDI_NOTE);
			e.SetChannel(m_events[i].channel);
			e.SetKey(m_events[i].key);
			e.SetValue(state ? m_events[i].high_value : m_events[i].low_value);
			m_organfile->SendMidiMessage(e);
		}
		if (m_events[i].type == MIDI_S_CTRL)
		{
			GOrgueMidiEvent e;
			e.SetDevice(m_events[i].device);
			e.SetMidiType(MIDI_CTRL_CHANGE);
			e.SetChannel(m_events[i].channel);
			e.SetKey(m_events[i].key);
			e.SetValue(state ? m_events[i].high_value : m_events[i].low_value);
			m_organfile->SendMidiMessage(e);
		}
		if (m_events[i].type == MIDI_S_PGM_ON && state)
		{
			GOrgueMidiEvent e;
			e.SetDevice(m_events[i].device);
			e.SetMidiType(MIDI_PGM_CHANGE);
			e.SetChannel(m_events[i].channel);
			e.SetKey(m_events[i].key);
			m_organfile->SendMidiMessage(e);
		}
		if (m_events[i].type == MIDI_S_PGM_OFF && !state)
		{
			GOrgueMidiEvent e;
			e.SetDevice(m_events[i].device);
			e.SetMidiType(MIDI_PGM_CHANGE);
			e.SetChannel(m_events[i].channel);
			e.SetKey(m_events[i].key);
			m_organfile->SendMidiMessage(e);
		}
		if (m_events[i].type == MIDI_S_NOTE_ON && state)
		{
			GOrgueMidiEvent e;
			e.SetDevice(m_events[i].device);
			e.SetMidiType(MIDI_NOTE);
			e.SetChannel(m_events[i].channel);
			e.SetKey(m_events[i].key);
			e.SetValue(m_events[i].low_value);
			m_organfile->SendMidiMessage(e);
		}
		if (m_events[i].type == MIDI_S_NOTE_OFF && !state)
		{
			GOrgueMidiEvent e;
			e.SetDevice(m_events[i].device);
			e.SetMidiType(MIDI_NOTE);
			e.SetChannel(m_events[i].channel);
			e.SetKey(m_events[i].key);
			e.SetValue(m_events[i].high_value);
			m_organfile->SendMidiMessage(e);
		}
		if (m_events[i].type == MIDI_S_CTRL_ON && state)
		{
			GOrgueMidiEvent e;
			e.SetDevice(m_events[i].device);
			e.SetMidiType(MIDI_CTRL_CHANGE);
			e.SetChannel(m_events[i].channel);
			e.SetKey(m_events[i].key);
			e.SetValue(m_events[i].low_value);
			m_organfile->SendMidiMessage(e);
		}
		if (m_events[i].type == MIDI_S_CTRL_OFF && !state)
		{
			GOrgueMidiEvent e;
			e.SetDevice(m_events[i].device);
			e.SetMidiType(MIDI_CTRL_CHANGE);
			e.SetChannel(m_events[i].channel);
			e.SetKey(m_events[i].key);
			e.SetValue(m_events[i].high_value);
			m_organfile->SendMidiMessage(e);
		}
	}
}

void GOrgueMidiSender::SetKey(unsigned key, bool state)
{
	for(unsigned i = 0; i < m_events.size(); i++)
	{
		if (m_events[i].type == MIDI_S_NOTE)
		{
			GOrgueMidiEvent e;
			e.SetDevice(m_events[i].device);
			e.SetMidiType(MIDI_NOTE);
			e.SetChannel(m_events[i].channel);
			e.SetKey(key);
			e.SetValue(state ? m_events[i].high_value : m_events[i].low_value);
			m_organfile->SendMidiMessage(e);
		}
	}
}

void GOrgueMidiSender::SetValue(unsigned value)
{
	for(unsigned i = 0; i < m_events.size(); i++)
	{
		if (m_events[i].type == MIDI_S_CTRL)
		{
			GOrgueMidiEvent e;
			e.SetDevice(m_events[i].device);
			e.SetMidiType(MIDI_CTRL_CHANGE);
			e.SetChannel(m_events[i].channel);
			e.SetKey(m_events[i].key);
			unsigned val = m_events[i].low_value + ((m_events[i].high_value - m_events[i].low_value) * value) / 0x7f;
			if (val < 0)
				val = 0;
			if (val > 0x7f)
				val = 0x7f;
			e.SetValue(val);
			m_organfile->SendMidiMessage(e);
		}
	}
}

void GOrgueMidiSender::SetLabel(wxString text)
{
}

GOrgueSettings& GOrgueMidiSender::GetSettings()
{
	return m_organfile->GetSettings();
}

