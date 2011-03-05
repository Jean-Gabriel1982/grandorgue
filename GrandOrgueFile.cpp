/*
 * GrandOrgue - free pipe organ simulator based on MyOrgan
 *
 * MyOrgan 1.0.6 Codebase - Copyright 2006 Milan Digital Audio LLC
 * MyOrgan is a Trademark of Milan Digital Audio LLC
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

#include "GrandOrgueFile.h"

#include <math.h>
#include <wx/progdlg.h>
#include <wx/image.h>
#include <wx/mstream.h>

#include "IniFileConfig.h"
#include "GrandOrgue.h"
#include "GrandOrgueFrame.h"
#include "GOrgueCoupler.h"
#include "GOrgueDisplayMetrics.h"
#include "GOrgueDivisional.h"
#include "GOrgueDivisionalCoupler.h"
#include "GOrgueEnclosure.h"
#include "GOrgueFrameGeneral.h"
#include "GOrgueGeneral.h"
#include "GOrgueLabel.h"
#include "GOrgueMeter.h"
#include "GOrguePipe.h"
#include "GOrguePiston.h"
#include "GOrguePushbutton.h"
#include "GOrgueSound.h"
#include "GOrgueStop.h"
#include "GOrgueThread.h"
#include "GOrgueTremulant.h"
#include "GOrgueWave.h"
#include "GOrgueWindchest.h"
#include "OrganDocument.h"
#include "OrganFile.h"
#include "zlib.h"

extern GOrgueSound* g_sound;
GrandOrgueFile* organfile = 0;
extern const unsigned char* ImageLoader_Stops[];
extern int c_ImageLoader_Stops[];

GrandOrgueFile::GrandOrgueFile() :
	m_pipe_filenames(),
	m_pipe_filesizes(),
	m_pipe_files(),
	m_pipe_ptrs(),
	m_pipe_windchests(),
	m_pipe_percussive(),
	m_pipe_amplitudes(),
	m_path(),
	m_b_squash(0),
	m_compress_p(NULL),
	m_cfg(NULL),
	m_filename(),
	m_elapsed(0),
	m_b_customized(false),
	m_DivisionalsStoreIntermanualCouplers(false),
	m_DivisionalsStoreIntramanualCouplers(false),
	m_DivisionalsStoreTremulants(false),
	m_GeneralsStoreDivisionalCouplers(false),
	m_CombinationsStoreNonDisplayedDrawstops(false),
	m_HighestSampleFormat(0),
	m_FirstManual(0),
	m_NumberOfManuals(0),
	m_NumberOfEnclosures(0),
	m_NumberOfTremulants(0),
	m_NumberOfWindchestGroups(0),
	m_NumberOfReversiblePistons(0),
	m_NumberOfLabels(0),
	m_NumberOfGenerals(0),
	m_NumberOfFrameGenerals(0),
	m_NumberOfDivisionalCouplers(0),
	m_NumberOfStops(0),
	m_NumberOfPipes(0),
	m_AmplitudeLevel(0),
    m_HauptwerkOrganFileFormatVersion(),
	m_ChurchName(),
	m_ChurchAddress(),
	m_OrganBuilder(),
	m_OrganBuildDate(),
	m_OrganComments(),
	m_RecordingDetails(),
    m_InfoFilename(),
	m_enclosure(NULL),
	m_tremulant(NULL),
	m_windchest(NULL),
	m_piston(NULL),
	m_label(NULL),
	m_general(NULL),
	m_framegeneral(NULL),
	m_divisionalcoupler(NULL),
	m_pipe(NULL)
{
	for (int i = 0; i < 9; ++i)
	{
		m_images[i] = wxBitmap();
	}
	for (int i = 0; i < 7; ++i)
	{
		m_manual[i] = GOrgueManual();
	}
}


void GrandOrgueFile::readOrganFile()
{
	IniFileConfig ini(m_cfg);
	const char group[] = "Organ";

	/* load all GUI display metrics */
	m_DisplayMetrics = new GOrgueDisplayMetrics(ini);

	/* load church info */
	m_HauptwerkOrganFileFormatVersion = ini.ReadString( group,"HauptwerkOrganFileFormatVersion",  256, false);
	m_ChurchName = ini.ReadString( group,"ChurchName",  128);
	m_ChurchAddress = ini.ReadString( group,"ChurchAddress",  128);
	m_OrganBuilder = ini.ReadString( group,"OrganBuilder",  128, false);
	m_OrganBuildDate = ini.ReadString( group,"OrganBuildDate",  128, false);
	m_OrganComments = ini.ReadString( group,"OrganComments",  256, false);
	m_RecordingDetails = ini.ReadString( group,"RecordingDetails",  256, false);
	m_InfoFilename = ini.ReadString( group,"InfoFilename",  256, false);
	wxFileName fn = m_filename;
	if (m_InfoFilename.IsEmpty())
		fn.SetExt(".html");
	else
		fn.SetFullName(m_InfoFilename);
	if (fn.FileExists())
		m_InfoFilename = fn.GetFullPath();
	else
		m_InfoFilename = wxEmptyString;

	/* load basic organ information */
	m_NumberOfManuals = ini.ReadInteger(group, "NumberOfManuals", 1, 6);
	m_FirstManual = ini.ReadBoolean(group, "HasPedals") ? 0 : 1;
	m_NumberOfEnclosures = ini.ReadInteger(group, "NumberOfEnclosures", 0, 6);
	m_NumberOfTremulants = ini.ReadInteger(group, "NumberOfTremulants", 0, 10);
	m_NumberOfWindchestGroups = ini.ReadInteger(group, "NumberOfWindchestGroups", 1, 12);
	m_NumberOfReversiblePistons = ini.ReadInteger(group, "NumberOfReversiblePistons", 0, 32);
	m_NumberOfLabels = ini.ReadInteger(group, "NumberOfLabels", 0, 16);
	m_NumberOfGenerals = ini.ReadInteger(group, "NumberOfGenerals", 0, 99);
	m_NumberOfFrameGenerals = 512;	// we never want this to change, what's the point?
	m_NumberOfDivisionalCouplers = ini.ReadInteger(group, "NumberOfDivisionalCouplers", 0, 8);
	m_AmplitudeLevel = ini.ReadInteger(group, "AmplitudeLevel", 0, 1000);
	m_DivisionalsStoreIntermanualCouplers = ini.ReadBoolean(group, "DivisionalsStoreIntermanualCouplers");
	m_DivisionalsStoreIntramanualCouplers = ini.ReadBoolean(group, "DivisionalsStoreIntramanualCouplers");
	m_DivisionalsStoreTremulants = ini.ReadBoolean(group, "DivisionalsStoreTremulants");
	m_GeneralsStoreDivisionalCouplers = ini.ReadBoolean(group, "GeneralsStoreDivisionalCouplers");
	m_CombinationsStoreNonDisplayedDrawstops = ini.ReadBoolean(group, "CombinationsStoreNonDisplayedDrawstops");

	char buffer[64];

	for (int i = m_FirstManual; i <= m_NumberOfManuals; i++)
	{
		sprintf(buffer, "Manual%03d", i);
		m_manual[i].Load(ini, buffer, m_DisplayMetrics, i);
	}

	m_enclosure = new GOrgueEnclosure[m_NumberOfEnclosures];
	for (int i = 0; i < m_NumberOfEnclosures; i++)
	{
		sprintf(buffer, "Enclosure%03d", i + 1);
		m_enclosure[i].Load(ini, buffer, m_DisplayMetrics);
	}

	m_windchest = new GOrgueWindchest[m_NumberOfTremulants + 1 + m_NumberOfWindchestGroups];
	for (int i = 0; i < m_NumberOfWindchestGroups; i++)
	{
		sprintf(buffer, "WindchestGroup%03d", i + 1);
		m_windchest[m_NumberOfTremulants + 1 + i].Load(ini, buffer);
	}

	m_tremulant = new GOrgueTremulant[m_NumberOfTremulants];
	for (int i = 0; i < m_NumberOfTremulants; i++)
	{
		sprintf(buffer, "Tremulant%03d", i + 1);
		m_tremulant[i].Load(ini, buffer, m_DisplayMetrics);
	}

	m_piston = new GOrguePiston[m_NumberOfReversiblePistons];
	for (int i = 0; i < m_NumberOfReversiblePistons; i++)
	{
		sprintf(buffer, "ReversiblePiston%03d", i + 1);
		m_piston[i].Load(ini, buffer, m_DisplayMetrics);
	}

	m_label = new GOrgueLabel[m_NumberOfLabels];
	for (int i = 0; i < m_NumberOfLabels; i++)
	{
		sprintf(buffer, "Label%03d", i + 1);
		m_label[i].Load(ini, buffer, m_DisplayMetrics);
	}

	m_general = new GOrgueGeneral[m_NumberOfGenerals];
	for (int i = 0; i < m_NumberOfGenerals; i++)
	{
		sprintf(buffer, "General%03d", i + 1);
		m_general[i].Load(ini, buffer, m_DisplayMetrics);
	}

	m_framegeneral = new GOrgueFrameGeneral[m_NumberOfFrameGenerals];
	for (int i = 0; i < m_NumberOfFrameGenerals; i++)
	{
		sprintf(buffer, "General%03d", i + 100);
		m_framegeneral[i].Load(ini, buffer);
		m_framegeneral[i].ObjectNumber = i + 100;
	}

	m_divisionalcoupler = new GOrgueDivisionalCoupler[m_NumberOfDivisionalCouplers];
	for (int i = 0; i < m_NumberOfDivisionalCouplers; i++)
	{
		sprintf(buffer, "DivisionalCoupler%03d", i + 1);
		m_divisionalcoupler[i].Load(ini, buffer, m_FirstManual, m_NumberOfManuals, m_DisplayMetrics);
	}

}

