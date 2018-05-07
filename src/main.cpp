//
//  main.cpp
//  LifeFade
//
//  Created by Paul Herz on 2018-02-02.
//  Copyright © 2018 Paul Herz. All rights reserved.
//

// -std=c++1z -lsfml-graphics -lsfml-window -lsfml-system
// -Ofast -ffast-math

#include <SFML/Graphics.hpp>
#include <valarray>
#include <algorithm>
#include <fmt/format.h>
#include <cstdlib> // rand
#include <ctime> // time

#include "LifeIterator.hpp"
#include "ImageFader.hpp"
#include "ColorMapper.hpp"

sf::Texture generateRandomTexture(unsigned w, unsigned h) {
	std::srand((unsigned)std::time(nullptr));
	
	sf::Texture tex;
	tex.create(w, h);
	
	std::size_t size = w*h*4; // rgba
	std::valarray<sf::Uint8> b(size);
	sf::Uint8 x;
	for(size_t i = 0; i < size; i+=4) {
		x = std::rand() % 2 * 255;
		b[i] = x;     // R
		b[i+1] = x;   // G
		b[i+2] = x;   // B
		b[i+3] = 255; // A
	}
	
	tex.update(&b[0]);
	return tex;
}

// given `n` terms (n-1^th degree) and variable `x`,
// evaluate the polynomial in nested form.
using Terms = std::valarray<float>;
double poly(Terms ts, float x) {
	auto it=begin(ts);auto out=(*it++);
	for(;it!=end(ts);++it){out=std::fma(out,x,*it);}
	return out;
}

std::valarray<sf::Uint8> generateMagmaColormap() {
	// three arrays: r,g,b polynomial terms
	static Terms const terms[3] {
		{1.768954328517466e-19, -2.0899392858932824e-16, 1.0152490714613931e-13,
		-2.6013383302664676e-11, 3.7473325439173056e-09, -3.0022308133709077e-07,
		1.2962186364725177e-05, -0.00043308147129426017, 0.02832743643720828,
		0.22725919606195824, 0.2208635718283415},
		{1.8685179746512906e-19, -2.9699664826087055e-16, 1.987987923489676e-13,
		-7.306233051797275e-11, 1.608682201135677e-08, -2.169714278392896e-06,
		0.0001756534137468473, -0.007959629302991413, 0.17277231882549918,
		-0.8789711923231053, 1.7155982496580202},
		{-7.518018623822508e-19, 1.0001167999055078e-15, -5.638147080758243e-13,
		1.7505196951628535e-10, -3.2544205623229974e-08, 3.682030593989472e-06,
		-0.0002447217607566503, 0.00856719775327428, -0.1301690739392554,
		2.6562048734958834, 1.6720938890709975}
	};
	// 256 RGBA values for whole 8-bit light scale to map to
	std::valarray<sf::Uint8> cm(255, 256*4); // fill with 255
	for(int i = 0; i < 256; ++i) for(int t = 0; t < 3; ++t) {
		cm[i*4+t] = (int)poly(terms[t], i);
	}
	return cm;
}

// provide two vectors with floats 0...255 and get a colormap with a linear gradient.
std::valarray<sf::Uint8> generateGradientColormap(sf::Vector3i avec, sf::Vector3i bvec) {
	float a[3] = {(float)avec.x,(float)avec.y,(float)avec.z};
	float b[3] = {(float)bvec.x,(float)bvec.y,(float)bvec.z};
	
	std::valarray<sf::Uint8> cm(255, 256*4); // fill with 255
	for(int i = 0; i < 256; ++i) for(int t = 0; t < 3; ++t) {
		float from = a[t]; float to = b[t];
		float interp = from + (i/255.)*(to - from);
		cm[i*4+t] = (sf::Uint8)interp;
	}
	return cm;
}

static unsigned
scaleFactor = 4,
epochsPerSecond = 30;
//fadeRate = 2;

int main(int argc, char *argv[]) {
	
	int microsecondsPerEpoch = 1000000 / epochsPerSecond;
	
	// Fullscreen video modes (first is best)
	auto mode = sf::VideoMode::getFullscreenModes()[0];
	unsigned width = mode.width / scaleFactor;
	unsigned height = mode.height / scaleFactor;
	
	// Window
	sf::RenderWindow window(mode, "Life", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
	
	auto s = window.getSettings();
	fmt::print("OpenGL {:d}.{:d}\n",s.majorVersion,s.minorVersion);
	
	// Shader
	LifeIterator lifeIterator;
	lifeIterator.start(generateRandomTexture(width, height));
	
	ImageFader imageFader;
	imageFader.start(lifeIterator.texture());
	
	ColorMapper colorMapper;
	colorMapper.load(generateMagmaColormap()); // Matplotlib `magma` colormap
//	colorMapper.load(generateGradientColormap({255, 197, 0},{194, 21, 0})); // kyoto
//	colorMapper.load(generateGradientColormap({255,107,107},{85,98,112})); // cheer up emo kid
	
	sf::Sprite displaySprite;
	displaySprite.setScale(sf::Vector2f(scaleFactor, scaleFactor));
	displaySprite.setTexture(imageFader.texture());
	
	/* =============================
	   GAME LOOP
	   ============================= */
	
	sf::Clock clock;
	while(window.isOpen()) {
		// HANDLE EVENTS EACH LOOP
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed) {
				window.close();
			}
		}
		
		// UPDATE GAME STATE SOMETIMES (ON CLOCK)
		if(clock.getElapsedTime().asMicroseconds() > microsecondsPerEpoch) {
			clock.restart();
			lifeIterator.step();
			imageFader.step();
		}
		
		// DRAW EACH LOOP
		window.draw(displaySprite, colorMapper.shader().get());
		window.display();
	}
	
	return EXIT_SUCCESS;
}
