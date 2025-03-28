#include <iostream>
#include <limits>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int num_uncovered = 0, difficulty;

void instructions() {
    cout << "Welcome to Minesweeper!\n\n";
    cout << "Game Instructions:\n";
    cout << "1. The grid consists of tiles, some of which contain mines ('m') and others are empty.\n";
    cout << "2. Your goal is to uncover all the tiles that don't contain mines.\n";
    cout << "3. The numbers on uncovered tiles represent how many mines are adjacent to that tile (including diagonals).\n";
    cout << "4. You can uncover a tile by entering the command 'uc its coordinates.\n";
    cout << "5. If you uncover a tile with a mine, you lose the game! (the first tile uncovered will never be a mine)\n\n";
    cout << "Flagging:\n";
    cout << "1. If you think a tile contains a mine, you can flag it to mark it.\n";
    cout << "2. Flags are a way to keep track of tiles you suspect contain mines.\n";
    cout << "3. You cannot uncover a flagged tile unless you remove the flag.\n\n";
    cout << "Game controls:\n";
    cout << "1. Use the coordinates (the letters 'uc'followed by row and column) to uncover tiles.\n";
    cout << "2. To flag or unflag a tile, use 'fl' followed by coordinates.\n";
    cout << "3. To win, uncover all non-mine tiles. The game ends if you uncover a mine (or, of course, if you win).\n\n";
}

void display_grid(vector<vector<char> > &grid, vector<vector<int> > &uncovered) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (uncovered[i][j] == 1) {
                cout << grid[i][j] << " ";
            } else if (uncovered[i][j] == 3) {
                cout << "F" << " ";
            } else {
                cout << "#" << " ";
            }
        }

        cout << "\n";
    }
}

void setup(vector<vector<char> >& grid, vector<vector<int> >& uncovered, int difficulty, int a, int b) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (i == a - 1 && j == b - 1) {
                break;
            }
            switch (difficulty) {
                case 1:
                    if ((rand() % 100) + 1 <= 10) {
                        grid[i][j] = 'm';
                        num_uncovered++;
                        uncovered[i][j] = 2;
                    }

                    break;
                case 2:
                    if ((rand() % 100) + 1 <= 15) {
                        grid[i][j] = 'm';
                        num_uncovered++;
                        uncovered[i][j] = 2;
                    }

                    break;
                case 3:
                    if ((rand() % 100) + 1 <= 20) {
                        grid[i][j] = 'm';
                        num_uncovered++;
                        uncovered[i][j] = 2;
                    }

                    break;
                case 4:
                    if ((rand() % 100) + 1 <= 25) {
                        grid[i][j] = 'm';
                        num_uncovered++;
                        uncovered[i][j] = 2;
                    }

                    break;
                case 5:
                    if ((rand() % 100) + 1 <= 30) {
                        grid[i][j] = 'm';
                        num_uncovered++;
                        uncovered[i][j] = 2;
                    }
            }
        }
    }
}

void calc_for_tile(vector<vector<char> >& grid) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] != 'm') {
                if (i < grid.size() - 1) {
                    if (j < grid[0].size() - 1) {
                        if (grid[i + 1][j + 1] == 'm') {
                            grid[i][j]++;
                        }
                    }

                    if (j > 0) {
                        if (grid[i + 1][j - 1] == 'm') {
                            grid[i][j]++;
                        }
                    }

                    if (grid[i + 1][j] == 'm') {
                        grid[i][j]++;
                    }
                }

                if (i > 0) {
                    if (j < grid[0].size() - 1) {
                        if (grid[i - 1][j + 1] == 'm') {
                            grid[i][j]++;
                        }
                    }

                    if (j > 0) {
                        if (grid[i - 1][j - 1] == 'm') {
                            grid[i][j]++;
                        }
                    }

                    if (grid[i - 1][j] == 'm') {
                        grid[i][j]++;
                    }
                }

                if (j < grid[0].size() - 1) {
                    if (grid[i][j + 1] == 'm') {
                        grid[i][j]++;
                    }
                }

                if (j > 0) {
                    if (grid[i][j - 1] == 'm') {
                        grid[i][j]++;
                    }
                }
            }
        }
    }
}