wxString GrandOrgueFile::Load(const wxString& file, const wxString& file2)
{
	wxFileConfig *cfg = 0, *extra_cfg = 0;

	wxProgressDialog dlg(_("Loading sample set"), _("Parsing sample set definition file"), 32768, 0, wxPD_AUTO_HIDE | wxPD_CAN_ABORT | wxPD_APP_MODAL | wxPD_ELAPSED_TIME | wxPD_ESTIMATED_TIME | wxPD_REMAINING_TIME);

	m_filename = file;
	m_b_squash = wxConfigBase::Get()->Read("LosslessCompression", 1);

	wxString key, key2, error = "!";

  	// NOTICE: unfortunately, the format is not adhered to well at all. with logging enabled, most sample sets generate warnings.
    wxLog::EnableLogging(false);
    m_cfg = cfg = new wxFileConfig(wxEmptyString, wxEmptyString, wxEmptyString, file, wxCONFIG_USE_GLOBAL_FILE | wxCONFIG_USE_NO_ESCAPE_CHARACTERS);
    wxLog::EnableLogging(true);

    if (!cfg->GetNumberOfGroups())
	{
		error.Printf("Unable to read '%s'", file.c_str());
		return error;
	}

	m_b_customized = false;
    long cookie;
    bool bCont = cfg->GetFirstGroup(key, cookie);
    while (bCont)
    {
        if (key.StartsWith("_"))
        {
            m_b_customized = true;
            cfg->SetPath('/' + key);
            long cookie2;
            bool bCont2 = cfg->GetFirstEntry(key2, cookie2);
            while (bCont2)
            {
                cfg->Write('/' + key.Mid(1) + '/' + key2, cfg->Read(key2));
                bCont2 = cfg->GetNextEntry(key2, cookie2);
            }
            cfg->SetPath("/");
        }
        bCont = cfg->GetNextGroup(key, cookie);
    }

	if (!file2.IsEmpty())
	{
	    // NOTICE: unfortunately, the format is not adhered to well at all. with logging enabled, most sample sets generate warnings.
        wxLog::EnableLogging(false);
		extra_cfg = new wxFileConfig(wxEmptyString, wxEmptyString, wxEmptyString, file2, wxCONFIG_USE_GLOBAL_FILE | wxCONFIG_USE_NO_ESCAPE_CHARACTERS);
        wxLog::EnableLogging(true);

		key = "/Organ/ChurchName";
		if (cfg->Read(key).Trim() == extra_cfg->Read(key).Trim())
		{
			long cookie;
			bool bCont = extra_cfg->GetFirstGroup(key, cookie);
			while (bCont)
			{
				extra_cfg->SetPath('/' + key);
				long cookie2;
				bool bCont2 = extra_cfg->GetFirstEntry(key2, cookie2);
				while (bCont2)
				{
					cfg->Write(key + '/' + key2, extra_cfg->Read(key2));
					bCont2 = extra_cfg->GetNextEntry(key2, cookie2);
				}
				extra_cfg->SetPath("/");
				bCont = extra_cfg->GetNextGroup(key, cookie);
			}
		}
		else
		{
			if (!extra_cfg->GetNumberOfGroups())
			{
				error.Printf("Unable to read '%s'", file2.c_str());
				return error;
			}
			::wxLogWarning("This combination file is only compatible with:\n%s", extra_cfg->Read(key).c_str());
		}
		delete extra_cfg;
	}

	try
	  {
		readOrganFile();
	  }
	catch (wxString error_)
	  {
	    return error_;
	  }

#ifdef __VFD__
    GOrgueLCD_WriteLineOne(ChurchName+" "+OrganBuilder);
    GOrgueLCD_WriteLineTwo("Loading...");
#endif
	m_pipe = new GOrguePipe*[m_NumberOfPipes + m_NumberOfTremulants];
	memset(m_pipe, 0, sizeof(GOrguePipe*) * (m_NumberOfPipes + m_NumberOfTremulants));

	for (unsigned int i = 0; i < m_NumberOfPipes + m_NumberOfTremulants; i++)
		m_pipe[i] = new GOrguePipe();

	m_path = file;
	m_path.MakeAbsolute();
	wxString temp;
	m_path.SetCwd(m_path.GetPath());
	int j, progress = 0;
	char *mbuffer_p = 0, *ptr, *compress;
	short *s_ptr;
	unsigned mbuffer_s = 0, compress_s = 0;
	m_compress_p = 0;
	int ffile = -1;

	/* The wave filenames stored in m_pipe_files are relative paths. This code
	 * takes each filename, converts it to it's absolute path and then stores
	 * it into the pipe_keys vector (FIXME: bad variable name). Reference pipe
	 * filenames are converted to an empty string so for each m_pipe_files[x],
	 * pipe_keys[x] is it's absolute path. */
	std::vector<wxString> pipe_keys;
	for (std::vector<wxString>::const_iterator aFileIter = m_pipe_files.begin();
		 aFileIter != m_pipe_files.end();
		 ++aFileIter)
	{

		if (aFileIter->StartsWith("REF:"))
		{
			pipe_keys.push_back(wxEmptyString);
			continue;
		}

		m_path = *aFileIter;
		m_path.MakeAbsolute();

		// FIXME: breaks an eventual translation to unicode
		key.Printf("%s", m_path.GetFullPath().c_str());
		pipe_keys.push_back(key);

	}

	/* Load pipes */
	for (int i = 0; i < m_pipe_files.size(); i++)
	{

		wxLogDebug("Loading file %s", m_pipe_files[i].c_str());

		/* If this pipe filename is a reference to another pipe, skip. We
		 * load these pipes later... */
		if (m_pipe_files[i].StartsWith("REF:"))
			continue;

		/* Update the progress dialog */
		if (!dlg.Update(((progress + 1) << 15) / (int)(m_NumberOfPipes + 1), m_pipe_files[i]))
		{
			error = "!"; // FIXME: what is this? how can a progress dialog fail to update?
			break;
		}

		// 327: max parameter to progress dialog divided by 100 to calculate percentage
#ifdef __VFD__
		int n=(((progress + 1) << 15) / (int)(organfile->NumberOfPipes + organfile->NumberOfTremulants ))/327;
		GOrgueLCD_WriteLineTwo(wxString::Format("Loading %d%%", n));
#endif

		/* FIXME: bad variable name. "pipe_filename" suggestion */
		key = pipe_keys[i];

		int amp = m_pipe_amplitudes[progress];
		m_pipe[progress]->LoadFromFile(key, amp);
		*m_pipe_ptrs[i] = (short)progress;
		m_pipe[progress]->WindchestGroup = m_pipe_windchests[i];
		progress++;

	}

	/* Load tremulants */
	for (int i = 0; i < m_NumberOfTremulants; i++)
	{

		wxLogDebug("Loading tremulant #%d", i);

		m_pipe[progress]->CreateFromTremulant(&m_tremulant[i]);
		m_tremulant[i].pipe = m_pipe[progress];
		m_pipe[progress]->WindchestGroup = i;
		progress++;

	}

	if (mbuffer_p)
		free(mbuffer_p);
	if (m_compress_p)
		free(m_compress_p);

	/* Resolve references in m_pipe_files */
	/* This code goes through the list of all pipe filenames
	 * searching for filenames starting with the "REF:" identifier,
	 * if a pipe is found, it will try to resolve the pipe.	*/
	for (int i = 0; i < m_pipe_files.size(); i++)
	{

		if (!m_pipe_files[i].StartsWith("REF:"))
			continue;

		int manual, stop, pipe;
		sscanf(m_pipe_files[i].c_str() + 4, "%d:%d:%d", &manual, &stop, &pipe);
		if ((manual < m_FirstManual) || (manual > m_NumberOfManuals) ||
			(stop <= 0) || (stop > m_manual[manual].GetStopCount()) ||
			(pipe <= 0) || (pipe > m_manual[manual].GetStop(stop-1)->NumberOfLogicalPipes))
			return "Invalid reference " + m_pipe_files[i];

		*m_pipe_ptrs[i] = m_manual[manual].GetStop(stop-1)->pipe[pipe-1];

	}

	/* TODO: ? check for correctness ? */
	/* Load the images for the stops */
	for (int i = 0; i < 9; i++)
	{

		wxMemoryInputStream mem((const char*)ImageLoader_Stops[i], c_ImageLoader_Stops[i]);
		wxImage img(mem, wxBITMAP_TYPE_PNG);
		m_images[i] = wxBitmap(img);

	}

	m_pipe_files.clear();
	m_pipe_ptrs.clear();
	m_pipe_amplitudes.clear();
	m_pipe_windchests.clear();
	m_pipe_percussive.clear();

	if (m_cfg)
	{
		::wxGetApp().frame->m_meters[0]->SetValue(m_cfg->Read("/Organ/Volume", g_sound->GetVolume()));
		delete m_cfg;
		m_cfg = 0;
	}

#ifdef __VFD__
	GOrgueLCD_WriteLineTwo("Ready!");
#endif
	return wxEmptyString;

}

