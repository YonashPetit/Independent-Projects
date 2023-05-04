
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <chrono>
#include "Tiles.h"
#include <random>
#include <ctime>
#include <thread>

#include <sstream>




sf::RectangleShape setRectangle(sf::Vector2f size,float positionx, float positiony, float originx, float originy, sf::Color color){
    sf::RectangleShape rect;
    rect.setSize(size);
    rect.setPosition(positionx, positiony);
    rect.setOrigin(originx,originy);
    rect.setFillColor(color);
    return rect;
}

sf::Text setText(sf::Font font, std::string line, int font_size, sf::Vector2f position){
    sf::Text text;
    text.setFont(font);
    text.setString(line);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setCharacterSize(font_size);
    text.setPosition(sf::Vector2f(position));
    text.setOrigin(text.getLocalBounds().width/2,text.getLocalBounds().height/2);
    return text;
}

void InsertIntoPlace_I(std::vector<int> &vec, int item, int index){
    size_t vectorSize = vec.size();


    vec.resize(vectorSize + 1);


    for (size_t i = vectorSize; i > index; --i) {
        vec[i] = vec[i - 1];
    }
    vec[index] = item;
}

void InsertIntoPlace_S(std::vector<std::string> &vec, std::string item, int index){
    size_t vectorSize = vec.size();


    vec.resize(vectorSize + 1);


    for (size_t i = vectorSize; i > index; --i) {
        vec[i] = vec[i - 1];
    }
    vec[index] = item;
}

void LeaderboardWindow(sf::RenderWindow &main_window, int width, int height, bool win, std::string Player_Name, int minute, int second, int col, int row, bool &leaderboard_con, bool &play, bool &pause, sf::Sprite pausebutton, int &no_exceed){
    width = 16*width;
    height = 16*height+50;
//    auto minute = 7;
//    auto second = 10;
//    bool win = true;
    std::string newcomer_name = Player_Name;

    // Create SFML window
    sf::RenderWindow window(sf::VideoMode(width, height), "Leaderboard");
    sf::RectangleShape BCCOLOR = setRectangle(sf::Vector2f(width,height),0,0,0,0, sf::Color::Blue);
    sf::Font font;
    if (!font.loadFromFile("files/font.ttf")) {
        // handle font loading error
        return;
    }

    int counter;
    int c = 0;

    std::vector<std::string> names;
    std::vector<std::string> time;
    std::vector<int> time_int_inSeconds;
    std::string scoreboard;
    std::fstream people ( "files/leaderboard.txt", std::ios_base::in);
    if (people.is_open()) {
        std::string line, word;
        while (getline(people, line)){

            std::stringstream s_stream(line);
            while(s_stream.good()){
                std::string substr;
                getline(s_stream, substr, ',');
                if(counter % 2 == 0 ) {
                    int num1 = std::atoi(&substr[0]);
                    int num2 = std::atoi(&substr[3]);
                    int min_string = (num1)*60;
                    //std::cout << typeid(time[index][0]).name() << std::endl;
                    int sec_string = (num2);
                    time_int_inSeconds.push_back(min_string + sec_string);
                    time.push_back(substr.c_str());
                } else {
                    names.push_back(substr);
                }
                c++;
                counter++;
            }
        }
//        for(int i = 0; i < names.size(); i++){
//            std::cout << names[i] << std::endl;
//        }
        for(int i = 0; i < names.size(); i++){
            if(i>4)
                break;
            if (newcomer_name == names[i]){
                scoreboard += std::to_string(i+1) + ".     " + time[i] + "      " + names[i] + '*' + "\n\n";
            }else{
                scoreboard += std::to_string(i+1) + ".     " + time[i] + "      " + names[i] + "\n\n";
            }

        }
        people.close();
    }else{
        std::cout << "File did not open" << std::endl;
    }

    if(win && no_exceed <1){
        scoreboard = "";
        int newcomer_time = minute*60+second;
        std::cout << "is it owrking?" << std::endl;

        int position = 4;
        for(int i = position; i >= 0; i--){
            if(newcomer_time>time_int_inSeconds[i]){

                break;

            }else{
                position = i;
            }
        }

        std::cout << "hi there" << std::endl;
        auto sminute = std::to_string(minute);
        auto ssecond = std::to_string(second);
        if (sminute.length()==1)
            sminute = "0" + sminute;
        if (ssecond.length()==1)
            ssecond = "0" + ssecond;
        InsertIntoPlace_I(time_int_inSeconds, newcomer_time, position);
        InsertIntoPlace_S(time, ( sminute + ':' + ssecond ), position);
        InsertIntoPlace_S(names, newcomer_name, position);

        for(int i = 0; i < names.size(); i++){
            if(i>4)
                break;
            if (newcomer_name == names[i] && sminute + ':' + ssecond == time[i]){
                scoreboard += std::to_string(i+1) + ".     " + time[i] + "      " + names[i] + '*' + "\n\n";
            }else{
                scoreboard += std::to_string(i+1) + ".     " + time[i] + "      " + names[i] + "\n\n";
            }

        }

        //delete previous content of file
        std::ofstream file("files/leaderboard.txt", std::ios::trunc);
        if (file.is_open()) {
            file.close(); // Close the file, which truncates its content
            std::cout << "File content deleted." << std::endl;
        } else {
            std::cout << "Failed to open the file." << std::endl;
        }

        //put in new content for file
        std::fstream people ( "files/leaderboard.txt", std::ios_base::out);
        if(people.is_open()){
            for(int i = 0; i < names.size(); i++){
                people << time[i] << "," << names[i] << std::endl;
            }
            people.close();
        }else{std::cout << "file not open properly" << std::endl;}
        no_exceed++;
    }


    for(int i = 0; i < time_int_inSeconds.size(); i++){

        std::cout << names[i] << ": ";
        std::cout << time_int_inSeconds[i] << std::endl;

    }


//Stuff to initialize Leaderboard text and Scoreboard text
    sf::Text Title = setText(font, "LEADERBOARD",  20, sf::Vector2f(width/2.0f, height/2.0f - 120));
    Title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    Title.setFont(font);

    sf::Text Scoreboard = setText(font, "hi",  18, sf::Vector2f(width/2.0f, height/2.0f + 120));
    Scoreboard.setStyle(sf::Text::Bold | sf::Text::Underlined);
    Scoreboard.setFont(font);


    Scoreboard.setFont(font);
    Scoreboard.setString(scoreboard);
    Scoreboard.setFillColor(sf::Color::White);
    Scoreboard.setStyle(sf::Text::Bold);
    Scoreboard.setCharacterSize(18);
    Scoreboard.setPosition(sf::Vector2f(width/2.0f, height/2.0f + 40));
    Scoreboard.setOrigin(Scoreboard.getLocalBounds().width/2,Scoreboard.getLocalBounds().height/2);

    while (window.isOpen()) {
        sf::Event event;


        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                if(play && !pause)
                    window.draw(pausebutton);
                leaderboard_con = false;
                window.close();
            }
        }

        while (main_window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                int xz = event.mouseButton.x;
                int yz = event.mouseButton.y;
                if ((col * 32) - 176  <= xz && xz <= ((col * 32) - 176 + 64)){
                    if ((32 * (row+0.5f) <= yz && yz <= (32 * (row+0.5f)+64))) {
                        if(play && !pause)
                            window.draw(pausebutton);
                        leaderboard_con = false;
                        window.close();

                    }
                }
            }
        }

        window.draw(BCCOLOR);
        window.draw(Scoreboard);
        window.draw(Title);
        window.display();
    }
}

