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

#ifndef FOOTPRINT_EXCHANGE_H
#define FOOTPRINT_EXCHANGE_H

#include <functional>
#include <core/mirror.h>
#include <math/vector2d.h>

class BOARD;
class BOARD_COMMIT;
class FOOTPRINT;

/**
 * Replace \a aExisting with \a aNew on \a aBoard, carrying over position, orientation, side,
 * lock state, UUIDs and pad nets (the body of PCB_EDIT_FRAME::ExchangeFootprint, frame-free).
 *
 * @param aFlipDirection used when \a aNew must move to \a aExisting's side.
 * @param aPlace         positions \a aNew; the editor passes PlaceFootprint() (undo bookkeeping),
 *                       headless callers just set the position.
 */
void ExchangeFootprintOnBoard( BOARD* aBoard, FOOTPRINT* aExisting, FOOTPRINT* aNew,
                               BOARD_COMMIT& aCommit, FLIP_DIRECTION aFlipDirection,
                               const std::function<void( FOOTPRINT*, const VECTOR2I& )>& aPlace,
                               bool deleteExtraTexts = true, bool resetTextLayers = true,
                               bool resetTextEffects = true, bool resetTextPositions = true,
                               bool resetTextContent = true, bool resetFabricationAttrs = true,
                               bool resetClearanceOverrides = true, bool reset3DModels = true,
                               bool* aUpdated = nullptr );

#endif
