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

#ifndef JOB_SCH_IMPORT_H
#define JOB_SCH_IMPORT_H

#include <kicommon.h>
#include "job.h"

/**
 * Job to import a non-KiCad schematic (or an Altium project's schematics) to KiCad format.
 *
 * Writes the .kicad_sch hierarchy and a .kicad_pro next to the output schematic.
 */
class KICOMMON_API JOB_SCH_IMPORT : public JOB
{
public:
    JOB_SCH_IMPORT();

    wxString GetDefaultDescription() const override;
    wxString GetSettingsDialogTitle() const override;

    enum class FORMAT
    {
        AUTO,
        ALTIUM,
        CADSTAR,
        EAGLE,
        EASYEDA,
        EASYEDAPRO,
        LTSPICE,
        PADS,
        GEDA
    };

    wxString m_inputFile;
    FORMAT   m_format = FORMAT::AUTO;
};

#endif
