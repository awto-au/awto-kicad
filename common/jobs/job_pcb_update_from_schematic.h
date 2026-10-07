/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright The KiCad Developers, see AUTHORS.txt for contributors.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef JOB_PCB_UPDATE_FROM_SCHEMATIC_H
#define JOB_PCB_UPDATE_FROM_SCHEMATIC_H

#include <kicommon.h>
#include "job.h"

/// Headless Update PCB from Schematic (F8): same engine and options as the dialog.
class KICOMMON_API JOB_PCB_UPDATE_FROM_SCHEMATIC : public JOB
{
public:
    JOB_PCB_UPDATE_FROM_SCHEMATIC();

    wxString m_filename;            ///< input board
    bool     m_dryRun;              ///< report only; write nothing
    bool     m_relinkFootprints;    ///< dialog "Re-link footprints to schematic symbols"
    bool     m_replaceFootprints;
    bool     m_deleteUnusedFootprints;
    bool     m_overrideLocks;
    bool     m_updateFields;
    bool     m_removeExtraFields;
    bool     m_transferGroups;
};

#endif
