#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int num_uncovered = 0;

void display_grid(vector<vector<char> > &grid, vector<vector<int> > &uncovered) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (uncovered[i][j] == 1) {
                cout << grid[i][j] << " ";
            } else {
                cout << '#' << " ";
            }
        }

        cout << "\n";
    }
}

void setup(vector<vector<char> >& grid, vector<vector<int> >& uncovered) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if ((rand() % 100) + 1 <= 15) {
                grid[i][j] = 'm';
                num_uncovered++;
                uncovered[i][j] = 2;
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

                if (grid[i][j] == 'm') {
                    grid[i][j]++;
                }
            }
        }
    }
}

int uncover(int a, int b, vector<vector<char> > grid, vector<vector<int> > &uncovered) {
    uncovered[a][b] = 1;
    if (grid[a][b] == 'm') {
        return 1;
    }

    num_uncovered++;
    return 0;
}

int main() {
    srand(time(0));
    bool win = false;
    int a, b, grid_size;

    cout << "How large would you like the side of the grid to be, from 3-20?\n";
    cin >> grid_size;

    while (grid_size < 3 || grid_size > 20) {
        cout << "Invalid input (try again): ";
        cin >> grid_size;
    }

    vector<vector<char> > grid(grid_size, vector<char>(grid_size, '0'));
    vector<vector<int> > uncovered(grid_size, vector<int>(grid_size, 0));

    setup(grid, uncovered);
    calc_for_tile(grid);


    display_grid(grid, uncovered);
    cout << "Enter coordinates of where you want to uncover (integers seperated by a single space): ";
    cin >> a >> b;

    while (a < 1 || b < 1 || a > grid_size || b > grid_size) {
        cout << "Invalid coordinates, please try again: ";
        cin >> a >> b;
    }

    a--;
    b--;

    if (num_uncovered == (grid_size) * (grid_size)) {
        win = true;
    }
    
    while (uncover(a, b, grid, uncovered) == 0 && (!win)) {
        if (num_uncovered == (grid_size) * (grid_size)) {
            win = true;
            break;
        }

        display_grid(grid, uncovered);
        cout << "Enter coordinates of where you want to uncover (integers seperated by a single space): ";
        cin >> a >> b;

        while (a < 1 || b < 1 || a > grid_size || b > grid_size) {
            cout << "Invalid coordinates, please try again: ";
            cin >> a >> b;
        }

        a--;
        b--;
    }

    if (win) {
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