int Count_Neighbors(Tiles cell, std::vector<std::vector<Tiles>> grid, int cols, int rows){
    if(cell._mine){
        cell._neighbor_count_int = -1;
        return cell._neighbor_count_int;
    }

    int total = 0;
    int cow = cell._i;
    int bird = cell._j;
    for (int xoff = -1; xoff <=1; xoff++){
        for (int yoff = -1; yoff <= 1; yoff++){
            int n = cow + xoff;
            int m = bird + yoff;
            if (n > -1 && n < cols && m > -1 && m < rows){
                auto neighbor = grid[n][m];
                if (neighbor._mine){
                    total++;
                }
            }
        }
    }
    cell._neighbor_count_int = total;
    //std::cout << "Total Near By:  " << total << std::endl;
    return total;
}

std::vector<std::vector<Tiles>> make2dArray(int col, int row, int mine, std::map<std::string, sf::Sprite> Images){
    int c = 0;
    float x = 0.0f;
    float y = 0.0f;
    std::vector<bool> AssortMines;
    for(int i = 0; i < col*row; i++){
        if(i < col*row - mine){
            AssortMines.push_back(false);
        }else{
            AssortMines.push_back(true);
        }
    }
    std::shuffle(AssortMines.begin(), AssortMines.end(), std::default_random_engine(std::random_device()()));

    std::vector<std::vector<Tiles>> array;
    std::vector<Tiles> array2;
    std::vector<Tiles*> partners;

//    std::cout<< "size of pic: " << sizeof(Images["hidden"]) << ", size of col: " << col << ", size of row : " << row << std::endl;
    for(int i = 0; i < col; i++){
        array2.clear();
        for(int j = 0; j < row; j++){
            bool danger = AssortMines.at(c);
            Tiles a = Tiles(danger, partners,false, x, y, true, Images["hidden"]);
            array2.push_back(a);
            c++;
            y = y + 32;
        }
        array.push_back(array2);
        x = x + 32;
        y=0;
    }

    for(int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            auto total = Count_Neighbors(array[i][j], array, col, row);
            array[i][j]._neighbor_count_int = total;
            if (total == 0) {
                array[i][j]._neighbor_count_spt = "revealed";
            }else{
                array[i][j]._neighbor_count_spt = "num" + std::to_string(Count_Neighbors(array[i][j], array, col, row));
            }

//            x = array[i][j]._i;
//            y = array[i][j]._j;
//            array[i][j]._neighbors_list.push_back(&array[x-1][y-1]);
//            array[i][j]._neighbors_list.push_back(&array[x][y-1]);
//            array[i][j]._neighbors_list.push_back(&array[x+1][y-1]);
//            array[i][j]._neighbors_list.push_back(&array[x-1][y]);
//            array[i][j]._neighbors_list.push_back(&array[x+1][y]);
//            array[i][j]._neighbors_list.push_back(&array[x-1][y+1]);
//            array[i][j]._neighbors_list.push_back(&array[x][y+1]);
//            array[i][j]._neighbors_list.push_back(&array[x+1][y+1]);



        }
    }
    for(int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {

            int cow = array[i][j]._i;
            int bird = array[i][j]._j;
            for (int xoff = -1; xoff <=1; xoff++){
                for (int yoff = -1; yoff <= 1; yoff++){
                    int n = cow + xoff;
                    int m = bird + yoff;
                    if (n > -1 && n < col && m > -1 && m < row){
                        array[i][j]._neighbors_list.push_back(&array[n][m]);
                        if (array[i][j]._position == array[n][m]._position){
                            array[i][j]._neighbors_list.pop_back();
                        }
                    }
                }
            }


        }
    }
    return array;
}

std::string Up_Low(std::string player_name){
    if (player_name.size() == 1)
        player_name[0] = std::toupper(player_name[0]);
    if (player_name.size() > 1)
        for(int i = 1; i <= player_name.size(); i++)
            player_name[i] = std::tolower(player_name[i]);
    return player_name;
}

sf::Sprite CreateDigit(char x){
//    int num1 = int(num[0]), num2 =int(num[1]), num3 = int(num[2]), num4 = int(num[3]);

    sf::Texture Digits;
    if (!Digits.loadFromFile("files/images/digits.png"))
    {
        std::cout << "did not load" << std::endl;
    }
    sf::Sprite digit0;
    sf::Sprite digit1;
    sf::Sprite digit2;
    sf::Sprite digit3;
    sf::Sprite digit4;
    sf::Sprite digit5;
    sf::Sprite digit6;
    sf::Sprite digit7;
    sf::Sprite digit8;
    sf::Sprite digit9;
    sf::Sprite dash;

    digit0.setTexture(Digits);
    digit0.setTextureRect(sf::IntRect(0, 0, 21, 32));
    digit1.setTexture(Digits);
    digit1.setTextureRect(sf::IntRect(21, 0, 21*2, 32));
    digit2.setTexture(Digits);
    digit2.setTextureRect(sf::IntRect(21*2, 0, 21*3, 32));
    digit3.setTexture(Digits);
    digit3.setTextureRect(sf::IntRect(21*3, 0, 21*4, 32));
    digit4.setTexture(Digits);
    digit4.setTextureRect(sf::IntRect(21*4, 0, 21*5, 32));
    digit5.setTexture(Digits);
    digit5.setTextureRect(sf::IntRect(21*5, 0, 21*6, 32));
    digit6.setTexture(Digits);
    digit6.setTextureRect(sf::IntRect(21*6, 0, 21*7, 32));
    digit7.setTexture(Digits);
    digit7.setTextureRect(sf::IntRect(21*7, 0, 21*8, 32));
    digit8.setTexture(Digits);
    digit8.setTextureRect(sf::IntRect(21*8, 0, 21*9, 32));
    digit9.setTexture(Digits);
    digit9.setTextureRect(sf::IntRect(21*9, 0, 21*10, 32));
    dash.setTexture(Digits);
    dash.setTextureRect(sf::IntRect(21*10, 0, 21*11, 32));
    std::map<char, sf::Sprite> map;
    map.emplace('0', digit0 );
    map.emplace('1', digit1 );
    map.emplace('2', digit2 );
    map.emplace('3', digit3 );
    map.emplace('4', digit4 );
    map.emplace('5', digit5 );
    map.emplace('6', digit6 );
    map.emplace('7', digit7 );
    map.emplace('8', digit8 );
    map.emplace('9', digit9 );
    map.emplace('-', dash);

    return map[x];
}

