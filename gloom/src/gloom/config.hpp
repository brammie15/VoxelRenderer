// Preprocessor directives
#ifndef GLOOM_HPP
#define GLOOM_HPP
#pragma once

// System Headers
#include <glad/glad.h>

// Standard headers
#include <string>
#include "PerlinNoise.hpp"

// Constants
const int         windowWidth     = 1200;
const int         windowHeight    = 900;
const std::string windowTitle     = "OpenGL";
const GLint       windowResizable = GL_FALSE;
const int         windowSamples   = 4;

const int         MAX_FPS = 60;

static bool renderWireframe = false;

static const int CHUNK_SIZE = 16;
static const int CHUNK_HEIGHT = 256;

static const int TEXTURE_WIDTH = 16;
static const int TEXTURE_HEIGHT = 16;

static const int ATLAS_WIDTH = 128;
static const int ATLAS_HEIGHT = 128;

static const double CELL_WIDTH = 1.0 / ATLAS_WIDTH * TEXTURE_WIDTH;
static const double CELL_HEIGHT = 1.0 / ATLAS_HEIGHT * TEXTURE_HEIGHT;

static const int RENDER_DISTANCE = 10;

static const int WORLD_WIDTH = 128;
static const int WORLD_HEIGHT = 128;

static int SEED = 1234u;

static siv::PerlinNoise perlin{ static_cast<unsigned int>(SEED) };

#endif
