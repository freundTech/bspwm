
/* Copyright (c) 2012, Bastien Dejean
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdbool.h>
#include "bspwm.h"
#include "query.h"
#include "settings.h"
#include "stack.h"
#include "tree.h"
#include "monitor.h"
#include "subscribe.h"
#include "events.h"
#include "window.h"
#include "touch.h"

void touch_init(void)
{
}

void grab_touches(void) {
	const xcb_query_extension_reply_t *qep = xcb_get_extension_data(dpy, &xcb_input_id);
	if (qep->present) {	
		const uint32_t mask[] = {
				XCB_INPUT_XI_EVENT_MASK_TOUCH_BEGIN
				| XCB_INPUT_XI_EVENT_MASK_TOUCH_UPDATE
				| XCB_INPUT_XI_EVENT_MASK_TOUCH_END
				| XCB_INPUT_XI_EVENT_MASK_TOUCH_OWNERSHIP
		};
		const uint32_t modifiers[] = {XCB_INPUT_MODIFIER_MASK_ANY};

		xcb_input_xi_passive_grab_device(
				dpy, 
				XCB_CURRENT_TIME, 
				root,
				XCB_CURSOR_NONE,
				0,
				XCB_INPUT_DEVICE_ALL_MASTER,
				1,
				1,
				XCB_INPUT_GRAB_TYPE_TOUCH_BEGIN,
				XCB_INPUT_GRAB_MODE_22_TOUCH,
				XCB_INPUT_GRAB_MODE_22_ASYNC,
				XCB_INPUT_GRAB_OWNER_NO_OWNER,
				mask,
				modifiers
			);
	}
}

void ungrab_touches(void)
{
	xcb_ungrab_button(dpy, XCB_BUTTON_INDEX_ANY, root, XCB_MOD_MASK_ANY);
}

