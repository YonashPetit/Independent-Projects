#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <chrono>
#include <string>
#include <thread>
#include <ctime>
//std::map<std::string, sf::Sprite> Image

class Tiles {
public:
    bool _mine;
    bool _clicked;
    int _i;
    int _j;
    std::vector<Tiles *> _neighbors_list;
    std::string _neighbor_count_spt;
    int _neighbor_count_int;
    sf::Vector2f _position;
    bool _still_hidden;
    sf::Sprite current_image;
    bool _flagged = false;
    sf::Sprite _temp;
    bool _minded = false;


public:
    Tiles() {};

    Tiles(bool mine, std::vector<Tiles *> neighbors, bool clicked, float x, float y, bool still_hidden, sf::Sprite Image) {
        _mine = mine;
        _neighbors_list = neighbors;
        _i = x / 32;
        _j = y / 32;
        _clicked = clicked;
        _position = sf::Vector2f(x, y);
        _still_hidden = still_hidden;

        current_image = Image;
    }
//    //Copy Constructor
//    Tiles(const Tiles& other) {
//        _mine = other._mine;
//        _position = other._position;
//        _still_hidden = other._still_hidden;
////        for(int i = 0; i < _neighbors.size(); i++ )
////            _neighbors[i] = neighbors[i];
//        current_image = other.current_image;
//    }
//
//    //Copy Assigner
//    Tiles& operator=(const Tiles& other) {
//        std::cout << "Copy assignment operator called." << std::endl;
//        if (this == &other) {
//            // Check for self-assignment
//            return *this;
//        }
//
//        _mine = other._mine;
//        _position = other._position;
//        _still_hidden = other._still_hidden;
////        for(int i = 0; i < _neighbors.size(); i++ )
////            _neighbors[i] = neighbors[i];
//        current_image = other.current_image;
//
//        // Return *this to allow for chained assignment
//        return *this;
//    }
//
//    //Copy Destructor
//    ~Tiles(){};
    void flood_fill_rec(std::map<std::string, sf::Sprite> Imagez, std::vector<std::vector<Tiles>> array, int cols,int rows, sf::RenderWindow &window) {
        for (int i = 0; i < _neighbors_list.size(); i++){
            auto neighbor = _neighbors_list[i];
            //std::cout << '(' << neighbor->_i << ',' << neighbor->_j << ')' << std::endl;
            //if (_neighbors_list[i]->_i > -1 && _neighbors_list[i]->_i < cols && _neighbors_list[i]->_j > -1 && _neighbors_list[i]->_j < rows) {

                if (!_neighbors_list[i]->_mine && _neighbors_list[i]->_still_hidden && !_neighbors_list[i]->_flagged) {
                    //std::cout << "not where im supposed to be" << std::endl;
                    if (_neighbors_list[i]->_neighbor_count_int == 0){
                        //_neighbors_list[i]->current_image = Imagez[_neighbor_count_spt];
                        _neighbors_list[i]->_clicked = true;
                        _neighbors_list[i]->_still_hidden = false;
                        _neighbors_list[i]->current_image.setPosition(_neighbors_list[i]->_position);
                        window.draw(Imagez["revealed"]);
                        window.draw(_neighbors_list[i]->current_image);
                        window.display();
                        //std::cout << "helo ther" << std::endl;
                        _neighbors_list[i]->flood_fill_rec(Imagez, array, cols, rows, window);

                    }else if (_neighbors_list[i]->_neighbor_count_int >0){
                        _neighbors_list[i]->_clicked = true;
                        _neighbors_list[i]->_still_hidden = false;

                        _neighbors_list[i]->current_image = Imagez[_neighbors_list[i]->_neighbor_count_spt];
                        _neighbors_list[i]->current_image.setPosition(_neighbors_list[i]->_position);
                        window.draw(Imagez["revealed"]);
                        window.draw(_neighbors_list[i]->current_image);
                        window.display();
                        continue;
                    }
                }else{ continue;}
            //}else{ _neighbors_list[i]->flood_fill_rec(Imagez, array, cols, rows, window);}
        }

        for(int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                if(_clicked)
                    current_image = Imagez[_neighbor_count_spt];
//                window.draw(array[i][j].current_image);
//                window.display();
            }
        }

    }

    void LeftClickTile(std::map<std::string, sf::Sprite> Imager, std::vector<std::vector<Tiles>> grid, int cols, int rows, sf::RenderWindow &window) {

        std::cout << _neighbor_count_int << std::endl;
        if (_mine) {
            current_image = Imager["mine"];
            _clicked = true;
            _still_hidden = false;
            //implement show all mines and a loss here
        } else if (_neighbor_count_int == 0) {
            current_image = Imager["revealed"];
            _clicked = true;
            current_image.setPosition(_position);
            window.draw(current_image);
            window.display();
            flood_fill_rec(Imager, grid, cols, rows, window);

        } else {
            current_image = Imager[_neighbor_count_spt];
            _clicked = true;
            _still_hidden = false;
            //flood_fill_rec(grid, cols, rows, Imager);


        }

    }

    void RightClickTile(std::map<std::string, sf::Sprite> Image){
        if(!_flagged && current_image.getTexture() == Image["hidden"].getTexture()){
            _flagged = true;
            current_image = Image["flag"];
        }else if(_flagged && _still_hidden){
            _flagged = false;
            current_image = Image["hidden"];
        }
    }

    void Show(sf::RenderWindow &window, std::map<std::string, sf::Sprite> Image){
//        if(!_mine)
//            current_image = Image[_neighbor_count_spt];
//        if(_mine)
//            current_image = Image["mine"];
        current_image.setPosition(_position);
        window.draw(current_image);
    }

    void DisplayAllMines(std::map<std::string, sf::Sprite> Image){
        if (_mine){
            _temp = current_image;
            current_image = Image["mine"];
        }
    }

    void ReturnAllMines(std::map<std::string, sf::Sprite> Image){
        if (_mine){
            current_image = _temp;
            current_image = Image["hidden"];
            if(_flagged){
                current_image = Image["flag"];
            }
        }
    }

};


