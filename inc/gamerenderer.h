#define RG_BLACK L"●"
#define RG_WHITE L"○"

#define RG_GRID_TYPE_1 L"└"
#define RG_GRID_TYPE_2 L"┴"
#define RG_GRID_TYPE_3 L"┘"
#define RG_GRID_TYPE_4 L"├"
#define RG_GRID_TYPE_5 L"┼"
#define RG_GRID_TYPE_6 L"┤"
#define RG_GRID_TYPE_7 L"┌"
#define RG_GRID_TYPE_8 L"┬"
#define RG_GRID_TYPE_9 L"┐"
#define RG_GRID_TYPE_H L"─"
#define RG_GRID_TYPE_V L"│"

void render_grid(char** grid, int width, int height);
char* generate_grid_string(char** grid, int width, int height);
void draw_grid(int x, int y, char** grid, short** stone_colors, int width, int height, short grid_color);
void coloring_stone(int offset_x, int offset_y, int x, int y, char glyph, short color);