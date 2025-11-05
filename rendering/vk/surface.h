/* SPDX-License-Identifier:BSD-3-Clause */
#ifndef SURFACE_H
#define SURFACE_H

#include "vk.h"

void vk_surface_init(struct renderer_context *context);
void vk_surface_deinit(struct renderer_context *context);

#endif