GrandOrgueFile::~GrandOrgueFile(void)
{

	/*
	 * This code used to delete the tremulants, but because of the code below
	 * and because they are stored in pipe objects, it is not necessary... but
	 * should come back at some point, because tremulants should not be stored
	 * in the pipes array... it doesn't make sense.
	 *
	for (int i = 0; i < m_NumberOfTremulants; i++)
        if (m_tremulant && m_tremulant[i].pipe)
            free(m_tremulant[i].pipe);
	*/

	if (m_pipe)
	{
		for (unsigned i = 0; i < m_NumberOfPipes + m_NumberOfTremulants; i++)
			if (m_pipe[i])
			{
				printf("nbp=%d,nbt=%d,i=%u\n", (int)m_NumberOfPipes, (int)m_NumberOfTremulants, i);
				delete m_pipe[i];
				m_pipe[i] = NULL;
			}
		delete[] m_pipe;
	}
	if (m_divisionalcoupler)
		delete[] m_divisionalcoupler;
	if (m_framegeneral)
		delete[] m_framegeneral;
	if (m_general)
		delete[] m_general;
	if (m_label)
		delete[] m_label;
	if (m_piston)
		delete[] m_piston;
	if (m_windchest)
		delete[] m_windchest;
	if (m_tremulant)
		delete[] m_tremulant;
	if (m_enclosure)
		delete[] m_enclosure;
	if (m_cfg)
		delete m_cfg;
}
void GrandOrgueFile::Revert(wxFileConfig& cfg)
{
    if (!m_b_customized)
        return;
    long cookie;
    wxString key;
    bool bCont = cfg.GetFirstGroup(key, cookie);
    wxArrayString to_drop;
    while (bCont)
    {
        if (key.StartsWith("_"))
            to_drop.Add(key);
        bCont = cfg.GetNextGroup(key, cookie);
    }
    for (unsigned i = 0; i < to_drop.Count(); i++)
        cfg.DeleteGroup(to_drop[i]);
}

