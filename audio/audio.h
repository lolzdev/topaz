#ifndef AUDIO_H
#define AUDIO_H

#include "../core/linear.h"

enum audio_filetype {
    AUDIO_FILETYPE_WAV,
    AUDIO_FILETYPE_MP3,
};

/*
 * The context object stores data related to audio, implementation 
 * depends on backend.
 */
struct audio_context;

/*
 * The resource object stores the read sound data 
 * loaded from a file and extra options.
 */
struct audio_resource;

/*
 * The source object represents an audio producing
 * object with a position, an orientation and a velocity.
 * A source must have a resource or multiple
 * resources attached to it to be usable. (see audio_source_attach_resource)
 */
struct audio_source;

/*
 * The listener object represents the client's camera(i.e. ears),
 * also having a position, an orientation and a velocity.
 */
struct audio_listener;

/*
 * This struct contains the flags with which 
 * audio files will be loaded.
 */
struct audio_resource_opts {
    enum audio_filetype type;
};

struct audio_source_play_opts { int dummy; };

struct audio_listener_opts { int dummy; };

struct audio_context *audio_context_init(void);
void audio_context_deinit(struct audio_context *context);

/*
 * Creates a resource object from 'path' using specified options
 */
struct audio_resource *audio_resource_load(const char *path, struct audio_resource_opts opts);
void audio_resource_free(struct audio_resource *resource);

struct audio_source *audio_source_init(vec3 pos, vec3 vel, vec3 ori);
void audio_source_deinit(struct audio_source *source);
/*
 * Attaches 'resource' to 'source'.
 * Returns a source-specific index which is used to play the resource via 'source'.
 */
u16 audio_source_attach_resource(struct audio_source *source, struct audio_resource *resource);
/*
 * Plays 'index'th audio resource via 'source' using 'opts'.
 * Will use default options if 'opts' is NULL.
 * defaults:
 * TODO
 */
void audio_source_play(struct audio_source *source, struct audio_source_play_opts *opts, u16 index);
/*
 * Attaches 'resource' to 'source' at given 'index' overwriting whatever was there first.
 */
void audio_source_attach_resource_index(struct audio_source *source, struct audio_resource *resource, u16 index);

struct audio_listener *audio_listener_init(vec3 pos, vec3 vel, vec3 ori);
void audio_listener_deinit(struct audio_listener *listener);
/*
 * Applies 'opts' to 'listener'.
 * Will use defaults if 'opts' was NULL.
 * defaults:
 * TODO
 */
void audio_listener_apply_opts(struct audio_listener *listener, struct audio_listener_opts *opts);

#endif 
