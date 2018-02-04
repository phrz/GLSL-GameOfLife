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
#include <random>
#include <algorithm>
#include <iostream>

static sf::Uint8 magmaColormap[1024] = {	0,0,4,255,1,0,5,255,1,1,6,255,1,1,8,255,2,1,9,255,2,2,11,255,2,2,13,255,3,3,15,255,3,3,18,255,4,4,20,255,5,4,22,255,6,5,24,255,6,5,26,255,7,6,28,255,8,7,30,255,9,7,32,255,10,8,34,255,11,9,36,255,12,9,38,255,13,10,41,255,14,11,43,255,16,11,45,255,17,12,47,255,18,13,49,255,19,13,52,255,20,14,54,255,21,14,56,255,22,15,59,255,24,15,61,255,25,16,63,255,26,16,66,255,28,16,68,255,29,17,71,255,30,17,73,255,32,17,75,255,33,17,78,255,34,17,80,255,36,18,83,255,37,18,85,255,39,18,88,255,41,17,90,255,42,17,92,255,44,17,95,255,45,17,97,255,47,17,99,255,49,17,101,255,51,16,103,255,52,16,105,255,54,16,107,255,56,16,108,255,57,15,110,255,59,15,112,255,61,15,113,255,63,15,114,255,64,15,116,255,66,15,117,255,68,15,118,255,69,16,119,255,71,16,120,255,73,16,120,255,74,16,121,255,76,17,122,255,78,17,123,255,79,18,123,255,81,18,124,255,82,19,124,255,84,19,125,255,86,20,125,255,87,21,126,255,89,21,126,255,90,22,126,255,92,22,127,255,93,23,127,255,95,24,127,255,96,24,128,255,98,25,128,255,100,26,128,255,101,26,128,255,103,27,128,255,104,28,129,255,106,28,129,255,107,29,129,255,109,29,129,255,110,30,129,255,112,31,129,255,114,31,129,255,115,32,129,255,117,33,129,255,118,33,129,255,120,34,129,255,121,34,130,255,123,35,130,255,124,35,130,255,126,36,130,255,128,37,130,255,129,37,129,255,131,38,129,255,132,38,129,255,134,39,129,255,136,39,129,255,137,40,129,255,139,41,129,255,140,41,129,255,142,42,129,255,144,42,129,255,145,43,129,255,147,43,128,255,148,44,128,255,150,44,128,255,152,45,128,255,153,45,128,255,155,46,127,255,156,46,127,255,158,47,127,255,160,47,127,255,161,48,126,255,163,48,126,255,165,49,126,255,166,49,125,255,168,50,125,255,170,51,125,255,171,51,124,255,173,52,124,255,174,52,123,255,176,53,123,255,178,53,123,255,179,54,122,255,181,54,122,255,183,55,121,255,184,55,121,255,186,56,120,255,188,57,120,255,189,57,119,255,191,58,119,255,192,58,118,255,194,59,117,255,196,60,117,255,197,60,116,255,199,61,115,255,200,62,115,255,202,62,114,255,204,63,113,255,205,64,113,255,207,64,112,255,208,65,111,255,210,66,111,255,211,67,110,255,213,68,109,255,214,69,108,255,216,69,108,255,217,70,107,255,219,71,106,255,220,72,105,255,222,73,104,255,223,74,104,255,224,76,103,255,226,77,102,255,227,78,101,255,228,79,100,255,229,80,100,255,231,82,99,255,232,83,98,255,233,84,98,255,234,86,97,255,235,87,96,255,236,88,96,255,237,90,95,255,238,91,94,255,239,93,94,255,240,95,94,255,241,96,93,255,242,98,93,255,242,100,92,255,243,101,92,255,244,103,92,255,244,105,92,255,245,107,92,255,246,108,92,255,246,110,92,255,247,112,92,255,247,114,92,255,248,116,92,255,248,118,92,255,249,120,93,255,249,121,93,255,249,123,93,255,250,125,94,255,250,127,94,255,250,129,95,255,251,131,95,255,251,133,96,255,251,135,97,255,252,137,97,255,252,138,98,255,252,140,99,255,252,142,100,255,252,144,101,255,253,146,102,255,253,148,103,255,253,150,104,255,253,152,105,255,253,154,106,255,253,155,107,255,254,157,108,255,254,159,109,255,254,161,110,255,254,163,111,255,254,165,113,255,254,167,114,255,254,169,115,255,254,170,116,255,254,172,118,255,254,174,119,255,254,176,120,255,254,178,122,255,254,180,123,255,254,182,124,255,254,183,126,255,254,185,127,255,254,187,129,255,254,189,130,255,254,191,132,255,254,193,133,255,254,194,135,255,254,196,136,255,254,198,138,255,254,200,140,255,254,202,141,255,254,204,143,255,254,205,144,255,254,207,146,255,254,209,148,255,254,211,149,255,254,213,151,255,254,215,153,255,254,216,154,255,253,218,156,255,253,220,158,255,253,222,160,255,253,224,161,255,253,226,163,255,253,227,165,255,253,229,167,255,253,231,169,255,253,233,170,255,253,235,172,255,252,236,174,255,252,238,176,255,252,240,178,255,252,242,180,255,252,244,182,255,252,246,184,255,252,247,185,255,252,249,187,255,252,251,189,255,252,253,191,255
};

