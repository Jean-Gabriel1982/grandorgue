/*
 * Copyright 2006 Milan Digital Audio LLC
 * Copyright 2009-2021 GrandOrgue contributors (see AUTHORS)
 * License GPL-2.0 or later
 * (https://www.gnu.org/licenses/old-licenses/gpl-2.0.html).
 */

#ifndef GOSETTINGSDIALOG_H
#define GOSETTINGSDIALOG_H

#include <wx/propdlg.h>

#include <vector>

#include "GOSettingsReason.h"

class GOSound;
class GOSettingsAudioGroup;
class GOSettingsAudio;
class SettingsMidiDevices;
class GOSettingsMidiMessage;
class GOSettingsOptions;
class GOSettingsPaths;
class GOSettingsOrgans;
class GOSettingsReverb;
class GOSettingsTemperaments;

class GOSettingsDialog : public wxPropertySheetDialog {
private:
  enum { ID_REASONS = 100 };

  GOSound &m_Sound;
  bool m_ReasonsAlreadyShown;
  SettingsReasons *m_Reasons;
  GOSettingsOptions *m_OptionsPage;
  GOSettingsPaths *m_PathsPage;
  GOSettingsAudio *m_AudioPage;
  SettingsMidiDevices *m_MidiDevicePage;
  GOSettingsMidiMessage *m_MidiMessagePage;
  GOSettingsOrgans *m_OrgansPage;
  GOSettingsReverb *m_ReverbPage;
  GOSettingsTemperaments *m_TemperamentsPage;

  void OnShow(wxShowEvent &);

  bool DoApply();

  void OnApply(wxCommandEvent &event);
  void OnOK(wxCommandEvent &event);
  void OnHelp(wxCommandEvent &event);
  void OnReasons(wxCommandEvent &event);

public:
  // the order must be the same as the order of pages
  typedef enum {
    PAGE_OPTIONS = 0,
    PAGE_DEFAULTS,
    PAGE_AUDIO_OUTPUT,
    PAGE_REVERB,
    PAGE_AUDIO_GROUPS,
    PAGE_ORGANS,
    PAGE_MIDI_DEVICES,
    PAGE_TEMPERAMENTS,
    PAGE_INIT_MIDI_CONFIG,
    PAGE_ORGAN_PACKAGES
  } PageSelector;

  GOSettingsDialog(wxWindow *parent, GOSound &sound, SettingsReasons *reasons);

  bool NeedReload();
  bool NeedRestart();

  DECLARE_EVENT_TABLE()
};

#endif
