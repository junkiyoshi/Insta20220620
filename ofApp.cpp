#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	ofNoFill();

	// 配色デザイン ビビッドレッド P038
	this->color_palette.push_back(ofColor(197, 0, 24));
	this->color_palette.push_back(ofColor(184, 12, 65));
	this->color_palette.push_back(ofColor(206, 97, 110));
	this->color_palette.push_back(ofColor(204, 85, 68));
	this->color_palette.push_back(ofColor(190, 145, 176));
	this->color_palette.push_back(ofColor(215, 130, 63));
	this->color_palette.push_back(ofColor(255, 241, 51));
	this->color_palette.push_back(ofColor(107, 182, 187));
}


//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	auto span = 240;
	auto deg_span = 20;

	for (auto radius = 60; radius <= 120; radius += 25) {

		for (auto x = span * 0.5; x < ofGetWidth(); x += span) {

			for (auto y = span * 0.5; y < ofGetHeight(); y += span) {

				auto noise_param = ofRandom(1000);

				ofPushMatrix();
				ofTranslate(x, y);

				for (auto deg = 0; deg < 360; deg += deg_span) {

					auto noise_radius = ofMap(ofNoise(noise_param, cos(deg * DEG_TO_RAD), sin(deg * DEG_TO_RAD) , radius * 0.02 + ofGetFrameNum() * 0.02), 0, 1, radius * 0.25, radius);
					vector<glm::vec2> vertices;
					vector<glm::vec2> noise_vertices;
					int deg_param = ofMap(noise_radius, radius * 0.25, radius, 3, 0);
					for (auto tmp_deg = deg + deg_param; tmp_deg <= deg + deg_span - deg_param; tmp_deg++) {

						vertices.push_back(glm::vec2(radius * cos(tmp_deg * DEG_TO_RAD), radius * sin(tmp_deg * DEG_TO_RAD)));
						if (tmp_deg > deg - 1 && tmp_deg < deg + deg_span + 1) {

							noise_vertices.push_back(glm::vec2(noise_radius * cos(tmp_deg * DEG_TO_RAD), noise_radius * sin(tmp_deg * DEG_TO_RAD)));
						}
					}

					vertices.push_back(glm::vec2());
					noise_vertices.push_back(glm::vec2());

					int color_index_1 = ofRandom(this->color_palette.size());
					int color_index_2 = color_index_1;
					do  {

						color_index_2 = ofRandom(this->color_palette.size());
					} while ((color_index_1 == color_index_2));

					/*
					ofSetColor(this->color_palette[color_index_1]);
					ofFill();
					ofBeginShape();
					ofVertices(noise_vertices);
					ofEndShape(true);
					*/

					ofSetColor(this->color_palette[color_index_2]);
					ofNoFill();
					ofBeginShape();
					ofVertices(noise_vertices);
					ofEndShape(true);
				}

				ofPopMatrix();
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}