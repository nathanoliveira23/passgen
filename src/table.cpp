#include "../includes/table.hpp"

char colHeads[NCOLS][50] = { "URL", "USERNAME", "PASSWORD" };

static void drawHorizontalLine()
{
    for (std::size_t i = 0; i < NCOLS; i++) {
        printf("+");
        for (std::size_t j = 0; j < COLUMN_WIDTH + 2; j++) {
            printf("-");
        }
    }
    printf("+\n"); 
}


static void drawRow(std::vector<std::string> colData) 
{
    printf("|");
    for (std::size_t i = 0; i < NCOLS; i++) {
            printf(" %-*s |", COLUMN_WIDTH, colData[i].c_str());
    }
    printf("\n");

    drawHorizontalLine();
}

void drawTableHeader() 
{
    drawHorizontalLine();

    printf("|");

    for (std::size_t i = 0; i < NCOLS; i++) {
        printf(" %-*s |", COLUMN_WIDTH, colHeads[i]);
    }

    printf("\n");

    drawHorizontalLine();
}


void drawTable(std::vector<std::string> tableData)
{
    drawRow(tableData);
}
