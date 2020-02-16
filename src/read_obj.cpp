#include "read_obj.h"


#include <fstream>
#include <sstream>

#include <algorithm>
#include <iostream>


ObjParser::ObjParser(std::string filename):
	filename(filename)
{
}


ObjParser::~ObjParser()
{

}

int ObjParser::Parse()
{
	std::ifstream obj_file(filename, std::fstream::in);

	if (obj_file.fail()) {
		return 1;
	}

	std::string line;

	while (std::getline(obj_file, line)) {
		if (line.rfind("v ", 0) == 0) {
			std::vector<std::string> vertex_data = Split(line, ' ');
			float4 vertex{ 0, 0, 0,1 };
			for (int i = 1; i < vertex_data.size(); i++) {
				vertex[i-1] = std::stof(vertex_data.at(i));
			}
			vertexes.push_back(vertex);
			//using namespace linalg::ostream_overloads;
			//std::cout << vertex << std::endl;
		}
		else if (line.rfind("f ", 0) == 0) {
			std::vector<std::string> faces_data = Split(line, ' ');
			std::vector<int> indexes;
			for (int i = 1; i < faces_data.size(); i++) {
				std::vector<std::string> index_data = Split(faces_data.at(i), '/');
				int index = std::stoi(index_data.at(0));
				if (index < 0) {
					index += vertexes.size();
				}
				indexes.push_back(index);
			}
			for (int i = 0; i < indexes.size()-2; i++) {
				face face;
				face.vertexes[0] = vertexes[indexes[0]];
				face.vertexes[1] = vertexes[indexes[i+1]];
				face.vertexes[2] = vertexes[indexes[i+2]];
				faces.push_back(face);
			}
		}
	}

	return 0;
}

const std::vector<face>& ObjParser::GetFaces()
{
	return faces;
}

std::vector<std::string> ObjParser::Split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		if (std::isdigit(token[0]) || std::isalpha(token[0]) || token == "-") {
			tokens.push_back(token);
		}
	}
	return tokens;
}


ReadObj::ReadObj(unsigned short width, unsigned short height, std::string obj_file): LineDrawing(width, height)
{
	parser = new ObjParser(obj_file);
	parser->Parse();
}

ReadObj::~ReadObj()
{
	delete parser;
}

void ReadObj::DrawScene()
{

}

