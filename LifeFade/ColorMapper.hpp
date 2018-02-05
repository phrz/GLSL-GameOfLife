//
//  ColorMapper.hpp
//  LifeFade
//
//  Created by Paul Herz on 2018-02-04.
//  Copyright © 2018 Paul Herz. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include <valarray>
#include "Shaders.hpp"

#ifndef ColorMapper_hpp
#define ColorMapper_hpp

class ColorMapper {
private:
	std::unique_ptr<sf::Shader> _shader;
	sf::Texture colormapTexture;
	std::valarray<sf::Uint8> colormap;
	
	unsigned width, height;
public:
	ColorMapper();
	void load(std::valarray<sf::Uint8>&& colormap);
	std::unique_ptr<sf::Shader> const& shader();
};

#endif /* ColorMapper_hpp */
