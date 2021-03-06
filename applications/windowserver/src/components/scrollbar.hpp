/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *  Ghost, a micro-kernel based operating system for the x86 architecture    *
 *  Copyright (C) 2015, Max Schlüssel <lokoxe@gmail.com>                     *
 *                                                                           *
 *  This program is free software: you can redistribute it and/or modify     *
 *  it under the terms of the GNU General Public License as published by     *
 *  the Free Software Foundation, either version 3 of the License, or        *
 *  (at your option) any later version.                                      *
 *                                                                           *
 *  This program is distributed in the hope that it will be useful,          *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *  GNU General Public License for more details.                             *
 *                                                                           *
 *  You should have received a copy of the GNU General Public License        *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.    *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __SCROLLBAR__
#define __SCROLLBAR__

#include <components/button_state.hpp>
#include <components/component.hpp>

class scrollbar_t;

/**
 *
 */
enum class scrollbar_orientation_t
	: uint8_t {
		VERTICAL, HORIZONTAL
};

/**
 *
 */
class scroll_handler_t {
public:
	virtual ~scroll_handler_t() {
	}
	virtual void handleScroll(scrollbar_t* bar) = 0;
};

/**
 *
 */
class scrollbar_t: public component_t {
private:
	scrollbar_orientation_t orientation;

	int modelPosition;
	int modelVisibleArea;
	int modelTotalArea;

	button_state_t decButtonState;
	button_state_t incButtonState;

	bool knobDrag;
	int dragPressPosition;
	int dragViewPosition;

	scroll_handler_t* scrollHandler;

public:
	scrollbar_t(scrollbar_orientation_t orientation) :
			orientation(orientation), modelPosition(0), modelVisibleArea(0), modelTotalArea(0), knobDrag(false), dragPressPosition(0), dragViewPosition(0), scrollHandler(
					0) {
	}

	virtual void paint();
	virtual bool handle(event_t& event);

	virtual void setScrollHandler(scroll_handler_t* handler) {
		scrollHandler = handler;
	}
	virtual scroll_handler_t* gettScrollHandler() {
		return scrollHandler;
	}

	void setModelArea(int visibleArea, int totalArea);
	int getModelVisibleArea() const {
		return modelVisibleArea;
	}
	int getModelTotalArea() const {
		return modelTotalArea;
	}

	void setModelPosition(int position);

	int getModelPosition() const {
		return modelPosition;
	}

	int getViewMax();
	int getKnobSize();

	g_rectangle calculateKnob();

};

#endif
