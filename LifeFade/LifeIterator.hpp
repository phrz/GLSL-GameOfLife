//
//  LifeIterator.hpp
//  LifeFade
//
//  Created by Paul Herz on 2018-02-04.
//  Copyright © 2018 Paul Herz. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include "Shaders.hpp"

#ifndef LifeIterator_hpp
#define LifeIterator_hpp

class LifeIterator {
private:
	std::unique_ptr<sf::Shader> shader;
	sf::Sprite renderSprite;
	sf::RenderTexture renderTexture;
	
	unsigned width, height;
public:
	LifeIterator();
	void start(sf::Texture const& initialTexture);
	void step();
	sf::Texture const& texture();
};

#endif /* LifeIterator_hpp */
