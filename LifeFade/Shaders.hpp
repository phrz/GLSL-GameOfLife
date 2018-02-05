//
//  Shaders.hpp
//  LifeFade
//
//  Created by Paul Herz on 2018-02-04.
//  Copyright © 2018 Paul Herz. All rights reserved.
//

#include <SFML/Graphics.hpp>

#ifndef Shaders_hpp
#define Shaders_hpp

std::unique_ptr<sf::Shader> loadShader(std::string const& fileName, sf::Shader::Type type);
std::unique_ptr<sf::Shader> loadIterateLifeShader(unsigned width, unsigned height);
std::unique_ptr<sf::Shader> loadFadeShader();

#endif /* Shaders_hpp */
