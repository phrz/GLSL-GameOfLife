//
//  ColorMapper.cpp
//  LifeFade
//
//  Created by Paul Herz on 2018-02-04.
//  Copyright © 2018 Paul Herz. All rights reserved.
//

#include "ColorMapper.hpp"

ColorMapper::ColorMapper() {}

void ColorMapper::load(std::valarray<sf::Uint8>&& colormap) {
	this->colormap = std::move(colormap);
	if(this->colormap.size() != 256*4) { // 256 rgba vals
		
		throw std::invalid_argument(fmt::format("A colormap is 1024 floats, i.e. 256 RGBA values in sequence ({:d} given)", this->colormap.size()));
	}
	
	colormapTexture.create(256, 1);
	colormapTexture.update(&(this->colormap[0]));
	
	_shader = loadShader("ColorMap.frag", sf::Shader::Fragment);
	_shader->setUniform("colormap", colormapTexture);
}

std::unique_ptr<sf::Shader> const& ColorMapper::shader() {
	return _shader;
}