// A simple wrapper around std::valarray that offers a 2D-indexing
// operator(long,long) that wraps around negative or oversize numbers
// (toroidal indexing). It also manages two-dimensional shape in
// .rows and .columns.
class Matrix {
private:
	std::valarray<int> data;
public:
	std::size_t rows, columns;
	Matrix(std::size_t r, std::size_t c): data(r*c), rows(r), columns(c) {}
	int& operator()(long i,long j) {
		// wrap around negative indices because modulus won't do that
		long ip=i,jp=j;if(ip<0){ip+=rows;};if(jp<0){jp+=columns;}
		
		// use modulus to wrap oversize indices, then convert
		// 2D index into 1D index.
		return data[std::fma(ip % rows, columns, jp % columns)];
	}
};

/*
static int neighbors[16] = {-1,-1,-1,0,-1,1,0,-1,0,1,1,-1,1,0,1,1};
inline int neighborSum(Matrix& m, long i, long j) {
	int sum = 0;
	for(unsigned n = 0; n < 16; n+=2) {
		sum += m(i+neighbors[n],j+neighbors[n+1]);
	}
	return sum;
}

// 1. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
// 2. Any live cell with two or three live neighbors lives on to the next generation.
// 3. Any live cell with fewer than two live neighbors dies as if caused by underpopulation.
// 4. Any live cell with more than three live neighbors dies, as if by overpopulation.

inline bool willSurvive(Matrix& m, long i, long j) {
	int sum = neighborSum(m, i, j);
	bool isAlive = m(i,j) == 1;
	return sum == 3 || (isAlive && (sum == 2));
}

inline void iterateLife(Matrix& next, Matrix& m) {
	for(long i = 0; i < m.rows; ++i) {
		for(long j = 0; j < m.columns; ++j) {
			next(i,j) = (int)willSurvive(m, i, j);
		}
	}
}
*/

/*
// matrix to pixels WITH FADE
void matrixToPixels(Matrix& m, std::valarray<sf::Uint8>& pixels, sf::Uint8 fadeRate) {
	for(long j = 0; j < m.columns; ++j) {
		for(long i = 0; i < m.rows; ++i) {
			long start = (i*m.columns + j) * 4;
			if(m(i,j) == 1L) {
				pixels[start]   = 255; // R
				pixels[start+1] = 255; // G
				pixels[start+2] = 255; // B
				pixels[start+3] = 255; // A
			} else {
				pixels[start]   = std::max(0, pixels[start] - fadeRate);
				pixels[start+1] = std::max(0, pixels[start+1] - fadeRate);
				pixels[start+2] = std::max(0, pixels[start+2] - fadeRate);
				pixels[start+3] = 255;
			}
		}
	}
}
*/

/*
sf::Texture generateColormapTexture() {
	sf::Texture tex;
	tex.create(256, 1);
	tex.update(&magmaColormap[0]);
	return tex;
}
*/

/*
void setInitialStateRandomly(Matrix* buffer) {
	// randomize the initial state
	// hardware random device to seed the generator
	std::random_device device;
	// mersenne twister generator
	std::mt19937 generator(device());
	// uniform integer distribution that employs generator
	std::uniform_int_distribution<> distribution(0,1);
	
	for(long i = 0; i < buffer->rows; ++i) {
		for(long j = 0; j < buffer->columns; ++j) {
			// fill randomly
			(*buffer)(i,j) = distribution(generator);
		}
	}
}
*/

