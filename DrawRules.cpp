#pragma once
#ifndef DRAWRULES
#define DRAWRULES

#include <iostream>
#include "Animals.cpp"
#include "HashMap.cpp"
#include "MinerSructers.cpp"

#define _DEFAULT_SIZE_ 15

class DrawInfoNode {
public:
	DrawInfoNode(unsigned char red, unsigned char green, unsigned char blue, unsigned char size, std::string Path) :rgb(red, green, blue), size(size), TexturePath(Path) {}
	DrawInfoNode(unsigned char red, unsigned char green, unsigned char blue, unsigned char size) :rgb(red, green, blue), size(size), TexturePath("") {}
	DrawInfoNode(unsigned char red, unsigned char green, unsigned char blue) :rgb(red,green,blue), size(_DEFAULT_SIZE_), TexturePath("") {}
	DrawInfoNode() :rgb(), size(_DEFAULT_SIZE_), TexturePath("") {}

	RGB rgb;
	int size;
	std::string TexturePath;

};


const HashMap<AnimalsSpecies, DrawInfoNode> DrawInfo(
	Pair2<AnimalsSpecies,DrawInfoNode>(Wolf, DrawInfoNode(255, 0, 0)),
	Pair2<AnimalsSpecies, DrawInfoNode> (Grass, DrawInfoNode(0, 255, 0, 10)),
	Pair2<AnimalsSpecies, DrawInfoNode>(Bunny, DrawInfoNode(255, 255, 0, 12))
);

#endif