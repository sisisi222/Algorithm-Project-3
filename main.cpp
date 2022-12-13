/* 
Name: Huong Duong
Project 3 - Graph modeling and graph algorithms 
Description: This project is to model the problem which is based on the 
"Itsy-Bitsy Spider" maze problem and then use a known graph algorithm to solve the problem
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct vertex_data {
    int level, row, col;        //indicate the position of the vertex
    string direction;           //6-bit binary to indicate the direction North-East-South-West-Up-Down
    bool discovered;
}; 

int main() {
    ifstream file_in("input.txt");      //open the input file
    ofstream file_out("output.txt");    //create output file
    queue<vertex_data> my_queue;        //queue for BFS
    

    //input variables
    int num_maze;                           //the number of mazes in the file
    int num_level, num_row, num_col;        //the number of levels, rows, and columns in a maze
    int begin_level, begin_row, begin_col;  //location of the start
    int end_level, end_row, end_col;        //location of the goal

    int j, k, n; //for loop

    file_in >> num_level >> num_row >> num_col;  //the number of levels, rows and columns
    file_in >> begin_level >> begin_row >> begin_col; //beginning position
    file_in >> end_level >> end_row >> end_col; //ending position

    vertex_data position[num_level][num_row][num_col]; //matrix for direction of each vertex
    bool visited[num_level][num_row][num_col];  //matrix for discovered vertex

    int count = 0;
    for (j = 0; j < num_level; j++) {
        for (k= 0; k < num_row; k++) {
            for (n = 0; n < num_col; n++) {
                position[j][k][n].level = j;
                position[j][k][n].row = k;
                position[j][k][n].col = n;
                position[j][k][n].discovered = false; //initialized all vertices undiscovered
                string pos_direction;
                file_in >> pos_direction;
                position[j][k][n].direction = pos_direction;
                visited[j][k][n] = false; //initialized all vertices undiscovered
            }
        }
    }

    //start with begin point
    my_queue.push(position[begin_level][begin_row][begin_col]);

    while (!my_queue.empty()) {
        vertex_data current = my_queue.front();
        string new_direction = current.direction;
        current.discovered = true;

        int l, r, c; //current level, row, column
        l = current.level;
        r = current.row;
        c = current.col;

        my_queue.pop();
        visited[l][r][c] = true;

        //find neighbor of vertex    
        int x;
        vector<int> neighbor;

        for (x = 0; x < 6; x++) {
            if (new_direction[x] == '1') {
                neighbor.push_back(x);
            }
        }

    for (j = 0; j < neighbor.size(); j++) {
        //NORTH
            if (neighbor[j] == 0) {
                if (visited[l][r-1][c] == 0) {
                    if (l == end_level && r == end_row + 1 && c == end_col) {
                        file_out << "N  ";
                            break;
                    }
                                
                    if (position[l][r-1][c].direction[2] == '1' &&
                    position[l][r-1][c].direction[1] == '0' && 
                    position[l][r-1][c].direction[0] == '0' &&
                    position[l][r-1][c].direction[3] == '0' &&
                    position[l][r-1][c].direction[4] == '0' &&
                    position[l][r-1][c].direction[5] == '0') {
                        continue;
                    }
                    
                    file_out << "N  ";
                    my_queue.push(position[l][r-1][c]);
                    visited[l][r-1][c] = 1;
                }
            }
        //EAST
            if (neighbor[j] == 1) {
                    if (visited[l][r][c+1] == 0) {
                        if (l == end_level && r == end_row && c == end_col - 1) {
                            file_out << "E  ";
                            break;
                        }

                        if (position[l][r][c+1].direction[3] == '1' &&
                        position[l][r][c+1].direction[1] == '0' && 
                        position[l][r][c+1].direction[2] == '0' &&
                        position[l][r][c+1].direction[0] == '0' &&
                        position[l][r][c+1].direction[4] == '0' &&
                        position[l][r][c+1].direction[5] == '0') {
                            continue;
                        }
                                
                        file_out << "E  ";
                        my_queue.push(position[l][r][c+1]);
                        visited[l][r][c+1] = 1;
                    }                 
                }

        //SOUTH
            if (neighbor[j] == 2) {
                if (visited[l][r+1][c] == 0) {
                    if (l == end_level && r == end_row - 1 && c == end_col) {
                        file_out << "S  ";
                        break;
                    }

                    if (position[l][r+1][c].direction[0] == '1' &&
                    position[l][r+1][c].direction[1] == '0' && 
                    position[l][r+1][c].direction[2] == '0' &&
                    position[l][r+1][c].direction[3] == '0' &&
                    position[l][r+1][c].direction[4] == '0' &&
                    position[l][r+1][c].direction[5] == '0') {
                        continue;
                    }

                    file_out << "S  ";
                    my_queue.push(position[l][r+1][c]);
                    visited[l][r+1][c] = 1;
                }
            }

        //WEST
            if (neighbor[j] == 3) {
                if (visited[l][r][c-1] == 0) {
                    if (l == end_level && r == end_row && c == end_col + 1) {
                        file_out << "W  ";
                        break;
                    }
                                
                    if (position[l][r][c-1].direction[1] == '1' &&
                    position[l][r][c-1].direction[0] == '0' && 
                    position[l][r][c-1].direction[2] == '0' &&
                    position[l][r][c-1].direction[3] == '0' &&
                    position[l][r][c-1].direction[4] == '0' &&
                    position[l][r][c-1].direction[5] == '0') {
                        continue;
                    }

                    file_out << "W  ";
                    my_queue.push(position[l][r][c-1]);
                    visited[l][r][c-1] = 1;
                }
            }

        //UP
            if (neighbor[j] == 4) {
                if (visited[l+1][r][c] == 0) {
                    if (l == end_level - 1 && r == end_row && c == end_col) {
                        file_out << "U  ";
                        break;
                    }

                    if (position[l+1][r][c].direction[5] == '1' &&
                    position[l+1][r][c].direction[1] == '0' && 
                    position[l+1][r][c].direction[2] == '0' &&
                    position[l+1][r][c].direction[3] == '0' &&
                    position[l+1][r][c].direction[4] == '0' &&
                    position[l+1][r][c].direction[0] == '0') {
                        continue;
                    }

                    file_out << "U  ";
                    my_queue.push(position[l+1][r][c]);
                    visited[l+1][r][c] = 1;
                }
            }
                
        //DOWN
            if (neighbor[j] == 5) {
                if (visited[l-1][r][c] == 0) {
                    if (l == (end_level + 1) && r == end_row && c == end_col) {
                        file_out << "D  ";
                        break;
                    }

                    if (position[l-1][r][c].direction[4] == '1' &&
                    position[l-1][r][c].direction[1] == '0' && 
                    position[l-1][r][c].direction[2] == '0' &&
                    position[l-1][r][c].direction[3] == '0' &&
                    position[l-1][r][c].direction[0] == '0' &&
                    position[l-1][r][c].direction[5] == '0') {
                        continue;
                    }
                                
                    file_out << "D  ";
                    my_queue.push(position[l-1][r][c]);
                    visited[l-1][r][c] = 1;
                }
            }

        }

        for (j = 0; j < neighbor.size(); j++) {
                neighbor.pop_back();
        }
    }
        
    return 0;    
}
