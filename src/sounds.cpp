#include "sounds.hpp"
#include <raylib.h>

static Music s_music;
static Sound s_rotate_sound;
static Sound s_clear_sound;

void Sounds::load_sounds() {
    s_music = LoadMusicStream("music.mp3");
    s_rotate_sound = LoadSound("rotate.mp3");
    s_clear_sound = LoadSound("clear.mp3");
}

void Sounds::unload_sounds() {
    UnloadMusicStream(s_music);
    UnloadSound(s_rotate_sound);
    UnloadSound(s_clear_sound);
}

void Sounds::start_background_music() {
    if (IsMusicReady(s_music)) {
        PlayMusicStream(s_music);
    }
}

void Sounds::continue_background_music() {
    UpdateMusicStream(s_music);
}

void Sounds::play_rotate() {
    if (IsSoundReady(s_rotate_sound)) {
        PlaySound(s_rotate_sound);
    }
}

void Sounds::play_clear() {
    if (IsSoundReady(s_clear_sound)) {
        PlaySound(s_clear_sound);
    }
}