void GrandOrgueFile::Save(const wxString& file)
{
    wxFileName fn(file);
    bool prefix = true;

    if (fn.GetExt().CmpNoCase("organ"))
    {
        if (::wxFileExists(file) && !::wxRemoveFile(file))
        {
            ::wxLogError("Could not write to '%s'", file.c_str());
            return;
        }
        prefix = false;
    }

    wxLog::EnableLogging(false);
    wxFileConfig cfg(wxEmptyString, wxEmptyString, file, wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_NO_ESCAPE_CHARACTERS);
    wxLog::EnableLogging(true);
    if (prefix)
        Revert(cfg);
	m_b_customized = true;

	IniFileConfig aIni(&cfg);
    aIni.SaveHelper(prefix, "Organ", "ChurchName", m_ChurchName);
    aIni.SaveHelper(prefix, "Organ", "ChurchAddress", m_ChurchAddress);
    aIni.SaveHelper(prefix, "Organ", "HauptwerkOrganFileFormatVersion", m_HauptwerkOrganFileFormatVersion);
    aIni.SaveHelper(prefix, "Organ", "NumberOfFrameGenerals", m_NumberOfFrameGenerals);
    aIni.SaveHelper(prefix, "Organ", "Volume", g_sound->GetVolume());

    int i, j;

	for (i = m_FirstManual; i <= m_NumberOfManuals; i++)
	{
		for (j = 0; j < m_manual[i].GetStopCount(); j++)
			m_manual[i].GetStop(j)->Save(aIni, prefix);
		for (j = 0; j < m_manual[i].GetCouplerCount(); j++)
			m_manual[i].GetCoupler(j)->Save(aIni, prefix);
		for (j = 0; j < m_manual[i].GetDivisionalCount(); j++)
			m_manual[i].GetDivisional(j)->Save(aIni, prefix);
	}
	for (j = 0; j < m_NumberOfTremulants; j++)
		m_tremulant[j].Save(aIni, prefix);
	for (j = 0; j < m_NumberOfDivisionalCouplers; j++)
		m_divisionalcoupler[j].Save(aIni, prefix);
	for (j = 0; j < m_NumberOfGenerals; j++)
		m_general[j].Save(aIni, prefix);
	for (j = 0; j < m_NumberOfFrameGenerals; j++)
		m_framegeneral[j].Save(aIni, prefix);
	for (j = 0; j < m_NumberOfReversiblePistons; j++)
		m_piston[j].Save(aIni, prefix);

}

