//
//  LifeIterator.cpp
//  LifeFade
//
//  Created by Paul Herz on 2018-02-04.
//  Copyright © 2018 Paul Herz. All rights reserved.
//

#include "LifeIterator.hpp"

LifeIterator::LifeIterator() {}

void LifeIterator::start(sf::Texture const& initialTexture) {
	renderSprite.setTexture(initialTexture);
	width = initialTexture.getSize().x;
	height = initialTexture.getSize().y;
	
	// Render texture (hidden buffer) and shader
	shader = loadIterateLifeShader(width, height);
	
	renderTexture.create(width, height);
	renderTexture.draw(renderSprite);
	renderTexture.display();
	renderTexture.setRepeated(false);
	
	renderSprite.setTexture(renderTexture.getTexture());
}

void LifeIterator::step() {
	renderTexture.draw(renderSprite, shader.get());
	renderTexture.display();
}

sf::Texture const& LifeIterator::texture() {
	return renderTexture.getTexture();
}
