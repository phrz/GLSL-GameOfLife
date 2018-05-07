//
//  ImageFader.cpp
//  LifeFade
//
//  Created by Paul Herz on 2018-02-04.
//  Copyright © 2018 Paul Herz. All rights reserved.
//

#include "ImageFader.hpp"

ImageFader::ImageFader() {}

void ImageFader::start(sf::Texture const& initialTexture) {
	renderSprite.setTexture(initialTexture);
	width = initialTexture.getSize().x;
	height = initialTexture.getSize().y;
	
	// Render texture (hidden buffer) and shader
	shader = loadFadeShader();
	
	renderTexture.create(width, height);
	renderTexture.draw(renderSprite);
	renderTexture.display();
	renderTexture.setRepeated(false);
	
	// no feedback wanted here
	// we keep the initial texture as our painting source
//	renderSprite.setTexture(renderTexture.getTexture());
}

void ImageFader::step() {
	renderTexture.draw(renderSprite, shader.get());
	renderTexture.display();
}

sf::Texture const& ImageFader::texture() {
	return renderTexture.getTexture();
}
