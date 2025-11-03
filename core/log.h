/* SPDX-License-Identifier:BSD-3-Clause */
#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>
#include "arena.h"

#define log_error_code(msg) do { printf("\x1b[31m" "[ERROR]" "\x1b[0m" "(" __FILE__ ":" __LINE__ "): %s", (msg)); } while (0)
#define log_warning_code(msg) do { printf("\x1b[33m" "[WARN]" "\x1b[0m" "(" __FILE__ ":" __LINE__ "): %s", (msg)); } while (0)
#define log_info_code(msg) do { printf("\x1b[32m" "[INFO]" "\x1b[0m" "(" __FILE__ ":" __LINE__ "): %s", (msg)); } while (0)

#define log_error(msg) do { printf("\x1b[31m" "[ERROR]" "\x1b[0m: %s", (msg)); } while (0)
#define log_warning(msg) do { printf("\x1b[33m" "[WARN]" "\x1b[0m: %s", (msg)); } while (0)
#define log_info(msg) do { printf("\x1b[32m" "[INFO]" "\x1b[0m: %s", (msg)); } while (0)

#define fatal(msg) do { arena_bump(global_arena); arena_deinit(global_arena); log_error(msg); exit(1); } while (0)

#endif