void flag(int a, int b, vector<vector<int> > &flagged) {
    if (flagged[a][b] != 1 && flagged[a][b] != 3) {
        flagged[a][b] = 3;
    } else if (flagged[a][b] == 3) {
        flagged[a][b] = 0;
    } else {
        cout << "Unable to flag specified coordinates\n";
    }
}

int uncover(int a, int b, vector<vector<char> > grid, vector<vector<int> > &uncovered) {
    if (uncovered[a][b] != 3 && uncovered[a][b] != 1) {
        uncovered[a][b] = 1;
        if (grid[a][b] == 'm') {
            return 1;
        }

        num_uncovered++;
        return 0;
    } else {
        cout << "Unable to uncover specified coordinates. That cell may already be uncovered, or it may be flagged. Remove the flag first to uncover.\n";
    }
    return 0;
}

vector<int> first_turn(int grid_size) {
    int a, b;
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            cout << "# ";
        }
        cout << "\n";
    }

    cout << "Enter coordinates to uncover (this one will not be a mine): ";
    cin >> a >> b;
    while (cin.fail() || a < 1 || a > grid_size || b < 1 || b > grid_size) {
        cout << "Invalid input (try again): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> a >> b;
    }

    return {a, b};
}

int main() {
    instructions();
    srand(time(0));
    string command;
    bool win = false;
    int a, b, grid_size;

    cout << "Enter your difficulty as an integer, from 1 (easiest) to 5 (hardest): ";
    cin >> difficulty;

    while (cin.fail() || difficulty < 1 || difficulty > 5) {
        cout << "Invalid input (try again): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> difficulty;
    }

    cout << "How large would you like the side of the grid to be, from 3-25?\n";
    cin >> grid_size;

    while (cin.fail() || grid_size < 3 || grid_size > 25) {
        cout << "Invalid input (try again): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> grid_size;
    }

    vector<vector<char> > grid(grid_size, vector<char>(grid_size, '#'));
    vector<vector<int> > uncovered(grid_size, vector<int>(grid_size, 0));

    vector<int> starting_co = first_turn(grid_size);

    setup(grid, uncovered, difficulty, starting_co[0], starting_co[1]);
    calc_for_tile(grid);

    display_grid(grid, uncovered);
    cout << "Enter coordinates of where you want to uncover (keyword uc) or flag (keyword fl): ";
    cin >> command >> a >> b;

    while (cin.fail() || a > grid_size || b > grid_size || a < 1 || b < 1) {
        cout << "Invalid coordinates, please try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> command >> a >> b;
    }

    a--;
    b--;

    if (num_uncovered == (grid_size) * (grid_size)) {
        win = true;
    }
    
    while (!win) {
        if (command == "uc") {
            if (uncover(a, b, grid, uncovered) == 1) {
                break;
            };
        } else if (command == "fl") {
            flag(a, b, uncovered);
        } else {
            cout << "Command not recognised\n";
        }

        if (num_uncovered == (grid_size) * (grid_size)) {
            win = true;
            break;
        }

        display_grid(grid, uncovered);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter coordinates of where you want to uncover (keyword uc) or flag (keyword fl): ";
        cin >> command >> a >> b;

        while (cin.fail() || a < 1 || b < 1 || a > grid_size || b > grid_size) {
            cout << "Invalid coordinates, please try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> command >> a >> b;
        }

        a--;
        b--;
    }

    if (win) {
        for (int i = 0; i < grid_size; i++) {
            for (int j = 0; j < grid_size; j++) {
                uncovered[i][j] = 1;
            }
        }

        display_grid(grid, uncovered);
        cout << "Congratulations you won!\n";
    } else {
        for (int i = 0; i < grid_size; i++) {
            for (int j = 0; j < grid_size; j++) {
                uncovered[i][j] = 1;
            }
        }

        cout << "You hit a mine; it's game over.\n" << "\nThe grid:\n";
        display_grid(grid, uncovered);
    }

    return 0;
}