int GrandOrgueFile::GetFirstManualIndex()
{
	return m_FirstManual;
}

int GrandOrgueFile::GetManualAndPedalCount()
{
	return m_NumberOfManuals;
}

GOrgueManual* GrandOrgueFile::GetManual(unsigned index)
{
	return &m_manual[index];
}

int GrandOrgueFile::GetTremulantCount()
{
	return m_NumberOfTremulants;
}

GOrgueTremulant* GrandOrgueFile::GetTremulant(unsigned index)
{
	return &m_tremulant[index];
}

bool GrandOrgueFile::DivisionalsStoreIntermanualCouplers()
{
	return m_DivisionalsStoreIntermanualCouplers;
}

bool GrandOrgueFile::DivisionalsStoreIntramanualCouplers()
{
	return m_DivisionalsStoreIntramanualCouplers;
}

bool GrandOrgueFile::DivisionalsStoreTremulants()
{
	return m_DivisionalsStoreTremulants;
}

int GrandOrgueFile::GetDivisionalCouplerCount()
{
	return m_NumberOfDivisionalCouplers;
}

GOrgueDivisionalCoupler* GrandOrgueFile::GetDivisionalCoupler(unsigned index)
{
	return &m_divisionalcoupler[index];
}

bool GrandOrgueFile::CombinationsStoreNonDisplayedDrawstops()
{
	return m_CombinationsStoreNonDisplayedDrawstops;
}

