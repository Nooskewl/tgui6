#include <cstring>

#include "tgui6/tgui6.h"
#include "tgui6/tgui6_sdl3.h"

TGUI_Event tgui_sdl_convert_event(SDL_Event *sdl_event)
{
	TGUI_Event event;

	switch (sdl_event->type) {
		case SDL_EVENT_QUIT:
			event.type = TGUI_QUIT;
			break;
		case SDL_EVENT_KEY_DOWN:
			event.type = TGUI_KEY_DOWN;
			event.keyboard.code = sdl_event->key.key;
			event.keyboard.is_repeat = sdl_event->key.repeat != 0;
			event.keyboard.simulated = false;
			break;
		case SDL_EVENT_KEY_UP:
			event.type = TGUI_KEY_UP;
			event.keyboard.code = sdl_event->key.key;
			event.keyboard.is_repeat = sdl_event->key.repeat != 0;
			event.keyboard.simulated = false;
			break;
		case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
			event.type = TGUI_JOY_DOWN;
			event.joystick.id = sdl_event->gbutton.which;
			event.joystick.button = sdl_event->gbutton.button;
			event.joystick.axis = -1;
			event.joystick.value = 0.0f;
			event.joystick.is_repeat = false;
			break;
		case SDL_EVENT_GAMEPAD_BUTTON_UP:
			event.type = TGUI_JOY_UP;
			event.joystick.id = sdl_event->gbutton.which;
			event.joystick.button = sdl_event->gbutton.button;
			event.joystick.axis = -1;
			event.joystick.value = 0.0f;
			event.joystick.is_repeat = false;
			break;
		case SDL_EVENT_GAMEPAD_AXIS_MOTION:
			event.type = TGUI_JOY_AXIS;
			event.joystick.id = sdl_event->gaxis.which;
			event.joystick.button = -1;
			event.joystick.axis = sdl_event->gaxis.axis;
			event.joystick.value = TGUI6_NORMALISE_JOY_AXIS(sdl_event->gaxis.value);
			event.joystick.is_repeat = false;
			break;
#ifndef TVOS
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			if (sdl_event->button.which != SDL_TOUCH_MOUSEID) {
				event.type = TGUI_MOUSE_DOWN;
				event.mouse.button = sdl_event->button.button;
				event.mouse.x = (float)sdl_event->button.x;
				event.mouse.y = (float)sdl_event->button.y;
				event.mouse.normalised = false;
				event.mouse.is_touch = false;
				event.mouse.is_repeat = false;
			}
			break;
		case SDL_EVENT_MOUSE_BUTTON_UP:
			if (sdl_event->button.which != SDL_TOUCH_MOUSEID) {
				event.type = TGUI_MOUSE_UP;
				event.mouse.button = sdl_event->button.button;
				event.mouse.x = (float)sdl_event->button.x;
				event.mouse.y = (float)sdl_event->button.y;
				event.mouse.normalised = false;
				event.mouse.is_touch = false;
				event.mouse.is_repeat = false;
			}
			break;
		case SDL_EVENT_MOUSE_MOTION:
			if (sdl_event->motion.which != SDL_TOUCH_MOUSEID) {
				event.type = TGUI_MOUSE_AXIS;
				event.mouse.button = sdl_event->button.button;
				event.mouse.x = (float)sdl_event->motion.x;
				event.mouse.y = (float)sdl_event->motion.y;
				event.mouse.dx = sdl_event->motion.xrel;
				event.mouse.dy = sdl_event->motion.yrel;
				event.mouse.normalised = false;
				event.mouse.is_touch = false;
				event.mouse.is_repeat = false;
			}
			break;
		case SDL_EVENT_MOUSE_WHEEL:
			event.type = TGUI_MOUSE_WHEEL;
			event.mouse.button = -1;
			event.mouse.x = (float)sdl_event->wheel.x;
			event.mouse.y = (float)sdl_event->wheel.y;
			event.mouse.normalised = false;
			break;
		case SDL_EVENT_FINGER_DOWN:
			event.type = TGUI_MOUSE_DOWN;
			event.mouse.button = SDL_BUTTON_LEFT;
			event.mouse.x = (float)sdl_event->tfinger.x;
			event.mouse.y = (float)sdl_event->tfinger.y;
			event.mouse.normalised = true;
			event.mouse.is_touch = true;
			event.mouse.finger = sdl_event->tfinger.fingerID;
			event.mouse.is_repeat = false;
			break;
		case SDL_EVENT_FINGER_UP:
			event.type = TGUI_MOUSE_UP;
			event.mouse.button = SDL_BUTTON_LEFT;
			event.mouse.x = (float)sdl_event->tfinger.x;
			event.mouse.y = (float)sdl_event->tfinger.y;
			event.mouse.normalised = true;
			event.mouse.is_touch = true;
			event.mouse.finger = sdl_event->tfinger.fingerID;
			event.mouse.is_repeat = false;
			break;
		case SDL_EVENT_FINGER_MOTION:
			event.type = TGUI_MOUSE_AXIS;
			event.mouse.button = SDL_BUTTON_LEFT;
			event.mouse.x = (float)sdl_event->tfinger.x;
			event.mouse.y = (float)sdl_event->tfinger.y;
			event.mouse.normalised = true;
			event.mouse.is_touch = true;
			event.mouse.finger = sdl_event->tfinger.fingerID;
			event.mouse.is_repeat = false;
			break;
#endif
		case SDL_EVENT_TEXT_INPUT:
			event.type = TGUI_TEXT;
#ifdef __GNUC__
			strncpy(event.text.text, sdl_event->text.text, 32);
#else
			strcpy_s(event.text.text, 32, sdl_event->text.text);
#endif
			break;
		default:
			event.type = TGUI_UNKNOWN;
			break;
	}

	return event;
}