std::string CounterUP(std::string x){
    int temp;
    std::string temp2;
    if(x == "-001") {
        temp2 = "000";
        return temp2;
    }else if(x[0] == '-'){
        temp = stoi(x);
        temp++;
        temp = temp * -1;
        if (std::to_string(temp).length()==1)
            temp2 = "-00" + std::to_string(temp);
        if (std::to_string(temp).length()==2)
            temp2 = "-0" + std::to_string(temp);
        if (std::to_string(temp).length()==3)
            temp2 = '-' + std::to_string(temp);
        return temp2;

    }else {
        temp = stoi(x);
        temp++;
        if (std::to_string(temp).length()==2)
            temp2 = '0' + std::to_string(temp);
        if (std::to_string(temp).length()==1||std::to_string(temp).length()==0)
            temp2 = "00" + std::to_string(temp);
        return temp2;
    }

}

std::string CounterDOWN(std::string x){
    int temp;
    std::string temp2;
    if(x[0] == '-' || x == "000"){
        temp = stoi(x);
        temp--;
        temp = temp * -1;
        if (std::to_string(temp).length()==1)
            temp2 = "-00" + std::to_string(temp);
        if (std::to_string(temp).length()==2)
            temp2 = "-0" + std::to_string(temp);
        if (std::to_string(temp).length()==3)
            temp2 = '-' + std::to_string(temp);
        return temp2;
    }else{
        temp = stoi(x);
        temp--;
        if (std::to_string(temp).length()==2)
            temp2 = '0' + std::to_string(temp);
        if (std::to_string(temp).length()==1||std::to_string(temp).length()==0)
            temp2 = "00" + std::to_string(temp);
        return temp2;
    }
}

void Timer(sf::RenderWindow &window, std::map<char, sf::Sprite> &map, int minute, int second, int width, int height) {
    std::string x = std::to_string(minute);
    std::string y = std::to_string(second);
    if (x.length()<2){
        x = '0' + x;
    }
    if (y.length()<2){
        y = '0' + y;
    }
    sf::Sprite Clock[4] = {map[x[0]], map[x[1]], map[y[0]], map[y[1]] };
    Clock[0].setPosition ((width*32)-97,32*(height+0.5f)+16);
    Clock[1].setPosition((width*32)-97+21,32*(height+0.5f)+16);
    Clock[2].setPosition((width*32)-54, 32*(height+0.5f)+16);
    Clock[3].setPosition((width*32)-54+21, 32*(height+0.5f)+16);
    window.draw(Clock[0]);
    window.draw(Clock[1]);
    window.draw(Clock[2]);
    window.draw(Clock[3]);
}

void CoverBoard(sf::RenderWindow &window, int columns, int rows){
    sf::Texture Revealed;
    sf::Sprite revealed;
    if (!Revealed.loadFromFile("files/images/tile_revealed.png"))
    {
        std::cout << "did not load" << std::endl;
    }
    revealed.setTexture(Revealed);
    int col_num = 0;
    int row_num = 0;
    for(int i = 0; i < columns; i++){
        revealed.setPosition(col_num, row_num);

        for(int j = 0; j < rows; j++){
            revealed.setPosition(col_num, row_num);
            window.draw(revealed);
            row_num = row_num + 32;
        }
        col_num = col_num + 32;
        row_num = 0;
    }

}

void BetterDrawBoard(sf::RenderWindow &window, int col, int row, std::vector<std::vector<Tiles>> grid , std::map<std::string, sf::Sprite> Image){
    for(int i = 0; i < col; i++){
        for(int j = 0; j < row; j++) {
            grid[i][j].Show(window, Image);
        }
    }
}

bool Click_Happy( int xpos, int ypos, int col, int row, bool loser, bool leaderboard_con){
    if (((col / 2.0) * 32)-32  <= xpos && xpos <= ((col / 2.0) * 32) - 32 + 64 && !loser && !leaderboard_con){
        if ((32 *(row +0.5f) <= ypos && ypos <= (32 *(row +0.5f)+64))) {
            std::cout << "hi" << std::endl;
            return true;
        }
    }
    return false;
}

bool Click_Sad( int xpos, int ypos, int col, int row, bool loser, bool leaderboard_con){
    if (((col / 2.0) * 32)-32  <= xpos && xpos <= ((col / 2.0) * 32) - 32 + 64 && loser && !leaderboard_con){
        if ((32 *(row +0.5f) <= ypos && ypos <= (32 *(row +0.5f)+64))) {
            std::cout << "hi" << std::endl;
            return true;
        }
    }
    return false;
}

bool Click_Debug( int xpos, int ypos, int col, int row, bool paused, bool loser, bool winner, bool leaderboard_con){
    if ((col * 32) - 304  <= xpos && xpos <= ((col * 32) - 304 + 64) && !paused && !loser && !winner && !leaderboard_con){
        if ((32 * (row+0.5f) <= ypos && ypos <= (32 * (row+0.5f)+64))) {
            std::cout << "cat" << std::endl;
            return true;
        }
    }
    return false;
}

