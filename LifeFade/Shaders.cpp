//
//  Shaders.cpp
//  LifeFade
//
//  Created by Paul Herz on 2018-02-04.
//  Copyright © 2018 Paul Herz. All rights reserved.
//

#include "Shaders.hpp"

std::unique_ptr<sf::Shader> loadShader(std::string const& fileName, sf::Shader::Type type) {
	if (!sf::Shader::isAvailable()) {
		throw std::runtime_error("Shaders unavailable.");
	}
	
	auto shader = std::make_unique<sf::Shader>();
	if (!shader->loadFromFile(fileName.c_str(), type)) {
		throw std::runtime_error("Could not load shader.");
	}
	return shader;
}

std::unique_ptr<sf::Shader> loadIterateLifeShader(unsigned width, unsigned height) {
	auto shader = loadShader("IterateLife.frag", sf::Shader::Fragment);
	shader->setUniform("resolution", sf::Vector2f(width, height));
	return shader;
}

std::unique_ptr<sf::Shader> loadFadeShader() {
	auto shader = loadShader("FadeShader.frag", sf::Shader::Fragment);
	return shader;
}
