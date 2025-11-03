/* SPDX-License-Identifier:BSD-3-Clause */
#ifndef INSTANCE_H
#define INSTANCE_H

#include "../rendering/renderer.h"

void vk_instance_init(struct renderer_context *context);
void vk_instance_deinit(struct renderer_context *context);

#endif