bool Click_Pause( int xpos, int ypos, int col, int row, bool lost, bool pauser, bool winner, bool leaderboard_con){
    if ((col * 32) - 240  <= xpos && xpos <= ((col * 32) - 240 + 64) && !lost && !pauser && !winner && !leaderboard_con){
        if ((32 * (row+0.5f) <= ypos && ypos <= (32 * (row+0.5f)+64))) {
//            BetterDrawBoard(window, col, row, grid);
            std::cout << "dog" << std::endl;
            return true;
        }
    }
    return false;
}

bool Click_Play( int xpos, int ypos, int col, int row, bool lost, bool pauser, bool winner, bool leaderboard_con){
    if ((col * 32) - 240  <= xpos && xpos <= ((col * 32) - 240 + 64) && !lost && pauser && !winner && !leaderboard_con){
        if ((32 * (row+0.5f) <= ypos && ypos <= (32 * (row+0.5f)+64))) {
//            BetterDrawBoard(window, col, row, grid);
            std::cout << "dog" << std::endl;
            return true;
        }
    }
    return false;
}

bool Click_Leaderboard( int xpos, int ypos, int col, int row){

    if ((col * 32) - 176  <= xpos && xpos <= ((col * 32) - 176 + 64)){
        if ((32 * (row+0.5f) <= ypos && ypos <= (32 * (row+0.5f)+64))) {
//            BetterDrawBoard(window, col, row, grid);
            std::cout << "bird" << std::endl;
            return true;
        }

    }
    return false;
}

std::vector<std::chrono::duration<double>> TimeStartStop(std::chrono::high_resolution_clock::time_point start, std::chrono::high_resolution_clock::time_point now, std::chrono::high_resolution_clock::time_point pause, std::vector <std::chrono::duration<double>> temp_vector, std::vector <std::chrono::duration<double>> pause_vector, int &tally, bool paused){
    std::chrono::duration<double> buffer = std::chrono::duration<double>(0);
    std::chrono::duration<double> paused_time = std::chrono::duration<double>(0);
    auto test = std::chrono::high_resolution_clock::now();;
//    std::chrono::duration<double> paused_time_2 = start - start;
    auto current = test - start;
    if (paused) {
        for (int i = 0; i < temp_vector.size(); i++) {
            buffer = buffer + temp_vector[i];
        }
        paused_time = pause - start - buffer;
        pause_vector.push_back(paused_time);
        temp_vector.push_back(current - pause_vector[tally]);
        if (paused) {
            tally++;
        }
    }
    auto ongo = current - buffer;
    //auto future_paused_time = paused_time - buffer;
    std::vector<std::chrono::duration<double>> car;
    car.push_back(current);
    car.push_back(paused_time);
    car.push_back(ongo);
    return car;
}

std::vector<std::vector<Tiles>> LoseGame(sf::RenderWindow &window, int col, int row, std::map<std::string, sf::Sprite> Image, std::vector<std::vector<Tiles>> array ){
    for (int n = 0; n < col; n++) {
        for (int m = 0; m < row; m++) {
            if(array[n][m]._mine){
                array[n][m].current_image = Image["mine"];
                array[n][m].Show(window, Image);
                window.display();
            }
        }
    }
    //make happy face
    sf::Texture SadFace;
    sf::Sprite sad_face;
    if (!SadFace.loadFromFile("files/images/face_lose.png"))
    {
        std::cout << "did not load" << std::endl;
    }
    sad_face.setTexture(SadFace);
    sad_face.setPosition((col/2.0)*32 - 32, 32*(row+0.5f));
    window.draw(sad_face);
    window.display();
    return array;
}

std::vector<std::vector<Tiles>> WinGame(sf::RenderWindow &window, int col, int row, std::map<std::string, sf::Sprite> Image, std::vector<std::vector<Tiles>> array, std::string &num_mines ){
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (array[i][j]._mine){
                array[i][j].current_image = Image["flag"];
                array[i][j]._flagged = true;
                //win = true;
            }

        }
    }
    num_mines = "000";
    sf::Texture WinFace;
    sf::Sprite win_face;
    if (!WinFace.loadFromFile("files/images/face_win.png"))
    {
        std::cout << "did not load" << std::endl;
    }
    win_face.setTexture(WinFace);
    win_face.setPosition((col/2.0)*32 - 32, 32*(row+0.5f));
    window.draw(win_face);
    window.display();
    return array;
}

bool Check_Win(int col, int row, std::vector<std::vector<Tiles>> array, std::map<std::string, sf::Sprite> Image, int mines){
    int tally = 0;
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (!array[i][j]._mine && array[i][j]._clicked){
                tally++;
            }

        }
    }
    if(tally == ((col * row)-mines)){
        return true;
    }else{
        return false;}

}



