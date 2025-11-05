/* SPDX-License-Identifier:BSD-3-Clause */
#ifndef DEVICE_H
#define DEVICE_H

#include "vk.h"

void vk_device_init(struct renderer_context *context);
void vk_device_deinit(struct renderer_context *context);

#endif
