#pragma once

#include <string>
#include <vector>

const unsigned int NCOLS = 3;
const unsigned int COLUMN_WIDTH = 35;

typedef struct {
    std::string url, username, password;
} 
COLHEADER;

void drawTableHeader(); 
void drawTable(std::vector<std::string>);