void MainGame(std::string PlayerName){


    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    clock_t pausedTime = clock();
    bool restart = false;
    bool debug_view = false;
    bool win = false;
    bool lose = false;

    //pause, time, leaderboard
    bool pause = false;
    bool play = true;
    bool leaderboard_con = false;
    int Pseconds;
    int Pminutes;

    std::string num_rows, num_columns, num_mines;
    int columns = 0, rows = 0, mines = 0, TileCount = 0;
    std::fstream tempfile("files/board_config.cfg", std::ios_base::in);
    if (tempfile.is_open()){
        getline(tempfile, num_columns);
        getline(tempfile, num_rows);
        getline(tempfile, num_mines);
        //num_mines = "398";
        columns = stoi(num_columns);
        rows = stoi(num_rows);
        mines = stoi(num_mines);
        //mines = 398;

        TileCount = columns*rows;
    }else{ std::cout<<"isn't open"<<std::endl;}
    sf::RenderWindow window(sf::VideoMode(columns*32, rows*32+100), "Minesweeper");
    sf::Font font;
    if (!font.loadFromFile("files/font.ttf"))
    { std::cout << "font didn't load" << std::endl;}

    //make happy face
    sf::Texture HappyFace;
    sf::Sprite happy_face;
    if (!HappyFace.loadFromFile("files/images/face_happy.png"))
    {
        std::cout << "did not load" << std::endl;
    }
    happy_face.setTexture(HappyFace);
    happy_face.setPosition((columns/2.0)*32 - 32, 32*(rows+0.5f));

    //make debug button
    sf::Texture Debug;
    sf::Sprite debug;
    if (!Debug.loadFromFile("files/images/debug.png"))
    {
        std::cout << "did not load" << std::endl;
    }
    debug.setTexture(Debug);
    debug.setPosition((columns)*32 - 304, 32*(rows+0.5f));

    //make pause play button
    sf::Texture PausePlay;
    sf::Sprite pause_play;
    if (!PausePlay.loadFromFile("files/images/play.png"))
    {
        std::cout << "did not load" << std::endl;
    }
    pause_play.setTexture(PausePlay);
    pause_play.setPosition((columns)*32 - 240, 32*(rows+0.5f));

    //make leaderboard button
    sf::Texture Leaderboard;
    sf::Sprite leaderboard;
    if (!Leaderboard.loadFromFile("files/images/leaderboard.png"))
    {
        std::cout << "did not load" << std::endl;
    }
    leaderboard.setTexture(Leaderboard);
    leaderboard.setPosition((columns)*32 - 176, 32*(rows+0.5f));

    //pause button
    sf::Texture PauseButton;
    sf::Sprite pausebutton;
    if (!PauseButton.loadFromFile("files/images/pause.png"))
    {
        std::cout << "did not load" << std::endl;
    }
    pausebutton.setTexture(PauseButton);
    pausebutton.setPosition((columns)*32 - 240, 32*(rows+0.5f));

    //making map for number sprites*
    if (num_mines.length()==1)
        num_mines = "00" + num_mines;
    if (num_mines.length()==2)
        num_mines = "0" + num_mines;


    std::cout << num_mines << std::endl;
    sf::Sprite sprite = CreateDigit(num_mines[0]);
    sf::Sprite sprite1 = CreateDigit(num_mines[1]);
    sf::Sprite sprite2 = CreateDigit(num_mines[2]);




    sf::Texture Digits;
    if (!Digits.loadFromFile("files/images/digits.png"))
    {
        std::cout << "did not load" << std::endl;
    }
    sf::Sprite digit0;
    sf::Sprite digit1;
    sf::Sprite digit2;
    sf::Sprite digit3;
    sf::Sprite digit4;
    sf::Sprite digit5;
    sf::Sprite digit6;
    sf::Sprite digit7;
    sf::Sprite digit8;
    sf::Sprite digit9;
    sf::Sprite dash;
    digit0.setTexture(Digits);
    digit0.setTextureRect(sf::IntRect(0, 0, 21, 32));
    digit1.setTexture(Digits);
    digit1.setTextureRect(sf::IntRect(21, 0, 21, 32));
    digit2.setTexture(Digits);
    digit2.setTextureRect(sf::IntRect(21*2, 0, 21, 32));
    digit3.setTexture(Digits);
    digit3.setTextureRect(sf::IntRect(21*3, 0, 21, 32));
    digit4.setTexture(Digits);
    digit4.setTextureRect(sf::IntRect(21*4, 0, 21, 32));
    digit5.setTexture(Digits);
    digit5.setTextureRect(sf::IntRect(21*5, 0, 21, 32));
    digit6.setTexture(Digits);
    digit6.setTextureRect(sf::IntRect(21*6, 0, 21, 32));
    digit7.setTexture(Digits);
    digit7.setTextureRect(sf::IntRect(21*7, 0, 21, 32));
    digit8.setTexture(Digits);
    digit8.setTextureRect(sf::IntRect(21*8, 0, 21, 32));
    digit9.setTexture(Digits);
    digit9.setTextureRect(sf::IntRect(21*9, 0, 21, 32));
    dash.setTexture(Digits);
    dash.setTextureRect(sf::IntRect(21*10, 0, 21, 32));
    std::map<char, sf::Sprite> map;
    map.emplace('0', digit0 );
    map.emplace('1', digit1 );
    map.emplace('2', digit2 );
    map.emplace('3', digit3 );
    map.emplace('4', digit4 );
    map.emplace('5', digit5 );
    map.emplace('6', digit6 );
    map.emplace('7', digit7 );
    map.emplace('8', digit8 );
    map.emplace('9', digit9 );
    map.emplace('-', dash);
    //const std::map<char, sf::Sprite> map1 = map;
    //sf::Sprite numbers[11] = {digit0, digit1, digit2, digit3, digit4, digit5, digit6, digit7, digit8, digit9, dash};
    sf::Sprite map_counter[4] = {map[num_mines[0]], map[num_mines[1]], map[num_mines[2]]};



    std::map<std::string, sf::Sprite> Image;
    sf::Texture Hidden;
    sf::Sprite hidden;
    if (!Hidden.loadFromFile("files/images/tile_hidden.png"))
    {
        std::cout << "did not load" << std::endl;
    }
    hidden.setTexture(Hidden);
    Image.emplace("hidden", hidden);

    sf::Texture Flag;
    sf::Sprite flag;
    if(!Flag.loadFromFile("files/images/flag.png")){
        std::cout << "did not load" << std::endl;
    }
    flag.setTexture(Flag);
    Image.emplace("flag", flag);


    sf::Texture Mine;
    sf::Sprite mine;
    if(!Mine.loadFromFile("files/images/mine.png")){
        std::cout << "did not load" << std::endl;
    }
    mine.setTexture(Mine);
    Image.emplace("mine", mine);


    sf::Texture Revealed;
    sf::Sprite revealed;
    if(!Revealed.loadFromFile("files/images/tile_revealed.png")){
        std::cout << "did not load" << std::endl;
    }
    revealed.setTexture(Revealed);
    Image.emplace("revealed", revealed);


    sf::Texture Num1;
    sf::Sprite num1;
    if(!Num1.loadFromFile("files/images/number_1.png")){
        std::cout << "did not load" << std::endl;
    }
    num1.setTexture(Num1);
    Image.emplace("num1", num1);


    sf::Texture Num2;
    sf::Sprite num2;
    if(!Num2.loadFromFile("files/images/number_2.png")){
        std::cout << "did not load" << std::endl;
    }
    num2.setTexture(Num2);
    Image.emplace("num2", num2);


    sf::Texture Num3;
    sf::Sprite num3;
    if(!Num3.loadFromFile("files/images/number_3.png")){
        std::cout << "did not load" << std::endl;
    }
    num3.setTexture(Num3);
    Image.emplace("num3", num3);


    sf::Texture Num4;
    sf::Sprite num4;
    if(!Num4.loadFromFile("files/images/number_4.png")){
        std::cout << "did not load" << std::endl;
    }
    num4.setTexture(Num4);
    Image.emplace("num4", num4);

    sf::Texture Num5;
    sf::Sprite num5;
    if(!Num5.loadFromFile("files/images/number_5.png")){
        std::cout << "did not load" << std::endl;
    }
    num5.setTexture(Num5);
    Image.emplace("num5", num5);

    sf::Texture Num6;
    sf::Sprite num6;
    if(!Num6.loadFromFile("files/images/number_6.png")){
        std::cout << "did not load" << std::endl;
    }
    num6.setTexture(Num6);
    Image.emplace("num6", num6);

    sf::Texture Num7;
    sf::Sprite num7;
    if(!Num7.loadFromFile("files/images/number_7.png")){
        std::cout << "did not load" << std::endl;
    }
    num7.setTexture(Num7);
    Image.emplace("num7", num7);

    sf::Texture Num8;
    sf::Sprite num8;
    if(!Num8.loadFromFile("files/images/number_8.png")){
        std::cout << "did not load" << std::endl;
    }
    num8.setTexture(Num8);
    Image.emplace("num8", num8);

    std::cout << "hi" << std::endl;
    std::vector<std::vector<Tiles>> array = make2dArray(columns, rows, mines, Image);
    std::cout << "size is: " << array.size() << std::endl;


    int c = 0;
    long long int PSelapsed;
    long long int PMelapsed;


    sf::Clock clock;  // Create a clock to measure time
    int minutes;
    int seconds;
    sf::Time elapsedTime;
    int no_exceed = 0;

    //START OF WHILE LOOP
    while (window.isOpen()){


        if (play){
            sf::Time currentElapsedTime = elapsedTime + clock.getElapsedTime();
            float elapsedSeconds = currentElapsedTime.asSeconds();
             minutes = static_cast<int>(elapsedSeconds) / 60;
             seconds = static_cast<int>(elapsedSeconds) % 60;
        }

        //std::cout << "M: " << std::to_string(minutes) << " S:" << std::to_string(seconds )<< std::endl;





        sf::Event event;
        while (window.pollEvent(event))
        {
            //track mouse position
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "the left button was pressed" << std::endl;
                    int xz = event.mouseButton.x;
                    int yz = event.mouseButton.y;
                    if(!lose && !pause ) {
                        int xpos = ((event.mouseButton.x) / 32) * 32;
                        int ypos = ((event.mouseButton.y) / 32) * 32;
                        std::cout << "x: " << xz << " " << "y: " << yz << std::endl;
                        //meant for clicking tiles
                        for (int i = 0; i < columns; i++) {
                            for (int j = 0; j < rows; j++) {
                                if (xpos == array[i][j]._position.x && ypos == array[i][j]._position.y) {
                                    if (!array[i][j]._flagged){
                                        array[i][j].LeftClickTile(Image, array,  columns, rows, window); }
                                    if (array[i][j].current_image.getTexture() == Image["mine"].getTexture() &&
                                        array[i][j]._clicked) {
                                        array = LoseGame(window, columns, rows, Image, array);
                                        lose = true;
                                        elapsedTime += clock.getElapsedTime();
//                                        pause_time = std::chrono::high_resolution_clock::now();
//
//                                        Pseconds = std::chrono::duration_cast<std::chrono::seconds>(pause_time - start).count() % 60;
//                                        Pminutes = std::chrono::duration_cast<std::chrono::seconds>(pause_time - start).count()/60;
                                    }
                                    win = Check_Win( columns, rows, array, Image, mines);
                                    if(win)
                                        array = WinGame(window, columns, rows, Image, array, num_mines);
                                }
                            }
                        }
                    }
                    if (Click_Happy( xz, yz, columns, rows, lose, leaderboard_con)) {
//                        restart = true;
//                        array = make2dArray(columns, rows, mines, Image);
//                        num_mines = std::to_string(mines);
//                        if (num_mines.length()==1)
//                            num_mines = "00" + num_mines;
//                        if (num_mines.length()==2)
//                            num_mines = "0" + num_mines;
                        window.close();
                        MainGame(PlayerName);
                    }

                    if (Click_Sad( xz, yz, columns, rows, lose, leaderboard_con)) {

                        window.close();
                        MainGame(PlayerName);

                    }

                    if (Click_Debug(xz, yz, columns, rows, pause, lose, win, leaderboard_con)){
                        if(debug_view){
                            debug_view = false;
                        }else{debug_view = true;}
                        if (debug_view){
                            for (int i = 0; i < columns; i++) {
                                for (int j = 0; j < rows; j++) {
                                    array[i][j].DisplayAllMines(Image);
                                    array[i][j].Show(window, Image);
                                }
                            }
                        }else{
                            for (int i = 0; i < columns; i++) {
                                for (int j = 0; j < rows; j++) {
                                    array[i][j].ReturnAllMines(Image);
                                    array[i][j].Show(window, Image);

                                }}}
                }

                    if (Click_Pause(xz, yz, columns, rows, lose, pause, win, leaderboard_con)){
                        elapsedTime += clock.getElapsedTime();
                        pause =  true;
                        play = false;


                    }
                    else if (Click_Play(xz, yz, columns, rows, lose, pause, win, leaderboard_con)){
                        pause = false;
                        play = true;

                        c=0;
                        clock.restart();
                    }




                    if (Click_Leaderboard(xz, yz, columns, rows)){
                        if(!leaderboard_con){
                            leaderboard_con = true; }


                    }





            }
                if (event.mouseButton.button == sf::Mouse::Right) {
                    std::cout << "the right button was pressed" << std::endl;
                    //impliment else if you do lose, make it do the thing with the flags
                    if (!lose && !pause){
                        int xpos = ((event.mouseButton.x) / 32) * 32;
                        int ypos = ((event.mouseButton.y) / 32) * 32;
                        std::cout << "x: " << xpos << " " << "y: " << ypos << std::endl;
                        for (int i = 0; i < columns; i++) {
                            for (int j = 0; j < rows; j++) {
                                if (xpos == array[i][j]._position.x && ypos == array[i][j]._position.y) {
                                    array[i][j].RightClickTile(Image);
                                    if (array[i][j]._flagged && array[i][j].current_image.getTexture() == Image["flag"].getTexture()) {
                                        num_mines = CounterDOWN(num_mines);
                                    } else if (!array[i][j]._flagged && array[i][j].current_image.getTexture() == Image["hidden"].getTexture()) {
                                        num_mines = CounterUP(num_mines);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            //closes the game
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        //Buttons for stuff
        window.clear(sf::Color::White);
        for (int i = 0; i < columns; i++) {
            for (int j = 0; j < rows; j++) {
                if(array[i][j]._clicked){
                    auto back = Image["revealed"];
                    back.setPosition(i*32, j*32);
                    window.draw(back);
                }



                if(array[i][j]._mine){
                    auto back = Image["revealed"];
                    back.setPosition(i*32, j*32);
                    window.draw(back);
                }

                if(array[i][j]._flagged && array[i][j].current_image.getTexture() != Image["mine"].getTexture()){
                    auto back = Image["hidden"];
                    back.setPosition(i*32, j*32);
                    window.draw(back);
                }
            }
        }
        //window.draw(background);
        window.draw(happy_face);
        window.draw(debug);
        window.draw(pausebutton);
        window.draw(leaderboard);

        //Counter stuff
        if (num_mines[0] == '-'){
            std::cout << num_mines << std::endl;
            map_counter[0] = map[num_mines[0]];
            map_counter[0].setPosition(33-21, 32 * (rows + 0.5f)+16);
            map_counter[1] = map[num_mines[1]];
            map_counter[1].setPosition(33, 32 * (rows + 0.5f)+16);
            map_counter[2] = map[num_mines[2]];
            map_counter[2].setPosition(33+21, 32 * (rows + 0.5f)+16);
            map_counter[3] = map[num_mines[3]];
            map_counter[3].setPosition(33+21*2, 32 * (rows + 0.5f)+16);
            std::cout << "(" << map[num_mines[3]].getLocalBounds().left << ", " << map[num_mines[3]].getLocalBounds().top << ")" << std::endl;
            std::cout << "(" << map[num_mines[3]].getLocalBounds().width << ", " << map[num_mines[3]].getLocalBounds().height << ")" << std::endl;
        }else{
//            std::cout << "hi" << std::endl;
            map_counter[0] = map[num_mines[0]];
            map_counter[0].setPosition(33, 32 * (rows + 0.5f)+16);
            map_counter[1] = map[num_mines[1]];
            map_counter[1].setPosition(33+21, 32 * (rows + 0.5f)+16);
            map_counter[2] = map[num_mines[2]];
            map_counter[2].setPosition(33+21*2, 32 * (rows + 0.5f)+16);
            map_counter[3].setPosition(0, 0);
        }
        window.draw( map_counter[0]);
        window.draw( map_counter[1]);
        window.draw(map_counter[2]);
        window.draw(map_counter[3]);
        Timer(window, map, minutes, seconds, columns, rows);
        BetterDrawBoard(window, columns, rows, array, Image);

        if (lose){
            play = false;
            sf::Texture SadFace;
            sf::Sprite sad_face;
            if (!SadFace.loadFromFile("files/images/face_lose.png"))
            {
                std::cout << "did not load" << std::endl;
            }
            sad_face.setTexture(SadFace);
            sad_face.setPosition((columns/2.0)*32 - 32, 32*(rows+0.5f));
            window.draw(sad_face);
            Timer(window, map, minutes, seconds, columns, rows);
        }

        if (win){
            play = false;
            sf::Texture SadFace;
            sf::Sprite sad_face;
            if (!SadFace.loadFromFile("files/images/face_win.png"))
            {
                std::cout << "did not load" << std::endl;
            }
            sad_face.setTexture(SadFace);
            sad_face.setPosition((columns/2.0)*32 - 32, 32*(rows+0.5f));
            window.draw(sad_face);
            //const int win_second = seconds;
            //const int win_minute = minutes;
            Timer(window, map, minutes, seconds, columns, rows);
        }


        if (pause){
            if (play)
                window.draw(pausebutton);
            if (pause)
                Timer(window, map, minutes, seconds, columns, rows);
            window.draw(pause_play);
            CoverBoard(window, columns, rows);
            window.display();
        }

         if (leaderboard_con){
            if(play && !pause) {
                window.draw(pause_play);
                CoverBoard(window, columns, rows);
            }



            //Timer(window, map, minutes, seconds, columns, rows);
            window.display();
            LeaderboardWindow(window, columns, rows, win, PlayerName, minutes, seconds, columns, rows, leaderboard_con, play, pause, pausebutton, no_exceed);

        }

         if (pause){
            if (play)
                window.draw(pausebutton);
            if (pause)
                Timer(window, map, minutes, seconds, columns, rows);
            window.draw(pause_play);
            CoverBoard(window, columns, rows);
            window.display();
        }else{
            window.display();
        }


    }
}

void HomePage(){
    sf::Font font;
    if (!font.loadFromFile("files/font.ttf"))
    {
        std::cout << "font didn't load" << std::endl;
    }
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper", sf::Style::Close);
    sf::RectangleShape BCCOLOR = setRectangle(sf::Vector2f(800,600),0,0,0,0, sf::Color::Blue);
    sf::FloatRect home_background(0, 0, 800, 600);

    std::cout<< home_background.width << ", " <<  home_background.height << std::endl;

    sf::Text home_title;
    home_title.setFont(font);
    home_title.setString("WELCOME TO MINESWEEPER!");
    home_title.setOrigin(home_title.getLocalBounds().width/2-40,home_title.getLocalBounds().height/2);
    home_title.setFillColor(sf::Color::White);
    home_title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    home_title.setCharacterSize(24);
    home_title.setPosition(sf::Vector2f(home_background.width/2.0f, home_background.height/2.0f-150));

    sf::Text home_prompt;
    home_prompt.setFont(font);
    home_prompt.setString("Enter your name:");
    home_prompt.setOrigin(home_prompt.getLocalBounds().width/2.0f-40,home_prompt.getLocalBounds().height/2.0f);
    home_prompt.setFillColor(sf::Color::White);
    home_prompt.setStyle(sf::Text::Bold);
    home_prompt.setCharacterSize(20);
    home_prompt.setPosition(sf::Vector2f(home_background.width/2.0f, home_background.height/2.0f-75));

    sf::Text home_input;
    home_input.setFont(font);
    home_input.setString("|");
    home_input.setFillColor(sf::Color::Yellow);
    home_input.setStyle(sf::Text::Bold);
    home_input.setCharacterSize(18);
    home_input.setPosition(sf::Vector2f(home_background.width/2.0f, home_background.height/2.0f-45));


    std::string player_name = "";
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)){
            if (player_name.size() < 10){
                if (event.type == sf::Event::KeyReleased){
                    if (event.key.code == sf::Keyboard::A){
                        player_name = player_name + "A";
                        player_name = Up_Low(player_name);
                        //std::cout << player_name << std::endl;
                    }else if (event.key.code == sf::Keyboard::B){
                        player_name = player_name + "B";
                        player_name = Up_Low(player_name);
                    }else if (event.key.code == sf::Keyboard::C){
                        player_name = player_name + "C";
                        player_name = Up_Low(player_name);
                    }else if (event.key.code == sf::Keyboard::D){
                        player_name = player_name + "D";
                        player_name = Up_Low(player_name);
                    }else if (event.key.code == sf::Keyboard::E){
                        player_name = player_name + "E";
                        player_name = Up_Low(player_name);
                    }else if (event.key.code == sf::Keyboard::F){
                        player_name = player_name + "F";
                        player_name = Up_Low(player_name);
                    }else if (event.key.code == sf::Keyboard::G){
                        player_name = player_name + "G";
                        player_name = Up_Low(player_name);
                    }else if (event.key.code == sf::Keyboard::H){
                        player_name = player_name + "H";
                        player_name = Up_Low(player_name);
                    }else if (event.key.code == sf::Keyboard::I){
                        player_name = player_name + "I";
                        player_name = Up_Low(player_name);
                    }else if (event.key.code == sf::Keyboard::J){
                        player_name = player_name + "J";
                        player_name = Up_Low(player_name);
                    }else if (event.key.code == sf::Keyboard::K){
                        player_name = player_name + "K";
                        player_name = Up_Low(player_name);
                    }else if (event.key.code == sf::Keyboard::L){
                        player_name = player_name + "L";
                        player_name = Up_Low(player_name);
                    }else if (event.key.code == sf::Keyboard::M){
                        player_name = player_name + "M";
                        player_name = Up_Low(player_name);
                    }else if (event.key.code == sf::Keyboard::N){
                        player_name = player_name + "N";
                        player_name = Up_Low(player_name);
                    }else if (event.key.code == sf::Keyboard::O){
                        player_name = player_name + "O";
                        player_name = Up_Low(player_name);
                    }else if (event.key.code == sf::Keyboard::P){
                        player_name = player_name + "P";
                        player_name = Up_Low(player_name);
                    }else if (event.key.code == sf::Keyboard::Q){
                        player_name = player_name + "Q";
                        player_name = Up_Low(player_name);
                    }else if (event.key.code == sf::Keyboard::R){
                        player_name = player_name + "R";
                        player_name = Up_Low(player_name);
                    }else if (event.key.code == sf::Keyboard::S){
                        player_name = player_name + "S";
                        player_name = Up_Low(player_name);
                    }else if (event.key.code == sf::Keyboard::T){
                        player_name = player_name + "T";
                        player_name = Up_Low(player_name);
                    }else if (event.key.code == sf::Keyboard::U){
                        player_name = player_name + "U";
                        player_name = Up_Low(player_name);
                    }else if (event.key.code == sf::Keyboard::V){
                        player_name = player_name + "V";
                        player_name = Up_Low(player_name);
                    }else if (event.key.code == sf::Keyboard::W){
                        player_name = player_name + "W";
                        player_name = Up_Low(player_name);
                    }else if (event.key.code == sf::Keyboard::X){
                        player_name = player_name + "X";
                        player_name = Up_Low(player_name);
                    }else if (event.key.code == sf::Keyboard::Y){
                        player_name = player_name + "Y";
                        player_name = Up_Low(player_name);
                    }else if (event.key.code == sf::Keyboard::Z){
                        player_name = player_name + "Z";
                        player_name = Up_Low(player_name);
                    }else if (event.key.code == sf::Keyboard::Enter){
                        if (!player_name.empty()){
                            window.close();
                            MainGame(player_name);
                        }
                    }
                    home_input.setString(player_name + "|");
                    home_input.setOrigin(home_input.getLocalBounds().width/2,home_input.getLocalBounds().height/2);
                }
                std::cout << player_name << std::endl;
            }

            //implement backspace
            if (event.type == sf::Event::KeyReleased){
                if (event.key.code == sf::Keyboard::BackSpace){
                    if (!player_name.empty()){
                        player_name.pop_back();
                        home_input.setString(player_name + "|");
                        home_input.setOrigin(home_input.getLocalBounds().width/2,home_input.getLocalBounds().height/2);
                    }
                }
                std::cout << player_name << std::endl;
            }

            //close program if click x
            if (event.type == sf::Event::Closed)
                window.close();

        }


        window.clear();
        window.draw(BCCOLOR);
        window.draw(home_title);
        window.draw(home_prompt);
        window.draw(home_input);
        window.display();
    }
}

void test(){


    bool isPaused = false; // Global variable to keep track of pause state
    sf::Clock clock; // Global clock to keep track of elapsed time
    sf::Time elapsedTime; // Global variable to store elapsed time


        // Create SFML window
        sf::RenderWindow window(sf::VideoMode(800, 600), "Pause Button Example");

        // Create font for timer text
        sf::Font font;
        if (!font.loadFromFile("files/font.ttf")) {
            // handle font loading error
            return;
        }

        // Create timer text
        sf::Text timerText;
        timerText.setFont(font);
        timerText.setCharacterSize(24);
        timerText.setFillColor(sf::Color::Black);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {

                        isPaused = !isPaused;

                        if (isPaused) {
                            // Store the elapsed time when pausing
                            elapsedTime += clock.getElapsedTime();
                        } else {
                            // Resume the timer from where it left off
                            clock.restart();
                        }
                    }
                }


            // Update game logic based on pause state
            if (!isPaused) {
                // Update game logic here

                // Update timer
                sf::Time currentElapsedTime = elapsedTime + clock.getElapsedTime();
                float elapsedSeconds = currentElapsedTime.asSeconds();
                int minutes = static_cast<int>(elapsedSeconds) / 60;
                int seconds = static_cast<int>(elapsedSeconds) % 60;
                int milliseconds = static_cast<int>(elapsedSeconds * 1000) % 1000;
                timerText.setString("Time: " + std::to_string(minutes) + ":" + std::to_string(seconds) + "." + std::to_string(milliseconds));
            }

            // Clear window
            window.clear(sf::Color::White);

            // Draw timer text
            window.draw(timerText);

            // Draw other game objects here

            // Display window
            window.display();
        }
    }


int main(){
    HomePage();
    //MainGame();
    //LeaderboardWindow();
    //test();
    return 0;
}