sf::Texture generateRandomTexture(unsigned w, unsigned h) {
	sf::Texture tex;
	tex.create(w, h);
	
	// randomize the initial state
	// hardware random device to seed the generator
	std::random_device device;
	// mersenne twister generator
	std::mt19937 generator(device());
	// uniform integer distribution that employs generator
	std::uniform_int_distribution<> distribution(0,1);
	
	std::size_t size = w*h*4; // rgba
	std::valarray<sf::Uint8> b(size);
	sf::Uint8 x;
	for(size_t i = 0; i < size; i+=4) {
		x = 255 * distribution(generator);
		b[i] = x;     // R
		b[i+1] = x;   // G
		b[i+2] = x;   // B
		b[i+3] = 255; // A
	}
	
	tex.update(&b[0]);
	
	return tex;
}

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

void iterateLife(sf::RenderTexture& resultBuffer, sf::Sprite& sourceSprite, sf::Shader* shader) {
	resultBuffer.draw(sourceSprite, shader);
	resultBuffer.display();
}

static unsigned scaleFactor = 1;
//epochsPerSecond = 120,
//fadeRate = 2;

int main(int argc, char *argv[]) {
	
	/* =============================
	   SETUP
	   ============================= */
//	int microsecondsPerEpoch = 1000000 / epochsPerSecond;
	
	// Fullscreen video modes
	// (first is best)
	auto mode = sf::VideoMode::getFullscreenModes()[0];
	unsigned width = mode.width / scaleFactor;
	unsigned height = mode.height / scaleFactor;
	
	// Game state matrix
//	Matrix buffers[2] {
//		Matrix(height,width), Matrix(height,width)
//	};
//	Matrix *buffer = &buffers[0], *nextBuffer = &buffers[1];
//	std::valarray<sf::Uint8> pixels(height*width*4);
//	setInitialStateRandomly(buffer);
	
	// Window
	sf::RenderWindow window = sf::RenderWindow(mode, "Life", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
//	window.setFramerateLimit(1);
	
	// Shader
	/*
	sf::Texture magmaColormapTexture = generateColormapTexture();
	
	if (!sf::Shader::isAvailable()) {
		std::cout << "Shaders unavailable :(" << std::endl;
		return EXIT_FAILURE;
	}

	sf::Shader shader;
	if (!shader.loadFromFile("ColorMap.frag", sf::Shader::Fragment)) {
		std::cout << "Could not load shader :(" << std::endl;
		return EXIT_FAILURE;
	}
	shader.setUniform("colormap", magmaColormapTexture);
	*/
	
	auto initialTexture = generateRandomTexture(width, height);
	
	// display sprite
	// (we temporarily load the initial state texture into this sprite
	// to draw it into the iteration render-texture (a non-display buffer)
	// and then set its texture to that of the render-texture for actual
	// display, to avoid making a second sprite)
	sf::Sprite renderSprite;
	renderSprite.setTexture(initialTexture);
	
	// Render texture (hidden buffer) and shader
	auto iterateLifeShader = loadIterateLifeShader(width, height);
	sf::RenderTexture iterateLifeRender;
	iterateLifeRender.create(width, height);
	iterateLifeRender.draw(renderSprite);
	iterateLifeRender.display();
	iterateLifeRender.setRepeated(false);
	
	renderSprite.setTexture(iterateLifeRender.getTexture());
	
	sf::Sprite displaySprite;
	displaySprite.setScale(sf::Vector2f(scaleFactor, scaleFactor));
	displaySprite.setTexture(iterateLifeRender.getTexture());
	
	/* =============================
	   END SETUP
	   ============================= */
	
	/* =============================
	   GAME LOOP
	   ============================= */
	
	while(window.isOpen()) {
		// handle system events (window close)
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed) {
				window.close();
			}
		}
		
		iterateLife(iterateLifeRender, renderSprite, iterateLifeShader.get());
		
		window.clear();
		window.draw(displaySprite);
		window.display();
	}
	
	/*
	sf::Clock clock;
	bool lifeNeedsUpdate = true;
	while(window.isOpen()) {
		// handle system events (window close)
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed) {
				window.close();
			}
		}
		
		// only update the texture on epoch time
		sf::Time elapsed = clock.getElapsedTime();
		if(elapsed.asMicroseconds() > microsecondsPerEpoch) {
			clock.restart();
			lifeNeedsUpdate = true;
			
			// update texture from game-of-life matrix
			matrixToPixels(*buffer, pixels, fadeRate);
			lifeTexture.update(&pixels[0]);
		}
		
		if(lifeNeedsUpdate) {
			lifeNeedsUpdate = false;
			iterateLife(*nextBuffer, *buffer);
			std::swap(buffer, nextBuffer);
		}
		
		window.draw(lifeSprite, &shader);
		window.display();
	}
	*/
	
	return EXIT_SUCCESS;
}
