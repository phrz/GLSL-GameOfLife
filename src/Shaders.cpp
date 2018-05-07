//
//  Shaders.cpp
//  LifeFade
//
//  Created by Paul Herz on 2018-02-04.
//  Copyright © 2018 Paul Herz. All rights reserved.
//

#include "Shaders.hpp"

static const std::string fadeShader_frag = R"GLSL(
#version 120

uniform sampler2D texture;

void main() {
	float fadeRate = 0.01;
	vec4 color = texture2D(texture, gl_TexCoord[0].xy);
	gl_FragColor = vec4(color.rgb, color.r + fadeRate);
}
)GLSL";

static const std::string iterateLife_frag = R"GLSL(
#version 120

uniform sampler2D tex;
uniform vec2 resolution;

// get the value of the pixel at the coordinate
// relative to the current pixel
float v(float xrel, float yrel) {
	// gl_TexCoord[0]: fractional coordinate along texture
	// gl_FragCoord:   pixel coordinates (screen)
	vec2 xy;
	xy.x = mod(gl_FragCoord.x + xrel, resolution.x);
	xy.y = mod(gl_FragCoord.y + yrel, resolution.y);
	
	return texture2D(tex, xy/resolution).r;
}

float neighborSum() {
	float a=-1.,b=0.,c=1.;
	return v(a,a)+v(a,b)+v(a,c)+v(b,a)+v(b,c)+v(c,a)+v(c,b)+v(c,c);
}

void main() {
	bool alive = v(0.,0.) == 1.;
	float sum = neighborSum();
	bool b = sum == 3. || (alive && (sum == 2.));
	float a = float(b);
	gl_FragColor = vec4(a, a, a, 1.0);
}
)GLSL";

static const std::string motionBlurShader_frag = R"GLSL(
uniform sampler2D texture;

void main() {
	vec3 color = texture2D(texture, gl_TexCoord[0].xy).rgb;
	gl_FragColor = vec4(color, 0.1);
}
)GLSL";

std::unique_ptr<sf::Shader> loadShaderString(std::string const& shaderLiteral, sf::Shader::Type type) {
	if(!sf::Shader::isAvailable()) {
		throw std::runtime_error("Shaders unavailable.");
	}
	
	auto shader = std::make_unique<sf::Shader>();
	if(!shader->loadFromMemory(shaderLiteral, type)) {
		throw std::runtime_error("Could not load shader.");
	}
	return shader;
}

std::unique_ptr<sf::Shader> loadShader(std::string const& fileName, sf::Shader::Type type) {
	if(!sf::Shader::isAvailable()) {
		throw std::runtime_error("Shaders unavailable.");
	}
	
	auto shader = std::make_unique<sf::Shader>();
	if(!shader->loadFromFile(fileName.c_str(), type)) {
		throw std::runtime_error("Could not load shader.");
	}
	return shader;
}

std::unique_ptr<sf::Shader> loadIterateLifeShader(unsigned width, unsigned height) {
	// auto shader = loadShader("IterateLife.frag", sf::Shader::Fragment);
	auto shader = loadShaderString(iterateLife_frag, sf::Shader::Fragment);
	shader->setUniform("resolution", sf::Vector2f(width, height));
	return shader;
}

std::unique_ptr<sf::Shader> loadFadeShader() {
	auto shader = loadShaderString(fadeShader_frag, sf::Shader::Fragment);
	// auto shader = loadShader("FadeShader.frag", sf::Shader::Fragment);
	return shader;
}