GOrgueDisplayMetrics* GrandOrgueFile::GetDisplayMetrics()
{
	return m_DisplayMetrics;
}

wxBitmap* GrandOrgueFile::GetImage(unsigned index)
{
	return &m_images[index];
}

int GrandOrgueFile::GetNumberOfReversiblePistons()
{
	return m_NumberOfReversiblePistons;
}

GOrguePiston* GrandOrgueFile::GetPiston(unsigned index)
{
	return &m_piston[index];
}

bool GrandOrgueFile::GeneralsStoreDivisionalCouplers()
{
	return m_GeneralsStoreDivisionalCouplers;
}

int GrandOrgueFile::GetGeneralCount()
{
	return m_NumberOfGenerals;
}

GOrgueGeneral* GrandOrgueFile::GetGeneral(unsigned index)
{
	return &m_general[index];
}

GOrguePipe* GrandOrgueFile::GetPipe(unsigned index)
{
	return m_pipe[index];
}

GOrgueFrameGeneral* GrandOrgueFile::GetFrameGeneral(unsigned index)
{
	return &m_framegeneral[index];
}

long GrandOrgueFile::GetElapsedTime()
{
	return m_elapsed;
}

void GrandOrgueFile::SetElapsedTime(long elapsed)
{
	m_elapsed = elapsed;
}

