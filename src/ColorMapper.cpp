//
//  ColorMapper.cpp
//  LifeFade
//
//  Created by Paul Herz on 2018-02-04.
//  Copyright © 2018 Paul Herz. All rights reserved.
//

#include "ColorMapper.hpp"

const std::string ColorMapper::colorMap_frag = R"GLSL(
uniform sampler2D texture;
uniform sampler2D colormap;

float random(vec2 co) {
	return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
	// how much to separate the brightest pixels from the second brightest.
	// if zero, colormap is a smooth gradient but brightest pixels (white)
	// may not be discernable from others.
//	float differentiation = 0.05; for magma
	float differentiation = 0.33;
	
	// bottom n*100% of colors cutoff to zero.
//	float lowerCutoff = 0.05; for magma
	float lowerCutoff = 0.;
	
	// we assume r,g,b are the same (some shade of gray)
	// and use the r component as the "brightness"
	float level = texture2D(texture, gl_TexCoord[0].xy).r;
	
	// the colormap texture is 256 wide and 1 tall with
	// the colors corresponding to 8-bit black to white
	vec2 colormapCoordinate = vec2(1.,0.);
	if(level != 1.) {
		colormapCoordinate.x = smoothstep(lowerCutoff, 1., level*(1.-differentiation));
	}
	
	// the resultant color is the pixel at that position
	// in the colormap texture
	gl_FragColor = texture2D(colormap,colormapCoordinate);
}
)GLSL";

ColorMapper::ColorMapper() {}

void ColorMapper::load(std::valarray<sf::Uint8>&& colormap) {
	this->colormap = std::move(colormap);
	if(this->colormap.size() != 256*4) { // 256 rgba vals
		
		throw std::invalid_argument(fmt::format("A colormap is 1024 floats, i.e. 256 RGBA values in sequence ({:d} given)", this->colormap.size()));
	}
	
	colormapTexture.create(256, 1);
	colormapTexture.update(&(this->colormap[0]));
	
	// _shader = loadShader("ColorMap.frag", sf::Shader::Fragment);
	_shader = loadShaderString(colorMap_frag, sf::Shader::Fragment);
	_shader->setUniform("colormap", colormapTexture);
}

std::unique_ptr<sf::Shader> const& ColorMapper::shader() {
	return _shader;
}
