/* 
 * Copyright (C) 2002 - David W. Durham
 * 
 * This file is part of ReZound, an audio editing application.
 * 
 * ReZound is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 * 
 * ReZound is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA
 */

#ifndef __FXWaveScrollArea
#define __FXWaveScrollArea

#include "../../config/common.h"
#include "fox_compat.h"

#include <fox/fx.h>

#include "FXWaveCanvas.h" // for FXWaveCanvas::HorzRecenterTypes

class FXRezWaveView;

class CLoadedSound;
#include "../backend/CSound_defs.h"

class FXWaveScrollArea : public FXScrollArea
{
	FXDECLARE(FXWaveScrollArea)
public:
	FXWaveScrollArea(FXRezWaveView *parent,CLoadedSound *_loadedSound);
	virtual ~FXWaveScrollArea();

	void updateFromEdit();

						// ??? might be able to simply implement by setting the zoom factor and then calling centerStartPos or centerStopPos
	void setHorzZoom(double v,FXWaveCanvas::HorzRecenterTypes horzRecenterType);
	double getHorzZoom() const;
	void setVertZoom(double v);

	void centerStartPos();
	void centerStopPos();
	void showAmount(double seconds,sample_pos_t pos);

	void drawPlayPosition(sample_pos_t dataPosition,bool justErasing,bool scrollToMakeVisible);
	const sample_pos_t getSamplePosForScreenX(FXint x) const;

	const FXint getCanvasWidth() const;
	const FXint getCueScreenX(size_t cueIndex) const;
	const sample_pos_t getCueTimeFromX(FXint screenX) const;


	void updateFromSelectionChange(FXWaveCanvas::LastChangedPositions lastChangedPosition=FXWaveCanvas::lcpNone);


	// events I overload 
	virtual FXint getContentWidth();
	virtual FXint getContentHeight();
	virtual void moveContents(FXint x,FXint y);
	virtual void layout();

	void redraw();

	// events I get by message (actually sent by FXWaveCanvas since that's what will be clicked on)
	long onResize(FXObject *object,FXSelector sel,void *ptr);
	long onMouseDown(FXObject *object,FXSelector sel,void *ptr);
	long onMouseUp(FXObject *object,FXSelector sel,void *ptr);
	long onMouseMove(FXObject *object,FXSelector sel,void *ptr);

	long onAutoScroll(FXObject *object,FXSelector sel,void *ptr);

	enum
	{
		ID_CANVAS=FXScrollArea::ID_LAST,
		ID_LAST
	};

protected:
	FXWaveScrollArea() {}

private:
	FXRezWaveView *parent;
	FXWaveCanvas *canvas;
	CLoadedSound *loadedSound;
	bool draggingSelectStart,draggingSelectStop;

	void handleMouseMoveSelectChange(FXint X);
};


#endif