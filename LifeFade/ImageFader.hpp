//
//  ImageFader.hpp
//  LifeFade
//
//  Created by Paul Herz on 2018-02-04.
//  Copyright © 2018 Paul Herz. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include "Shaders.hpp"

#ifndef ImageFader_hpp
#define ImageFader_hpp

class ImageFader {
private:
	std::unique_ptr<sf::Shader> shader;
	sf::Sprite renderSprite;
	sf::RenderTexture renderTexture;
	
	unsigned width, height;
	public:
	ImageFader();
	void start(sf::Texture const& initialTexture);
	void step();
	sf::Texture const& texture();
};

#endif /* ImageFader_hpp */