GOrgueWindchest* GrandOrgueFile::GetWindchest(unsigned index)
{
	return &m_windchest[index];
}

int GrandOrgueFile::GetWinchestGroupCount()
{
	return m_NumberOfWindchestGroups;
}

const wxString& GrandOrgueFile::GetChurchName()
{
	return m_ChurchName;
}

const wxString& GrandOrgueFile::GetChurchAddress()
{
	return m_ChurchAddress;
}

const wxString& GrandOrgueFile::GetOrganBuilder()
{
	return m_OrganBuilder;
}

const wxString& GrandOrgueFile::GetOrganBuildDate()
{
	return m_OrganBuildDate;
}

const wxString& GrandOrgueFile::GetOrganComments()
{
	return m_OrganComments;
}

const wxString& GrandOrgueFile::GetRecordingDetails()
{
	return m_RecordingDetails;
}

const wxString& GrandOrgueFile::GetInfoFilename()
{
	return m_InfoFilename;
}

GOrgueEnclosure* GrandOrgueFile::GetEnclosure(unsigned index)
{
	return &m_enclosure[index];
}

int GrandOrgueFile::GetEnclosureCount()
{
	return m_NumberOfEnclosures;
}

int GrandOrgueFile::GetAmplitude()
{
	return m_AmplitudeLevel;
}

bool GrandOrgueFile::IsCustomized()
{
	return m_b_customized;
}

const wxString& GrandOrgueFile::GetODFFilename()
{
	return m_filename;
}

GOrgueLabel* GrandOrgueFile::GetLabel(unsigned index)
{
	return &m_label[index];
}

int GrandOrgueFile::GetLabelCount()
{
	return m_NumberOfLabels;
}

