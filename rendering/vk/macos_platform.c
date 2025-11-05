/* SPDX-License-Identifier:BSD-3-Clause */
#ifndef MACOS_PLATFORM
#define MACOS_PLATFORM

#include <objc/runtime.h>
#include <objc/message.h>
#include "../../rgfw.h"

#define cls objc_getClass
#define sel sel_getUid
typedef id (*object_message_send)(id, SEL, id); 
typedef id (*class_message_send)(Class, SEL, ...);

#define msg ((object_message_send)objc_msgSend)
#define cls_msg ((class_message_send)objc_msgSend)

void macos_set_window_layer(RGFW_window *window)
{
	Class CAMetalLayer = cls("CAMetalLayer");
	id metal_layer = cls_msg(CAMetalLayer, sel("layer"));
	id view = (id)RGFW_window_getView_OSX(window);
	msg(view, sel("setLayer:"), metal_layer);
}

#endif
